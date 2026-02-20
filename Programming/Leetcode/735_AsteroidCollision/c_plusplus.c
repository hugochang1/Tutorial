
// Hello world! Cplayground is an online sandbox that makes it easy to try out
// code.

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>

using namespace std;
// 735_AsteroidCollision

bool getSign(int value) {
    if (value > 0) return true;
    return false;
}

//time complexity: O(n)
vector<int> find(vector<int>& nums) {
    stack<int> s;
    
    for(auto n:nums) {
        if(s.empty()) {
            s.push(n);
        } else {
            while (!s.empty() && s.top() > 0 && s.top() < -n) {
                s.pop();
            }
            if (!s.empty() && s.top() > 0 && s.top() == -n) {
                s.pop();
            }
            if (s.empty() || s.top() < abs(n)) {
                s.push(n);
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

void dump(vector<int> v) {
    printf("dump ");
    for(auto a:v) {
        printf("%d ", a);
    }
    printf("\n");
}

int main() {
    vector<int> v1 = {5,10,-5};
    vector<int> v2 = {8, -8};
    vector<int> v3 = {3,5,-6,2,-1,4};
    vector<int> ret;
    ret = find(v1); dump(ret);
    ret = find(v2); dump(ret);
    ret = find(v3); dump(ret);
    
    return 0;
}
