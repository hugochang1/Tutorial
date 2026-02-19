#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <utility>

using namespace std;

void dump(deque<pair<int,int>> d) {
    for (auto [d1, d2] : d) {
        printf("{%d,%d}, ", d1, d2);
    }
    printf("\n");
}

int findPos(deque<pair<int,int>> d, int key) {
    for (int i = 0; i < d.size(); i++) {
        if (d[i].first == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    deque<pair<int, int>> d = {{1,2},{3,4}};
    dump(d); // {1,2}, {3,4}, 
    
    d.push_back({5,6});
    dump(d); // {1,2}, {3,4}, {5,6},
    
    d.push_front({0,0});
    dump(d); // {0,0}, {1,2}, {3,4}, {5,6},
    
    d.pop_front();
    dump(d); // {1,2}, {3,4}, {5,6},
    
    d.pop_back();
    dump(d); // {1,2}, {3,4}, 
    
    printf("%d\n", findPos(d, 1)); // 0
    printf("%d\n", findPos(d, 2)); // -1
    printf("%d\n", findPos(d, 3)); // 1
    
    int index = findPos(d, 1); // index = 0;
    d.erase(d.begin() + index);
    dump(d); // {3,4}, 
    
    d.insert(d.begin(), {1,2});
    dump(d); // {1,2}, {3,4}, 
    
    d.insert(d.end(), {5,6});
    dump(d); // {1,2}, {3,4}, {5,6},
    
    return 0;
}
