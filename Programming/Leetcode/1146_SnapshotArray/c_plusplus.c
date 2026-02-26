#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//1146_SnapshotArray
//3:35 -> 3:45
// TBD: Space Optimization 
class SnapshotArray {
    vector<int> v;
    vector<vector<int>> vs;
    int sanp_count;
public:
    SnapshotArray(int size) {
        sanp_count = 0;
        for(int i = 0; i < size; i++) {
            v.push_back(0);
        }
    }
    
    void set(int index, int val) {
        if(index >= v.size()) {
            return;
        }
        v[index] = val;
    }
    
    int snap() {
        sanp_count++;
        vs.push_back(v);
        return sanp_count - 1;
    }
    
    int get(int index, int snap_id) {
        if(index >= v.size()) return -1;
        if(snap_id >= sanp_count) return -1;
        return vs[snap_id][index];
    }
};

int main() {
    SnapshotArray s(3);
    
    s.set(0, 3);
    int id1 = s.snap();
    s.set(0, 5);
    int id2 = s.snap();
    printf("id=%d %d\n", id1, id2);
    printf("%d\n", s.get(0, id1)); // 3
    printf("%d\n", s.get(0, id2)); // 5
    
    return 0;
}
