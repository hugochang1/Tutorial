#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0035_SearchInsertPosition
//time complexity: O(logn)
int solution(vector<int> nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            return mid;
        } else if(nums[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    printf("%d\n", solution({1,3,5,6}, 5)); //2
    printf("%d\n", solution({1,3,5,6}, 2)); //1
    printf("%d\n", solution({1,3,5,6}, 7)); //4
    printf("%d\n", solution({1,3,5,6}, 0)); //0
    return 0;
}
