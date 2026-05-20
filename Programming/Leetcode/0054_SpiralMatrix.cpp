#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//0054_SpiralMatrix
//time complexity: O(mn)
vector<int> solution(vector<vector<int>> m) {
    vector<int> ret;
    int low = 0;
    int high = m.size() - 1;
    int left = 0;
    int right = m[0].size() - 1;
    int dir = 0; //0 right, 1 down, 2 left, 3 up
    
    while(low <= high && left <= right) {
        if(dir == 0) {
            for(int i = left; i <= right; i++) {
                ret.push_back(m[low][i]);
            }
            low++;
        } else if(dir == 1) {
            for(int i = low; i <= high; i++) {
                ret.push_back(m[i][right]);
            }
            right--;
        } else if(dir == 2) {
            for(int i = right; i >= left; i--) {
                ret.push_back(m[high][i]);
            }
            high--;
        } else {
            for(int i = high; i >= low; i--) {
                ret.push_back(m[i][left]);
            }
            left++;
        }
        dir = (dir + 1) % 4;
    }
    
    return ret;
}

int main() {
    vector<int> ret;
    
    ret = solution({{1,2,3},{4,5,6},{7,8,9}});
    for(auto& r:ret) {
        printf("%d ", r); //1,2,3,6,9,8,7,4,5
    }
    printf("\n");
    
    ret = solution({{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    for(auto& r:ret) {
        printf("%d ", r); //1,2,3,4,8,12,11,10,9,5,6,7
    }
    printf("\n");
    
    return 0;
}
