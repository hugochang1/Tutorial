#include <stdio.h>
#include <vector>
#include <deque>
#include <set>

using namespace std;
//490_TheMaze

//Time complexity: O(mn), space complexity:O(mn)
bool find(vector<vector<int>> maze, vector<int> start_pos, vector<int> end_pos) {
    int m = maze.size();
    int n = maze[0].size();
    deque<pair<int,int>> q;
    set<pair<int,int>> visited;

    q.push_back({start_pos[0], start_pos[1]});
    visited.insert({start_pos[0], start_pos[1]});

    vector<pair<int,int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop_front();

            if(x == end_pos[0] && y == end_pos[1]) return true;

            for(auto& dir:directions) {
                int move_x = dir.first;
                int move_y = dir.second;
                int next_x = x + move_x;
                int next_y = y + move_y;

                while(0 <= next_x && next_x < m && 0 <= next_y && next_y < n && maze[next_x][next_y] == 0) {
                    next_x += move_x;
                    next_y += move_y;
                }
                next_x -= move_x;
                next_y -= move_y;
                if(visited.count({next_x,next_y}) == 0) {
                    q.push_back({next_x,next_y});
                    visited.insert({next_x,next_y});
                }
            }
        }
    }
    return false;
}

int main() {
    printf("%d\n", find({{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}}, {0,4}, {4,4})); // true
    printf("%d\n", find({{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}}, {0,4}, {3,2})); // false
    printf("%d\n", find({{0,0,0,0,0},{1,1,0,0,1},{0,0,0,0,0},{0,1,0,0,1},{0,1,0,0,0}}, {4,3}, {0,1})); // false
    return 0;
}
