#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//1334_FindCityWithSmallestNumOfNeighborsAtThreshold

//time complexity: O(NE log N), N is the number of nodes, E is the number of edges
int solution(int n, vector<vector<int>> edges, int threshold) {
    int minCity = INT_MAX;
    int ret = 0;
    for(int i = 0; i < n; i++) {
        //adj[src] = {{dst1,w1},{dst2,w2},...}
        vector<vector<pair<int,int>>> adj(n);
        for(auto& edge:edges) {
            int start = edge[0];
            int end = edge[1];
            int w = edge[2];
            adj[start].push_back({end,w});
            adj[end].push_back({start,w});
        }
        
        //dist[end]=w
        vector<int> dist(n, 1e9);
        dist[i] = 0;
        
        //min-heap  w,start
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        q.push({0,i});
        
        while(!q.empty()) { // E log N
            int weight = q.top().first;
            int start = q.top().second;
            q.pop();
            
            if(weight > dist[start]) continue;
            
            for(auto& a:adj[start]) {
                int end = a.first;
                int w = a.second;
                
                if(dist[end] > dist[start] + w) {
                    dist[end] = dist[start] + w;
                    q.push({dist[end], end});
                }
            }
        }
        
        int cnt = 0;
        for(auto d:dist) {
            if(d <= threshold) {
                cnt++;
            }
        }
        if(cnt <= minCity) {
            minCity = cnt;
            ret = i;
        }
    }
    
    return ret;
}

int main() {
    printf("%d\n", solution(4,{{0,1,3},{1,2,1},{1,3,4},{2,3,1}}, 4)); //3
    printf("%d\n", solution(5, {{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}}, 2)); //0
    return 0;
}
