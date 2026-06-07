#include <stdio.h>
#include <string>

using namespace std;
//443_StringCompression

void solution(string& str) {
    int i = 0;
    int j = 0;

    while(i < str.size()) {
        int cnt = 1;
        j++;
        while(i+1 < str.size() && str[i+1] == str[i]) {
            cnt++;
            i++;
        }
        if(cnt > 1) {
            string cnt_str = to_string(cnt);
            for(auto& s:cnt_str) {
                str[j] = s;
                j++;
            }
        }
        i++;
    }
    str[j] = 0;
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
