#include <stdio.h>
#include <vector>

using namespace std;
//526_BeautifulArrangement

void recu(vector<int>& nums, int n, int index, vector<vector<int>>& ret) {
    if(n == index) {
        for(int i = 0; i < n; i++) {
            if(nums[i] % (i+1) == 0 || (i+1) % nums[i] == 0) continue;
            else return;
        }
        ret.push_back(nums);
        return;
    }

    for(int i = index; i < n; i++) {
        swap(nums[index], nums[i]);
        recu(nums, n, index + 1, ret);
        swap(nums[index], nums[i]);
    }
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> ret;
    vector<int> nums;
    for(int i = 0; i < n; i++) {
        nums.push_back(i+1);
    }
    recu(nums, n, 0, ret);
    return ret;
}

int main() {
    vector<vector<int>> ret;
    ret = solution(4);
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("} ");
    }
    printf("\n");

    return 0;
}
