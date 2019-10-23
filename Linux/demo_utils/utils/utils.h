#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> //uint64_t, int64_t
#include <unistd.h> //usleep
#include <stdarg.h>
#include <stdlib.h> //exit
#include <string.h> //strerror()
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/epoll.h> //epoll

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Log
******************************************************************************/
void utils_logd(const char* tag, const char* fmt, ...);
void utils_logw(const char* tag, const char* fmt, ...);
void utils_loge(const char* tag, const char* fmt, ...);

#ifdef LOGD
#undef LOGD
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGE
#undef LOGE
#endif
#define LOGD(...) utils_logd("default", __VA_ARGS__)
#define LOGW(...) utils_logw("default", __VA_ARGS__)
#define LOGE(...) utils_loge("default", __VA_ARGS__)

/******************************************************************************
* Utils
******************************************************************************/
#define assert(expr) {\
	if(!(expr)) {\
		LOGE("assert(%s) failed, %s %s() line=%d", #expr, __FILE__, __FUNCTION__, __LINE__);\
		exit(1);\
	}\
\
}

#define crash_with_log() {\
	LOGE("crash_with_log() %s %s() line=%d", __FILE__, __FUNCTION__, __LINE__);\
	exit(1);\
}

#define crash_with_log_0(file, function, line) {\
	LOGE("crash_with_log() %s %s() line=%d", file, function, line);\
	exit(1);\
}

