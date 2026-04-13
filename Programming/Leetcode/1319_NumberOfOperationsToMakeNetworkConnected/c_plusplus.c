#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

//1319_NumberOfOperationsToMakeNetworkConnected

//time complexity: O(n) which n is the number of connections
int find(int n, vector<pair<int,int>> connections) {
    if(n - 1 > connections.size()) return -1;
    
    unordered_set<int> visited;
    for(auto [a, b]:connections) {
        visited.insert(a);
        visited.insert(b);
    }
    return n - visited.size();
}

int main() {
    printf("%d\n", find(4, {{0,1}, {0,2}, {1,2}})); // 1
    printf("%d\n", find(6, {{0,1}, {0,2}, {0,3}, {1,2}, {1,3}})); //2
    printf("%d\n", find(6, {{0,1}, {0,2}, {0,3}, {1,2}})); // -1
    return 0;
}
