#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
//0121_BestTimeToBuyAndSellStack

int solution(vector<int> nums) {
    int ret = 0;
    int low = nums[0];
    for(int i = 1; i < nums.size(); i++) {
        if(low > nums[i]) {
            low = nums[i];
        } else {
            ret = max(ret, nums[i] - low);
        }
    }
    return ret;
}

int main() {
    printf("%d\n", solution({7,1,5,3,6,4})); // 5
    printf("%d\n", solution({7,6,4,3,1})); // 0
    return 0;
}
