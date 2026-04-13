#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//1328_BreakAPalindrome

string find(string str) {
    if(str.size() <= 1) return "";
    for(int i = 0; i < str.size()/2; i++) {
        if(str[i] != 'a') {
            str[i] = 'a';
            return str;
        }
    }
    str.back() = 'b';
    return str;
}

int main() {
    printf("%s\n", find("a").c_str()); //
    printf("%s\n", find("aa").c_str()); // ab
    printf("%s\n", find("aaaaaa").c_str()); // aaaaab
    printf("%s\n", find("abccba").c_str()); //aaccba
    return 0;
}
