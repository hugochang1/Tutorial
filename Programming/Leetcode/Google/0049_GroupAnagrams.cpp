#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//0049_GroupAnagrams
//time complexity: O(n x mlogm), n is the number of strings, m is the max length of string in strings
vector<vector<string>> solution(vector<string> strings) {
    vector<vector<string>> ret;
    unordered_map<string, int> m;
    int cnt = 0;
    
    for(auto& s:strings) {
        string tmp = s;
        sort(tmp.begin(), tmp.end());
        if(m.count(tmp) == 0) {
            vector<string> tmp2 = {s};
            ret.push_back(tmp2);
            m[tmp] = cnt;
            cnt++;
        } else {
            int index = m[tmp];
            ret[index].push_back(s);
        }
    }
    return ret;
}

int main() {
    vector<vector<string>> ret;
    
    ret = solution({"eat","tea","tan","ate","nat","bat"});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        for(auto& s:r) {
            printf("%s ", s.c_str());
        }
        printf("\n");
    }
    
    return 0;
}
