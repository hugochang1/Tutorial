#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
using namespace std;

//1319_NumberOfOperationsToMakeNetworkConnected

//Time complexity is O(nlogn)
//It can be improved to O(n) if change the data structure from set to unorder_set
int find(int n, vector<pair<int,int>> connections) {
    if (connections.size() < (n-1)) {
        return -1;
    }
    //go through all connections and use the set for visited nodes
    //the answer is the number of un-visited nodes
    set<int> s;
    
    for(auto connection:connections) {
        if(s.find(connection.first) == s.end()) {
            s.insert(connection.first);
        }
        if(s.find(connection.second) == s.end()) {
            s.insert(connection.second);
        }
    }
    return n - s.size();
}

int main() {
    printf("%d\n", find(3, {{0,1}, {0,2}, {1,2}})); // 1
    printf("%d\n", find(6, {{0,1}, {0,2}, {0,3}, {1,2}, {1,3}})); //2
    printf("%d\n", find(6, {{0,1}, {0,2}, {0,3}, {1,2}})); // -1
    return 0;
}
