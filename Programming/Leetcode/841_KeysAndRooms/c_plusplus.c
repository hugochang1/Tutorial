#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <unordered_set>

using namespace std;

//841_KeysAndRooms
//time complexity: O(m x n), n is the number of rooms, m is the number of keys in rooms
bool find(vector<vector<int>> rooms) {
    //use unordered_set for visited rooms
    //use queue to handle the keys
    deque<int> q;
    q.push_back(0);
    unordered_set<int> visited;
    
    while(!q.empty()) {
        int k = q.front();
        q.pop_front();
        visited.insert(k);
        if(visited.size() == rooms.size()) return true;
        for(int key:rooms[k]) {
            if(visited.count(key) == 0) {
                q.push_back(key);
            }
        }
    }
    return false;
}

int main() {
    printf("%d\n", find({{1},{2},{3},{}})); // true
    printf("%d\n", find({{1,3},{3,0,1},{2},{0}})); // false
    return 0;
}
