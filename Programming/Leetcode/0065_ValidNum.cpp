#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//0065_ValidNum

bool solution(string str) {
    int state = 0;
    for(auto& c:str) {
        if(state == 0) {
            if(c == ' ') {
            } else if(c == '+' || c == '-') {
                state = 2;
            } else if(c >= '0' && c <= '9') {
                state = 2;
            } else {
                return false;
            }
        } else if(state == 1) {
            if(c == '+' || c == '-') {
                state = 2;
            } else if(c >= '0' && c <= '9') {
                state = 2;
            } else {
                return false;
            }
        } else if(state == 2) {
            if(c >= '0' && c <= '9') {
            } else if(c == '.') {
                state = 3;
            } else if(c == 'e') {
                state = 4;
            } else {
                return false;
            }
        } else if(state == 3) {
            if(c >= '0' && c <= '9') {
            } else if(c == 'e') {
                state = 4;
            } else {
                return false;
            }
        } else if(state == 4) {
            if(c >= '0' && c <= '9') {
                state = 6;
            } else if(c == '+' || c== '-') {
                state = 5;
            } else {
                return false;
            }
        } else if(state == 5) {
            if(c >= '0' && c <= '9') {
                state = 6;
            } else {
                return false;
            }
        } else if(state == 6) {
            if(c >= '0' && c <= '9') {
            } else {
                return false;
            }
        }
    }
    
    if(state == 4 || state == 5) return false;
    return true;
}

int main() {
    printf("%d\n", solution("0")); //1
    printf("%d\n", solution("0.1")); //1
    printf("%d\n", solution("2e10")); //1
    printf("%d\n", solution(" -90e3")); //1
    printf("%d\n", solution(" 6e-1")); //1
    printf("%d\n", solution("53.5e93")); //1
    printf("\n");
    printf("%d\n", solution("abc")); //0
    printf("%d\n", solution("1 a")); //0
    printf("%d\n", solution(" 1e")); //0
    printf("%d\n", solution("e3")); //0
    printf("%d\n", solution(" 99e2.5")); //0
    printf("%d\n", solution(" --6")); //0
    printf("%d\n", solution("+-3")); //0
    printf("%d\n", solution("95a54e53")); //0
    return 0;
}
