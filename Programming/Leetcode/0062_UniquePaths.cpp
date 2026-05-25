#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;
//0062_UniquePaths

void recursive(int x, int y, int m, int n, string currentpath, unordered_set<string>& visited) {
    if(x == m - 1 && y == n - 1) {
        if(visited.count(currentpath) == 0) {
            visited.insert(currentpath);
        }
        return;
    }
    
    if(x + 1 < m) {
        currentpath += "x";
        recursive(x+1, y, m, n, currentpath, visited);
        currentpath.pop_back();
    }
    if(y + 1 < n) {
        currentpath += "y";
        recursive(x, y+1, m, n, currentpath, visited);
        currentpath.pop_back();
    }
}

int solution(int m, int n) {
    unordered_set<string> visited;
    string currentPath;
    recursive(0,0,m,n,currentPath,visited);
    return visited.size();
}

int main() {
    printf("%d\n", solution(3, 2)); //3
    printf("%d\n", solution(7, 3)); //28
    return 0;
}
