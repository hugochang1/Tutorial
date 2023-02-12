#include <stdio.h>

/*********************************
           struct
 ********************************/
struct student {
    int id;
    int age;
};
// struct student s;
// struct student s = {.id=3, .age=5 };
// sizeof(struct student)=8
// s.id = 5;

typedef struct student student_t;
// student_t s;

typedef struct {
    int id;
    int age;
} student5;
// student5 s;
// student5 s = { .id=3, .age=5 };
// student5 s = { 3, 5 };

typedef struct student6 {
    int id;
    int age;
} student6;
// struct student6 s;
// student6 s;

struct student2 {
    int id;
    int age;
} s3; // s3 is a variable and can be used directly
// struct student2 s;
// s3.id = 5;

struct student3 {
    int id;
    int age;
} s4, s5; // no need to declare s4, s5
// s4.id = 1; s5.id=2;

struct student4 {
    int id:16; // id uses only 16-bit
    int age:8; // age uses only 8-bit
};
// sizeof(struct student4)=4

/*********************************
           enum
 ********************************/
enum fruit {
    apple,  //0
    banana, //1
    lemon,  //2
};
//enum fruit f = lemon;
//sizeof(enum fruit)=4

typedef enum car1 {
    CAR_1,
    CAR_2,
} car2;
//enum car1 c;
//car2 c;

typedef enum good {
    GOOD_1,
    GOOD_2,
} good;
// enum good g;
// good g

enum type {
    type_1 = 1,
    type_2 = 2,
    type_3,      //3
    type_10 = 10,//10
    type_11,     //11
};

/*********************************
           union
 ********************************/
union u1 {
    int a;
    char name[32];
};
// union u1 u;
// sizeof(union u1)=32

typedef union u1 uu;
// uu u;

typedef union u2 {
    int a;
    char name[32];
} u2;
// u2 u;

/*********************************
           main
 ********************************/
int main() {
    struct student6 s = {12, 34};
    printf("id=%d age=%d\n", s.id, s.age);
    return 0;
}