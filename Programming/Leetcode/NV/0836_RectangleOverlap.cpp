#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//836_RectangleOverlap

bool isOverlap(vector<int> r1, vector<int> r2) {
    if(r1[0] >= r2[2] ||
        r1[1] >= r2[3] ||
        r1[2] <= r2[1] ||
        r1[3] <= r2[0])
        return false;
    return true;
}

int main() {
    printf("%d\n", isOverlap({0,0,2,2}, {1,1,3,3})); // 1
    printf("%d\n", isOverlap({0,0,1,1}, {1,0,2,1})); // 0
    printf("%d\n", isOverlap({0,0,1,1}, {2,2,3,3})); // 0
    return 0;
}
