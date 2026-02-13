#include <iostream>
#include <list>

using namespace std;

void dump(list<int>& l) {
    printf("dump list: ");
    for (auto a: l) {
        printf("%d ", a);
    }
    printf("\n");
}

int main() {
    list<int> l = {1,2,3};
    dump(l); // dump list: 1 2 3 
    
    // Time complexity: O(1)
    l.push_front(0);
    dump(l); // dump list: 0 1 2 3 
    l.push_back(4);
    dump(l); // dump list: 0 1 2 3 4
    
    l.pop_front();
    dump(l); // dump list: 1 2 3 4
    l.pop_back();
    dump(l); // dump list: 1 2 3
    
    // Time complexity: O(N)
    l.erase(l.begin());
    dump(l); // dump list: 2 3
    
    list<int>::iterator it = l.begin();
    advance(it, 1);
    l.insert(it, 4);
    dump(l); // dump list: 2 4 3
    
    l.remove(4);
    dump(l); // dump list: 2 3
    
    l.clear();
    dump(l); // dump list:
    
    return 0;
}
