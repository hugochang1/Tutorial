#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>

// 773_SlidingPuzzle

using namespace std;

// convert 2D to 1D 
// use breadth first search (BFS) by using queue
// use unordered_set to record visited position
int find(vector<vector<int>> v) {
    string target = "123450";
    string pos = "";
    
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); j++) {
            pos += to_string((v[i][j]));
        }
    }
    
    if (pos == target) return 0;
    
    queue<string> q;
    q.push(pos);
    
    unordered_set<string> visited;
    visited.insert(pos);
    
    // 0 1 2
    // 3 4 5
    vector<vector<int>> moves = {
        {1, 3},     //neighbor of index 0
        {0, 2, 4},  //neighbor of index 1
        {1, 5},     //neighbor of index 2
        {0, 4},     //neighbor of index 3
        {1, 3, 5},  //neighbor of index 4
        {2, 4}      //neighbor of index 5
    };
    
    int level = 0;
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            string currPos = q.front();
            q.pop();
            
            if (currPos == target) return level;
            
            int zeroPos = currPos.find('0');
            
            for(int neighborPos : moves[zeroPos]) {
                string nextPos = currPos;
                swap(nextPos[zeroPos], nextPos[neighborPos]);
                
                if(visited.find(nextPos) == visited.end()) {
                    visited.insert(nextPos);
                    q.push(nextPos);
                }
            }
        }
        level++;
    }
    return -1;
}

int main() {
    vector<vector<int>> v1 = {{1,2,3}, {4,0,5}}; // output: 1
    vector<vector<int>> v2 = {{1,2,3}, {5,4,0}}; // output: -1
    vector<vector<int>> v3 = {{4,1,2}, {5,0,3}}; // output: 5
    vector<vector<int>> v4 = {{1,2,3}, {4,5,0}}; // output: 0
    printf("%d\n", find(v1));
    printf("%d\n", find(v2));
    printf("%d\n", find(v3));
    printf("%d\n", find(v4));
    return 0;
}
