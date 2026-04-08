#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

//773_SlidingPuzzle
//use a hashmap (unordered_map) to record the visited place (convert 2D array to a string)
//use BFS (breadth first seach) to solve this issue

int findRecu(vector<vector<int>>& maps, unordered_set<string>& m, int steps) {
    string target = "123450";
    string s;
    for(auto a:maps) {
        for(auto b:a) {
            s += to_string(b);
        }
    }
    m.insert(s);
    
    // 0 1 2
    // 3 4 5
    vector<vector<int>> moves = {
        /*0*/ {1, 3},
        /*1*/ {0, 4, 2},
        /*2*/ {1, 5},
        /*3*/ {0, 4},
        /*4*/ {3, 1, 5},
        /*5*/ {2, 4},
    };
    
    deque<string> q;
    q.push_back(s);
    
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            string current = q.front();
            q.pop_front();
            if(current == target) {
                return steps;
            }
            int zeroPos = current.find('0');
            for(auto move:moves[zeroPos]) {
                swap(current[zeroPos], current[move]);
                if(m.count(current) == 0) {
                    q.push_back(current);
                    m.insert(current);
                }
                swap(current[zeroPos], current[move]);
            }
        }
        steps++;
    }
    return -1;
}

int find(vector<vector<int>> maps) {
    unordered_set<string> m;
    return findRecu(maps, m, 0);
}

int main() {
    printf("%d\n", find({{1,2,3}, {4,0,5}})); //1
    printf("%d\n", find({{1,2,3}, {5,4,0}})); //-1
    printf("%d\n", find({{4,1,2}, {5,0,3}})); //5
    printf("%d\n", find({{1,2,3}, {4,5,0}})); //0
    return 0;
}
