#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <set>

using namespace std;

//use BFS (Breadth First Seach)
int find(int target_x, int target_y) {
    int steps = 0;
    
    deque<pair<int,int>> q;
    q.push_back({0, 0});
    set<pair<int,int>> visited;
    visited.insert({0,0});
    
    vector<pair<int,int>> moves = {{2,1},{2,-1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2}};
    
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop_front();
            if(x == target_x && y == target_y) return steps;
            for(auto [move_x, move_y]:moves) {
                int next_x = x + move_x;
                int next_y = y + move_y;
                if(visited.count({next_x, next_y}) == 0) {
                    q.push_back({next_x, next_y});
                    visited.insert({next_x, next_y});
                }
            }
        }
        steps++;
    }
    return -1;
}

int main() {
    printf("%d\n", find(2,1)); //1
    printf("%d\n", find(5,5)); //4
    return 0;
}
