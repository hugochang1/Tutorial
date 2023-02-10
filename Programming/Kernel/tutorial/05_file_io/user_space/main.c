#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h> //strerror
#include <fcntl.h> // open
#include <unistd.h> // close, getpid
#include <sys/ioctl.h>
#include <poll.h>
#include "hugo_ioctl.h"

#define HUGO_DEV "/dev/hugo_dev0"

void dump_buff(char *buff, int size) {
	int i = 0;
	printf("dump_buff() size=%d\n", size);
	for(i = 0; i < size; i++) {
		printf("%02x ", buff[i] & 0xff);
	}
	printf("\n");
}

int poll_io_test() {
	int fd;
	struct pollfd fds;
	int ret;
	char buff[128];
	
	//open
	fd = open(HUGO_DEV,  O_RDWR | O_NONBLOCK);
	if (fd == -1) {
		printf("open() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	
	fds.fd = fd;
	fds.events = POLLIN;
	
	//poll
	printf("poll()...\n");
	ret = poll(&fds, 1, 1000);
	printf("poll() after ret=%d\n", ret);
	if (ret == -1) {
		printf("poll() failed, errno=%d %s\n", errno, strerror(errno));
		goto exit;
	}
	if (ret == 0) {
		printf("poll() timeout\n");
		goto exit;
	}
	
	//read
	printf("revents=0x%x\n", fds.revents);
	if (fds.revents & POLLIN) {
		printf("read()...\n");
		ret = read(fd, buff, sizeof(buff));
		printf("read() ret=%d\n", ret);
		dump_buff(buff, ret);
	}
	
	//poll
	printf("poll()...\n");
	ret = poll(&fds, 1, 1000);
	printf("poll() after ret=%d\n", ret);
	if (ret == -1) {
		printf("poll() failed, errno=%d %s\n", errno, strerror(errno));
		goto exit;
	}
	if (ret == 0) {
		printf("poll() timeout\n");
		goto exit;
	}
	
	//read
	printf("revents=0x%x\n", fds.revents);
	if (fds.revents & POLLIN) {
		printf("read()...\n");
		ret = read(fd, buff, sizeof(buff));
		printf("read() ret=%d\n", ret);
		dump_buff(buff, ret);
	}

exit:
	//close
	ret = close(fd);
	if (ret == -1) {
		printf("close() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	return 0;
}

int ioctl_test() {
	int fd, ret;
	struct hugo_ioctl_cmd cmd = {.d1=2};

	//open
	fd = open(HUGO_DEV,  O_RDWR);
	if (fd == -1) {
		printf("open() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	
	//ioctl SET
	ret = ioctl(fd, HUGO_IOCTL_SET, &cmd);
	printf("ioctl() SET ret=%d\n", ret);
	if (ret == -1) {
		printf("ioctl() SET failed, errno=%d %s\n", errno, strerror(errno));
	}
	//ioctl GET
	ret = ioctl(fd, HUGO_IOCTL_GET, &cmd);
	printf("ioctl() GET ret=%d d1=%d\n", ret, cmd.d1);
	if (ret == -1) {
		printf("ioctl() GET failed, errno=%d %s\n", errno, strerror(errno));
	}
	//ioctl SU
	ret = ioctl(fd, HUGO_IOCTL_SU);
	printf("ioctl() SU ret=%d\n", ret);
	if (ret == -1) {
		printf("ioctl() SU failed, errno=%d %s\n", errno, strerror(errno));
	}
	//ioctl UNKNOWN
	ret = ioctl(fd, 0x12345678);
	printf("ioctl() UNKNOWN ret=%d\n", ret);
	if (ret == -1) {
		printf("ioctl() UNKNOWN failed, errno=%d %s\n", errno, strerror(errno));
	}
	
	//close
	ret = close(fd);
	if (ret == -1) {
		printf("close() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	return 0;
}

int simple_io_test(int open_flag) {
	int fd, ret;
	char buff[128];
	char sbuff[6];
	
	//open
	fd = open(HUGO_DEV,  open_flag);
	if (fd == -1) {
		printf("open() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	
	//write
	strcpy(buff, "hello from client");
	ret = write(fd, buff, strlen(buff) + 1); //for null-terminated string
	if (ret < 0) {
		printf("write() failed, errno=%d %s\n", errno, strerror(errno));
	}
	printf("write() ret=%d\n", ret);
		
	//read with small buff
	memset(sbuff, 0, sizeof(sbuff));
	printf("read...\n");
	ret = read(fd, sbuff, sizeof(sbuff));
	if (ret < 0) {
		printf("read() failed, errno=%d %s\n", errno, strerror(errno));
	}
	dump_buff(sbuff, ret);
		
	//read with big buff
	memset(buff, 0, sizeof(buff));
	printf("read...\n");
	ret = read(fd, buff, sizeof(buff));
	if (ret < 0) {
		printf("read() failed, errno=%d %s\n", errno, strerror(errno));
	}
	dump_buff(buff, ret);
		
	//close
	ret = close(fd);
	if (ret == -1) {
		printf("close() failed, errno=%d %s\n", errno, strerror(errno));
		return -1;
	}
	
	return 0;
}

int main() {
	printf("main() pid=%d\n", getpid());

	printf("-------------------- ioctl_test() --------------------\n");
	ioctl_test();
	/*
	-------------------- ioctl_test() --------------------
	ioctl() SET ret=0
	ioctl() GET ret=0 d1=2
	ioctl() SU ret=-1 d1=2
	ioctl() SU failed, errno=1 Operation not permitted
	ioctl() UNKNOWN ret=-1
	ioctl() UNKNOWN failed, errno=25 Inappropriate ioctl for device
	*/

	printf("-------------------- simple_io_test(O_RDWR) --------------------\n");
	simple_io_test(O_RDWR);
	/*
	-------------------- simple_io_test(O_RDWR) --------------------
	main() pid=5373
	write() ret=18
	read...
	dump_buff() size=6
	f0 f1 f2 f3 f4 f5 
	read...
	dump_buff() size=8
	f0 f1 f2 f3 f4 f5 f6 f7 

	[dmesg]
	[  898.615587] hugo_open() major=240 minor=0 pid=5373 ctx=000000003a0f0a5f flags=0x8002
	[  898.615593] hugo_write() pid=5373 ctx=000000003a0f0a5f count=18 buf=[hello from client]
	[  898.615598] hugo_read() pid=5373 ctx=000000003a0f0a5f count=6 buf=00000000991a5c07  
	[  899.129006] timer_func() pid=5373
	[  899.129131] after wait_event_interruptible() ret=0
	[  899.129174] hugo_read() pid=5373 ctx=000000003a0f0a5f count=128 buf=000000003dc5fb7b  
	[  899.641149] timer_func() pid=5373
	[  899.641263] after wait_event_interruptible() ret=0
	[  899.641346] hugo_release() major=240 minor=0 pid=5373 ctx=000000003a0f0a5f
	*/

	printf("-------------------- simple_io_test(O_RDWR | O_NONBLOCK) --------------------\n");
	simple_io_test(O_RDWR | O_NONBLOCK);
	/*
	-------------------- simple_io_test(O_RDWR | O_NONBLOCK) --------------------
	main() pid=5373
	write() ret=18
	read...
	read() failed, errno=11 Resource temporarily unavailable
	dump_buff() size=-1

	read...
	read() failed, errno=11 Resource temporarily unavailable
	dump_buff() size=-1

	[dmesg]
	[  899.641379] hugo_open() major=240 minor=0 pid=5373 ctx=00000000507aedcc flags=0x8802
	[  899.641384] hugo_write() pid=5373 ctx=00000000507aedcc count=18 buf=[hello from client]
	[  899.641388] hugo_read() pid=5373 ctx=00000000507aedcc count=6 buf=00000000991a5c07  
	[  899.641460] hugo_read() pid=5373 ctx=00000000507aedcc count=128 buf=000000003dc5fb7b  
	[  899.641465] hugo_release() major=240 minor=0 pid=5373 ctx=00000000507aedcc
	*/

	printf("-------------------- poll_io_test() --------------------\n");
	poll_io_test();
	/*
	-------------------- poll_io_test() --------------------
	poll()...
	poll() after ret=1
	revents=0x1
	read()...
	read() ret=8
	dump_buff() size=8
	f0 f1 f2 f3 f4 f5 f6 f7 
	poll()...
	poll() after ret=1
	revents=0x1
	read()...
	read() ret=8
	dump_buff() size=8
	f0 f1 f2 f3 f4 f5 f6 f7 
	
	[dmesg]
	[ 9302.793551] hugo_open() major=240 minor=0 pid=13243 ctx=00000000a865bb6f flags=0x8802
	[ 9302.793556] after poll_wait() has_data=0
	[ 9303.305083] timer_func() pid=13243
	[ 9303.305122] after poll_wait() has_data=1
	[ 9303.305153] hugo_read() pid=13243 ctx=00000000a865bb6f count=128 buf=000000001e272e6d  
	[ 9303.305160] after poll_wait() has_data=0
	[ 9303.817232] timer_func() pid=13243
	[ 9303.817283] after poll_wait() has_data=1
	[ 9303.817321] hugo_read() pid=13243 ctx=00000000a865bb6f count=128 buf=000000001e272e6d  
	[ 9303.817330] hugo_release() major=240 minor=0 pid=13243 ctx=00000000a865bb6f
	*/

	return 0;
}
