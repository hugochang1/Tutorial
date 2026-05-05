#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//0014_LongestCommonPrefix

string solution(vector<string> strs) {
    if(strs.size() == 0) return "";
    for(int i = 0; i < strs[0].size(); i++) {
        int ch = strs[0][i];
        for(int j = 1; j < strs.size(); j++) {
            if(i >= strs[j].size() || ch != strs[j][i]) {
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0];
}

int main() {
    printf("%s\n", solution({"flower", "flow", "flight"}).c_str()); // fl
    printf("%s\n", solution({"dog", "racecar", "car"}).c_str()); // 
    printf("%s\n", solution({"abc", "abcef", "abc123"}).c_str()); // abc
    return 0;
}
