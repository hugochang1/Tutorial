#include <stdio.h>
#include <stdlib.h>

int reverseInt(int value) {
    bool positive = value >= 0;
    int ret = 0;
    int pre = 0;
    
    if(!positive) value = -value;
    
    while(value > 0) {
        pre = ret;
        ret *= 10;
        if (pre != ret / 10) return 0;
        ret += value % 10;
        value /= 10;
    }
    
    if (!positive) ret = -ret;
    return ret;
}

int main() {
    int ret = reverseInt(-123);
    printf("ret=%d\n", ret);
    return 0;
}
