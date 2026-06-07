#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//0066_PlusOne
//time complexity: O(n), n is the number of nums
//space complexity: O(n)
vector<int> solution(vector<int> nums) {
    int value = 0;
    for(auto& num:nums) {
        value *= 10;
        value += num;
    }
    value++;
    
    int numDigit = 0;
    int tmp = value;
    while(tmp > 0) {
        numDigit++;
        tmp /= 10;
    }
    
    int i = numDigit - 1;
    vector<int> ret(numDigit, 0);
    while(value > 0) {
        ret[i] = value % 10;
        i--;
        value /= 10;
    }
    return ret;
}

int main() {
    vector<int> ret;
    
    ret = solution({1,2,3});
    for(auto& r:ret) {
        printf("%d ", r);
    }
    printf("\n"); // 1 2 4
    
    ret = solution({4,3,2,1});
    for(auto& r:ret) {
        printf("%d ", r);
    }
    printf("\n"); // 4 3 2 2
    
    return 0;
}
