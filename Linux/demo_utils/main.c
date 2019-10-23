#include "utils.h"

//---------------------------------- log -------------------------------------------

#ifdef LOGD
#undef LOGD
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGE
#undef LOGE
#endif
#define LOGD(...) utils_logd("demo", __VA_ARGS__)
#define LOGW(...) utils_logw("demo", __VA_ARGS__)
#define LOGE(...) utils_loge("demo", __VA_ARGS__)

static void test_log() {
	LOGD("----- test_log() -----");
	LOGD("this is LOGD");
	LOGW("this is LOGW");
	LOGE("this is LOGE");
}

//----------------------------------- file ------------------------------------------
static void test_file() {
	LOGD("----- test_file() -----");
	char buff[128] = {0};
	const char* TEST_FILE = "test_file.txt";
	const char* TEST_FOLDER = "test_folder";
	const char* TEST_FILE_DATA = "hello world";

	// file not exist
	assert(file_is_file_exist(TEST_FILE) == false);
	assert(file_chmod(TEST_FILE, 0642) == false);
	assert(file_get_file_size(TEST_FILE) == -1);
	assert(file_read(TEST_FILE, buff, sizeof(buff)) == false);

	// create file
	assert(file_create_file(TEST_FILE) == true);
	assert(file_create_file(TEST_FILE) == true);	// the file can be overwritten
	assert(file_is_file_exist(TEST_FILE) == true);
	assert(file_chmod(TEST_FILE, 0666) == true);
	assert(file_get_file_size(TEST_FILE) == 0);

	// read file
	assert(file_read(TEST_FILE, buff, sizeof(buff)) == true);
	assert(strcmp(buff, "") == 0);

	// write file
	strcpy(buff, TEST_FILE_DATA);
	assert(file_write(TEST_FILE, buff, strlen(buff)) == true);

	// read file again
	memset(buff, 0, sizeof(buff));
	assert(file_read(TEST_FILE, buff, sizeof(buff)) == true);
	assert(strcmp(buff, TEST_FILE_DATA) == 0);

	// delete file
	assert(file_delete(TEST_FILE) == true);
	assert(file_delete(TEST_FILE) == false);
	assert(file_is_file_exist(TEST_FILE) == false);

	// folder not exist
	assert(file_is_folder_exist(TEST_FOLDER) == false);
	assert(file_chmod(TEST_FOLDER, 0666) == false);
	assert(file_get_file_size(TEST_FOLDER) == -1);

	// create folder
	assert(file_create_folder(TEST_FOLDER) == true);
	assert(file_create_folder(TEST_FOLDER) == false);
	assert(file_is_folder_exist(TEST_FOLDER) == true);
	assert(file_chmod(TEST_FOLDER, 0666) == true);
	assert(file_get_file_size(TEST_FOLDER) > 0);

	// delete folder
	assert(file_delete(TEST_FOLDER) == true);
	assert(file_delete(TEST_FOLDER) == false);
	assert(file_is_folder_exist(TEST_FOLDER) == false);
}

//---------------------------------- time -------------------------------------------
static void test_time() {
	LOGD("----- test_time() -----");

	//test time tick
	int64_t tick = time_get_tick();
	assert(tick > 0);
	msleep(100);
	tick = time_get_tick() - tick;
	assert(tick >= 100);
	assert(tick <= 150);

	//test system time
	int64_t system_time = time_get_system_time();
	assert(system_time > 0);
	msleep(100);
	system_time = time_get_system_time() - system_time;
	assert(system_time >= 100);
	assert(system_time <= 150);
}

//---------------------------------- timer -------------------------------------------
static void test_timer() {
	LOGD("----- test_timer() -----");

	void my_timer_routine(int id) {
		LOGD("my_timer_routine() id=%d", id);
	}

	timer_t timerid = timer_init(my_timer_routine, 123);

	timer_start(timerid, 10);
	assert(timer_get_remaining_time(timerid) > 0);
	msleep(50); // wait for timer timeout
	assert(timer_get_remaining_time(timerid) == 0);

	timer_start(timerid, 10);
	assert(timer_get_remaining_time(timerid) > 0);
	timer_stop(timerid);
	assert(timer_get_remaining_time(timerid) == 0);
	
	assert(timer_deinit(timerid));
}

