#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//008_StringToInteger

int solution(string str) {
    long long ret = 0;
    bool got_sign = false;
    bool positive = true;
    for(auto c:str) {
        if(c == ' ') {
            continue;
        } else if(c == '-') {
            if(!got_sign) {
                positive = false;
                got_sign = true;
            }
            continue;
        } else if(c >= '0' && c <= '9') {
            ret *= 10;
            ret += c - '0';
            if(positive) {
                if(ret > 0x7fffffff) {
                    ret = 0x7fffffff;
                }
            } else {
                if(ret > 0x80000000) {
                    ret = 0x80000000;
                }
            }
        } else {
            break;
        }
    }
    
    if(!positive) {
        ret = -ret;
    }
    return ret;
}

int main() {
    printf("%d\n", solution("42")); //42
    printf("%d\n", solution("   42")); //42
    printf("%d\n", solution("-42")); //-42
    printf("%d\n", solution("4193 with words")); //4193
    printf("%d\n", solution("words 123")); //0
    printf("%d\n", solution("-91283472332")); //-2147483648
    printf("%d\n", solution("91283472332")); //2147483647
    return 0;
}
