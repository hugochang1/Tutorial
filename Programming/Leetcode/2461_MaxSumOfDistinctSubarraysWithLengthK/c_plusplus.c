#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

//2461_MaxSumOfDistinctSubarraysWithLengthK

// time complexity: O(n x k)
int find(vector<int> nums, int k) {
    int out = 0;
    for(int i = 0; i < nums.size(); i++) {
        unordered_set<int> visited;
        int sum = 0;
        for(int j = i; j < nums.size(); j++) {
            if(visited.count(nums[j]) == 0) {
                visited.insert(nums[j]);
                sum += nums[j];
                if(visited.size() == k) {
                    out = max(out, sum);
                    break;
                }
            }
        }
    }
    return out;
}

int main() {
    printf("%d\n", find({1,5,4,2,9,9,9}, 3)); //15
    printf("%d\n", find({4,4,4}, 3)); //0
    printf("%d\n", find({4,4,4,5,6}, 3)); //15
    printf("%d\n", find({1,2,4,4,4}, 3)); //7
    return 0;
}
