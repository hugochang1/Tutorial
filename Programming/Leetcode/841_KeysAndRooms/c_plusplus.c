#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

//841_KeysAndRooms

// Time complexity: O(MxN), which M is the number of the room and N is the number of key
// Space complexity: O(max(K, MxN)), which K is the number of bucket
bool find(vector<vector<int>> r) {
    // use queue/deque to store the keys while traveling the rooms
    // to reduce time complexity, use HashMap/unordered_set to the visited rooms
    deque<int> keys;
    unordered_set<int> visited;
    
    for(auto key:r[0]) {
        keys.push_back(key);
        visited.insert(0);
    }
    if (visited.size() == r.size()) return true;
    
    while(!keys.empty()) {
        int key = keys.front();
        keys.pop_front();
        
        if(visited.find(key) == visited.end()) {
            visited.insert(key);
            for(auto new_key:r[key]) {
                keys.push_back(new_key);
            }
            if (visited.size() == r.size()) return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> r1 = {{1},{2},{3},{}}; //true
    vector<vector<int>> r2 = {{1,3},{3,0,1},{2},{0}}; //false
    
    printf("%d\n", find(r1));
    printf("%d\n", find(r2));
    return 0;
}
