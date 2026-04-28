#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// time complexity: O(n^2)
vector<int> selectionSort(vector<int> nums) {
    int n = nums.size();
    if(n <= 1) return nums;
    for(int i = 0; i < n; i++) {
        int min_index = i;
        for(int j = i; j < n; j++) {
            if(nums[min_index] > nums[j]) {
                min_index = j;
            }
        }
        swap(nums[min_index], nums[i]);
    }
    return nums;
}

// time complexity: O(n^2), best case: O(n)
vector<int> insertionSort(vector<int> nums) {
    int n = nums.size();
    if(n <= 1) return nums;
    for(int i = 1; i < n; i++) {
        int pos = i;
        for(int j = i - 1; j >= 0; j--) {
            if(nums[pos] < nums[j]) {
                swap(nums[pos], nums[j]);
                pos = j;
            } else {
                break;
            }
        }
    }
    return nums;
}

// time complexity: average case: O(nlogn), worst csae: O(n^2)
vector<int> quickSort(vector<int> nums) {
    return nums;
}

// time complexity: O(n^2)
vector<int> mergeSort(vector<int> nums) {
    return nums;
}

int main() {
    vector<int> ret;
    
    ret = insertionSort({3,2,1,4,5,0,-1});
    for(auto a:ret) {
        printf("%d ", a);
    } // -1 0 1 2 3 4 5 
    printf("\n");
    return 0;
}