#define UNUSED(x) do { (void)(x); } while (0)
#define msleep(usec) {\
	int ret = usleep((usec)*1000);\
	if(ret == -1) {\
		LOGE("usleep() failed, usec=%lu reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

int64_t utils_gettid();
void utils_get_time_str(char* buff, int len);


/******************************************************************************
* File
******************************************************************************/
bool file_is_file_exist(const char* path);
bool file_is_folder_exist(const char* path);
// -1 means fail
int file_get_file_size(const char* path);
bool file_create_file(const char* path);
bool file_create_folder(const char* path);
bool file_delete(const char* path);
//User: S_IRUSR (read), S_IWUSR (write), S_IXUSR (execute)
//Group: S_IRGRP (read), S_IWGRP (write), S_IXGRP (execute)
//Others: S_IROTH (read), S_IWOTH (write), S_IXOTH (execute)
// or 0660 is -rw-rw----
bool file_chmod(const char* path, int mode);

bool  file_read(const char* path, char* buff, int buff_size);
bool file_write(const char* path, const char* buff, int buff_size);

/******************************************************************************
* Time
******************************************************************************/
//-1 means fail or the time tick is returned and the unit is millisecond
int64_t time_get_tick();

//-1 means fail or the system time tick is returned and the unit is millisecond
int64_t time_get_system_time();

/******************************************************************************
* Timer
******************************************************************************/
typedef void (*timer_routine) (int id);
//-1 means fail or timerid is returned

//NULL means fail or timerid is returned
timer_t timer_init(timer_routine cb, int id);
bool timer_deinit(timer_t timerid);

bool timer_start(timer_t timerid, int milliseconds);
bool timer_stop(timer_t timerid);

//-1 means fail or the remaining time is returned
int64_t timer_get_remaining_time(timer_t timerid);

/******************************************************************************
* Socket
******************************************************************************/
//-1 means fail or serverfd is returned
int socket_tcp_server_bind_ipv4(int port);

//-1 means fail or serverfd is returned
int socket_tcp_server_bind_ipv6(int port);

//-1 means fail or serverfd is returned
int socket_tcp_server_bind_local(bool abstract, const char* name);

//-1 means fail or new clientfd is returned
int socket_tcp_server_new_connect(int serverfd);


//-1 means fail or clientfd is returned
int socket_tcp_client_connect_ipv4(const char* ip, int port);

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_ipv6(const char* ip, int port);

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_fqdn(const char* host, int port);

//-1 means fail or clientfd is returned
int socket_tcp_client_connect_local(bool abstract, const char* name);


//-1 means fail or serverfd is returned
int socket_udp_server_bind_ipv4(int port);

//-1 means fail or serverfd is returned
int socket_udp_server_bind_ipv6(int port);

//-1 means fail or serverfd is returned
int socket_udp_server_bind_local(bool abstract, const char* name);


//-1 means fail or clientfd is returned
int socket_udp_client_create_ipv4(const char* ip, int port);

//-1 means fail or clientfd is returned
int socket_udp_client_create_ipv6(const char* ip, int port);

//-1 means fail or clientfd is returned
int socket_udp_client_create_fqdn(const char* host, int port);

//-1 means fail or clientfd is returned
int socket_udp_client_create_local(bool abstract, const char* name);

bool socket_set_blocking(int fd, bool blocking);
bool socket_set_rcv_buff_size(int fd, uint32_t size);
bool socket_set_snd_buff_size(int fd, uint32_t size);
bool socket_tcp_disable_keepalive(int fd);
//UDP and Local socket are not supported
//time: the interval between the last data packet sent
//intvl: the interval between subsequential keepalive probes
//probes: the number of unacknowledged probes to send before considering the connection dead and notifying the application layer
bool socket_tcp_enable_keepalive(int fd, uint32_t time, uint32_t intvl, uint32_t probes);
//set the protocol-defined priority for all packets to be sent on this socket.
//Linux uses this value to order the networking queues:
//packets with a higher priority may be processed first depending on the selected device
//queueing discipline, range 0 (low priority) to 6 (high priority)
bool socket_set_priority(int fd, int prio);
//UDP and Local socket are not supported
//segments are always sent as soon as possible, even if there is only a small amount of data
bool socket_set_no_delay(int fd, bool no_delay);
//Local socket is not supported
//minimize delays for interactive traffic, #inlcude <netinet/ip.h>
//#define IPTOS_LOWDELAY 0x10
//#define IPTOS_THROUGHPUT 0x08
//#define IPTOS_RELIABILITY 0x04
//#define IPTOS_MINCOST 0x02
bool socket_set_tos(int fd, int tos);
void socket_dump_fd_state(int fd, const char* msg);

/******************************************************************************
* Epoll (need to check whether to remove it)
******************************************************************************/
bool epoll_add_fd(int epfd, int fd, int events);

#define UTILS_EPOLLIN    0x01 //The associated file is available for read(2) operations
#define UTILS_EPOLLPRI   0x02 //there is urgent data available for read(2) operations
#define UTILS_EPOLLOUT   0x04 //The associated file is available for write(2) operations
#define UTILS_EPOLLERR   0x08 //Error condition happened on the associated file. epoll_wait(2) will always wait for this event
#define UTILS_EPOLLHUP   0x10 //Hang up happened on the associated file. epoll_wait(2) will always wait for this event
typedef void (*epoll_routine) (int fd, int events);
typedef struct epoll epoll;
bool utils_epoll_create(epoll** ep, uint32_t size);
bool utils_epoll_delete(epoll** ep);
void utils_epoll_dump(epoll* ep);
bool utils_epoll_add_fd(epoll* ep, int fd, int events, epoll_routine routine);
bool utils_epoll_modify_fd(epoll* ep, int fd, int events, epoll_routine routine);
bool utils_epoll_remove_fd(epoll* ep, int fd);
//-1 means fail or return the number of event is handled
int utils_epoll_wait(epoll* ep, int timeout);

/******************************************************************************
* TCP Server Client List
******************************************************************************/
typedef struct server_client_list server_client_list;

server_client_list* server_client_list_init(int max_client_number);
void server_client_list_cleanup(server_client_list* list);
bool server_client_list_add(server_client_list* list, int fd);
bool server_client_list_remove(server_client_list* list, int fd);
int server_client_list_get_client_num(server_client_list* list);
bool server_client_list_contains(server_client_list* list, int fd);
// return -1 means failed
int server_client_list_get_fd(server_client_list* list, int index);

/******************************************************************************
* assume always success, if failure then crash with log
******************************************************************************/

#define malloc_0(size) malloc_0_impl(size, __FILE__, __FUNCTION__, __LINE__)

//pthread
#define pthread_create_0(thread, attr, start_routine, arg) {\
	int ret = pthread_create(thread, attr, start_routine, arg);\
	if (ret != 0) {\
		LOGE("pthread_create() failed ret=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

#define pthread_detach_0(thread) {\
	int ret = pthread_detach(thread);\
	if(ret != 0) {\
		LOGE("pthread_detach() failed, reason=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

//mutex
#define pthread_mutex_init_0(mutex, attr) {\
	int ret = pthread_mutex_init(mutex, attr);\
	if(ret != 0) {\
		LOGE("pthread_mutex_init() failed reason=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

#define pthread_mutex_lock_0(mutex) {\
	int ret = pthread_mutex_lock(mutex);\
	if(ret != 0) {\
		LOGE("pthread_mutex_lock() failed reason=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

#define pthread_mutex_unlock_0(mutex) {\
	int ret = pthread_mutex_unlock(mutex);\
	if(ret != 0) {\
		LOGE("pthread_mutex_unlock() failed reason=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

#define pthread_mutex_destroy_0(mutex) {\
	int ret = pthread_mutex_destroy(mutex);\
	if(ret != 0) {\
		LOGE("pthread_mutex_destroy() failed reason=[%s]%d", strerror(ret), ret);\
		crash_with_log();\
	}\
}

//semaphore
#define sem_init_0(sem, pshared, value) {\
	int ret = sem_init(sem, pshared, value);\
	if(ret != 0) {\
		LOGE("sem_init() failed reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

#define sem_post_0(sem) {\
	int ret = sem_post(sem);\
	if(ret != 0) {\
		LOGE("sem_post() failed reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

#define sem_getvalue_0(sem, sval) {\
	int ret = sem_getvalue(sem, sval);\
	if(ret != 0) {\
		LOGE("sem_getvalue() failed reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

#define sem_wait_0(sem) {\
	int ret = sem_wait(sem);\
	if(ret != 0) {\
		LOGE("sem_wait() failed reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

#define sem_destroy_0(sem) {\
	int ret = sem_destroy(sem);\
	if(ret != 0) {\
		LOGE("sem_destroy() failed reason=[%s]%d", strerror(errno), errno);\
		crash_with_log();\
	}\
}

/******************************************************************************
* Misc
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __UTILS_H__