//---------------------------------- socket -------------------------------------------
static bool util_write(int fd, const char* msg) {
	int len = strlen(msg);
	if(write(fd, msg, len) == -1) {
		LOGE("util_write() write() failed, fd=%d len=%d reason=[%s]%d",
			fd, len, strerror(errno), errno);
		return false;
	}
	return true;
}

static bool util_read(int fd, const char* expected_msg) {
	char buff[2048] = {0};
	if(read(fd, buff, sizeof(buff)) == -1) {
		LOGE("util_read() read() failed, fd=%d reason=[%s]%d",
			fd, strerror(errno), errno);
		return false;
	}
	if(strcmp(buff, expected_msg) != 0) {
		LOGE("util_read() strcmp() failed, expected_msg=[%s] actual_msg=[%s]",
			expected_msg, buff);
		return false;
	}
	return true;
}

static void test_socket() {
	LOGD("----- test_socket() -----");

	int serverfd, clientfd, servernewfd;
	//test socket tcp ipv4
	serverfd = socket_tcp_server_bind_ipv4(1);
	assert(serverfd == -1);
	serverfd = socket_tcp_server_bind_ipv4(12345);
	assert(serverfd > 0);
	clientfd = socket_tcp_client_connect_ipv4("127.0.0.1", 12346);
	assert(clientfd == -1);
	clientfd = socket_tcp_client_connect_ipv4("127.0.0.1", 12345);
	assert(clientfd > 0);
	servernewfd = socket_tcp_server_new_connect(serverfd);
	assert(servernewfd > 0);
	close(servernewfd);
	close(clientfd);
	close(serverfd);

	//test socket tcp ipv6
	serverfd = socket_tcp_server_bind_ipv6(1);
	assert(serverfd == -1);
	serverfd = socket_tcp_server_bind_ipv6(12345);
	assert(serverfd > 0);
	clientfd = socket_tcp_client_connect_ipv6("::1", 12345);
	assert(clientfd > 0);
	servernewfd = socket_tcp_server_new_connect(serverfd);
	assert(servernewfd > 0);
	close(servernewfd);
	close(clientfd);
	close(serverfd);

	//test socket tcp fqdn
	serverfd = socket_tcp_server_bind_ipv4(12345);
	assert(serverfd > 0);
	clientfd = socket_tcp_client_connect_fqdn("localhost", 12345);
	assert(clientfd > 0);
	servernewfd = socket_tcp_server_new_connect(serverfd);
	assert(servernewfd > 0);
	assert(socket_tcp_disable_keepalive(clientfd));
	assert(socket_tcp_enable_keepalive(clientfd, 10, 10, 10));
	assert(socket_set_priority(clientfd, 6));
	assert(!socket_set_priority(clientfd, 7));
	assert(!socket_set_priority(clientfd, -1));
	assert(socket_set_no_delay(clientfd, true));
	assert(socket_set_tos(clientfd, 0x10));
	socket_dump_fd_state(clientfd, "TCP FQDN");
	
	assert(util_write(clientfd, "client to server"));
	assert(util_read(servernewfd, "client to server"));
	assert(util_write(servernewfd, "server to client"));
	assert(util_read(clientfd, "server to client"));

	close(servernewfd);
	close(clientfd);
	close(serverfd);

	//test socket tcp local
	serverfd = socket_tcp_server_bind_local(true, "hugo");
	assert(serverfd > 0);
	assert(socket_tcp_server_bind_local(true, "hugo") == -1);
	clientfd = socket_tcp_client_connect_local(true, "hugo");
	assert(clientfd > 0);
	servernewfd = socket_tcp_server_new_connect(serverfd);
	assert(servernewfd > 0);
	close(servernewfd);
	close(clientfd);
	close(serverfd);

	//test socket udp ipv4
	serverfd = socket_udp_server_bind_ipv4(12345);
	assert(serverfd > 0);
	assert(socket_udp_server_bind_ipv4(12345) == -1);
	clientfd = socket_udp_client_create_ipv4("127.0.0.1", 12345);
	assert(clientfd > 0);
	close(clientfd);
	close(serverfd);

	//test socket udp ipv6
	serverfd = socket_udp_server_bind_ipv6(12345);
	assert(serverfd > 0);
	assert(socket_udp_server_bind_ipv6(12345) == -1);
	clientfd = socket_udp_client_create_ipv6("::1", 12345);
	assert(clientfd > 0);
	close(clientfd);
	close(serverfd);

	//test socket udp fqdn
	serverfd = socket_udp_server_bind_ipv4(12345);
	assert(serverfd > 0);
	clientfd = socket_udp_client_create_fqdn("localhost", 12345);
	assert(clientfd > 0);
	close(clientfd);
	close(serverfd);

	//test socket udp local
	serverfd = socket_udp_server_bind_local(true, "hugo");
	assert(serverfd > 0);
	assert(socket_udp_server_bind_local(true, "hugo") == -1);
	clientfd = socket_udp_client_create_local(true, "hugo");
	assert(clientfd > 0);
	assert(socket_udp_client_create_local(true, "hugo1") == -1);

	assert(socket_set_blocking(clientfd, true));
	assert(socket_set_blocking(clientfd, false));
	assert(socket_tcp_disable_keepalive(clientfd));
	assert(!socket_tcp_enable_keepalive(clientfd, 10, 10, 10));
	assert(socket_set_priority(clientfd, 6));
	assert(!socket_set_no_delay(clientfd, true));
	assert(!socket_set_tos(clientfd, 0x10));
	assert(socket_set_rcv_buff_size(clientfd, 10)); //min: 2304
	assert(socket_set_snd_buff_size(clientfd, 10)); //min: 4608
	socket_dump_fd_state(clientfd, "UDP Local");

	assert(socket_set_rcv_buff_size(clientfd, 2000));
	assert(socket_set_snd_buff_size(clientfd, 3000));
	socket_dump_fd_state(clientfd, "UDP Local 2");

	assert(util_write(clientfd, "hello world!!!"));
	assert(util_read(serverfd, "hello world!!!"));

	close(clientfd);
	close(serverfd);
}

