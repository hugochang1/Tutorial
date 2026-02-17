#include <stdio.h>
#include <stdlib.h>

//time complexity: O(n^2)
//TODO can be optimized to O(n) by using hashmap
int subarraySum(int *nums, int size, int target) {
    int count = 0;
    int i, j;
    int sum;
    
    for (i = 0; i < size; i++) {
        sum = 0;
        for (j = i; j < size; j++) {
            sum += nums[j];
            if (sum == target) {
                printf("found %d %d\n", i, j);
                count++;
                break;
            }
        }
    }
    return count;
}

int main() {
    int nums[] = {1,2,3};
    int target = 3;
    int ret = subarraySum(nums, sizeof(nums)/4, target);
    printf("ret=%d\n", ret);
    return 0;
}
