#include "utils.h"

//TODO implement handler timeout mechanism

int udp_server_fd;
int udp_client_fd;

int tcp_server_fd;
int tcp_client_fd;

server_client_list* client_list;

static bool util_write(int fd, const char* msg) {
	int len = strlen(msg);
	if(write(fd, msg, len) == -1) {
		LOGE("util_write() write() failed, fd=%d len=%d reason=[%s]%d",
			fd, len, strerror(errno), errno);
		return false;
	}
	return true;
}

static void* thread_trigger_event(void* arg) {
	LOGD("thread_trigger_event()");

	// set detach to avoid memory leak
	pthread_detach_0(pthread_self());

	// do what you want to do here
	while(true) {
		msleep(500);
		LOGD("start sending the events");
		util_write(udp_client_fd, "hello from UDP client");
		util_write(tcp_client_fd, "hello from TCP client");

		int fd = server_client_list_get_fd(client_list, 0);
		util_write(fd, "hello from TCP server");
	}

	return NULL;
}

void demo_epoll() {
	LOGD("demo_epoll()");

	//setup fds
	udp_server_fd = socket_udp_server_bind_local(true, "hugo");
	assert(udp_server_fd > 0);
	udp_client_fd = socket_udp_client_create_local(true, "hugo");
	assert(udp_client_fd > 0);

	tcp_server_fd = socket_tcp_server_bind_local(true, "hugo");
	assert(tcp_server_fd > 0);
	tcp_client_fd = socket_tcp_client_connect_local(true, "hugo");
	assert(tcp_client_fd > 0);

	client_list = server_client_list_init(10);
	assert(client_list != NULL);

	//create the thread to trigger the events
	pthread_t thread1;
	pthread_create_0(&thread1, NULL, thread_trigger_event, "hello");
	
	// demo how to use the epoll
	#define MAX_EPOLL_EVENT 10
	struct epoll_event events[MAX_EPOLL_EVENT];
	int epfd = epoll_create(MAX_EPOLL_EVENT);
	if(epfd == -1) {
		LOGE("epoll_create() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}

	epoll_add_fd(epfd, udp_server_fd, EPOLLIN);
	epoll_add_fd(epfd, tcp_server_fd, EPOLLIN);
	epoll_add_fd(epfd, tcp_client_fd, EPOLLIN);
	epoll_add_fd(epfd, STDIN_FILENO, EPOLLIN);

	while(true) {
		int i, n;
		n = epoll_wait(epfd, events, MAX_EPOLL_EVENT, -1);
		LOGD("epoll_wait n=%d", n);
		if(n == -1) {
			if(errno == EINTR) {
				continue;
			} else {
				LOGE("epoll_wait() failed reason=[%s]%d", strerror(errno), errno);
				crash_with_log();
			}
		}
		
		for(i = 0; i < n; i++) {
			int fd = events[i].data.fd;
			//start timer to recover the blocking case 
			if(fd == udp_server_fd) {
				if(events[i].events & EPOLLIN) {
					char buff[2048] = {0};
					if(read(fd, buff, sizeof(buff)) == -1) {
						LOGE("udp_server_fd read() failed, fd=%d reason=[%s]%d",
							STDIN_FILENO, strerror(errno), errno);
						crash_with_log();
					}
					LOGD("UDP server has data [%s]", buff);
				}
			} else if(fd == tcp_server_fd) {
				if(events[i].events & EPOLLIN) {
					int new_fd = socket_tcp_server_new_connect(fd);
					assert(new_fd > 0);
					epoll_add_fd(epfd, new_fd, EPOLLIN);
					server_client_list_add(client_list, new_fd);
					LOGD("TCP server has acceped a new client=%d", new_fd);
				}
			} else if(fd == tcp_client_fd) {
				if(events[i].events & EPOLLIN) {
					char buff[2048] = {0};
					int len = read(fd, buff, sizeof(buff));
					if(len == -1) {
						LOGE("tcp_client_fd read() failed, fd=%d reason=[%s]%d",
							STDIN_FILENO, strerror(errno), errno);
						close(fd);
					} else if(len == 0) {
						LOGD("TCP client find the server side has closed the session");
						close(fd);
					} else {
						LOGD("TCP client has data [%s]", buff);
					}
				}
			} else if(fd == STDIN_FILENO) {
				if(events[i].events & EPOLLIN) {
					char buff[2048] = {0};
					if(read(fd, buff, sizeof(buff)) == -1) {
						LOGE("STDIN read() failed, fd=%d reason=[%s]%d", fd, strerror(errno), errno);
						crash_with_log();
					}
					LOGD("stdin has data [%s]", buff);
					goto exit;
				}
			} else {
				if(server_client_list_contains(client_list, fd)) {
					if(events[i].events & EPOLLIN) {
						char buff[2048] = {0};
						int len = read(fd, buff, sizeof(buff));
						if(len == -1) {
							LOGE("TCP server=%d read() failed, fd=%d reason=[%s]%d",
								fd, strerror(errno), errno);
							close(fd);
						} else if(len == 0) {
							LOGD("TCP server=%d find the remote side has closed the session", fd);
							close(fd);
						} else {
							LOGD("TCP server=%d has data [%s]", fd, buff);
						}
					}
				} else {
					LOGE("unexpected fd=%d coming", fd);
					crash_with_log();
				}
			}
			//stop timer
		}
	}

exit:
	server_client_list_cleanup(client_list);
	close(udp_server_fd);
	close(udp_client_fd);
	close(epfd);
}

