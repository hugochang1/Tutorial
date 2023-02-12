#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <math.h>
#include <stdbool.h> //true, false

#define UNUSED(x) (void)(x)

void demo_single_array() {
    int a[3];
    int b[3] = {1,2,3};
    int c[] = {4,5,6};
    int d[3] = {0}; // all zeros
    int e[3] = {1}; // e[] = {1, 0, 0}

    for (int i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("b[%d]=%d\n", i, b[i]);
        /*
        b[0]=1
        b[1]=2
        b[2]=3
        */
    }

    UNUSED(a);
    UNUSED(b);
    UNUSED(c);
    UNUSED(d);
    UNUSED(e);
}

void demo_two_dimension_array() {
    #define ARR_SIZE 3
    int m[ARR_SIZE][ARR_SIZE] = {0};
    int m2[ARR_SIZE][ARR_SIZE] = {{1,2,3},{4,5,6},{7,8,9}};

    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {
            m[i][j] = i*ARR_SIZE + j;
            printf("m[%d][%d]=%d\n", i, j, m[i][j]);
            /*
            m[0][0]=0
            m[0][1]=1
            m[0][2]=2
            m[1][0]=3
            m[1][1]=4
            m[1][2]=5
            m[2][0]=6
            m[2][1]=7
            m[2][2]=8
            */
        }
    }

    UNUSED(m2);
}

typedef struct my_struct {
    int a;
    int b;
    int c;
} my_struct;

void demo_pointer() {
    char* p = NULL;
    int* ip = NULL;
    my_struct* my_p = NULL;
    for (int i = 0; i < 3; i++) {
        printf("p=%p\n", p);
        /*
        p=(nil)
        p=0x1
        p=0x2
        */
        p++;
    }

    for (int i = 0; i < 3; i++) {
        printf("ip=%p\n", ip);
        /*
        ip=(nil)
        ip=0x4
        ip=0x8
        */
        ip++;
    }

    printf("sizeof(my_struct)=%zu\n", sizeof(my_struct)); // sizeof(my_struct)=12
    for (int i = 0; i < 3; i++) {
        printf("my_p=%p\n", my_p);
        /*
        my_p=(nil)
        my_p=0xc
        my_p=0x18
        */
        my_p++;
    }
}

int main(int argc, char *argv[]) {
    demo_single_array();
    demo_two_dimension_array();
    demo_pointer();
    return 0;
}

