#include <errno.h> //errno
#include <time.h> //struct tm
#include <stdio.h> //printf, fflush, stdout
#include <stdarg.h> //va_start, va_end
#include <stdlib.h> //free
#include <syscall.h> //syscall
#include <signal.h> //struct sigevent
#include <string.h> //memset, strncpy
#include <stddef.h> //offsetof
#include <netdb.h> //struct addrinfo
#include <fcntl.h> //F_GETFL, F_SETFL, O_NONBLOCK
#include <sys/types.h> //gettid
#include <sys/time.h> //gettimeofday, localtime
#include <sys/stat.h> //struct stat
#include <sys/socket.h> //getsockopt, setsockopt
#include <sys/un.h> //struct sockaddr_un
#include <arpa/inet.h> //inet_pton
#include <netinet/in.h> //struct sockaddr_in
#include <netinet/tcp.h> //TCP_KEEPIDLE, TCP_KEEPINTVL, TCP_KEEPCNT
#include <netinet/ip.h> //IPTOS_LOWDELAY
#include <unistd.h> //usleep, close
#include <sys/epoll.h> //epoll_create
#include <semaphore.h> //sem_t
#include <pthread.h> //pthread
#include <inttypes.h> //PRId64

#include "utils.h"

#ifdef LOGD
#undef LOGD
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGE
#undef LOGE
#endif
#define LOGD(...) utils_logd("utils", __VA_ARGS__)
#define LOGW(...) utils_logw("utils", __VA_ARGS__)
#define LOGE(...) utils_loge("utils", __VA_ARGS__)

/******************************************************************************
* Utils
******************************************************************************/
int64_t utils_gettid() {
	int64_t ret = syscall(SYS_gettid);
	if(ret == -1) {
		//error case
	}
	return ret;
}

void utils_get_time_str(char* buff, int len) {
	struct timeval tv;
	struct timezone tz;
	struct tm* tm;

	gettimeofday(&tv, &tz);
	tm = localtime(&tv.tv_sec);

	memset(buff, 0, len);
	sprintf(buff, "%04d/%02d/%02d %02d:%02d:%02d.%03d",
		tm->tm_year+ 1900, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour,
		tm->tm_min, tm->tm_sec, (int)(tv.tv_usec/1000));
}

/******************************************************************************
* Log
******************************************************************************/
typedef enum {
	LOG_TYPE_DEBUG = 0,
	LOG_TYPE_WARNING,
	LOG_TYPE_ERROR,
} utils_log_type_enum;

void utils_log(utils_log_type_enum type, const char* tag, const char* msg) {
	char time_str[32] = {0};
	utils_get_time_str(time_str, sizeof(time_str));

	char log_type_str[64] = {0};
	char text_color[16] = {0};
	if(type == LOG_TYPE_DEBUG) {
		sprintf(log_type_str, "[%s/D]", tag);
	} else if(type == LOG_TYPE_WARNING) {
		sprintf(log_type_str, "[%s/W]", tag);
		strncpy(text_color, "\E[1;35;40m", sizeof(text_color));
	} else if(type == LOG_TYPE_ERROR) {
		sprintf(log_type_str, "[%s/E]", tag);
		strncpy(text_color, "\E[1;31;40m", sizeof(text_color));
	}

	printf("%s%s %5"PRId64" %14s %s\E[0m\r\n", text_color, time_str, utils_gettid(),
		log_type_str, msg);
	fflush(stdout);
}

void utils_logd(const char* tag, const char* fmt, ...) {
	char buff[1024] = {0};
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buff, sizeof(buff), fmt, ap);
	va_end(ap);

	utils_log(LOG_TYPE_DEBUG, tag, buff);
}

void utils_logw(const char* tag, const char* fmt, ...) {
	char buff[1024] = {0};
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buff, sizeof(buff), fmt, ap);
	va_end(ap);

	utils_log(LOG_TYPE_WARNING, tag, buff);

}

void utils_loge(const char* tag, const char* fmt, ...) {
	char buff[1024] = {0};
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buff, sizeof(buff), fmt, ap);
	va_end(ap);

	utils_log(LOG_TYPE_ERROR, tag, buff);

}

/******************************************************************************
* File
******************************************************************************/
bool file_is_file_exist(const char* path) {
	struct stat s;
	int ret = stat(path, &s);
	if(ret == -1) {
		if(errno != ENOENT) {
			LOGE("file_is_file_exist() stat() failed, path=[%s] reason=[%s]%d",
				path, strerror(errno), errno);
		}
	} else {
		if(S_ISREG(s.st_mode)) {
			return true;
		}
	}
	return false;
}

bool file_is_folder_exist(const char* path) {
	struct stat s;
	int ret = stat(path, &s);
	if(ret == -1) {
		if(errno != ENOENT) {
			LOGE("file_is_folder_exist() stat() failed, path=[%s] reason=[%s]%d",
				path, strerror(errno), errno);
		}
	} else {
		if(S_ISDIR(s.st_mode)) {
			return true;
		}
	}
	return false;
}

