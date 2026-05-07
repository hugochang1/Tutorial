#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <queue>

//1976_NumberOfWaysToArriveAtDestination

using namespace std;

int solution(int n, vector<vector<int>> connections) {
    vector<vector<pair<int,int>>> adj(n);
    for(auto& conn:connections) {
        int start = conn[0];
        int end = conn[1];
        int w = conn[2];
        adj[start].push_back({end, w});
        adj[end].push_back({start, w});
    }
    
    //dist[dst] = weight
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;
    
    vector<int> ways(n, 0);
    ways[0] = 1;
    
    //min-heap start weight
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0, 0});
    
    while(!q.empty()) {
        int start = q.top().first;
        int weight = q.top().second;
        q.pop();
        
        if(weight > dist[start]) continue;
        
        for(auto& a:adj[start]) {
            int end = a.first;
            int w = a.second;
            
            if(dist[end] > dist[start] + w) {
                dist[end] = dist[start] + w;
                q.push({end, dist[end]});
                ways[end] = ways[start];
            } else if(dist[end] == dist[start] + w) {
                ways[end] = ways[start] + ways[end];
            }
        }
    }
    return ways.back();
}

int main() {
    printf("%d\n", solution(7, {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}})); // 4
    printf("%d\n", solution(2, {{1,0,10}})); // 1
    return 0;
}
