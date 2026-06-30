#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
//0344_ReverseString

void solution(string& s) {
    int n = s.size();
    for(int i = 0; i < n/2; i++) {
        swap(s[i], s[n-i-1]);
    }
}

int main() {
    string s;
    s = "hello";
    solution(s);
    printf("%s\n", s.c_str()); //olleh
    
    s = "Hannah";
    solution(s);
    printf("%s\n", s.c_str()); //hannaH

    return 0;
}
