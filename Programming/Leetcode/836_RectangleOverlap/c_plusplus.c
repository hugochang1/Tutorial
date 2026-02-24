#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//836_RectangleOverlap
bool isOverlap(vector<int> r1, vector<int> r2) {
    return !(
        r1[0] >= r2[2] || //left
        r1[2] <= r2[0] || //right
        r1[1] >= r2[3] || //bottom
        r1[3] <= r2[1] //top
        );
}

int main() {
    // x1,y1,x2,y2
    // x1,y1 bottom-left
    // x2,y2 top-right
    printf("%d\n", isOverlap({0,0,2,2}, {1,1,3,3})); // 1
    printf("%d\n", isOverlap({0,0,1,1}, {1,0,2,1})); // 0
    printf("%d\n", isOverlap({0,0,1,1}, {2,2,3,3})); // 0
    return 0;
}
