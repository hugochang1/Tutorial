#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

//0064_MinPathSum

int recursive(vector<vector<int>>& matrix, int x, int y, int currSum) {
    int m = matrix.size();
    int n = matrix[0].size();
    if(x == m - 1 && y == n - 1) {
        return currSum;
    }
    
    int ret1 = 1e9;
    int ret2 = 1e9;
    if(x + 1 < m) {
        ret1 = recursive(matrix, x+1, y, currSum + matrix[x+1][y]);
    }
    if(y + 1 < n) {
        ret1 = recursive(matrix, x, y+1, currSum + matrix[x][y+1]);
    }
    return min(ret1, ret2);
}

int solution(vector<vector<int>> m) {
    return recursive(m, 0, 0, m[0][0]);
}

int main() {
    printf("%d\n", solution({{1,3,1},{1,5,1},{4,2,1}}));// 7
    return 0;
}
