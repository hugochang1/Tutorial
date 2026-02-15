#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>

using namespace std;

// Time Complexity: O(N)
int findLength(const char* str, int size) {
    if (size == 0) return 0;
    unordered_map<char, int> m;
    int i = 0;
    int max_len = 0;
    int prev = 0;
    for (i = 0; i < size; i++) {
        auto ret = m.find(str[i]);
        if(ret == m.end()) {
            m[str[i]] = i;
            int curr_len = (i - prev) + 1;
            if (max_len < curr_len) {
                max_len = curr_len;
            }
        } else {
            int index = m[str[i]];
            prev = index + 1;
            m[str[i]] = i;
        }
    }
    return max_len;
}

int main() {
    const char* str = "baaaa123";
    
    int ret = findLength(str, strlen(str));
    printf("ret=%d\n", ret);
    
    return 0;
}
