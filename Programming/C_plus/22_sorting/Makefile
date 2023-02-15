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
  main.cpp \

CSRC=\

EXECUTABLE=test
COBJS=$(CSRC:.c=.o)
CXXOBJS=$(CXXSRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(COBJS) $(CXXOBJS)
	$(CXX) $(COBJS) $(CXXOBJS) $(LIBS) $(FLAGS) $(CPPFLAGS) -o $@

%.o : %.c
	$(CXX) -c $(FLAGS) $(INCLUDE) -o $@ $<

%.o : %.cpp
	$(CXX) -c $(FLAGS) $(INCLUDE) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) rm -rf *.o
	find ./ -name *.o | xargs rm -rf
