#include <stdio.h>
#include <stdlib.h>

bool isValidTriangle(int a, int b, int c) {
    if ((a+b) > c && (a+c) > b && (b+c) > a) return true;
    return false;
}

int cmpfun(const void* a, const void *b) {
    return *(int*)a - *(int*)b;
}

// time complexity: O(n^2)
int solution(int *arr, int size) {
    int count = 0;
    
    qsort(arr, size, sizeof(int), cmpfun);//O(nlogn)

    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    for(int i = size - 1; i >= 2 ; i--) {
        int left = 0;
        int right = i - 1;
        
        while (left < right) {
            if (arr[left] + arr[right] > arr[i]) {
                count += (right - left);
                right--;
            } else {
                left++;
            }
        }
    }
    
    return count;
}


int main() {
    int arr[] = {2,2,3,4}; // ret=3
    //int arr[] = {4,2,3,4}; // ret=4
    int ret = solution(arr, sizeof(arr)/sizeof(arr[0]));
    printf("ret=%d\n", ret);
    
    return 0;
}
