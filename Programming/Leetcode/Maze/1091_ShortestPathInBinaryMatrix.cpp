#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <set>

using namespace std;

//1091_ShortestPathInBinaryMatrix

//time complexity: O(MxN), space complexity: O(MxN)
int solution(vector<vector<int>> matrix) {
    if(matrix[0][0] == 1) return -1;
    int m = matrix.size(); //x-axis
    int n = matrix[0].size(); //y-axis
    
    int ret = 0;
    vector<pair<int,int>> moves = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    deque<pair<int,int>> q;
    q.push_back({0,0});
    
    set<pair<int,int>> visited;
    visited.insert({0,0});

    while(!q.empty()) {
        int size = q.size();
        ret++;
        for(int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop_front();
            
            if(x == m - 1 && y == n - 1) return ret;
            
            for(auto& move:moves) {
                int next_x = x + move.first;
                int next_y = y + move.second;
                
                if(visited.count({next_x, next_y}) > 0) continue;
                
                if(0 <= next_x && next_x < m && 0 <= next_y && next_y < n && matrix[next_x][next_y] == 0) {
                    visited.insert({next_x, next_y});
                    q.push_back({next_x, next_y});
                }
            }
        }
    }
    return ret;
}

int main() {
    printf("%d\n", solution({{0,1},{1,0}})); //2
    printf("%d\n", solution({{0,0,0},{1,1,0},{1,1,0}})); //4
    printf("%d\n", solution({{1,0,0},{1,1,0},{1,1,0}})); //-1
    return 0;
}
