obj-m := hugo.o
hugo-objs := \
  hugo1.o \
  hugo2.o \

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean