#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//0050_Pow
//time complexity: O(n)
float solution(float x, int n) {
    float ret = 1;
    if(n == 0) return ret;
    if(n < 0) {
        n = -n;
        x = 1/x;
    }
    
    while(n > 0) {
        ret *= x;
        n--;
    }
    
    return ret;
}

int main() {
    printf("%f\n", solution(2.0, 10)); //1024
    printf("%f\n", solution(2.1, 3)); //9.261
    printf("%f\n", solution(2.0, -2)); // 0.25
    return 0;
}
