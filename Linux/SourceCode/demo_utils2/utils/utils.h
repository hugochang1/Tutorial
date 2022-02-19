#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h> //exit()
#include <stdbool.h>
#include <string.h> //strlen()

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* For internal use
******************************************************************************/
void _utils_logd(const char* format, ...);
void _utils_logw(const char* format, ...);
void _utils_loge(const char* format, ...);
/******************************************************************************
* Logs
******************************************************************************/

void utils_set_log(void (*logd)(const char* msg),
	void (*logw)(const char* msg),
	void (*loge)(const char* msg));

void utils_log_test();

/******************************************************************************
* Utils
******************************************************************************/

#define assert(expr) {\
	if(!(expr)) {\
		_utils_loge("assert(%s) failed, %s %s() line=%d", #expr, __FILE__, __FUNCTION__, __LINE__);\
		exit(1);\
	}\
\
}

#define crash_with_log() {\
	_utils_loge("crash_with_log() %s %s() line=%d", __FILE__, __FUNCTION__, __LINE__);\
	exit(1);\
}

#define UNUSED(x) do { (void)(x); } while (0)

#define msleep(msec) usleep((msec)*1000)

#ifdef __cplusplus
}
#endif

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

bool file_read(const char* path, char* buff, int buff_size);
//create a new file if the path does not exist
bool file_write(const char* path, const char* buff, int buff_size);

/******************************************************************************
* Time
******************************************************************************/
//-1 means fail or the time tick is returned and the unit is millisecond
long long time_get_tick();

//-1 means fail or the system time tick is returned and the unit is millisecond
long long time_get_system_time();

/******************************************************************************
* End
******************************************************************************/

#endif // __UTILS_H__
