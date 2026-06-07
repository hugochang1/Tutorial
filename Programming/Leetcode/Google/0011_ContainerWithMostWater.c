#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0011_ContainerWithMostWater
//Time complexity: O(n)
//two pointer
int solution(vector<int> nums) {
    int ret = 0;
    int l = 0;
    int r = nums.size() - 1;
    while(l < r) {
        int height = min(nums[l], nums[r]);
        int width = r - l;
        int size = height * width;
        ret = max(ret, size);
        if(nums[l] > nums[r]) {
            r--;
        } else {
            l++;
        }
    }
    return ret;
}

int main() {
    printf("%d\n", solution({1,8,6,2,5,4,8,3,7})); // 49
    return 0;
}
