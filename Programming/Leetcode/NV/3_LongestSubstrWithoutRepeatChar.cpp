#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
//3_LongestSubstrWithoutRepeatChar

int solution(string s) {
    unordered_set<char> visited; //char
    int ret = 0;
    int j = 0;
    for(int i = 0; i < s.size(); i++) {
        while(visited.count(s[i])) {
            visited.erase(s[j]);
            j++;
        }
        visited.insert(s[i]);
        ret = max(ret, i - j + 1);
    }
    return ret;
}

int main() {
    printf("%d\n", solution("abcabcbb")); // 3
    printf("%d\n", solution("bbbbbb")); // 1
    printf("%d\n", solution("pwwkew")); // 3
    return 0;
}
