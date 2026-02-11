#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

#ifdef LOGD
#undef LOGD
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGE
#undef LOGE
#endif
#define LOGD(...) my_log("[TAG]D", __VA_ARGS__);
#define LOGW(...) my_log("[TAG]W", __VA_ARGS__);
#define LOGE(...) my_log("[TAG]E", __VA_ARGS__);

void my_log(const char* tag, const char *fmt, ...) {
    // get time
    struct timeval tv;
    struct timezone tz;
    struct tm *tm;
    char time_str[32];
    
    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);
    if (tm != NULL) {
        snprintf(time_str, sizeof(time_str),
        "%04d-%02d-%02d %02d:%02d:%02d.%03d",
        tm->tm_year + 1900, 1 + tm->tm_mon, tm->tm_mday, tm->tm_hour,
        tm->tm_min, tm->tm_sec, (int)(tv.tv_usec / 1000));
    }
    
    // print
    char buff[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buff, sizeof(buff), fmt, ap);
    va_end(ap);
    printf("%s %s %s", time_str, tag, buff);
}

int main() {
    LOGD("Test: %d, %s\n", 100, "abc"); // 2026-02-11 00:36:08.953 [TAG]D Test: 100, abc
    LOGW("LOGW\n"); // 2026-02-11 00:36:08.953 [TAG]W LOGW
    LOGD("LOGD\n"); // 2026-02-11 00:36:08.953 [TAG]D LOGD
    return 0;
}
