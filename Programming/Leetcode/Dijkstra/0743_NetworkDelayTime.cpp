#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <climits>

//0743_NetworkDelayTime

using namespace std;

int solution(int n, vector<vector<int>> connections, int k) {
    //1 build up associations
    //adj[src] = {{dst1, weight1}, {dst2, weight2}, ...}
    vector<vector<pair<int,int>>> adj(n);
    for(auto& conn:connections) {
        int start = conn[0] - 1;
        int end = conn[1] - 1;
        int weight = conn[2];
        adj[start].push_back({end, weight});
    }
    
    //dist[dst] = min weight
    vector<int> dist(n, INT_MAX);
    dist[k - 1] = 0;
    
    //dst, weight
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({k - 1, 0});
    
    while(!q.empty()) {
        int start = q.top().first;
        int weight = q.top().second;
        q.pop();
        
        if(weight > dist[start]) continue;
        
        for(auto& edge:adj[start]) {
            int dst = edge.first;
            int weight = edge.second;
            if(dist[dst] > dist[start] + weight) {
                dist[dst] = dist[start] + weight;
                q.push({dst, dist[dst]});
            }
        }
    }
    
    int ret = 0;
    for(auto d:dist) {
        if(d == INT_MAX) return -1;
        ret = max(ret, d);
    }
    return ret;
}

int main() {
    printf("%d\n", solution(4, {{2,1,1},{2,3,1},{3,4,1}}, 2)); // 2
    printf("%d\n", solution(2, {{1,2,1}}, 1)); // 1
    printf("%d\n", solution(2, {{1,2,1}}, 2)); // -1
    return 0;
}
