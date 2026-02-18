#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

bool isValidTriangle(int a, int b, int c) {
    if ((a+b) > c && (a+c) > b && (b+c) > a) return true;
    return false;
}

// time complexity: O(n^3), TODO improve it
int solution(int *arr, int size) {
    int count = 0;
    
    //sort(arr, arr + size); //O(nlogn)
    
    int i, j, k;
    
    for(i = 0; i < size; i++) {
        for(j = i + 1; j < size; j++) {
            for(k = j + 1; k < size; k++) {
                if(isValidTriangle(arr[i], arr[j], arr[k])) count++;
            }
        }
    }
    
    return count;
}


int main() {
    int arr[] = {2,2,3,4};
    int ret = solution(arr, sizeof(arr)/sizeof(arr[0]));
    printf("ret=%d\n", ret);
    
    return 0;
}
