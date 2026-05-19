#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//0048_RotateImage
//Time complexity: O(n^2)
void rotate(vector<vector<int>>& m) {
    int n = m.size();
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(m[i][j], m[j][i]);
        }
    }
    
    for(int i = 0; i < n; i++) {
        reverse(m[i].begin(), m[i].end());
    }
}

int main() {
    vector<vector<int>> m;
    
    m = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    rotate(m);
    for(auto& a:m) {
        for(auto& b:a) {
            printf("%d ", b);
        }
        printf("\n");
    }
    printf("\n");
    
    m = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };
    rotate(m);
    for(auto& a:m) {
        for(auto& b:a) {
            printf("%d ", b);
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
}
