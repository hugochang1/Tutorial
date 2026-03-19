#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

list<int> solution(list<int> l1, list<int> l2) {
    list<int> ret;
    int v1 = 0;
    int v2 = 0;
    while(!l1.empty()) {
        v1 *= 10;
        v1 += l1.back();
        l1.pop_back();
    }
    while(!l2.empty()) {
        v2 *= 10;
        v2 += l2.back();
        l2.pop_back();
    }
    int v = v1 + v2;
    while(v > 0) {
        int value = v % 10;
        ret.push_back(value);
        v /= 10;
    }
    return ret;
}

int main() {
    list<int> ret;
    ret = solution({2,4,3}, {5,6,4});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    // {7,0,8}
    
    return 0;
}
