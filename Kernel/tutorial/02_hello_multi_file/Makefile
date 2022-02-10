CFILES := \
  hugo1.c \
  hugo2.c \

obj-m := hugo.o

hugo-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean