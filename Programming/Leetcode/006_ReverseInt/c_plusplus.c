#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int solution(int num) {
    int ret = 0;
    bool negative = false;
    if(num < 0) {
        negative = true;
        num = -num;
    }
    
    while(num > 0) {
        int pre = ret;
        ret *= 10;
        if(ret/10 != pre) return 0;
        ret += num % 10;
        num /= 10;
    }
    
    if(negative) {
        ret = -ret;
    }
    
    return ret;
}

int main() {
    printf("%d\n", solution(123)); //321
    printf("%d\n", solution(-123)); //-321
    printf("%d\n", solution(120)); //21
    printf("%d\n", solution(1234567899)); //0
    return 0;
}
