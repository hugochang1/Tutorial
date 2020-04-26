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

/******************************************************************************
* Logs
******************************************************************************/
void simple_print_impl(const char* msg) {
	printf("%s\r\n", msg);
}

void (*__logd)(const char* msg) = simple_print_impl;
void (*__logw)(const char* msg) = simple_print_impl;
void (*__loge)(const char* msg) = simple_print_impl;

void _utils_logd(const char* format, ...) {
	char buff[8192] = {0};
	va_list args;
	va_start(args, format);
	vsnprintf(buff, sizeof(buff), format, args);
	__logd(buff);
	va_end(args);
}

void _utils_logw(const char* format, ...) {
	char buff[8192] = {0};
	va_list args;
	va_start(args, format);
	vsnprintf(buff, sizeof(buff), format, args);
	__logw(buff);
	va_end(args);
}

void _utils_loge(const char* format, ...) {
	char buff[8192] = {0};
	va_list args;
	va_start(args, format);
	vsnprintf(buff, sizeof(buff), format, args);
	__loge(buff);
	va_end(args);
}

#define LOGD(...) _utils_logd(__VA_ARGS__)
#define LOGW(...) _utils_logw(__VA_ARGS__)
#define LOGE(...) _utils_loge(__VA_ARGS__)

void utils_set_log(void (*logd)(const char* msg),
		void (*logw)(const char* msg),
		void (*loge)(const char* msg)) {
	if(logd != NULL) {
		__logd = logd;
	}
	if(logw != NULL) {
		__logw = logw;
	}
	if(loge != NULL) {
		__loge = loge;
	}
}

void utils_log_test() {
	LOGD("LOGD %d %f %s", 123, 12.34, "hello");
	LOGW("LOGW %d %f %s", 123, 12.34, "hello");
	LOGE("LOGE %d %f %s", 123, 12.34, "hello");
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
long long time_get_tick() {
	struct timespec ts;
	if(clock_gettime(CLOCK_BOOTTIME, &ts) == -1) {
		LOGE("time_get_tick() clock_gettime() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}

//-1 means fail or the system time tick is returned and the unit is millisecond
long long time_get_system_time() {
	struct timespec ts;
	if(clock_gettime(CLOCK_REALTIME, &ts) == -1) {
		LOGE("time_get_system_time() clock_gettime() failed, reason=[%s]%d",
			strerror(errno), errno);
		return -1;
	}
	return ((int64_t)ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}



