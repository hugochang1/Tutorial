#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//490_TheMaze

bool bfs(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, int target_x, int target_y) {
    int m = maze.size();
    int n = maze[0].size();
    
    visited[x][y] = true;
    
    if(x == target_x && y == target_y) return true;
    
    vector<vector<int>> moves = {{0,1},{0,-1},{1,0},{-1,0}};
    
    for(auto move:moves) {
        int next_x = x + move[0];
        int next_y = y + move[1];
        
        while(0 <= next_x && next_x < m && 0 <= next_y && next_y < n && maze[next_x][next_y] == 0) {
            next_x += move[0];
            next_y += move[1];
        }
        next_x -= move[0];
        next_y -= move[1];
        
        if(!visited[next_x][next_y]) {
            if(bfs(maze, visited, next_x, next_y, target_x, target_y)) return true;
        }
    }
    return false;
}

bool find(vector<vector<int>> maze, vector<int> start_pos, vector<int> end_pos) {
    int m = maze.size();
    int n = maze[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    return bfs(maze, visited, start_pos[0], start_pos[1], end_pos[0], end_pos[1]);
}

int main() {
    printf("%d\n", find({{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}}, {0,4}, {4,4})); // true
    printf("%d\n", find({{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}}, {0,4}, {3,2})); // false
    printf("%d\n", find({{0,0,0,0,0},{1,1,0,0,1},{0,0,0,0,0},{0,1,0,0,1},{0,1,0,0,0}}, {4,3}, {0,1})); // false
    return 0;
}
