#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>

using namespace std;

//2571_MinimumOperationsToReduceAnIntegerTo0
int find(int n) {
    int op = 0;
    int cnt = 0;
    
    for(; n > 0; n >>= 1) {
        if(n % 2 == 1) {
            cnt++;
        } else {
            if(cnt) op++;
            if(cnt == 1) cnt = 0;
            if(cnt > 1) cnt = 1;
        }
    }
    if(cnt == 1) op++;
    if(cnt > 1) op+=2;
    return op;
}

int main() {
    printf("%d\n", find(39)); // 3
    printf("%d\n", find(54)); // 3
    //39 0x27
    //3
    // 39 + 1 = 40 (0x28)
    // 40 - 8 = 32 (0x20)
    // 32 - 32 = 0 (0x00)
    
    //54 (0x36)
    //3
    //0x38
    //0x40
    //0x00
    
    return 0;
}
