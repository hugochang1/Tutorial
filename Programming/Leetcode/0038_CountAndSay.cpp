#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//0038_CountAndSay

string solution(int n) {
    string ret = "1";
    while(n-- > 1) {
        string current;
        int i = 0;
        
        while(i < ret.size()) {
            char last = ret[i];
            int cnt = 1;
            i++;
            while(i < ret.size() && last == ret[i]) {
                cnt++;
                i++;
            }
            current += to_string(cnt) + last;
        }
        ret = current;
    }
    return ret;
}

int main() {
    for(int i = 1; i <= 6; i++) {
        printf("n=%d %s\n", i, solution(i).c_str());
        //n=1, 1
        //n=2, 11
        //n=3, 21
        //n=4, 1211
        //n=5, 111221
        //n=6, 312211
    }
    
    return 0;
}
