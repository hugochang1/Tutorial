// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <numeric>

using namespace std;

// 724_FindPivotIndex

//time complexity: O(n)
int findPivotIndex2(vector<int> &nums) {
    int right_sum = accumulate(nums.begin(), nums.end(), 0);
    int left_sum = 0;
    int i;
    for(i = 0; i < nums.size(); i++) {
        right_sum -= nums[i];
        if(right_sum == left_sum) return i;
        left_sum += nums[i];
    }
    return -1;
}

int main() {
    vector<int> v1 = {1,7,3,6,5,6}; // 3
    vector<int> v2 = {1,2,3}; // -1
    vector<int> v3 = {2,1,-1}; // 0
    
    printf("%d\n", findPivotIndex2(v1)); // 3
    printf("%d\n", findPivotIndex2(v2)); // -1
    printf("%d\n", findPivotIndex2(v3)); // 0
    
    return 0;
}
