#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//540_SingleElementInASortedArray
//time complexity: O(logn)
int recu(vector<int>& nums, int left, int right) {
    if(left == right) {
        return left;
    }
    
    int m1 = (right+left)/2;
    int m2 = m1 ^ 1;
    
    if(nums[m1] == nums[m2]) {
        int mid = max(m1, m2) + 1;
        return recu(nums, mid, right);
    } else {
        int mid = min(m1, m2);
        return recu(nums, left, mid);
    }
}

int find(vector<int> nums) {
    int left = 0;
    int right = nums.size() - 1;
    return recu(nums, left, right);
}

int main() {
    printf("%d\n", find({1,2,2,3,3})); //0
    printf("%d\n", find({1,1,2,2,3})); //4
    printf("%d\n", find({1,1,2,3,3})); //2
    printf("%d\n", find({1,1,2})); // 2
    printf("%d\n", find({1,2,2})); // 0
}
