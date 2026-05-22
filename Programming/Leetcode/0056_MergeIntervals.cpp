#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0056_MergeIntervals
//time complexity: O(nlogn), space complexity: O(logn)
vector<vector<int>> solution(vector<vector<int>> intervals) {
    vector<vector<int>> ret;
    if(intervals.size() == 0) return ret;
    
    sort(intervals.begin(), intervals.end()); //nlogn
    
    ret.push_back(intervals[0]);
    
    for(int i = 1; i < intervals.size(); i++) {
        if(intervals[i][0] > ret.back()[1]) {
            ret.push_back(intervals[i]);
        } else {
            if(intervals[i][1] > ret.back()[1]) {
                ret.back()[1] = intervals[i][1];
            }
        }
    }
    return ret;
}

int main() {
    vector<vector<int>> ret;
    
    ret = solution({{1,3},{2,6},{15,18},{8,10}});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("}");
    } // {1,6,} {8,10} {15,18}
    printf("\n");
    
    ret = solution({{1,4},{4,5}});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("}\n");
    } // {1,5}
    printf("\n");
    
    return 0;
}
