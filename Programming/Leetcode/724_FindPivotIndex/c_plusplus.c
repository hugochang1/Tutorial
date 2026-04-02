#include <stdio.h>
#include <vector>
#include <numeric>

using namespace std;

//724_FindPivotIndex
//time complexity: O(n)
int find(vector<int> nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int leftSum = 0;
    for(int i = 0; i < nums.size(); i++) {
        sum -= nums[i];
        if(leftSum == sum) return i;
        leftSum += nums[i];
    }
    return -1;
}

int main() {
    printf("%d\n", find({1,7,3,6,5,6})); //3
    printf("%d\n", find({1,2,3})); //-1
    printf("%d\n", find({2,1,-1})); //0
    return 0;
}

