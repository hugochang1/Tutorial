#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Time Complexity: O(n^2)
void find(const char* str, char* out) {
    int len = strlen(str);
    if (len == 0) return;
    int i, j;
    int max_len = 1, max_begin = 0, max_end = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; (i - j) >= 0 && (i + j) < len; j++) {
            int begin = i - j;
            int end = i + j;
            if (str[begin] == str[end]) {
                int curr_len = (end - begin) + 1;
                if (curr_len > max_len) {
                    max_len = curr_len;
                    max_begin = begin;
                    max_end = end;
                }
            } else {
                break;
            }
        }
    }
    memcpy(out, str + max_begin, max_len);
}

int main() {
    const char* str = "ababd";
    char out[1024] = {0};
    //expect output: bab or aba
    
    find(str, out);
    printf("out=%s\n", out);
    return 0;
}
