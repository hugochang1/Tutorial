# dump all variables
# $(foreach v, $(.VARIABLES), $(info $(v) = $($(v))))

# set variable
MY_FLAG = yes

# dump variable
$(warning  MY_FLAG=$(MY_FLAG))

# if else
ifeq (no, $(MY_FLAG))
  $(warning  MY_FLAG is no)
else ifneq (yes, $(MY_FLAG))
  $(warning  MY_FLAG is not yes)
else
  $(warning  else case)
endif

# check if file or folder exists in hard code
ifneq (,$(wildcard Makefile))
  $(warning Makefile exist)
endif

# check if file or folder exists in variable
MY_FILE_PATH=aaaa
ifneq (,$(wildcard $(MY_FILE_PATH)))
  $(warning $(MY_FILE_PATH) exist)
else
  $(warning $(MY_FILE_PATH) not exist)
endif

#----------------------------------------------------

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
	$(CXX) $(COBJS) $(CXXOBJS) $(LIBS) $(FLAGS) $(CPPFLAGS) -o $@

%.o : %.c
	$(CC) -g -c $(INCLUDE) $(FLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) -g -c $(INCLUDE) $(FLAGS) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) rm -rf *.o
	find ./ -name *.o | xargs rm -rf
