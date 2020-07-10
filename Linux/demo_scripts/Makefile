CC=gcc
CXX=g++

FLAGS=\
  -g \
  -Wall \
  -D __COMPILE_OPTION__ \

CPPFLAGS=\
  -std=c++11 \

INCLUDE=\
  -I./ \

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
	$(CXX) $(COBJS) $(CXXOBJS) $(LIBS) $(FLAGS) -o $@

%.o : %.c
	$(CC) -g -c $(INCLUDE) $(FLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) -g -c $(INCLUDE) $(FLAGS) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) rm -rf *.o
	find ./ -name *.o | xargs rm -rf
