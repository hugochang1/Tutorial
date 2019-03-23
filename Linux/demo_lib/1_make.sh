# build shared_lib_c
gcc -fPIC -c shared_lib_c/abc1.c -o shared_lib_c/abc1.o
ld -shared   shared_lib_c/abc1.o -o shared_lib_c/libabc1.so

# build shared_lib_cpp
g++ -fPIC -c shared_lib_cpp/abc2.cpp -o shared_lib_cpp/abc2.o
ld -shared   shared_lib_cpp/abc2.o   -o shared_lib_cpp/libabc2.so

# build static_lib_c
gcc -c static_lib_c/abc3.c -o static_lib_c/abc3.o
ar rcs static_lib_c/libabc3.a static_lib_c/abc3.o

# build static_lib_cpp
g++ -c static_lib_cpp/abc4.cpp -o static_lib_cpp/abc4.o
ar rcs static_lib_cpp/libabc4.a   static_lib_cpp/abc4.o

# build main
gcc -c main.c -o main.o -I./shared_lib_c -I./shared_lib_cpp -I./static_lib_c -I./static_lib_cpp
gcc -o main main.o shared_lib_c/libabc1.so shared_lib_cpp/libabc2.so static_lib_c/libabc3.a static_lib_cpp/libabc4.a

LD_LIBRARY_PATH=. ./main
