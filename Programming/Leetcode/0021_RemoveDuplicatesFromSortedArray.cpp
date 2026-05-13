#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0026_RemoveDuplicatesFromSortedArray

int solution(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    int p = 1;
    int last = nums[0];
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] != last) {
            nums[p] = nums[i];
            last = nums[i];
            p++;
        }
    }
    return p;
}

int main() {
    vector<int> nums;
    int ret;
    
    nums = {1,1,2};
    ret = solution(nums);
    printf("len=%d\n", ret);
    for(int i = 0; i < ret; i++) {
        printf(" %d", nums[i]);
    }
    printf("\n");
    
    nums = {0,0,1,1,1,2,2,3,3,4};
    ret = solution(nums);
    printf("len=%d\n", ret);
    for(int i = 0; i < ret; i++) {
        printf(" %d", nums[i]);
    }
    printf("\n");
    
    return 0;
}
