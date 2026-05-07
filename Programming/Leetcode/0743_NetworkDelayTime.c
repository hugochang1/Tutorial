#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>

//0743_NetworkDelayTime

using namespace std;

int solution(int n, vector<vector<int>> connections, int k) {
    vector<int> dist(n, INT_MAX);
    dist[k - 1] = 0;
    
    for(int i = 0; i < n; i++) {
        vector<int> tmp = dist;
        for(auto conn:connections) {
            int start = conn[0] - 1;
            int end = conn[1] - 1;
            int weight = conn[2];
            
            if(dist[start] != INT_MAX) {
                tmp[end] = min(tmp[end], dist[start] + weight);
            }
        }
        dist = tmp;
    }
    
    int ret = 0;
    for(auto d:dist) {
        if(d == INT_MAX) return -1;
        ret = max(ret, d);
    }
    return ret;
}

int main() {
    printf("%d\n", solution(4, {{2,1,1,},{2,3,1},{3,4,1}}, 2)); // 2
    printf("%d\n", solution(2, {{1,2,1}}, 1)); // 1
    printf("%d\n", solution(2, {{1,2,1}}, 2)); // -1
    return 0;
}
