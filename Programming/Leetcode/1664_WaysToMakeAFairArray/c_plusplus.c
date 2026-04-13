#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//1664_WaysToMakeAFairArray

#if 0
// Time complexity: O(n^2)
int solution(vector<int> nums) {
    int cnt = 0;
    for(int i = 0; i < nums.size(); i++) {
        bool even = true;
        int oddSum = 0;
        int evenSum = 0;
        for(int j = 0; j < nums.size(); j++) {
            if(i == j) continue;
            if(even) {
                evenSum += nums[j];
            } else {
                oddSum += nums[j];
            }
            even = !even;
        }
        if(oddSum == evenSum) cnt++;
    }
    return cnt;
}
#else
// Time complexity: O(n)
int solution(vector<int> nums) {
    int cnt = 0;
    int oddSum = 0;
    int evenSum = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(i%2 == 0) {
            evenSum += nums[i];
        } else {
            oddSum += nums[i];
        }
    }
    
    int newOdSum = 0;
    int newEvenSum = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(i%2 == 0) {
            evenSum -= nums[i];
        } else {
            oddSum -= nums[i];
        }
        
        if((newOdSum + evenSum) == (newEvenSum + oddSum)) cnt++;
        
        if(i%2 == 0) {
            newEvenSum += nums[i];
        } else {
            newOdSum += nums[i];
        }
    }
    
    return cnt;
}
#endif

int main() {
    printf("%d\n", solution({2,1,6,4})); // 1
    printf("%d\n", solution({1,1,1})); // 3
    printf("%d\n", solution({1,2,3})); // 0
    return 0;
}
