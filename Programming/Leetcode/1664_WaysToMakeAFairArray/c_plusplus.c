#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//1664_WaysToMakeAFairArray

// time complexity: O(n^2)
// can be improved TBD
int solution(vector<int> v) {
    int count = 0;
    for(int i = 0; i < v.size(); i++) {
        vector<int> tmp;
        for(int j = 0; j < v.size(); j++) {
            if(i != j) {
                tmp.push_back(v[j]);
            }
        }
        
        int oddSum = 0;
        int evenSum = 0;
        for(int j = 0; j < tmp.size(); j++) {
            if(j % 2 == 0) {
                evenSum += tmp[j];
            } else {
                oddSum += tmp[j];
            }
        }
        if(evenSum == oddSum) count++;
    }
    return count;
}

int main() {
    printf("%d\n", solution({2,1,6,4})); // 1
    printf("%d\n", solution({1,1,1})); // 3
    printf("%d\n", solution({1,2,3})); // 0
    return 0;
}
