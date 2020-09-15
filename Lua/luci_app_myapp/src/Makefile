include $(TOPDIR)/rules.mk

OBJS = my_app.o

CFLAGS += -I. -Wall -shared -fPIC

MY_APP_TARGET = my_app

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(MY_APP_TARGET)

$(MY_APP_TARGET): $(OBJS)
	$(CC) -o $@.so $^ $(CFLAGS)

compile: $(MY_APP_TARGET)

install: compile
	mkdir -p $(DESTDIR)/usr/lib/lua
	cp -pR my_app.so $(DESTDIR)/usr/lib/lua/

clean:
	rm -f *.o *.so

romfs:
