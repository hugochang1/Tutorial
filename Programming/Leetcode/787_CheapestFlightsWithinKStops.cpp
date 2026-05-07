#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <climits>

//787_CheapestFlightsWithinKStops

using namespace std;

int solution(int n, vector<vector<int>> flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    for(int i = 0; i <= k; i++) {
        vector<int> tmp = dist;
        for(auto& flight:flights) {
            int start = flight[0];
            int stop = flight[1];
            int price = flight[2];
            
            if(dist[start] != INT_MAX) {
                tmp[stop] = min(tmp[stop], dist[start] + price);
            }
        }
        dist = tmp;
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

int main() {
    printf("%d\n", solution(4, {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}}, 0, 3, 1)); // 700
    printf("%d\n", solution(3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 1)); // 200
    printf("%d\n", solution(3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 0)); // 500
    return 0;
}
