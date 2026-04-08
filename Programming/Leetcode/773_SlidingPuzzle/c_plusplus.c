#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

//773_SlidingPuzzle
int find(vector<vector<int>> maps) {
    //convert 2D maps to 1D string
    //use unordered_set for visited position
    //use queue to check steps
    string target = "123450";
    string s;
    for(auto a:maps) {
        for(auto b:a) {
            s+= to_string(b);
        }
    }
    unordered_set<string> visited;
    visited.insert(s);
    
    deque<string> q;
    q.push_back(s);
    
    // 0 1 2
    // 3 4 5
    vector<vector<int>> moves = {
        /*0*/ {1,3},
        /*1*/ {0,2,4},
        /*2*/ {1,5},
        /*3*/ {0,4},
        /*4*/ {1,3,5},
        /*5*/ {2,4},
    };
    
    int steps = 0;
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            string cur = q.front();
            q.pop_front();
            
            if(cur == target) return steps;
            
            int zeroPos = cur.find('0');
            
            for(auto move:moves[zeroPos]) {
                swap(cur[move], cur[zeroPos]);
                if(visited.count(cur) == 0) {
                    visited.insert(cur);
                    q.push_back(cur);
                }
                swap(cur[move], cur[zeroPos]);
            }
        }
        steps++;
    }
    return -1;
}

int main() {
    printf("%d\n", find({{1,2,3}, {4,0,5}})); //1
    printf("%d\n", find({{1,2,3}, {5,4,0}})); //-1
    printf("%d\n", find({{4,1,2}, {5,0,3}})); //5
    printf("%d\n", find({{1,2,3}, {4,5,0}})); //0
    return 0;
}
