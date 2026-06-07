#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0042_TrappingRainWater
int solution(vector<int> height) {
    int ret = 0;
    int left = 0;
    int right = height.size() - 1;
    int maxLeft = 0;
    int maxRight = 0;
    
    while(left <= right) {
        if(height[left] < height[right]) {
            //handle left part
            if(maxLeft < height[left]) {
                maxLeft = height[left];
            } else {
                ret += maxLeft - height[left];
            }
            left++;
        } else {
            //handle right part
            if(maxRight < height[right]) {
                maxRight = height[right];
            } else {
                ret += maxRight - height[right];
            }
            right--;
        }
    }
    return ret;
}

int main() {
    printf("%d\n", solution({0,1,0,2,1,0,1,3,2,1,2,1})); // 6
    return 0;
}
