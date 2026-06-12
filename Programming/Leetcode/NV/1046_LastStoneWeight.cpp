#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

//1046_LastStoneWeight

int find(vector<int> stones) {
    priority_queue<int> q;
    for(auto& stone:stones) {
        q.push(stone);
    }

    while(q.size() > 1) {
        int s1 = q.top();
        q.pop();
        int s2 = q.top();
        q.pop();
        int delta = s1 - s2;
        if(delta) {
            q.push(delta);
        }
    }

    return q.top();
}

int main() {
    printf("%d\n", find({2,7,4,1,8,1})); // 1
    printf("%d\n", find({5})); // 5
    return 0;
}
