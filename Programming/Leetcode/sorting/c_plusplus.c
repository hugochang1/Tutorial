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
int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int j = low;
    for(int i = low; i < high; i++) {
        if(nums[i] <= pivot) {
            swap(nums[i], nums[j]);
            j++;
        }
    }
    swap(nums[j], nums[high]);
    return j;
}

void quickSortRecu(vector<int>& nums, int low, int high) {
    if(low >= high) return;
    int pivot = partition(nums, low, high);
    quickSortRecu(nums, low, pivot - 1);
    quickSortRecu(nums, pivot + 1, high);
}

vector<int> quickSort(vector<int> nums) {
    quickSortRecu(nums, 0, nums.size() - 1);
    return nums;
}

// time complexity: O(n^2)

// divide and conquer
void merge(vector<int>& nums, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    vector<int> v1, v2;
    for(int i = 0; i < n1; i++) {
        v1.push_back(nums[low + i]);
    }
    for(int i =0; i < n2; i++) {
        v2.push_back(nums[mid + 1 + i]);
    }
    
    int i = 0, j = 0, pos = low;
    while(i < n1 && j < n2) {
        if(v1[i] <= v2[j]) {
            nums[pos++] = v1[i++];
        } else {
            nums[pos++] = v2[j++];
        }
    }
    while(i < n1) {
        nums[pos++] = v1[i++];
    }
    while(j < n2) {
        nums[pos++] = v2[j++];
    }
}

void mergeSortRecu(vector<int>& nums, int low, int high) {
    if(low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSortRecu(nums, low, mid);
    mergeSortRecu(nums, mid+1, high);
    merge(nums, low, mid, high);
}

vector<int> mergeSort(vector<int> nums) {
    mergeSortRecu(nums, 0, nums.size() - 1);
    return nums;
}

#define SORT mergeSort

int main() {
    vector<int> ret;
    
    ret = SORT({3,2,1,4,5,0,-1});
    for(auto a:ret) {
        printf("%d ", a);
    } // -1 0 1 2 3 4 5 
    printf("\n");
    
    ret = SORT({1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({1, 2});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({2, 1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({1,2,3});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({1,3,2});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({2,1,3});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({2,3,1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({3,1,2});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = SORT({3,2,1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    return 0;
}
