#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <utility>

using namespace std;
//706 design a HashMap, DesignHashMap

class HashMap {
    vector<deque<pair<int, int>>> v;
    int num_buck;
    
public:
    HashMap() {
        num_buck = 4;
        for (int i = 0; i < num_buck; i++) {
            deque<pair<int, int>> d;
            v.push_back(d);
        }
    }
    
    void put(int key, int value) {
        int hash_value = key % num_buck;
        deque<pair<int, int>>& d = v[hash_value];
        bool contain = false;
        for(auto& [k, v]:d) {
            if (k == key) {
                v = value;
                contain = true;
            }
        }
        if (!contain) {
            d.push_back({key, value});
        }
    }
    
    int get(int key) {
        int hash_value = key % num_buck;
        deque<pair<int, int>> d = v[hash_value];
        for (auto [k, v]:d) {
            if (k == key) return v;
        }
        return -1;
    }
    
    void remove(int key) {
        int hash_value = key % num_buck;
        deque<pair<int, int>>& d = v[hash_value];
        int remove_index = -1;
        for(int i = 0; i < d.size(); i++) {
            if (d[i].first == key) {
                remove_index = i;
                break;
            }
        }
        if(remove_index >= 0) {
            d.erase(d.begin() + remove_index);
        }
    }
    
    void dump() {
        printf("dump HashMap\n");
        for (int i = 0; i < v.size(); i++) {
            printf("i=%d size=%zu ", i, v[i].size());
            for (int j = 0; j < v[i].size(); j++) {
                printf("%d/%d ", v[i][j].first, v[i][j].second);
            }
            printf("\n");
        }
    }
};

int main() {
    HashMap m;
    
    m.put(1, 11);
    m.dump();
    /*
    dump HashMap
    i=0 size=0 
    i=1 size=1 1/11 
    i=2 size=0 
    i=3 size=0 
    */
    
    m.put(1, 12);
    m.dump();
    /*
    dump HashMap
    i=0 size=0 
    i=1 size=1 1/12
    i=2 size=0 
    i=3 size=0 
    */
    
    m.put(5, 55);
    m.dump();
    /*
    dump HashMap
    i=0 size=0 
    i=1 size=2 1/12 5/55 
    i=2 size=0 
    i=3 size=0 
    */
    
    m.put(2, 22);
    m.dump();
    /*
    dump HashMap
    i=0 size=0 
    i=1 size=2 1/12 5/55 
    i=2 size=1 2/22 
    i=3 size=0 
    */
    
    printf("%d\n", m.get(0)); // -1
    printf("%d\n", m.get(1)); // 12
    printf("%d\n", m.get(2)); // 22
    
    m.remove(0);
    m.dump(); // no change
    
    m.remove(5);
    m.dump();
    /*
    dump HashMap
    i=0 size=0 
    i=1 size=1 1/12 
    i=2 size=1 2/22 
    i=3 size=0 
    */
    return 0;
}
