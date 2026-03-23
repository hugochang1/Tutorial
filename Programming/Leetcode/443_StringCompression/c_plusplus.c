#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//443_StringCompression

void solution(string& s) {
    if(s.size() == 0) return;
    int read_pos = 0;
    int write_pos = 0;
    
    while(read_pos < s.size()) {
        int current_char = s[read_pos++];
        int cnt = 1;
        
        while(read_pos < s.size() && current_char == s[read_pos]) {
            read_pos++;
            cnt++;
        }
        
        s[write_pos++] = current_char;
        if(cnt > 1) {
            string cnt_str = to_string(cnt);
            for(auto c:cnt_str) {
                s[write_pos++] = c;
            }
        }
    }
    s[write_pos++] = 0;
}

int main() {
    string s = "aabbccc";
    solution(s);
    printf("%s\n", s.c_str()); // a2b2c3
    
    s = "a";
    solution(s);
    printf("%s\n", s.c_str()); // a
    
    s = "abbbbbbbbbbbb";
    solution(s);
    printf("%s\n", s.c_str()); // ab12
    return 0;
}
