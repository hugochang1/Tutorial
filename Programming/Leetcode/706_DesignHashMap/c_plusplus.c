#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <utility>

//706 design a HashMap, DesignHashMap

using namespace std;

class HashMap {
    vector<deque<pair<int, int>>> v;
    int buck_num;
public:
    HashMap() {
        buck_num = 4;
        for(int i = 0; i < buck_num; i++) {
            deque<pair<int, int>> d;
            v.push_back(d);
        }
    }

    void put(int key, int value) {
        int index = key % buck_num;
        v[index].push_back({key, value});
    }
    
    int get(int key) {
        int index = key % buck_num;
        deque<pair<int, int>> d = v[index];
        for (auto [k, v]:d) {
            if (k == key) {
                return v;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int index = key % buck_num;
        int index_for_remove = -1;
        deque<pair<int, int>> &d = v[index];
        for (int i = 0; i < d.size(); i++) {
            if (d[i].first == key) {
                index_for_remove = i;
                break;
            }
        }
        if (index_for_remove >= 0) {
            d.erase(d.begin() + index_for_remove);
        }
    }
    
    void print() {
        printf("size=%zu\n", v.size());
        for(int i = 0; i < v.size(); i++) {
            printf("i=%d size=%zu ", i, v[i].size());
            for(int j = 0; j < v[i].size(); j++) {
                printf("%d/%d ", v[i][j].first, v[i][j].second);
            }
            printf("\n");
        }
    }
};

int main() {
    HashMap m;
    
    m.put(1,11);
    m.put(17,12);
    m.put(0, 1);
    
    printf("%d\n", m.get(2));   // -1
    printf("%d\n", m.get(1));   // 11
    printf("%d\n", m.get(17));  // 12
    printf("%d\n", m.get(0));   // 1
    
    m.print();
    /*
    i=0 size=1 0/1 
    i=1 size=2 1/11 17/12 
    i=2 size=0 
    i=3 size=0 
    */
    
    m.remove(3);
    m.remove(1);
    m.remove(17);
    m.remove(17);
    m.remove(0);
    
    m.print();
    /*
    size=4
    i=0 size=0 
    i=1 size=0 
    i=2 size=0 
    i=3 size=0 
    */
    
    return 0;
}
