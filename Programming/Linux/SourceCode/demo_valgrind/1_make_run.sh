make clean
make
#valgrind --leak-check=yes ./test
valgrind --leak-check=full --log-file=valgrind.log ./test
#valgrind --leak-check=full --log-file=valgrind.log --show-leak-kinds=all ./test -l xxx.so
cat valgrind.log
