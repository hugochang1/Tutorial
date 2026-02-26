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
    
    /*************************************
        push and pop O(1)
    **************************************/
    d.push_back({5,6}); // {1,2}, {3,4}, {5,6},
    d.push_front({0,0}); // {0,0}, {1,2}, {3,4}, {5,6},
    
    d.pop_front(); // {1,2}, {3,4}, {5,6},
    d.pop_back(); // {1,2}, {3,4}, 
    
    printf("%d %d\n", d[0].first, d[0].second); // 1, 2
    
    /*************************************
        find O(n)
    **************************************/
    auto it = find(d.begin(), d.end(), pair<int,int>(3,4));
    // it = deque<pair<int,int>>::iterator
    if(it == d.end()) {
        printf("not found\n");
    } else {
        printf("found %d %d\n", it->first, it->second);
    }
    
    printf("%d\n", findPos(d, 1)); // 0
    printf("%d\n", findPos(d, 2)); // -1
    printf("%d\n", findPos(d, 3)); // 1
    
    /*************************************
        insert and erase O(n)
    **************************************/
    int index = findPos(d, 1); // index = 0;
    d.erase(d.begin() + index); // {3,4}, 
    d.insert(d.begin(), {1,2}); // {1,2}, {3,4},
    d.insert(d.end(), {5,6}); // {1,2}, {3,4}, {5,6},
    
    return 0;
}
