#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2342_MaxSumOfAPairWithEqualSumOfDigits

// go through all inputs and save the sum of digits into unordered_map
// time complexity: O(n)
int find(vector<int> inputs) {
    int out = -1;
    unordered_map<int, int> m;
    
    for(auto value:inputs) {
        int sum = 0;
        int tmp = value;
        while(tmp > 0) {
            sum += tmp % 10;
            tmp = tmp / 10;
        }
        
        if(m.count(sum)) {
            out = max(out, m[sum] + value);
        }
        
        if(m.count(sum)) {
            m[sum] = max(m[sum], value);
        } else {
            m[sum] = value;
        }
    }
    
    return out;
}

int main() {
    printf("%d\n", find({18,43,36,13,7})); // 54
    printf("%d\n", find({10,12,19,14})); // -1
    return 0;
}
