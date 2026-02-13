#include <iostream>
#include <list>

using namespace std;

list<int> ReverseLinkedList(list<int> l) {
    list<int> ret;
    for(auto a : l) {
        ret.push_front(a);
    }
    return ret;
}

void ReverseLinkedListRecu(list<int> l, list<int>& ret) {
    if(l.size() == 0) return;
    int a = l.front();
    l.pop_front();
    ReverseLinkedListRecu(l, ret);
    ret.push_back(a);
}

int main() {
    list<int> l = {1,2,3,4,5};
    
    auto ret = ReverseLinkedList(l);
    for(auto a:ret) {
        printf("%d ", a); // 5 4 3 2 1 
    }
    printf("\n");

    list<int> ret2;
    ReverseLinkedListRecu(l, ret2);
    for(auto a:ret2) {
        printf("%d ", a); // 5 4 3 2 1 
    }
    printf("\n");
    return 0;
}
