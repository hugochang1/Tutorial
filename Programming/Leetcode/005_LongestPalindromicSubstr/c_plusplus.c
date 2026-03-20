#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

bool isPalindromic(string s) {
    int left = 0;
    int right = s.size() - 1;
    while(left < s.size()) {
        if(s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

string find(string s) {
    string ret;
    
    for(int i = 0; i < s.size(); i++) {
        for(int j = i + 1; j < s.size() + 1; j++) {
            string sub = s.substr(i, j);
            if(isPalindromic(sub)) {
                if(ret.size() < sub.size()) {
                    ret = sub;
                }
            }
        }
    }

    return ret;
}

int main() {
    printf("%s\n", find("babad").c_str()); //bab
    printf("%s\n", find("cbbd").c_str()); //bb
    return 0;
}
