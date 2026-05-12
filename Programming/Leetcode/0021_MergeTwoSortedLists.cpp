#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

//0021_MergeTwoSortedLists

//time complexity: O(n1+n2), n1 is the number of list_1, n2 is the number of list_2
//space complexity: O(n1+n2)
list<int> solution(list<int> l1, list<int> l2) {
    list<int> ret;
    list<int>::iterator it1 = l1.begin();
    list<int>::iterator it2 = l2.begin();
    
    while(it1 != l1.end() && it2 != l2.end()) {
        if(*it1 <= *it2) {
            ret.push_back(*it1);
            it1++;
        } else {
            ret.push_back(*it2);
            it2++;
        }
    }
    
    while(it1 != l1.end()) {
        ret.push_back(*it1);
        it1++;
    }
    while(it2 != l2.end()) {
        ret.push_back(*it2);
        it2++;
    }
    return ret;
}

int main() {
    list<int> ret;
    
    ret = solution({1,2,4}, {1,3,4});
    for(auto& r:ret) {
        printf("%d ", r);
    }
    printf("\n"); //1 1 2 3 4 4
    return 0;
}
