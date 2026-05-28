#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;
//0206_ReverseLinkedList

list<int> solution(list<int> l) {
    list<int> ret;
    for(auto& i:l) {
        ret.push_front(i);
    }
    return ret;
}

//---------------------------------------------------------
void recu(list<int>& l, list<int>::iterator it, list<int>& ret) {
    if(it == l.end()) return;
    ret.push_front(*it);
    it++;
    recu(l, it, ret);
}

list<int> solutionRecu(list<int> l) {
    list<int> ret;
    recu(l, l.begin(), ret);
    return ret;
}

int main() {
    list<int> l;
    l = solutionRecu({1,2,3,4,5});
    for(auto& i:l) {
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}
