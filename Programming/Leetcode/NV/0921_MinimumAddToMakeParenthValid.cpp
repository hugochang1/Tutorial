#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//921_MinimumAddToMakeParenthValid
int find(string s) {
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
            cnt++;
        } else {
            cnt--;
        }
    }
    return abs(cnt);
}

int main() {
    printf("%d\n", find("())")); // 1
    printf("%d\n", find("(((")); // 3
    printf("%d\n", find("")); // 0
    printf("%d\n", find(")))")); // 3
    printf("%d\n", find("())))")); // 3
    printf("%d\n", find(")))()")); // 3
    printf("%d\n", find("(((()")); // 3
    printf("%d\n", find("()(((")); // 3
    return 0;
}
