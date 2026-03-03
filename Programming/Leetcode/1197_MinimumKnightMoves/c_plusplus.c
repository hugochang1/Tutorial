#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <string>
using namespace std;

//1197_MinimumKnightMoves

vector<vector<int>> moves = {{2,1},{2,-1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2}};

//use BFS (Breadth First Search)
//Time complexity: O(nlogn) can be improved to O(n) if change set to unordered_set
int find(int x, int y) {
    int step = 0;
    
    deque<pair<int,int>> q;
    set<pair<int,int>> visited;
    
    unordered_set<pair<int,int>, pair_hash> a;
    
    if(x == 0 && y == 0) return 0;
    
    for(auto move:moves) {
        visited.insert({move[0], move[1]});
        q.push_back({move[0], move[1]});
    }
    
    while(!q.empty()) {
        step++;
        int size = q.size();
        for(int i = 0; i < size; i++) {
            pair<int, int> pos = q.front();
            q.pop_front();
            
            if(pos.first == x && pos.second == y) return step;
            
            for(auto move:moves) {
                int next_x = pos.first + move[0];
                int next_y = pos.second + move[1];
                if(visited.find({next_x, next_y}) == visited.end()) {
                    visited.insert({next_x, next_y});
                    q.push_back({next_x, next_y});
                }
            }
        }
    }
    return -1;
}

int main() {
    printf("%d\n", find(2,1));
    printf("%d\n", find(5,5));
    return 0;
}
