CC=gcc
CXX=g++

FLAGS=\
  -g \
  -Wall \
  -D __COMPILE_OPTION__ \
#  -m32 \
CPPFLAGS=\
  -std=c++11 \

INCLUDE=\
  -I./ \
  -I./utils/ \

LIBS=\
  -ldl \
  -lrt \
  -lpthread \

CXXSRC=\

CSRC=\
  main.c \

EXECUTABLE=test
COBJS=$(CSRC:.c=.o)
CXXOBJS=$(CXXSRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(COBJS) $(CXXOBJS)
	$(CC) $(COBJS) $(CXXOBJS) $(LIBS) $(FLAGS) $(CPPFLAGS) -o $@

%.o : %.c
	$(CC) -c $(FLAGS) $(INCLUDE) -o $@ $<

%.o : %.cpp
	$(CC) -c $(FLAGS) $(INCLUDE) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) rm -rf *.o
	find ./ -name *.o | xargs rm -rf
