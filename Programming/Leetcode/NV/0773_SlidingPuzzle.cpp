#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;
//773_SlidingPuzzle

int find(vector<vector<int>> m) {
    unordered_set<string> visited;
    string target = "123450";
    string curr;
    deque<string> q;

    for(auto& a:m) {
        for(auto& b:a) {
            curr += to_string(b);
        }
    }
    if(curr == target) return 0;
    q.push_back(curr);
    visited.insert(curr);

    // 0 1 2
    // 3 4 5
    vector<vector<int>> moves = {
        {1,3}, //index 0
        {0,2,4}, //index 1
        {1,5}, //index 2
        {0,4}, //index 3
        {1,3,5}, //index 4
        {2,4} //index 5
    };

    int cnt = 0;
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            curr = q.front();
            q.pop_front();
            if(curr == target) return cnt;
            int zeroPos = curr.find('0');
            for(auto& move:moves[zeroPos]) {
                swap(curr[zeroPos], curr[move]);
                if(visited.count(curr) == 0) {
                    q.push_back(curr);
                    visited.insert(curr);
                }
                swap(curr[zeroPos], curr[move]);
            }
        }
        cnt++;
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
