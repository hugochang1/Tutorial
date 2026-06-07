#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

//0033_SearchInRotatedSortedArray

//time complexity: O(logn)
int solution(vector<int> nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left)/2;
        
        if(nums[mid] == target) return mid;
        
        if(nums[left] <= nums[mid]) {
            //left part is sorted
            if(nums[left] <= target && target <= nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            //right part is sorted
            if(nums[mid] <= target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    printf("%d\n", solution({4,5,6,7,0,1,2}, 0)); //4
    printf("%d\n", solution({4,5,6,7,0,1,2}, 3)); //-1
    return 0;
}
