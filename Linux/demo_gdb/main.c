#include "stdio.h"

typedef struct {
  char a1;
  short a2;
} my_struct1;

typedef struct {
  int a;
  int b;
  char c[32];
  my_struct1 d;
}

typedef enum {
  ENUM_A = 0,
  ENUM_B = 1,
  ENUM_C = 2,
} my_enum

static my_enum en = ENUM_B;
static my_struct2 s;

void crash_here() {
  char* crash = NULL;
  *crash = 1;
}

int main() {
  printf("gdb demo program started\n");
  crash_here();
  printf("end\n");
}
