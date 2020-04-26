#include "utils.h"
#include "my_log.h"

void utils_logd(const char* msg) {
	LOGD("%s", msg);
}

void utils_logw(const char* msg) {
	LOGW("%s", msg);
}

void utils_loge(const char* msg) {
	LOGE("%s", msg);
}

int main(int argc, char** argv) {
	// log
	LOGD("LOGD");
	LOGW("LOGW");
	LOGE("LOGE");

	utils_set_log(utils_logd, utils_logw, utils_loge);
	utils_log_test();
	assert(1);
	//assert(1 == 2); //assert(1 == 2) failed, main.c main() line=24
	//crash_with_log(); //crash_with_log() main.c main() line=25
	UNUSED(argc);

	LOGD("msleep before");
	msleep(100);
	LOGD("msleep after");

	// file
	file_delete("abc");

	assert(!file_is_file_exist("abc"));
	assert(file_is_file_exist("Makefile"));
	assert(!file_is_folder_exist("abc"));
	assert(file_is_folder_exist("utils"));
	LOGD("file_get_file_size(Makefile)=[%d]", file_get_file_size("Makefile"));

	assert(file_create_file("abc"));
	assert(file_is_file_exist("abc"));
	assert(file_delete("abc"));
	assert(!file_is_file_exist("abc"));

	assert(file_create_folder("abc"));
	assert(file_is_folder_exist("abc"));
	assert(file_delete("abc"));
	assert(!file_is_folder_exist("abc"));

	char buff[8192];
	memset(buff, 0, sizeof(buff));

	strcpy(buff, "hello world");
	assert(file_write("abc", buff, strlen(buff)));

	memset(buff, 0 , sizeof(buff));
	assert(file_read("abc", buff, sizeof(buff)));
	LOGD("file_read(abc) data=[%s]", buff);
	assert(strcmp("hello world", buff) == 0);

	assert(file_delete("abc"));

	// time
	LOGD("time_get_tick()=%lld", time_get_tick());
	LOGD("time_get_system_time()=%lld", time_get_system_time());

	long long tick = time_get_tick();
	long long sys_time = time_get_system_time();
	msleep(100);
	assert((time_get_tick() - tick) >= 100);
	assert((time_get_system_time() - sys_time) >= 100);


	return 0; //0~255
}
