#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>

using namespace std;

//use two points and unordered_map (char, index)

int find(string s) {
    unordered_map<char,int> m;
    int left = 0;
    int ret = 0;
    
    for(int i = 0; i < s.size(); i++) {
        if(m.count(s[i])) {
            left = m[s[i]] + 1;
        } else {
            ret = max(ret, i - left + 1);
        }
        m[s[i]] = i;
    }
    
    return ret;
}

int main() {
    printf("%d\n", find("abcabcbb")); //3
    printf("%d\n", find("bbbbb")); //1
    printf("%d\n", find("pwwkew")); //3
    return 0;
}
