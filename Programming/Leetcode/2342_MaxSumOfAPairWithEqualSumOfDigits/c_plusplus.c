#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2342_MaxSumOfAPairWithEqualSumOfDigits

int sumOfDigits(int num) {
    int sum = 0;
    while(num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

//time complexity: O(n)
int find(vector<int> nums) {
    int out = -1;
    unordered_map<int, int> m; //key: sum of digits, value: num
    
    for(auto num:nums) {
        int sum = sumOfDigits(num);
        if(m.count(sum)) {
            out = max(out, num + m[sum]);
            m[sum] = max(num, m[sum]);
        } else {
            m[sum] = num;
        }
    }
    
    return out;
}

int main() {
    printf("%d\n", find({18,43,36,13,7})); // 54
    printf("%d\n", find({10,12,19,14})); // -1
    return 0;
}
