#include <sys/ioctl.h>

//to avoid use long or point due to they are different in 32-bit CPU architecture and 64-bit CPU architecture

struct hugo_ioctl_cmd {
	int d1;
};

#define HUGO_IOCTL_GET _IOR('d', 1, struct hugo_ioctl_cmd)
#define HUGO_IOCTL_SET _IOW('d', 2, struct hugo_ioctl_cmd)
#define HUGO_IOCTL_SU _IOW('d', 3, struct hugo_ioctl_cmd)

