#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <unordered_map>

using namespace std;

class Node {
public:
    int key;
    int value;
    Node(int k, int v): key(k), value(v) {}
};

class LRUCache {
public:
    list<Node> l;
    unordered_map<int, list<Node>::iterator> m;
    int cap;
    LRUCache(int capacity): cap(capacity) {}
    
    void put(int key, int value) {
        if(m.count(key)) {
            list<Node>::iterator n = m[key];
            n->value = value;
            l.splice(l.begin(), l, n);
        } else {
            if(l.size() >= cap) {
                int least_used_key = l.back().key;
                l.pop_back();
                m.erase(least_used_key);
            }
            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }
    
    int get(int key) {
        if(m.count(key)) {
            list<Node>::iterator n = m[key];
            l.splice(l.begin(), l, n);
            return n->value;
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
