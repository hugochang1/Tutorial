#include <stdio.h>
#include <vector>

using namespace std;
//0238_ProductOfArrayExceptSelf

vector<int> solution(vector<int> nums) {
    int n = nums.size();
    vector<int> ret(n, 1);
    int pref = 1;
    for(int i = 0; i < n; i++) {
        ret[i] *= pref;
        pref *= nums[i];
    }
    int suffix = 1;
    for(int i = n-1; i >= 0; i--) {
        ret[i] *= suffix;
        suffix *= nums[i];
    }
    return ret;
}

int main() {
    vector<int> ret;
    ret = solution({1,2,3,4});
    for(auto& a:ret) {
        printf("%d ", a);
    }
    printf("\n"); //24 12 8 6
    
    ret = solution({-1,1,0,-3,3});
    for(auto& a:ret) {
        printf("%d ", a);
    }
    printf("\n"); //0 0 9 0 0
    return 0;
}
