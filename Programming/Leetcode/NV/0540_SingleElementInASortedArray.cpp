#include <stdio.h>
#include <vector>

using namespace std;
//540_SingleElementInASortedArray

int find(vector<int> nums) {
  int left = 0;
  int right = nums.size() - 1;
  while(left < right) {
    int mid1 = (left + right) / 2;
    int mid2 = mid1 ^ 1;
    if(nums[mid1] == nums[mid2]) {
      //search right part
      left = max(mid1, mid2) + 1;
    } else {
      //search left part
      right = min(mid1, mid2);
    }
  }
  return left;
}

int main() {
    printf("%d\n", find({1,2,2,3,3})); //0
    printf("%d\n", find({1,1,2,2,3})); //4
    printf("%d\n", find({1,1,2,3,3})); //2
    printf("%d\n", find({1,1,2})); // 2
    printf("%d\n", find({1,2,2})); // 0
    return 0;
}
