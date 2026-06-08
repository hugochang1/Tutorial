#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

//706_DesignHashMap
//void put(int key, int value)
//int get(int key)
//void remove(int key)

class HashMap {
    vector<list<pair<int,int>>> v;
    int cap = 10;
public:
    HashMap() {
        v.resize(cap);
    }

    void put(int key, int value) {
        int index = key % cap;
        for(auto& [k,v]:v[index]) {
            if(k == key) {
                v = value;
                return;
            }
        }
        v[index].push_back({key, value});
    }

    int get(int key) {
        int index = key % cap;
        for(auto& [k,v]:v[index]) {
            if(k == key) {
                return v;
            }
        }
        return -1;
    }

    void remove(int key) {
        int index = key % cap;
        auto& l = v[index];
        for(auto it = l.begin(); it != l.end(); it++) {
            if(it->first == key) {
                l.erase(it);
                return;
            }
        }
    }
};


int main() {
    HashMap m;
    
    m.put(1,11);
    
    m.put(1,22);
    m.put(3,33);
    
    printf("%d\n", m.get(1)); //22
    printf("%d\n", m.get(2)); //-1
    printf("%d\n", m.get(3)); //33
    
    m.remove(1);
    printf("%d\n", m.get(1)); //-1
    printf("%d\n", m.get(3)); //33
    return 0;
}
