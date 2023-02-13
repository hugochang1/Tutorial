#include <stdio.h>
#include <string.h>
#include <errno.h>

#define AAA
#if defined AAA
// this will take affect
#elif defined BBB
// this will not take affect
aaa
#else
// this will not take affect
aaa
#endif

#if !defined AAA
// this will not take affect
aaa
#endif

#if defined AAA && defined BBB
// this will not take affect
aaa
#endif

#if defined AAA || defined BBB
// this will take affect
#endif

#undef AAA
#if defined AAA
// this will not take affect
aaa
#endif

#define AAA 3
#if AAA == 3
// this will take affect
#endif

void demo_string_concatenate() {
    # define join(a,b) a##b
    int join(var,123); //int var123;
    var123 = 3;
}

void demo_standard_preprocessor() {
    printf("__FILE__=%s __FUNCTION__=%s __LINE__=%d\n", __FILE__, __FUNCTION__, __LINE__);
    //__FILE__=D:\VS Code Codebase\ws1\test.c __FUNCTION__=demo_standard_preprocessor __LINE__=48

    printf("__TIME__=%s __DATE__=%s\n", __TIME__, __DATE__);
    //__TIME__=10:59:21 __DATE__=Feb 13 2023
}

#define NDEBUG // disable assert
//#undef NDEBUG // enable assert (default)
#include <assert.h>
void demo_assert() {
    assert(0);
    /*
    Assertion failed!

    Program: D:\VS Code Codebase\ws1\test.exe
    File: D:\VS Code Codebase\ws1\test.c, Line 59

    Expression: 0
    */
}

#include <time.h>
void demo_time() {
    clock_t c;
    time_t t;
    
    printf("sizeof(clock_t)=%zu sizeof(time_t)=%zu\n",
        sizeof(clock_t), sizeof(time_t));
    //sizeof(clock_t)=4 sizeof(time_t)=8

    // clock_t clock(void)
    //   get system clock counted from the beginning of this problem
    //   the unit depedns on CLOCKS_PER_SEC
    //   for sample if CLOCKS_PER_SEC=1000, the unit is millisecond
    c = clock();
    printf("clock() returns %llu\n", c);
    printf("CLOCKS_PER_SEC=%d", CLOCKS_PER_SEC); // CLOCKS_PER_SEC=1000
    printf("change to second %f\n", (float)c / CLOCKS_PER_SEC);

    // time_t time(time_t *t)
    //   get the system time started from 00:00:00 UTC1970/1/1
    //   the unit is the second
    t = time(NULL); // get current time
    printf("time(NULL) returns %llu\n", t);
    //time(NULL) returns 1676258214
    
    // char *ctime(const time_t *timer)
    printf("ctime()=%s\n", ctime(&t));
    //ctime()=Mon Feb 13 11:19:10 2023
}

/*********************************
           main
 ********************************/
int main() {
    demo_string_concatenate();
    demo_standard_preprocessor();
    demo_assert();
    demo_time();
    return 0;
}
