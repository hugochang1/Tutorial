#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

//1721_SwappingNodesInALinkedList

list<int> solution(list<int> l, int k) {
    list<int>::iterator it1 = next(l.begin(), k - 1);
    list<int>::iterator it2 = next(l.begin(), l.size() - k);
    swap(*it1, *it2);
    return l;
}

int main() {
    list<int> ret;
    ret = solution({1,2,3,4,5}, 4);
    for(auto a:ret) {
        printf("%d ", a); // 1 4 3 2 5
    }
    printf("\n");
    return 0;
}
