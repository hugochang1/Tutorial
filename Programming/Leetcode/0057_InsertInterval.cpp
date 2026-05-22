#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0057_InsertInterval
//time complexity: O(n), space complexity:O(n)
vector<vector<int>> solution(vector<vector<int>> intervals, vector<int> newInterval) {
    vector<vector<int>> ret;
    
    int begin = -1;
    int end = newInterval[1];
    for(auto& interval:intervals) {
        if(begin == -1) {
            if(newInterval[0] > interval[1]) {
                ret.push_back(interval);
            } else {
                begin = interval[0];
            }
        } else if(begin == 1e9) {
            ret.push_back(interval);
        } else {
            if(newInterval[1] < interval[0]) {
                ret.push_back({begin, end});
                begin = 1e9;
                ret.push_back(interval);
            } else {
                end = max(end, interval[1]);
            }
        }
    }
    return ret;
}

int main() {
    vector<vector<int>> ret;
    
    ret = solution({{1,3},{6,9}}, {2,5});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("} ");
    }
    printf("\n");
    //{1,5} {6,9}
    
    ret = solution({{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,8});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("} ");
    }
    printf("\n");
    //{1,2} {3,10}, {12,16}
    
    return 0;
}
