#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0057_InsertInterval
//time complexity: O(n), space complexity:O(n)
vector<vector<int>> solution(vector<vector<int>> intervals, vector<int> newInterval) {
    vector<vector<int>> ret;
    
    int n = intervals.size();
    int i = 0;
    
    while(i < n && intervals[i][1] < newInterval[0]) {
        ret.push_back(intervals[i]);
        i++;
    }
    
    int begin = intervals[i][0];
    int end = newInterval[1];
    while(i < n && intervals[i][0] <= newInterval[1]) {
        end = max(end, intervals[i][1]);
        i++;
    }
    ret.push_back({begin, end});
    
    while(i < n) {
        ret.push_back(intervals[i]);
        i++;
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
