#include <pthread.h>
#include "utils.h"

void* thread_routine(void* arg) {
	LOGD("thread_routine()");
	LOGD("arg=[%s]", arg);

	// set detach to avoid memory leak
	int ret = pthread_detach(pthread_self());
	if(ret != 0) {
		LOGE("pthread_detach() failed, reason=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}

	// do what you want to do here

	return NULL;
}

void demo_pthread() {
	LOGD("demo_pthread()");

	int ret;
	pthread_t thread1;
	ret = pthread_create(&thread1, NULL, thread_routine, "hello");
	if (ret != 0) {
		LOGE("pthread_create() failed ret=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}
	
	pthread_join(thread1, NULL);
}
