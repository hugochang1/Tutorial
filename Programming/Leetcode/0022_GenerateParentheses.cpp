#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//0022_GenerateParentheses

void solution(int n, int n1, int n2, string& current, vector<string>& out) {
    if(n1 == n && n2 == n) {
        out.push_back(current);
        return;
    }
    if(n1 < n) {
        current += '(';
        solution(n, n1+1, n2, current, out);
        current.pop_back();
    }
    if(n2 < n && n2 < n1) {
        current += ')';
        solution(n, n1, n2+1, current, out);
        current.pop_back();
    }
}

vector<string> solution(int n) {
    vector<string> ret;
    string current;
    solution(n, 0, 0, current, ret);
    return ret;
}

int main() {
    vector<string> ret;
    
    ret = solution(3);
    
    printf("size=%zu\n", ret.size());
    for(auto& s:ret) {
        printf("%s\n", s.c_str());
    }
    /*
    5
    ((()))
    (()())
    (())()
    ()(())
    ()()()
    */
    return 0;
}
