#ifndef __MY_LOG_H__
#define __MY_LOG_H__

#include <stdio.h>
#include <unistd.h>
#include <time.h> //struct tm
#include <sys/time.h> //gettimeofday, localtime
#include <sys/syscall.h> //SYS_gettid

#ifdef __cplusplus
extern "C" {
#endif


#define YOUR_MODULE_VERSION "Module_1.00"

#define LOGD(...) {\
	struct timeval tv;\
	struct timezone tz;\
	struct tm* tm;\
	gettimeofday(&tv, &tz);\
	tm = localtime(&tv.tv_sec);\
	printf("%04d/%02d/%02d %02d:%02d:%02d.%03d ",\
		tm->tm_year + 1900, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour,\
		tm->tm_min, tm->tm_sec, (int)(tv.tv_usec/1000));\
	printf("%ld %ld ", (long)getpid(), syscall(SYS_gettid));\
	printf("[%s][D] %s() %d ", YOUR_MODULE_VERSION, __FUNCTION__, __LINE__);\
	printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

#define LOGW(...) {\
	struct timeval tv;\
	struct timezone tz;\
	struct tm* tm;\
	gettimeofday(&tv, &tz);\
	tm = localtime(&tv.tv_sec);\
	printf("\E[1;35;40m");\
	printf("%04d/%02d/%02d %02d:%02d:%02d.%03d ",\
		tm->tm_year + 1900, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour,\
		tm->tm_min, tm->tm_sec, (int)(tv.tv_usec/1000));\
	printf("%ld %ld ", (long)getpid(), syscall(SYS_gettid));\
	printf("[%s][D] %s() %d ", YOUR_MODULE_VERSION, __FUNCTION__, __LINE__);\
	printf(__VA_ARGS__); printf("\E[0m"); printf("\n"); fflush(stdout); }

#define LOGE(...) {\
	struct timeval tv;\
	struct timezone tz;\
	struct tm* tm;\
	gettimeofday(&tv, &tz);\
	tm = localtime(&tv.tv_sec);\
	printf("\E[1;31;40m");\
	printf("%04d/%02d/%02d %02d:%02d:%02d.%03d ",\
		tm->tm_year + 1900, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour,\
		tm->tm_min, tm->tm_sec, (int)(tv.tv_usec/1000));\
	printf("%ld %ld ", (long)getpid(), syscall(SYS_gettid));\
	printf("[%s][D] %s() %d ", YOUR_MODULE_VERSION, __FUNCTION__, __LINE__);\
	printf(__VA_ARGS__); printf("\E[0m"); printf("\n"); fflush(stdout); }


#ifdef __cplusplus
}
#endif

#endif // __MY_LOG_H__
