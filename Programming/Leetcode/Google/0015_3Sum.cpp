#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>

//0015_3Sum

using namespace std;

//Time complexity: O(n^2)
vector<vector<int>> solution(vector<int> nums) {
    vector<vector<int>> ret;
    int n = nums.size();
    
    sort(nums.begin(), nums.end());
    
    for(int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        while(left != right) {
            if(nums[i] + nums[left] + nums[right] == 0) {
                ret.push_back({nums[i], nums[left], nums[right]});
                break;
            } else if(nums[i] + nums[left] + nums[right] > 0) {
                right--;
            } else if(nums[i] + nums[left] + nums[right] < 0) {
                left++;
            }
        }
    }
    
    return ret;
}

int main() {
    vector<vector<int>> ret;
    
    ret = solution({-1, 0, 1, 2, -1, -4});
    printf("size=%zu\n", ret.size());
    for(auto r:ret) {
        for(auto a:r) {
            printf("%d ", a);
        }
        printf("\n");
    }
    /*
    size=2
    -1 -1 2 
    -1 0 1 
    */
    
    return 0;
}
