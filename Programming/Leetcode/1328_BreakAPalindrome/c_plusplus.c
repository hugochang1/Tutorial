#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//1328_BreakAPalindrome

string find(string s) {
    int size = s.size();
    if(size <= 1) return "";
    for(int i = 0; i < size/2; i++) {
        if(s[i] != 'a') {
            s[i] = 'a';
            return s;
        }
    }
    s.back() = 'b';
    return s;
}

int main() {
    printf("%s\n", find("a").c_str()); //
    printf("%s\n", find("aa").c_str()); // ab
    printf("%s\n", find("abccba").c_str()); //aaccba
    
    return 0;
}
