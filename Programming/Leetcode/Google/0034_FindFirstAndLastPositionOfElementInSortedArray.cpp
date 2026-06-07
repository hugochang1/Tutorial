#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0034_FindFirstAndLastPositionOfElementInSortedArray
//time complexity: O(n)
int left(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    int last = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            //keep search left part
            last = mid;
            high = mid - 1;
        } else if(nums[mid] > target) {
            high = mid - 1;
        } else if(nums[mid] < target) {
            low = mid + 1;
        }
    }
    return last;
}

int right(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    int last = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] == target) {
            //keep search right part
            last = mid;
            low = mid + 1;
        } else if(nums[mid] > target) {
            high = mid - 1;
        } else if(nums[mid] < target) {
            low = mid + 1;
        }
    }
    return last;
}

vector<int> solution(vector<int> nums, int target) {
    return {left(nums, target), right(nums, target)};
}

int main() {
    vector<int> ret;
    
    ret = solution({5,7,7,8,8,10}, 8);
    printf("%d %d\n", ret[0], ret[1]); // 3, 4
    
    ret = solution({5,7,7,8,8,10}, 6);
    printf("%d %d\n", ret[0], ret[1]); // -1,-1
    return 0;
}
