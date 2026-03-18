#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

//2461_MaxSumOfDistinctSubarraysWithLengthK

//go through nums
//use unordered_set to check whether value already existed
//time complexity: O(k x n)
int find(vector<int> nums, int k) {
    int ret = 0;
    
    for(int i = 0; i <= nums.size() - k; i++) {
        int sum = 0;
        unordered_set<int> s;
        for(int j = i; j < i + k; j ++) {
            if(s.count(nums[j])) {
                sum = 0;
                break;
            }
            sum += nums[j];
            s.insert(nums[j]);
        }
        ret = max(ret, sum);
    }
    return ret;
}

int main() {
    
    printf("%d\n", find({1,5,4,2,9,9,9}, 3)); //15
    printf("%d\n", find({4,4,4}, 3)); //0
    
    return 0;
}
