TODO:
1. 32-bit vs 64-bit
gcc -m32

2. How to print int64 in c
https://stackoverflow.com/questions/9225567/how-to-print-a-int64-t-type-in-c

3. build warning for timer_t to cast to int64_t
gcc -g -c -I./ -I./utils/  -g -Wall -D __COMPILE_OPTION__ -m32  -o utils/utils.o utils/utils.c
utils/utils.c: In function âtimer_initâ:
utils/utils.c:306:12: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]
     return (int64_t)timerid;

