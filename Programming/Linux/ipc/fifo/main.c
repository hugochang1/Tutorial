#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//for mkfifo
#include <sys/types.h>
#include <sys/stat.h>

//for open/close
#include <fcntl.h>
#include <unistd.h>

void test_fifo_read_write(const char* filename) {
	int ret;
	int r, w;
	char buff[65535] = {0};
	int i = 0;
	
	//reader must be prior than writer, or writer's open() will be failed
	r = open(filename, O_RDONLY | O_NONBLOCK);
	printf("r=%d\n", r);
	if (r == -1) {
		printf("open() failed, reason=[%s]%d\n", strerror(errno), errno);
	} else {
		printf("open() r success\n");
	}
	
	w = open(filename, O_WRONLY | O_NONBLOCK);
	printf("w=%d\n", w);
	if (w == -1) {
		printf("open() failed, reason=[%s]%d\n", strerror(errno), errno);
	} else {
		printf("open() w success\n");
	}
	
	for (i = 0; i < 100000; i++) {
		printf("write() i=%d\n", i);
		//the max buffer size is 65536 Bytes
		ret = write(w, buff, sizeof(buff));
		if (ret <= 0) {
			printf("write failed ret=%d, reason=[%s]%d\n", ret, strerror(errno), errno);
			break;
		}
	}
    
	ret = read(r, buff, sizeof(buff));
	printf("read() ret=%d buff=[%s]\n", ret, buff);
	
	close(r);
	close(w);
}

void test_fifo() {
	char filename[] = "./gggg";
	int ret;
	
	ret = mkfifo(filename, 0777);
	if (ret == -1) {
		printf("mkfifo() fail, errno=[%s]%d\n", strerror(errno), errno);
	} else {
		printf("mkfifo() success\n");
	}
	
	test_fifo_read_write(filename);
	
	remove(filename);
}
