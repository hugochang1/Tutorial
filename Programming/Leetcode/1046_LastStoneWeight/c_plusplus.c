#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

//1046_LastStoneWeight

int find(vector<int> s) {
    priority_queue<int> q;
    for(auto a:s) {
        q.push(a);
    }
    
    while(q.size() > 1) {
        int first = q.top();
        q.pop();
        int second = q.top();
        q.pop();
        
        q.push(first - second);
    }
    return q.top();
}

int main() {
    vector<int> s = {2,7,4,1,8,1}; // 1
    printf("%d\n", find(s));
    
    s = {5};
    printf("%d\n", find(s)); // 5
    return 0;
}
