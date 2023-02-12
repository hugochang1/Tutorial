#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <math.h>
#include <stdbool.h> //true, false

void fun1() {}
void fun2() { return; }
int fun3() { return 1; }
void fun4(int a) {}

int* fun5() {
    int* ip;
    ip = (int*)malloc(sizeof(int));
    *ip = 123;
    return ip;
}

void* fun6() {
    double *dp;
    dp = (double*)malloc(sizeof(double));
    *dp = -123.456;
    return (void*)dp;
}

void fun10(int* a) {
    *a = 123;
}

void fun_strs(char **strs, int n) {
    for (int i = 0; i < n; i++) {
        printf("str[%d]=[%s]\n", i, strs[i]);
        /*
        str[0]=[hello]
        str[1]=[world]
        str[2]=[gg!!]
        */
    }
}

void my_callback(int a) {
    printf("my_callback() a=%d\n", a);
}

void demo_callback() {
    void (*p_function) (int a);

    p_function = my_callback;
    p_function(123); // my_callback() a=123
}

long long factorial(int n) {
    if (n < 2)
        return n;
    else
        return n * factorial(n-1);
}

#include<stdarg.h>

void demo_various_parameter(int a1, int a2, ...) {
    va_list parg;
    va_start(parg, a2);
    int value = 0;

    printf("a1=%d a2=%d\n", a1, a2); // a1=1 a2=2
    while ((value = va_arg(parg, int)) != 0) {
        printf("value=%d\n", value);
        /*
        value=3
        value=4
        value=5
        value=6
        value=7
        value=8
        */
    }
    va_end(parg);
}

int main(int argc, char *argv[]) {
    printf("argc=%d\n", argc); // argc=1
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]=%s\n", i, argv[i]); // argv[0]=./test
    }
    
    {
        int *ip = NULL;
        ip = fun5();
        printf("ip=%d\n", *ip);
        free(ip);  // ip=123
    }

    {
        double* dp = NULL;
        dp = fun6();
        printf("dp=%lf\n", *dp); // dp=-123.456000
        free(dp);
    }
    
    {
        int a = 0;
        fun10(&a);
        printf("a=%d\n", a); // a=123
    }
    
    {
        char *strs[] = {"hello", "world", "gg!!"};
        fun_strs(strs, 3);
    }

    demo_callback();

    printf("factorial(20)=%lld\n", factorial(20)); // factorial(20)=2432902008176640000

    demo_various_parameter(1,2,3,4,5,6,7,8,0); // which 0 is the ended condition

    return 0;
}

