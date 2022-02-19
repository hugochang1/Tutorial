#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> //usleep

#include <sys/types.h> //getpid
#include <unistd.h> //getpid

#define UNUSED(x) (void)(x)
#define msleep(interval) usleep((interval)*1000);

void alloc() {
	int i = 0;
	for(i = 0; i < 20; i++) {
		char* data = (char*)malloc(2048);
		UNUSED(data);
		//free(data);
	}
}

int main() {
	printf("you can terminate this program by\n");
	printf("[Method 1] Press the enter key\n");
	printf("[Method 2] # kill -term %d\n", getpid());

	int i = 0;
	for(i = 0; i < 10; i++) {
		char* data = (char*)malloc(1024);
		UNUSED(data);
		//free(data);
	}

	alloc();

	//wait for the enter key
	getchar();

	return 0;
}
