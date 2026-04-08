#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//761_SpecialBinaryString

string find(string s) {
    vector<string> v;
    int cnt = 0;
    int start = 0;
    
    for(int i = 0; i < s.size(); i++) {
        char ch = s[i];
        if(ch == '0') {
            cnt--;
        } else if(ch == '1') {
            cnt++;
        }
        
        if(cnt == 0) {
            string sub = find(s.substr(start + 1, i - start - 1));
            v.push_back('1' + sub + '0');
            start = i + 1;
        }
    }
    
    sort(v.begin(), v.end(), greater<string>());
    
    string out;
    for(auto a:v) {
        out += a;
    }
    
    return out;
}

int main() {
    printf("%s\n", find("11011000").c_str()); //"11100100"
    printf("%s\n", find("10").c_str()); //"10"
    
    return 0;
}
