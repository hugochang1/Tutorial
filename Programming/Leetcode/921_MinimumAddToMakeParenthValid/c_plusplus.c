#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//921_MinimumAddToMakeParenthValid

int find(string s) {
    int valid_count = 0;
    int addition_count = 0;
    
    for(char c:s) {
        if(c == '(') {
            valid_count++;
        } else {
            if(valid_count > 0) {
                valid_count--;
            } else {
                addition_count++;
            }
        }
    }
    return valid_count + addition_count;
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
