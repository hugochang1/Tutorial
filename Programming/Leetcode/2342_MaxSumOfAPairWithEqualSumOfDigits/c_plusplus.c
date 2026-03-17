#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2342_MaxSumOfAPairWithEqualSumOfDigits

// go through all inputs and save the sum of digits into unordered_map
// time complexity: O(n^2)
int find(vector<int> inputs) {
    int out = -1;
    unordered_map<int, vector<int>> m;
    
    for(auto value:inputs) {
        int sum = 0;
        int tmp = value;
        while(tmp > 0) {
            sum += tmp % 10;
            tmp = tmp / 10;
        }
        
        if(m.find(sum) != m.end()) {
            vector<int> matches = m[sum];
            for(auto match:matches) {
                out = max(out, match + value);
            }
        }
        m[sum].push_back(value);
    }
    return out;
}

int main() {
    printf("%d\n", find({18,43,36,13,7})); // 54
    printf("%d\n", find({10,12,19,14})); // -1
    return 0;
}
