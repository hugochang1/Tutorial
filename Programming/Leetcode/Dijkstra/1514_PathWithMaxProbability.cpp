#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <queue>

//1514_PathWithMaxProbability

using namespace std;

float solution(int n, vector<vector<int>> edges, vector<float> prob, int start, int end) {
    //adj[src] = {{dst1, prob1}, {dst2, prob2}, ...}
    vector<vector<pair<int,float>>> adj(n);
    for(int i = 0; i < edges.size(); i++) {
        int start = edges[i][0];
        int end = edges[i][1];
        adj[start].push_back({end, prob[i]});
    }
    
    //dist[dst] = prob
    vector<float> dist(n, 0);
    dist[start] = 1;
    
    //dst, prob
    priority_queue<pair<int,float>, vector<pair<int,float>>, greater<pair<int,float>>> q;
    q.push({start, prob[start]});

    while(!q.empty()) {
        int start = q.top().first;
        float prob = q.top().second;
        q.pop();
        
        for(auto& a:adj[start]) {
            int end = a.first;
            float p = a.second;
            
            if(dist[end] < dist[start] * p) {
                dist[end] = dist[start] * p;
                q.push({end, dist[end]});
            }
        }
    }
    
    return dist[end];
}

int main() {
    printf("%f\n", solution(3, {{0,1},{1,2},{0,2}}, {0.5,0.5,0.2}, 0, 2)); // 0.25
    printf("%f\n", solution(3, {{0,1},{1,2},{0,2}}, {0.5,0.5,0.3}, 0, 2)); // 0.3
    printf("%f\n", solution(3, {{0,1}}, {0.5}, 0, 2)); // 0
    return 0;
}
