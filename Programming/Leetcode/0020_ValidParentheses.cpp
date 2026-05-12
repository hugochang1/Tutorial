#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>

using namespace std;

//0020_ValidParentheses

//time complexity: O(n), n is the length of string
//space complexity: O(n)
bool solution(string input) {
    stack<char> s;
    for(auto& ch:input) {
        if(ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        } else {
            char c = s.top();
            if(c == '(' && ch != ')') return false;
            if(c == '[' && ch != ']') return false;
            if(c == '{' && ch != '}') return false;
            s.pop();
        }
    }
    
    if(s.size() > 0) return false;
    return true;
}

int main() {
    printf("%d\n", solution("()")); // 1
    printf("%d\n", solution("()[]{}")); // 1
    printf("%d\n", solution("(]")); // 0
    printf("%d\n", solution("([)]")); // 0
    printf("%d\n", solution("{[]}")); // 1
    return 0;
}
