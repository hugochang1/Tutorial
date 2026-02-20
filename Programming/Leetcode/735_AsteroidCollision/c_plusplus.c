// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>

using namespace std;

vector<int> find(vector<int> &input) {
    stack<int> s;
    for(auto n:input) {
        if(s.empty()) {
            s.push(n);
        } else {
            while(!s.empty() && s.top() > 0 && s.top() < -n) {
                s.pop();
            }
            if(!s.empty() && s.top() > 0 && s.top() == -n) {
                s.pop();
            } else {
                if(s.empty() || s.top() < abs(n)) {
                    s.push(n);
                }
            }
        }
    }
    
    vector<int> ret(s.size());
    int i = s.size();
    while(!s.empty()) {
        ret[--i] = s.top();
        s.pop();
    }
    return ret;
}

void dump(vector<int> &input) {
    printf("dump ");
    for(auto a:input) {
        printf("%d ", a);
    }
    printf("\n");
}

int main() {
    vector<int> v1 = {5,10,-5};
    vector<int> v2 = {8, -8};
    vector<int> v3 = {3,5,-6,2,-1,4};
    vector<int> ret;
    ret = find(v1); dump(ret); // 5 10
    ret = find(v2); dump(ret); // 
    ret = find(v3); dump(ret); // -6 2 4
    return 0;
}
