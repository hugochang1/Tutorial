#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0046_Permuation
//time complexity: O(n!)
void permutation(vector<int>& nums, int index, vector<vector<int>>& out) {
    if(index == nums.size()) {
        out.push_back(nums);
        return;
    }
    for(int i = index; i < nums.size(); i++) {
        swap(nums[i], nums[index]);
        permutation(nums, index + 1, out);
        swap(nums[i], nums[index]);
    }
}

vector<vector<int>> permutation(vector<int> nums) {
    vector<vector<int>> ret;
    permutation(nums, 0, ret);
    return ret;
}

int main() {
    vector<vector<int>> ret;
    
    ret = permutation({1,2,3});
    printf("size=%zu\n", ret.size());
    for(auto& r:ret) {
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("\n");
    }
    return 0;
}
