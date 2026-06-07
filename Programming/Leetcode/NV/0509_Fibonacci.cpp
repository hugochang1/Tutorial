#include <stdio.h>

using namespace std;
//509_FibonacciNumber

//time complexity: O(n), space complexity: O(1)
int fibnoacci(int i) {
    if(i == 0) return 0;
    if(i == 1) return 1;
    int pre = 0;
    int cur = 1;

    for(int k = 2; k <= i; k++) {
        int tmp = cur;
        cur += pre;
        pre = tmp;
    }
    return cur;
}

int main() {
    for(int i = 0; i <= 10; i++) {
        printf("i=%d ret=%lld\n", i, fibnoacci(i));
    }
    /*
    i=0 ret=0
    i=1 ret=1
    i=2 ret=1
    i=3 ret=2
    i=4 ret=3
    i=5 ret=5
    i=6 ret=8
    i=7 ret=13
    i=8 ret=21
    i=9 ret=34
    i=10 ret=55
    */
    return 0;
}
