#include <stdio.h>
#include <stdlib.h>

int reverseInt(int value) {
    int ret = 0;
    int pre = 0;
    bool positive = true;
    if (value < 0) {
        positive = false;
        value = -value;
    }
    
    while(value) {
        pre = ret;
        ret *= 10;
        if (ret/10 != pre) return 0;
        ret += value % 10;
        value /= 10;
    }
    
    if (!positive) {
        ret = -ret;
    }
    return ret;
}

int main() {
    int ret;
    ret = reverseInt(123456789);
    printf("ret=%d\n", ret); //987654321
    
    ret = reverseInt(-123456789);
    printf("ret=%d\n", ret); //-987654321
    
    ret = reverseInt(1234567899);
    printf("ret=%d\n", ret); //0
    
    ret = reverseInt(-1234567899);
    printf("ret=%d\n", ret); //0
    return 0;
}
