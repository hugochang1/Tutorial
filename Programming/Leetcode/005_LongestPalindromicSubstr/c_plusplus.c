#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find(const char* str, char* out, int size) {
    int len = strlen(str);
    if (len == 0) return;
    int i, j;
    int max_count = 1;
    int max_begin = 0, max_end = 0;
    for(i = 0; i < len; i++) {
        for (j = 1; (i - j) >= 0 && (i + j) < size; j++) {
            int start = i - j;
            int end = i + j;
            if (str[start] == str[end]) {
                int diff = (end - start) + 1;
                if (diff > max_count) {
                    max_count = diff;
                    max_begin = start;
                    max_end = end;
                }
            } else {
                break;
            }
        }
    }
    memcpy(out, str + max_begin, max_count);
}

int main() {
    const char* str = "abab12567";
    char out[1024] = {0};
    //expect output: bab or aba
    
    find(str, out, sizeof(out));
    printf("out=%s\n", out);
    return 0;
}
