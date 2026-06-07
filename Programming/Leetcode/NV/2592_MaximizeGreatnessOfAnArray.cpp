#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

//2592_MaximizeGreatnessOfAnArray
//sort the nums and use two points to get the answer

int find(vector<int> nums) {
    sort(nums.begin(), nums.end(), greater<int>());
    int i = 1, j = 0;
    int size = nums.size();
    
    int c = 0;
    while(i < size && j < size) {
        if(nums[j] > nums[i]) {
            j++;
            c++;
        }
        i++;
    }
    return c;
}

int main() {
    printf("%d\n", find({1,3,5,2,1,3,1})); //4
    printf("%d\n", find({1,2,3,4})); //3
    return 0;
}
