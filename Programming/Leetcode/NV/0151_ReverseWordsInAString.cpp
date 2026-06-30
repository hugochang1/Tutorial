#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
//0151_ReverseWordsInAString

string solution(string s) {
    string ret;
    stringstream ss(s);
    string str;
    vector<string> v;
    while(getline(ss, str, ' ')) {
        if(str.size()) {
            v.push_back(str);
        }
    }

    for(int i = v.size() - 1; i >= 0; i--) {
        ret += v[i] + " ";
    }
    ret.pop_back();
    return ret;
}

int main() {
    printf("%s\n", solution("the sky is blue").c_str()); // blue is sky the
    printf("%s\n", solution("  hello world  ").c_str()); // world hello
    printf("%s\n", solution("a good  example").c_str()); // example good a

    return 0;
}
