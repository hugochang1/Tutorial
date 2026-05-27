#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
    int capacity;
    list<pair<int,int>> l; //key, value
    unordered_map<int, list<pair<int,int>>::iterator> m; //key, list
    
public:
    LRUCache(int cap) {
        capacity = cap;
    }
    
    void put(int key, int value) {
        if(m.count(key)) {
            auto it = m[key];
            it->second = value;
            l.splice(l.begin(), l, it);
        } else {
            if(m.size() == capacity) {
                int lruKey = l.back().first;
                l.pop_back();
                m.erase(lruKey);
            }
            l.push_front({key, value});
            m[key] = l.begin();
        }
    }
    
    int get(int key) {
        if(m.count(key)) {
            auto it = m[key];
            l.splice(l.begin(), l, it);
            return it->second;
        }
        return -1;
    }
};

int main() {
    LRUCache c(2);
    c.put(1,1);
    c.put(2,2);
    printf("%d\n", c.get(1)); //1
    c.put(3,3);
    printf("%d\n", c.get(2)); //-1
    c.put(4,4);
    printf("%d\n", c.get(1)); //-1
    printf("%d\n", c.get(3)); //3
    printf("%d\n", c.get(4)); //4
    return 0;
}
