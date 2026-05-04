#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//0013_RomanToInteger

// I 1 V
// V 5
// X 10 V
// L 50
// C 100 V
// D 500
// M 1000 V

// 4 IV
// 9 IX
// 40 XL
// 90 XC
// 400 CD
// 900 CM

int solution(string str) {
    int n = str.size();
    int ret = 0;
    int i = 0;
    while(i < n) {
        if(str[i] == 'M') {
            ret += 1000;
        } else if(str[i] == 'C') {
            if(i + 1 < n && str[i+1] == 'M') {
                ret += 900;
                i++;
            } else if(i + 1 < n && str[i+1] == 'D') {
                ret += 400;
                i++;
            } else {
                ret += 1000;
            }
        } else if(str[i] == 'X') {
            if(i + 1 < n && str[i+1] == 'L') {
                ret += 40;
                i++;
            } else if(i + 1 < n && str[i+1] == 'C') {
                ret += 90;
                i++;
            } else {
                ret += 10;
            }
        } else if(str[i] == 'I') {
            if(i + 1 < n && str[i+1] == 'X') {
                ret += 9;
                i++;
            } else if(i + 1 < n && str[i+1] == 'V') {
                ret += 4;
                i++;
            } else {
                ret += 1;
            }
        } else if(str[i] == 'D') {
            ret += 500;
        } else if(str[i] == 'L') {
            ret += 50;
        } else if(str[i] == 'V') {
            ret += 5;
        }
        i++;
    }
    return ret;
}

int main() {
    printf("%d\n", solution("III")); //3
    printf("%d\n", solution("IV")); //4
    printf("%d\n", solution("IX")); //9
    printf("%d\n", solution("LVIII")); //58
    printf("%d\n", solution("MCMXCIV")); //1994
    return 0;
}
