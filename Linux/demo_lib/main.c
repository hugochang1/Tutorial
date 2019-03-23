#include <stdio.h>
#include "abc1.h"
#include "abc2.h"
#include "abc3.h"
#include "abc4.h"

int main() {
	printf("main start\n");

	printf("abc1=%d\n", abc1(1, 2));
	printf("abc2=%d\n", abc2(2, 3));
	printf("abc3=%d\n", abc3(3, 2));
	printf("abc4=%d\n", abc4(6, 2));

	return 0;
}

