#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//0043_MultiplyString

int string2int(string s) {
    int ret = 0;
    for(auto& c:s) {
        ret *= 10;
        ret += c - '0';
    }
    return ret;
}

string solution(string s1, string s2) {
    string ret;
    int n1 = string2int(s1);
    int n2 = string2int(s2);
    int product = n1 * n2;
    if(product == 0) {
        ret = "0";
    } else {
        while(product > 0) {
            char ch = (product % 10) + '0';
            ret =  ch + ret;
            product /= 10;
        }
    }
    return ret;
}

int main() {
    printf("%s\n", solution("2", "3").c_str()); //6
    printf("%s\n", solution("123", "456").c_str()); //56088
    return 0;
}
