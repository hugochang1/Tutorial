#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//1570_DotProductOfTwoSparseVectors
int solution(vector<pair<int,int>> v1, vector<pair<int,int>> v2) {
    if(v1.size() == 0 || v2.size() == 0) return 0;
    unordered_map<int,int> m;
    for(auto [index, value]:v1) {
        m[index] = value;
    }
    
    int ret = 0;
    for(auto [index, value]:v2) {
        if(m.find(index) != m.end()) {
            ret += m[index] * value;
        }
    }
    
    return ret;
}

int main() {
    printf("%d\n", solution({{0,1},{3,2},{4,3}}, {{1,3},{3,4}})); // 8
    printf("%d\n", solution({{1,1}}, {{4,2}})); // 0
    
    return 0;
}
