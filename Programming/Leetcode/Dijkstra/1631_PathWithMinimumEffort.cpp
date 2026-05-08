#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

//1631_PathWithMinimumEffort

int solution(vector<vector<int>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    //dist[r][c] = effort
    vector<vector<int>> dist(rows, vector<int>(cols, 1e9));
    dist[0][0] = 0;
    
    //min-heap, effort, {row, col}
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> q;
    q.push({0,{0,0}});
    
    vector<pair<int,int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};
    
    while(!q.empty()) {
        int effort = q.top().first;
        int r = q.top().second.first;
        int c = q.top().second.second;
        q.pop();
        
        if(r == rows - 1 && c == cols - 1) return effort;
        
        if(effort > dist[r][c]) continue;
        
        for(auto& [mr, mc]:moves) {
            int nr = r + mr;
            int nc = c + mc;
            if(0 <= nr && nr < rows && 0 <= nc && nc < cols) {
                int newEffort = max(effort, abs(matrix[nr][nc] - matrix[r][c]));
                if(newEffort < dist[nr][nc]) {
                    dist[nr][nc] = newEffort;
                    q.push({newEffort, {nr,nc}});
                }
            }
        }
    }
    return 0;
}

int main() {
    printf("%d\n", solution({{1,2,2},{3,8,2},{5,3,5}})); //2
    printf("%d\n", solution({{1,2,3},{3,8,4},{5,3,5}})); //1
    printf("%d\n", solution({{1,2,1,1,1},{1,2,1,2,1},{1,2,1,2,1},{1,2,1,2,1},{1,1,1,2,1}})); //0
    return 0;
}
