#include "utils.h"

void demo_semaphore() {
	LOGD("demo_semaphore()");
	int ret;

	//------------------ demo mutex -------------------
	pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
	//or
	ret = pthread_mutex_init(&mutex1, NULL);
	if(ret != 0) {
		LOGE("pthread_mutex_init() failed reason=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}

	ret = pthread_mutex_lock(&mutex1);
	if(ret != 0) {
		LOGE("pthread_mutex_lock() failed reason=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}

	ret = pthread_mutex_unlock(&mutex1);
	if(ret != 0) {
		LOGE("pthread_mutex_unlock() failed reason=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}

	ret = pthread_mutex_destroy(&mutex1);
	if(ret != 0) {
		LOGE("pthread_mutex_destroy() failed reason=[%s]%d", strerror(ret), ret);
		crash_with_log();
	}

	//------------------ demo semaphore -------------------
	sem_t sem;
	ret = sem_init(&sem, 0 /*pshared*/, 0 /*value*/);
	if(ret != 0) {
		LOGE("sem_init() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}

	ret = sem_post(&sem);
	if(ret != 0) {
		LOGE("sem_post() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}

	int value = 0;
	ret = sem_getvalue(&sem, &value);
	if(ret != 0) {
		LOGE("sem_getvalue() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}
	LOGD("sem_getvalue()=%d", value);

	ret = sem_wait(&sem);
	if(ret != 0) {
		LOGE("sem_wait() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}

	ret = sem_destroy(&sem);
	if(ret != 0) {
		LOGE("sem_destroy() failed reason=[%s]%d", strerror(errno), errno);
		crash_with_log();
	}
}
