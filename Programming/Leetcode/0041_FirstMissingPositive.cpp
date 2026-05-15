#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0041_FirstMissingPositive
//time complexity: O(n)
//space complexity: O(1)
int solution(vector<int> nums) {
    int n = nums.size();
    
    //use cyclic sort
    int i = 0;
    while(i < n) {
        int correctIndex = nums[i] - 1;
        if(0 < nums[i] && nums[i] <= n && nums[i] != nums[correctIndex]) {
            swap(nums[i], nums[correctIndex]);
        } else {
            i++;
        }
    }
    for(int i = 0; i < n; i++) {
        if(nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

int main() {
    printf("%d\n", solution({1,2,0})); //3
    printf("%d\n", solution({3,4,-1,1})); //2
    printf("%d\n", solution({7,8,9,11,12})); //1
    return 0;
}