//---------------------------------- epoll -------------------------------------------
static void test_epoll() {
	LOGD("----- test_epoll() -----");

	void my_epoll_routine(int fd, int events) {
		LOGW("epoll_routine() fd=%d events=0x%x", fd, events);
	}
	int serverfd = socket_udp_server_bind_local(true, "hugo");
	assert(serverfd > 0);
	int clientfd = socket_udp_client_create_local(true, "hugo");
	assert(clientfd > 0);

	epoll* ep = NULL;
	assert(utils_epoll_create(&ep, 10));
	assert(!utils_epoll_create(&ep, 10));
	assert(utils_epoll_add_fd(ep, serverfd, UTILS_EPOLLIN, my_epoll_routine));
	assert(utils_epoll_add_fd(ep, clientfd, UTILS_EPOLLIN, my_epoll_routine));
	assert(utils_epoll_modify_fd(ep, clientfd, UTILS_EPOLLIN | UTILS_EPOLLOUT, NULL));
	utils_epoll_dump(ep);
	assert(!utils_epoll_remove_fd(ep, -1));
	assert(utils_epoll_remove_fd(ep, clientfd));
	utils_epoll_dump(ep);

	assert(utils_epoll_wait(ep, 10) == 0);
	assert(util_write(clientfd, "hello world"));
	assert(utils_epoll_wait(ep, 10) == 1);
	assert(util_read(serverfd, "hello world"));
	assert(utils_epoll_wait(ep, 10) == 0);

	assert(utils_epoll_delete(&ep));
	assert(ep == NULL);
	assert(!utils_epoll_delete(&ep));
	close(clientfd);
	close(serverfd);
}

//-----------------------------------------------------------------------------
extern void test_utils();

int main() {
	test_log();
	test_file();
	test_time();
	test_timer();

	test_socket();
	test_epoll();

	extern void demo_pthread();
	demo_pthread();

	extern void demo_semaphore();
	demo_semaphore();

	extern void demo_epoll();
	demo_epoll();

	LOGD("size=%d", sizeof(long));

	return 0; //0~255
}