// -1 means fail
int file_get_file_size(const char* path) {
	struct stat s;
	if(stat(path, &s) == -1) {
		LOGE("file_get_file_size() stat() failed, path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		return -1;
	}
	return s.st_size;
}

bool file_create_file(const char* path) {
	FILE* fp = NULL;
	fp = fopen(path, "w");
	if(fp == NULL) {
		LOGE("file_create_file() fopen() failed, path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		return false;
	}
	fclose(fp);
	return true;
}

bool file_create_folder(const char* path) {
//mkdir() mode
//User: S_IRUSR (read), S_IWUSR (write), S_IXUSR (execute)
//Group: S_IRGRP (read), S_IWGRP (write), S_IXGRP (execute)
//Others: S_IROTH (read), S_IWOTH (write), S_IXOTH (execute)
	if(mkdir(path, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) == -1) {
		LOGE("file_create_folder() mkdir(), path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		return false;
	}
	return true;
}

bool file_delete(const char* path) {
	if(remove(path) == -1) {
		if(errno != ENOENT) {
			LOGE("file_delete() remove() failed, path=[%s] reason=[%s]%d",
				path, strerror(errno), errno);
		}
		return false;
	}
	return true;
}

//User: S_IRUSR (read), S_IWUSR (write), S_IXUSR (execute)
//Group: S_IRGRP (read), S_IWGRP (write), S_IXGRP (execute)
//Others: S_IROTH (read), S_IWOTH (write), S_IXOTH (execute)
bool file_chmod(const char* path, int mode) {
	if(chmod(path, mode) == -1) {
		LOGE("file_chmod() chmod() failed, path=[%s] mode=%o reason=[%s]%d",
			path, mode, strerror(errno), errno);
		return false;
	}
	return true;
}

//-1 means failure
bool file_read(const char* path, char* buff, int buff_size) {
	FILE* fp = NULL;
	fp = fopen(path, "r");
	if(fp == NULL) {
		LOGE("file_read() fopen() failed, path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		return false;
	}

	fread(buff, buff_size, 1, fp);
	
	fclose(fp);
	return true;
}

bool file_write(const char* path, const char* buff, int buff_size) {
	FILE* fp = NULL;
	fp = fopen(path, "w");
	if(fp == NULL) {
		LOGE("file_write() fopen() failed, path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		return false;
	}

	if(fwrite(buff, buff_size, 1, fp) != 1) {
		LOGE("file_write() fwrite() failed, path=[%s] reason=[%s]%d",
			path, strerror(errno), errno);
		fclose(fp);
		return false;
	}


	fclose(fp);
	return true;
}

/******************************************************************************
* Time
******************************************************************************/
//-1 means fail or the time tick is returned and the unit is millisecond
int64_t time_get_tick() {
	struct timespec ts;
	if(clock_gettime(CLOCK_BOOTTIME, &ts) == -1) {
		LOGE("time_get_tick() clock_gettime() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

//-1 means fail or the system time tick is returned and the unit is millisecond
int64_t time_get_system_time() {
	struct timespec ts;
	if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
		LOGE("time_get_system_time() clock_gettime() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	return ((int64_t)ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

/******************************************************************************
* Timer
******************************************************************************/

//NULL means fail or timerid is returned
timer_t timer_init(timer_routine cb, int id) {
	struct sigevent sevp;
	timer_t timerid;

	memset(&sevp, 0, sizeof(sevp));
	sevp.sigev_value.sival_int = id;
	sevp.sigev_notify = SIGEV_THREAD;
	sevp.sigev_notify_function = (void*)cb;

	if(timer_create(CLOCK_BOOTTIME, &sevp, &timerid) == -1) {
		LOGE("timer_init() timer_create() failed, reason=[%s]%d",
			strerror(errno), errno);
		return NULL;
	}
	return timerid;
}

bool timer_deinit(timer_t timerid) {
	if(timer_delete(timerid) == -1) {
		LOGE("timer_deinit() timer_delete() failed, timerid=%ld reason=[%s]%d",
			timerid, strerror(errno), errno);
		return false;
	}
	return true;
}

bool timer_start(timer_t timerid, int milliseconds) {
	struct itimerspec expire;
	expire.it_interval.tv_sec = 0;
	expire.it_interval.tv_nsec = 0;
	expire.it_value.tv_sec = milliseconds/1000;
	expire.it_value.tv_nsec = (milliseconds%1000)*1000000;
	if(timer_settime(timerid, 0, &expire, NULL) == -1) {
		LOGE("timer_start() timer_settime() failed, timerid=%ld reason=[%s]%d",
			timerid, strerror(errno), errno);
		return false;
	}
	return true;
}

bool timer_stop(timer_t timerid) {
	return timer_start(timerid, 0);
}

//-1 means fail or the remaining time is returned
int64_t timer_get_remaining_time(timer_t timerid) {
	struct itimerspec ts;
	if(timer_gettime(timerid, &ts) == -1) {
		LOGE("timer_get_remaining_time() timer_gettime() failed, timerid=%ld reason=[%s]%d",
			timerid, strerror(errno), errno);
		return -1;
	}
	return ((int64_t)ts.it_value.tv_sec * 1000 + ts.it_value.tv_nsec / 1000000);
}

/******************************************************************************
* Socket
******************************************************************************/
//-1 means fail or serverfd is returned
int socket_tcp_server_bind_ipv4(int port) {
	int fd;
	struct sockaddr_in addr;
	int reuse_addr = 1;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1) {
		LOGE("socket_tcp_server_bind_ipv4() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) == -1) {
		LOGW("socket_tcp_server_bind_ipv4() setsockopt(REUSEADDR) failed, reason=[%s]%d",
			strerror(errno), errno);
	}
	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_tcp_server_bind_ipv4() bind() failed, port=%d reason=[%s]%d",
			port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	if(listen(fd, 5) == -1) {
		LOGW("socket_tcp_server_bind_ipv4() listen() failed, reason=[%s]%d",
			strerror(errno), errno);
	}
	return fd;
}

//-1 means fail or serverfd is returned
int socket_tcp_server_bind_ipv6(int port) {
	int fd;
	struct sockaddr_in6 addr;
	int reuse_addr = 1;

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	addr.sin6_addr = in6addr_any;
	fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1) {
		LOGE("socket_tcp_server_bind_ipv6() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) == -1) {
		LOGW("socket_tcp_server_bind_ipv6() setsockopt(REUSEADDR) failed, reason=[%s]%d",
			strerror(errno), errno);
	}
	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_tcp_server_bind_ipv6() bind() failed, port=%d reason=[%s]%d",
			port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	if(listen(fd, 5) == -1) {
		LOGW("socket_tcp_server_bind_ipv6() listen() failed, reason=[%s]%d",
			strerror(errno), errno);
	}
	return fd;
}

//-1 means fail or serverfd is returned
int socket_tcp_server_bind_local(bool abstract, const char* name) {
	int fd;
	int size;
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	size = strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1;
	if(abstract) {
		addr.sun_path[0] = 0;
		memcpy(addr.sun_path + 1, name, strlen(name));
	} else {
		strncpy(addr.sun_path, name, sizeof(addr.sun_path));
		if(unlink(addr.sun_path) == -1) {
			LOGW("socket_tcp_server_bind_local() unlink() failed, reason=[%s]%d",
				strerror(errno), errno);
		}
	}
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd == -1) {
		LOGE("socket_tcp_server_bind_local() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(bind(fd, (struct sockaddr*)&addr, size) == -1) {
		LOGE("socket_tcp_server_bind_local() bind() failed, abstruct=%d name=[%s] reason=[%s]%d",
			abstract, name, strerror(errno), errno);
		close(fd);
		return -1;
	}
	if(listen(fd, 5) == -1) {
		LOGW("socket_tcp_server_bind_local() listen() failed, reason=[%s]%d",
			strerror(errno), errno);
	}
	return fd;
}

//-1 means fail or new clientfd is returned
int socket_tcp_server_new_connect(int serverfd) {
	int newfd;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	newfd = accept(serverfd, (struct sockaddr*)&addr, &len);
	if(newfd == -1) {
		LOGE("socket_tcp_server_new_connect() accept() failed, serverfd=%d reason=[%s]%d",
			serverfd, strerror(errno), errno);
		return -1;
	}
	return newfd;
}

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_ipv4(const char* ip, int port) {
	int fd;
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
		LOGE("socket_tcp_client_connect_ipv4() inet_pton() failed, due to ip=[%s] is not standard dotted-decimal notation", ip);
		return -1;
	}
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1) {
		LOGE("socket_tcp_client_connect_ipv4() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	LOGD("socket_tcp_client_connect_ipv4() connect() ip=[%s] port=%d", ip, port);
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_tcp_client_connect_ipv4() connect() failed, ip=[%s] port=%d reason=[%s]%d",
			ip, port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_ipv6(const char* ip, int port) {
	int fd;
	struct sockaddr_in6 addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	if(inet_pton(AF_INET6, ip, &addr.sin6_addr) != 1) {
		LOGE("socket_tcp_client_connect_ipv6() inet_pton() failed, due to ip=[%s] does not contain a character string representing a valid network address", ip);
		return -1;
	}
	fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1) {
		LOGE("socket_tcp_client_connect_ipv6() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	LOGD("socket_tcp_client_connect_ipv6() connect() ip=[%s] port=%d", ip, port);
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_tcp_client_connect_ipv6() connect() failed, ip=[%s] port=%d reason=[%s]%d",
			ip, port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_fqdn(const char* host, int port) {
	struct addrinfo hints;
	struct addrinfo* result;
	struct addrinfo* rp;
	int fd = 0;
	int ret;
	char port_str[11] = {0};

	sprintf(port_str, "%u", port);
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //allow IPv4, IPv6, AF_UNSPEC, AF_INET, AF_INET6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_ADDRCONFIG; //check local system
	hints.ai_protocol = IPPROTO_TCP;
	LOGD("socket_tcp_client_connect_fqdn() getaddrinfo() host=[%s] port=%d",
		host, port);
	ret = getaddrinfo(host, port_str, &hints, &result);
	if(ret != 0) {
		LOGE("socket_tcp_client_connect_fqdn() getaddrinfo() failed, reason=[%s] ret=%d",
			gai_strerror(ret), ret);
		return -1;
	}
	for(rp = result; rp != NULL; rp = rp->ai_next) {
		if(rp->ai_family == AF_INET) {
			struct sockaddr_in* addr = (struct sockaddr_in*)rp->ai_addr;
			char ip_str[INET_ADDRSTRLEN] = {0};
			const char* p_ret = inet_ntop(AF_INET, &addr->sin_addr, ip_str,
				INET_ADDRSTRLEN);
			if(p_ret == NULL) {
				LOGE("socket_tcp_client_connect_fqdn() inet_ntop() failed, reason=[%s]%d",
					strerror(errno), errno);
				continue;
			}
			fd = socket_tcp_client_connect_ipv4(ip_str, ntohs(addr->sin_port));
			if(fd != -1) {
				break;
			}
		}
		if(rp->ai_family == AF_INET6) {
			struct sockaddr_in6* addr = (struct sockaddr_in6*)rp->ai_addr;
			char ip_str[INET6_ADDRSTRLEN] = {0};
			const char* p_ret = inet_ntop(AF_INET6, &addr->sin6_addr, ip_str,
				INET6_ADDRSTRLEN);
			if(p_ret == NULL) {
				LOGE("socket_tcp_client_connect_fqdn() inet_ntop() failed, reason=[%s]%d",
					strerror(errno), errno);
				continue;
			}
			fd = socket_tcp_client_connect_ipv6(ip_str, ntohs(addr->sin6_port));
			if(fd != -1) {
				break;
			}
		}
	}
	freeaddrinfo(result);
	return fd;
}

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_local(bool abstract, const char* name) {
	int fd;
	int size;
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	size = strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1;
	if(abstract) {
		addr.sun_path[0] = 0;
		memcpy(addr.sun_path + 1, name, strlen(name));
	} else {
		strncpy(addr.sun_path, name, sizeof(addr.sun_path));
	}
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd == -1) {
		LOGE("socket_tcp_client_connect_local() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(connect(fd, (struct sockaddr*)&addr, size) == -1) {
		LOGE("socket_tcp_client_connect_local() connect() failed, abstract=%d name=[%s] reason=[%s]%d",
			abstract, name, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or serverfd is returned
int socket_udp_server_bind_ipv4(int port) {
	int fd;
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(fd == -1) {
		LOGE("socket_udp_server_bind_ipv4() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_udp_server_bind_ipv4() bind() failed, port=%d reason=[%s]%d",
			port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or serverfd is returned
int socket_udp_server_bind_ipv6(int port) {
	int fd;
	struct sockaddr_in6 addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	addr.sin6_addr = in6addr_any;
	fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if(fd == -1) {
		LOGE("socket_udp_server_bind_ipv6() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_udp_server_bind_ipv6() bind() failed, port=%d reason=[%s]%d",
			port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or serverfd is returned
int socket_udp_server_bind_local(bool abstract, const char* name) {
	int fd;
	int size;
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	size = strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1;
	if(abstract) {
		addr.sun_path[0] = 0;
		memcpy(addr.sun_path + 1, name, strlen(name));
	} else {
		strncpy(addr.sun_path, name, sizeof(addr.sun_path));
		if(unlink(addr.sun_path) == -1) {
			LOGW("socket_udp_server_bind_local() unlink() failed, reason=[%s]%d",
				strerror(errno), errno);
		}
	}
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(fd == -1) {
		LOGE("socket_udp_server_bind_local() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(bind(fd, (struct sockaddr*)&addr, size) == -1) {
		LOGE("socket_udp_server_bind_local() bind() failed, abstract=%d name=[%s] reason=[%s]%d",
			abstract, name, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or clientfd is returned
int socket_udp_client_create_ipv4(const char* ip, int port) {
	int fd;
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
		LOGE("socket_udp_client_create_ipv4() inet_pton() failed, due to ip=[%s] is not standard dotted-decimal notation", ip);
		return -1;
	}
	fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(fd == -1) {
		LOGE("socket_udp_client_create_ipv4() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_udp_client_create_ipv4() connect() failed, ip=[%s] port=%d reason=[%s]%d",
			ip, port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or clientfd is returned
int socket_udp_client_create_ipv6(const char* ip, int port) {
	int fd;
	struct sockaddr_in6 addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	if(inet_pton(AF_INET6, ip, &addr.sin6_addr) != 1) {
		LOGE("socket_udp_client_create_ipv6() inet_pton() failed, due to ip=[%s] does not contain a character string representing a valid network address", ip);
		return -1;
	}
	fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if(fd == -1) {
		LOGE("socket_udp_client_create_ipv6() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOGE("socket_udp_client_create_ipv6() connect() failed, ip=[%s] port=%d reason=[%s]%d",
			ip, port, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

//-1 means fail or clientfd is returned
int socket_udp_client_create_fqdn(const char* host, int port) {
	struct addrinfo hints;
	struct addrinfo* result;
	struct addrinfo* rp;
	int fd = 0;
	int ret;
	char port_str[11] = {0};

	sprintf(port_str, "%u", port);
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //allow IPv4, IPv6, AF_UNSPEC, AF_INET, AF_INET6
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_ADDRCONFIG; //check local system
	hints.ai_protocol = IPPROTO_UDP;
	LOGD("socket_udp_client_create_fqdn() getaddrinfo() host=[%s] port=%d", host, port);
	ret = getaddrinfo(host, port_str, &hints, &result);
	if(ret != 0) {
		LOGE("socket_udp_client_create_fqdn() getaddrinfo() failed, reason=[%s] ret=%d",
			gai_strerror(ret), ret);
		return -1;
	}
	for(rp = result; rp != NULL; rp = rp->ai_next) {
		if(rp->ai_family == AF_INET) {
			struct sockaddr_in* addr = (struct sockaddr_in*)rp->ai_addr;
			char ip_str[INET_ADDRSTRLEN] = {0};
			const char* p_ret = inet_ntop(AF_INET, &addr->sin_addr, ip_str,
				INET_ADDRSTRLEN);
			if(p_ret == NULL) {
				LOGE("socket_udp_client_create_fqdn() inet_ntop() failed, reason=[%s]%d",
					strerror(errno), errno);
				continue;
			}
			LOGD("try to connect IPv4 ip=[%s] port=%d",
				ip_str, ntohs(addr->sin_port));
			fd = socket_udp_client_create_ipv4(ip_str, ntohs(addr->sin_port));
			if(fd != -1) {
				break;
			}
		}
		if(rp->ai_family == AF_INET6) {
			struct sockaddr_in6* addr = (struct sockaddr_in6*)rp->ai_addr;
			char ip_str[INET6_ADDRSTRLEN] = {0};
			const char* p_ret = inet_ntop(AF_INET6, &addr->sin6_addr, ip_str,
				INET6_ADDRSTRLEN);
			if(p_ret == NULL) {
				LOGE("socket_udp_client_create_fqdn() inet_ntop() failed, reason=[%s]%d",
					strerror(errno), errno);
				continue;
			}
			LOGD("try to connect IPv6 ip=[%s] port=%d",
				ip_str, ntohs(addr->sin6_port));
			fd = socket_udp_client_create_ipv6(ip_str, ntohs(addr->sin6_port));;
			if(fd != -1) {
				break;
			}
		}
	}
	freeaddrinfo(result);
	return fd;
}

//-1 means fail or clientfd is returned
int socket_udp_client_create_local(bool abstract, const char* name) {
	int fd;
	int size;
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	size = strlen(name) + offsetof(struct sockaddr_un, sun_path) + 1;
	if(abstract) {
		addr.sun_path[0] = 0;
		memcpy(addr.sun_path + 1, name, strlen(name));
	} else {
		strncpy(addr.sun_path, name, sizeof(addr.sun_path));
	}
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(fd == -1) {
		LOGE("socket_udp_client_create_local() socket() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	if(connect(fd, (struct sockaddr*)&addr, size) == -1) {
		LOGE("socket_udp_client_create_local() connect() failed, abstract=%d name=[%s] reason=[%s]%d",
			abstract, name, strerror(errno), errno);
		close(fd);
		return -1;
	}
	return fd;
}

bool socket_set_blocking(int fd, bool blocking) {
	int ret;
	if(fd == -1) {
		LOGE("socket_set_blocking() fd is invalid");
		return false;
	}
	ret = fcntl(fd, F_GETFL, 0);
	if(ret == -1) {
		LOGE("socket_set_blocking() fcntl(F_GETFL) failed, fd=%d", fd);
		return false;
	}
	if(blocking) {
		ret &= ~O_NONBLOCK;
	} else {
		ret |= O_NONBLOCK;
	}
	ret = fcntl(fd, F_SETFL, ret);
	if(ret == -1) {
		LOGE("socket_set_blocking() fcntl(F_SETFL) failed, fd=%d", fd);
		return false;
	}
	return true;
}

bool socket_set_rcv_buff_size(int fd, uint32_t size) {
	if(setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) == -1) {
		LOGE("socket_set_rcv_buff_size() setsockopt(SO_RCVBUF) failed, fd=%d size=%d reason=[%s]%d",
			fd, size, strerror(errno), errno);
		return false;
	}
	return true;
}

bool socket_set_snd_buff_size(int fd, uint32_t size) {
	if(setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size)) == -1) {
		LOGE("socket_set_snd_buff_size() setsockopt(SO_SNDBUF) failed, fd=%d size=%d reason=[%s]%d",
			fd, size, strerror(errno), errno);
		return false;
	}
	return true;
}

bool socket_tcp_disable_keepalive(int fd) {
	int disable = 0;
	if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &disable, sizeof(disable)) == -1) {
		LOGE("socket_tcp_disable_keepalive(() setsockopt(SO_KEEPALIVE) failed, fd=%d reason=[%s]%d",
			fd, strerror(errno), errno);
		return false;
	}
	return true;
}

//UDP and Local socket are not supported
//time: the interval between the last data packet sent
//intvl: the interval between subsequential keepalive probes
//probes: the number of unacknowledged probes to send before considering the connection dead and notifying the application layer
bool socket_tcp_enable_keepalive(int fd, uint32_t time, uint32_t intvl, uint32_t probes) {
	int enable = 1;
	if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable)) == -1) {
		LOGE("socket_tcp_enable_keepalive() setsockopt(SO_KEEPALIVE) failed, fd=%d reason=[%s]%d",
			fd, strerror(errno), errno);
		return false;
	}
	if(setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &time, sizeof(time)) == -1) {
		LOGE("socket_tcp_enable_keepalive() setsockopt(TCP_KEEPIDLE) failed, time=%dd reason=[%s]%d",
			time, strerror(errno), errno);
		return false;
	}
	if(setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &intvl, sizeof(intvl)) == -1) {
		LOGE("socket_tcp_enable_keepalive() setsockopt(TCP_KEEPINTVL) failed, intvl=%d reason=[%s]%d",
			intvl, strerror(errno), errno);
		return false;
	}
	if(setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &probes, sizeof(probes)) == -1) {
		LOGE("socket_tcp_enable_keepalive() setsockopt(TCL_KEEPCNT) failed, probes=%d reason=[%s]%d",
			probes, strerror(errno), errno);
		return false;
	}
	return true;
}

//set the protocol-defined priority for all packets to be sent on this socket.
//Linux uses this value to order the networking queues:
//packets with a higher priority may be processed first depending on the selected device
//queueing discipline, range 0 (low priority) to 6 (high priority)
bool socket_set_priority(int fd, int prio) {
	if(setsockopt(fd, SOL_SOCKET, SO_PRIORITY, &prio, sizeof(prio)) == -1) {
		LOGE("socket_set_priority() setsockopt(SO_PRIORITY) failed, fd=%d prio=%d (0-6) reason=[%s]%d",
			fd, prio, strerror(errno), errno);
		return false;
	}
	return true;
}

//UDP and Local socket are not supported
//segments are always sent as soon as possible, even if there is only a small amount of data
bool socket_set_no_delay(int fd, bool no_delay) {
	int value = no_delay;
	if(setsockopt(fd, SOL_TCP, TCP_NODELAY, &value, sizeof(value)) == -1) {
		LOGE("socket_set_no_delay() setsockopt(TCP_NODELAY) failed, fd=%d no_delay=%d reason=[%s]%d",
			fd, no_delay, strerror(errno), errno);
		return false;
	}
	return true;
}

//Local socket is not supported
//minimize delays for interactive traffic, #inlcude <netinet/ip.h>
//#define IPTOS_LOWDELAY 0x10
//#define IPTOS_THROUGHPUT 0x08
//#define IPTOS_RELIABILITY 0x04
//#define IPTOS_MINCOST 0x02
bool socket_set_tos(int fd, int tos) {
	if(setsockopt(fd, SOL_IP, IP_TOS, &tos, sizeof(tos)) == -1) {
		LOGE("socket_set_tos() setsockopt(IP_TOS) failed, fd=%d tos=0x%x reason=[%s]%d",
			fd, tos, strerror(errno), errno);
		return false;
	}
	return true;
}

void socket_dump_fd_state(int fd, const char* msg) {
	int ret;
	if(fd == -1) {
		LOGE("socket_dump_fd_state() fd is invalid");
		return;
	}

	bool is_block = true;
	ret = fcntl(fd, F_GETFL, 0);
	if(ret == -1) {
		LOGE("socket_dump_fd_state() fcntl(F_GETFL) failed, fd=%d", fd);
		return;
	}
	if(ret & O_NONBLOCK) {
		is_block = false;
	}

	socklen_t optlen = sizeof(int);
	int rcvbuf = -1;
	if(getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &optlen) == -1) {
		LOGE("socket_dump_fd_state() getsockopt(SO_RCVBUF) failed, reason=[%s]%d",
			strerror(errno), errno);
		return;
	}
	int sndbuf = -1;
	if(getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &sndbuf, &optlen) == -1) {
		LOGE("socket_dump_fd_state() getsockopt(SO_SNDBUF) failed, reason=[%s]%d",
			strerror(errno), errno);
		return;
	}
	
	int is_keepalive = -1;
	if(getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &is_keepalive, &optlen) == -1) {
		LOGE("socket_dump_fd_state() getsockopt(SO_KEEPALIVE) failed, reason=[%s]%d",
			strerror(errno), errno);
		return;
	}
	int time = -1;
	if(getsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &time, &optlen) == -1) {
		//UDP and local socket will fail
	}
	int intvl = -1;
	if(getsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &intvl, &optlen) == -1) {
		//UDP and local socket will fail
	}
	int probes = -1;
	if(getsockopt(fd, SOL_TCP, TCP_KEEPCNT, &probes, &optlen) == -1) {
		//UDP and local socket will fail
	}

	int prio = -1;
	if(getsockopt(fd, SOL_SOCKET, SO_PRIORITY, &prio, &optlen) == -1) {
		LOGE("socket_dump_fd_state() getsockopt(SO_PRIORITY) failed, reason=[%s]%d",
			strerror(errno), errno);
		return;
	}
	int no_delay = -1;
	if(getsockopt(fd, SOL_TCP, TCP_NODELAY, &no_delay, &optlen) == -1) {
		//UDP and local socket will fail
	}
	int tos = -1;
	if(getsockopt(fd, SOL_IP, IP_TOS, &tos, &optlen) == -1) {
		//Local socket will fail
	}

	LOGD("[%s] fd=%d [block=%d rcvbuf=%d sndbuf=%d] [keepalive=%d time=%d intvl=%d probes=%d] [prio=%d no_delay=%d tos=0x%x]",
		msg, fd, is_block, rcvbuf, sndbuf, is_keepalive, time, intvl, probes, prio,
		no_delay, tos);
}

/******************************************************************************
* Epoll
******************************************************************************/
typedef struct {
	int fd;
	int events;
	epoll_routine routine;
} epoll_fd_struct;

typedef struct {
	int epfd;
	int size;
	int index;
	struct epoll_event events[10];
	epoll_fd_struct* fds;
} epoll_context;

bool utils_epoll_create(epoll** ep, uint32_t size) {
	if(*ep != NULL) {
		LOGE("utils_epoll_create() ep is NOT NULL");
		return false;
	}
	//malloc
	epoll_context* p = malloc(sizeof(epoll_context));
	if(p == NULL) {
		LOGE("utils_epoll_create() malloc() failed");
		return false;
	}
	p->fds = malloc(sizeof(epoll_fd_struct) * size);
	if(p->fds == NULL) {
		LOGE("utils_epoll_create() malloc() 2 failed");
		free(p);
		return false;
	}
	//init values	
	p->epfd = epoll_create(size);
	if(p->epfd == -1) {
		LOGE("utils_epoll_create() epoll_create() failed, reason=[%s]%d",
			strerror(errno), errno);
		free(p->fds);
		free(p);
		return false;
	}
	p->size = size;
	p->index = 0;
	*ep = (epoll*)p;
	return true;
}

bool utils_epoll_delete(epoll** ep) {
	if(*ep == NULL) {
		LOGE("utils_epoll_delete() ep is NULL");
		return false;
	}
	epoll_context* p = (epoll_context*)*ep;
	close(p->epfd);
	free(p->fds);
	free(p);
	*ep = NULL;
	return true;
}

void utils_epoll_dump(epoll* ep) {
	if(ep == NULL) {
		LOGW("utils_epoll_dump() ep is NULL");
	}
	epoll_context* p = (epoll_context*)ep;
	LOGD("utils_epoll_dump() epfd=%d size=%d index=%d",
		p->epfd, p->size, p->index);
	int i = 0;
	for(i = 0; i < p->index; i++) {
		LOGD("  i=%2d fd=%d events=0x%x", i, p->fds[i].fd,p->fds[i].events);
	}
}

bool utils_epoll_add_fd(epoll* ep, int fd, int events, epoll_routine routine) {
	if(ep == NULL) {
		LOGE("utils_epoll_add_fd() ep is NULL");
		return false;
	}
	if(routine == NULL) {
		LOGE("utils_epoll_add_fd() routine is NULL");
		return false;
	}
	epoll_context* p = (epoll_context*)ep;
	if(p->size == p->index) {
		LOGE("utils_epoll_add_fd() size=%d is full", p->size);
		return false;
	}

	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.data.fd = fd;
	ev.events = events;
	if(epoll_ctl(p->epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		LOGE("utils_epoll_add_fd() epoll_ctl() failed, epfd=%d fd=%d events=0x%x reason=[%s]%d",
			p->epfd, fd, events, strerror(errno), errno);
		return false;
	}
	epoll_fd_struct* epoll_fd = &p->fds[p->index];
	epoll_fd->fd = fd;
	epoll_fd->events = events;
	epoll_fd->routine = routine;
	p->index++;
	return true;
}

bool utils_epoll_modify_fd(epoll* ep, int fd, int events, epoll_routine routine) {
	if(ep == NULL) {
		LOGE("utils_epoll_modify_fd() ep is NULL");
		return false;
	}
	int i;
	epoll_context* p = (epoll_context*)ep;

	//find fd
	for(i = 0; i < p->index; i++) {
		if(p->fds[i].fd == fd) {
			p->fds[i].events = events;
			if(routine) {
				p->fds[i].routine = routine;
			}
			break;
		}
	}
	if(i == p->index) {
		LOGE("utils_epoll_modify_fd() fd=%d is not found", fd);
		return false;
	}

	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.data.fd = fd;
	ev.events = events;
	if(epoll_ctl(p->epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
		LOGE("utils_epoll_modify_fd() epoll_ctl() failed, epfd=%d fd=%d events=0x%x reason=[%s]%d",
			p->epfd, fd, events, strerror(errno), errno);
		return false;
	}
	return true;
}

bool utils_epoll_remove_fd(epoll* ep, int fd) {
	if(ep == NULL) {
		LOGE("utils_epoll_remove_fd() ep is NULL");
		return false;
	}
	int i;
	epoll_context* p = (epoll_context*)ep;
	if(p->index == 0) {
		LOGE("utils_epoll_remove_fd() fds is empty");
		return false;
	}
	//find fd
	for(i = 0; i < p->index; i++) {
		if(p->fds[i].fd == fd) {
			break;
		}
	}
	if(i == p->index) {
		LOGE("utils_epoll_remove_fd() fd=%d is not found", fd);
		return false;
	}
	utils_epoll_modify_fd(ep, p->fds[i].fd, 0, NULL);

	//move others to previous slot
	for(; i < (p->index - 1); i++) {
		p->fds[i] = p->fds[i + 1];
	}
	p->index--;
	return true;
}

//-1 means fail or return the number of event is handled
int utils_epoll_wait(epoll* ep, int timeout) {
	int n, i, j;
	if(ep == NULL) {
		LOGE("");
		return -1;
	}
	epoll_context* p = (epoll_context*)ep;
	struct epoll_event events[p->size];
	n = epoll_wait(p->epfd, events, p->size, timeout);
	if(n == -1) {
		LOGE("utils_epoll_wait() failed, epfd=%d size=%d reason=[%s]%d",
			p->epfd, p->size, strerror(errno), errno);
		return -1;
	}
	LOGD("n=%d", n);
	for(i = 0; i < n; i++) {
		for(j = 0; j < p->size; j++) {
			if(events[i].data.fd == p->fds[j].fd) {
				p->fds[j].routine(p->fds[j].fd, events[i].events);
			}
		}
	}
	return n;
}


bool epoll_add_fd(int epfd, int fd, int events) {
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.data.fd = fd;
	ev.events = events;
	//don't set fd to edge trigger due to event lost when multiple events coming together
	//level trigger can avoid above issue
	//do not set EPOLLOUT due to it will always trigger when write is available
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		LOGE("epoll_ctl() failed, epfd=%d fd=%d events=0x%x reason=[%s]%d",
			epfd, fd, events, strerror(errno), errno);
		return false;
	}
	return true;
}


/******************************************************************************
* TCP Server Client List
******************************************************************************/

typedef struct {
	int size;
	int index;
	int* fds;
} server_client_list_context;


server_client_list* server_client_list_init(int max_client_number) {
	server_client_list_context* out = malloc(sizeof(server_client_list_context));
	if(out == NULL) {
		LOGE("malloc() failed 1");
		crash_with_log();
	}
	out->size = max_client_number;
	out->index = 0;
	out->fds = malloc(sizeof(int) * max_client_number);
	if(out->fds == NULL) {
		LOGE("malloc() failed 2");
		crash_with_log();
	}
	return (server_client_list*)out;
}

void server_client_list_cleanup(server_client_list* list) {
	server_client_list_context* context = (server_client_list_context*)list;
	int i = 0;
	for(i = 0; i < context->index; i++) {
		close(context->fds[i]);
	}
	free(context->fds);
	free(context);
}

bool server_client_list_add(server_client_list* list, int fd) {
	server_client_list_context* context = (server_client_list_context*)list;
	if(context->index == context->size) {
		return false;
	}
	context->fds[context->index] = fd;
	context->index++;
	return true;
}

bool server_client_list_remove(server_client_list* list, int fd) {
	server_client_list_context* context = (server_client_list_context*)list;
	if(context->index == 0) {
		return false;
	}

	int i;
	for(i = 0; i < context->index; i++) {
		if(context->fds[i] == fd) {
			break;
		}
	}

	if(i == context->index) {
		return false;
	}

	close(fd);
	for(; i < context->index; i++) {
		context->fds[i] = context->fds[i + 1];
	}
	context->index--;
	return true;
}

int server_client_list_get_client_num(server_client_list* list) {
	server_client_list_context* context = (server_client_list_context*)list;
	return context->index;
}

bool server_client_list_contains(server_client_list* list, int fd) {
	server_client_list_context* context = (server_client_list_context*)list;
	int i;
	for(i = 0; i < context->index; i++) {
		if(context->fds[i] == fd) {
			return true;
		}
	}
	return false;
}

// return -1 means failed
int server_client_list_get_fd(server_client_list* list, int index) {
	server_client_list_context* context = (server_client_list_context*)list;

	if(context->index < index) {
		return -1;
	}
	
	return context->fds[index];
}


/******************************************************************************
* assume always success, if failure then crash with log
******************************************************************************/
void* malloc_0_impl(size_t size, const char* file, const char* function, int line) {
	void* out = malloc(size);
	if(out == NULL) {
		LOGE("malloc() failed, size=%d", size);
		crash_with_log_0(file, function, line);
	}
	return out;
}

/******************************************************************************
* Misc
******************************************************************************/

