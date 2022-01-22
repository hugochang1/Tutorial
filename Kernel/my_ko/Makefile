KDIR=/lib/modules/5.4.0-94-generic/build

obj-m += hello.o

all:
	$(MAKE) -C $(KDIR)  M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR)  M=$(PWD) clean

