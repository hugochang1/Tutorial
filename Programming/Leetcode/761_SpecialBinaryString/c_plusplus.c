#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

//761_SpecialBinaryString

string find(string s) {
    int i = 0;
    int j = 0;
    int count = 0;
    vector<string> v;
    for(i = 0; i < s.size(); i++) {
        if(s[i] == '0') {
            count--;
        } 
        if(s[i] == '1') {
            count++;
        }
        if(count == 0) {
            string inner_s = s.substr(j+1, i-j-1);
            string max_inner_s = find(inner_s);
            v.push_back("1" + max_inner_s + "0");
            j = i + 1;
        }
    }
    
    sort(v.rbegin(), v.rend());
    string out;
    
    for(auto a:v) {
        out += a;
    }
    return out;
}

int main() {
    string s = "11011000";
    printf("%s\n", find(s).c_str());
    //output 11100100
    return 0;
}
