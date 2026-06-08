#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
//611_ValidTriangleNumber

//time complexity: O(nlogn)
int find(vector<int> nums) {
    int ret = 0;
    sort(nums.begin(), nums.end());
    for(int i = nums.size() - 1; i >= 0; i--) {
        int left = 0;
        int right = i - 1;
        while(left < right) {
            if(nums[left] + nums[right] > nums[i]) {
                ret += right - left;
                right--;
            } else {
                left++;
            }
        }
    }
    return ret;
}

int main() {
    printf("%d\n", find({2,2,3,4}));//3
    printf("%d\n", find({4,2,3,4}));//4
    return 0;
}
