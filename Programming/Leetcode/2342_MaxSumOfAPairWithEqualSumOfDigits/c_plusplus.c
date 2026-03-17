#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2342_MaxSumOfAPairWithEqualSumOfDigits

// go through all inputs and save the sum of digits into unordered_map
// time complexity: O(n^2)
int find(vector<int> v) {
    unordered_map<int, vector<int>> m;
    int out = -1;
    
    for(auto a:v) {
        int sum = 0;
        int tmp = a;
        while(tmp != 0) {
            sum += (tmp % 10);
            tmp = tmp / 10;
        }
        
        if(m.find(sum) != m.end()) {
            vector<int> v1 = m[sum];
            for(auto v2:v1) {
                out = max(out, v2 + a);
            }
        }
        m[sum].push_back(a);
    }
    return out;
}

int main() {
    printf("%d\n", find({18,43,36,13,7})); // 54
    printf("%d\n", find({10,12,19,14})); // -1
    return 0;
}
