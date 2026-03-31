#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;

//706_DesignHashMap
//void put(int key, int value)
//int get(int key)
//void remove(int key)

class HashMap {
    int capacity = 3;
    vector<list<pair<int,int>>> v; //key value
public:
    HashMap() {
        for(int i = 0; i < capacity; i++) {
            list<pair<int,int>> a;
            v.push_back(a);
        }
    }
    
    void put(int key, int value) {
        int index = key % capacity;
        auto& l = v[index];
        for(auto& [k, v]:l) {
            if(k == key) {
                v = value;
                return;
            }
        }
        l.push_back({key,value});
    }
    
    int get(int key) {
        int index = key % capacity;
        auto l = v[index];
        for(auto [k, v]:l) {
            if(k == key) {
                return v;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int index = key % capacity;
        auto& l = v[index];
        for(auto it = l.begin(); it != l.end(); it++) {
            if(it->first == key) {
                l.erase(it);
                return;
            }
        }
    }
    
    void dump() {
        printf("dump()\n");
        for(auto a:v) {
            for(auto [key, value]:a) {
                printf("%d/%d ", key, value);
            }
            printf("\n");
        }
    }
};

int main() {
    HashMap m;
    
    m.put(1,11);
    m.dump();
    
    m.put(1,12);
    m.put(3,33);
    m.dump();
    
    printf("%d\n", m.get(1)); //22
    printf("%d\n", m.get(2)); //-1
    printf("%d\n", m.get(3)); //33
    
    m.remove(1);
    m.dump();
    
    return 0;
}
