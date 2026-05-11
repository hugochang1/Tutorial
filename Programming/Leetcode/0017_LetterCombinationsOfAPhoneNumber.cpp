#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

//0017_LetterCombinationsOfAPhoneNumber

using namespace std;

void backtrack(string& num, int index, string& current, vector<string>& out, vector<string>& mapping) {
    if(index == num.size()) {
        out.push_back(current);
        return;
    }
    
    string words = mapping[num[index] - '0'];
    for(auto& ch:words) {
        current.push_back(ch);
        backtrack(num, index + 1, current, out, mapping);
        current.pop_back();
    }
}

vector<string> solution(string num) {
    vector<string> ret;
    vector<string> mapping = {"", "", "abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    string current;
    backtrack(num, 0, current, ret, mapping);
    return ret;
}

int main() {
    vector<string> ret;
    
    ret = solution("23");
    printf("size=%zu\n", ret.size());
    for(auto& s:ret) {
        printf("%s\n", s.c_str());
    }
    printf("\n");
    /*
    size=9
    ad
    ae
    af
    bd
    be
    bf
    cd
    ce
    cf
    */
    return 0;
}
