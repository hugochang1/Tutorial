#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//0001_TwoSum
vector<int> solution(vector<int> nums, int target) {
    unordered_map<int, int> m; //target - num, index
    for(int i = 0; i < nums.size(); i++) {
        if(m.count(nums[i])) {
            return {m[nums[i]], i};
        }
        m[target - nums[i]] = i;
    }
    return {-1, -1};
}

int main() {
    vector<int> ret;
    ret = solution({2,7,11,15}, 9);
    printf("%d %d\n", ret[0], ret[1]); // 0 1
    
    ret = solution({3,2,4}, 6);
    printf("%d %d\n", ret[0], ret[1]); // 1 2
    
    ret = solution({3,3}, 6);
    printf("%d %d\n", ret[0], ret[1]); // 0 1
    return 0;
}
