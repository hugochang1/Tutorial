#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//761_SpecialBinaryString

//time complexity: O(n^2), space complexity: O(n^2)
string find(string str) {
    string ret;
    vector<string> v;
    int cnt = 0;
    int begin = 0;

    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '0') cnt--;
        if(str[i] == '1') cnt++;
        if(cnt == 0) {
            string substr = find(str.substr(begin + 1, i - begin - 1));
            v.push_back("1" + substr + "0");
            begin = i+1;
        }
    }

    sort(v.rbegin(), v.rend());
    for(auto& s:v) {
        ret += s;
    }
    return ret;
}

int main() {
    printf("%s\n", find("11011000").c_str()); //"11100100"
    printf("%s\n", find("10").c_str()); //"10"
    return 0;
}
