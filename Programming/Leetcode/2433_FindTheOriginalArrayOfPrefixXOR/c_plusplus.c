#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//2433_FindTheOriginalArrayOfPrefixXOR
//time complexity: O(n)
vector<int> find(vector<int> nums) {
    vector<int> ret;
    int value = 0;
    for(auto num:nums) {
        value ^= num;
        int tmp = value;
        ret.push_back(value);
        value ^= num;
        value ^= tmp;
    }
    return ret;
}

int main() {
    vector<int> ret;
    
    ret = find({5,2,0,3,1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    // {5,7,2,3,2}
    
    ret = find({13});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    // {13}
    
    return 0;
}
