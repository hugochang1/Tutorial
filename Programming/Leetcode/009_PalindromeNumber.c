#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//009_PalindromeNumber
bool solution(int n) {
    if(n < 0) return false;
    vector<int> v;
    
    while(n > 0) {
        v.push_back(n % 10);
        n /= 10;
    }
    
    int l = 0;
    int r = v.size() - 1;
    while(l <= r) {
        if(v[l] != v[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main() {
    printf("%d\n", solution(121)); // 1
    printf("%d\n", solution(-121)); // 0
    printf("%d\n", solution(10)); // 0
    return 0;
}
