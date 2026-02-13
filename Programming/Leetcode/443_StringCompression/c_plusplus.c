#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compress(char* str, int size) {
    int read_index = 0;
    int write_index = 0;
    
    if (size == 0) return 0;
    
    while (read_index < size) {
        char curr_char = str[read_index];
        int count = 0;
        
        while (read_index < size && curr_char == str[read_index]) {
            count++;
            read_index++;
        }
        
        str[write_index] = curr_char;
        write_index++;
        
        if (count > 1) {
            char tmp[10] = {0};
            int len = sprintf(tmp, "%d", count);
            int j = 0;
            for(j = 0; j < len; j++) {
                str[write_index] = tmp[j];
                write_index++;
            }
        }
    }
    return write_index;
}


int main() {
    char str[] = "aabbccc";
    int ret = compress(str, strlen(str));
    printf("ret=%d str=%s\n", ret, str); // ret=6 str=a2b2c3c
    
    return 0;
}
