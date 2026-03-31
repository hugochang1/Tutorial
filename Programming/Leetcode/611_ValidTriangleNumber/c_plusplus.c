#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
//611_ValidTriangleNumber
//time complexity: O(n^2)
int find(vector<int> nums) {
    int cnt = 0;
    sort(nums.begin(), nums.end()); //O(nlogn)
    
    for(int i = nums.size() - 1; i >= 2; i--) {
        int left = 0;
        int right = i - 1;
        while(left != right) {
            if(nums[left] + nums[right] > nums[i]) {
                cnt += (right - left);
                right--;
            } else {
                left++;
            }
        }
    }
    
    return cnt;
}

int main() {
    printf("%d\n", find({2,2,3,4}));//3
    printf("%d\n", find({4,2,3,4}));//4
    return 0;
}
