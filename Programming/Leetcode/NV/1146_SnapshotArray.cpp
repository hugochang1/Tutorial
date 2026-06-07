#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//1146_SnapshotArray

class SnapshotArray {
    int snap_count;
    vector<vector<pair<int,int>>> v;
    
public:
    SnapshotArray(int length) {
        snap_count = 0;
        v.resize(length);
    }
    
    void set(int index, int value) {
        if(v[index].size() == 0) {
            v[index].push_back({-1, value});
        } else {
            v[index][0] = {-1, value};
        }
    }
    
    int snap() {
        for(auto& a:v) {
            if(a.size() > 0) {
                a.push_back({snap_count, a[0].second});
            }
        }
        snap_count++;
        return snap_count - 1;
    }
    
    int get(int index, int snap_id) {
        auto a = v[index];
        for(auto [record, value]:a) {
            if(record == snap_id) {
                return value;
            }
        }
        return 0;
    }
    
    void dump() {
        for(auto a:v) {
            printf("  size=%d ", a.size());
            for(auto [record, value]:a) {
                printf("%d,%d ", record, value);
            }
            printf("\n");
        }
    }
};

int main() {
    SnapshotArray s(3);
    s.set(0, 5);
    printf("id=%d\n", s.snap()); // 0
    s.set(0, 6);
    printf("%d\n", s.get(0, 0)); // 5
    printf("id=%d\n", s.snap()); // 1
    printf("%d\n", s.get(0, 0)); // 5
    printf("%d\n", s.get(0, 1)); // 6
    
    s.dump();
    
    return 0;
}
