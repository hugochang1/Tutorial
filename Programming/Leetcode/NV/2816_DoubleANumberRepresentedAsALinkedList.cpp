#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;

//2816_DoubleANumberRepresentedAsALinkedList
//Time complexity: O(n)
list<int> solution(list<int> nums) {
    int value = 0;
    for(auto a:nums) {
        value *= 10;
        value += a;
    }
    value *= 2;
    list<int> ret;
    while(value > 0) {
        int reminder = value % 10;
        ret.push_front(reminder);
        value /= 10;
    }
    return ret;
}

int main() {
    list<int> ret;
    
    ret = solution({1,8,9});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    //{3,7,8}
    
    ret = solution({9,9,9});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    //{1,9,9,8}
    return 0;
}
