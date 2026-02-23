#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <list>

using namespace std;

// 146 LRUCache

class Node {
public:
    int key;
    int value;
    Node(int k, int v): key(k), value(v) {}
};

class LRUCache {
    list<Node> l;
    unordered_map<int, list<Node>::iterator> m;
    int cap;
    
    void moveToHead(list<Node>::iterator it) {
        l.splice(l.begin(), l, it); //O(1)
    }
    
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (m.find(key) != m.end()) {
            list<Node>::iterator it = m[key];
            moveToHead(it);
            return it->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            list<Node>::iterator it = m[key];
            it->value = value;
            moveToHead(it);
        } else {
            if (l.size() == cap) {
                int least_used_key = l.back().key;
                l.pop_back();
                m.erase(least_used_key);
            }
            l.push_front(Node(key, value));
            m[key] = l.begin();
        }
    }
};

#include <algorithm>

int main() {
    LRUCache c(2);
    
    c.put(1, 1);
    c.put(2, 2);
    printf("%d\n", c.get(1)); //1
    c.put(3, 3); //remove 2,2
    printf("%d\n", c.get(2)); //-1
    c.put(4,4); //remove 1,1
    printf("%d\n", c.get(3)); //3
    printf("%d\n", c.get(4)); //4
    
    return 0;
}
