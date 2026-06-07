#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <cmath> // std::celi()

using namespace std;

//1962_RemoveStonesToMinimizeTheTotal

//use priority queue
//go through all stones and save to priority queue O(n)
//execute k-steps to minimize the number of stone O(klogn)
//calculate the result from priority queue O(logn)
//time complexity: O(n) or O(klogn)
int find(vector<int> stones, int k) {
    priority_queue<int> q;
    
    for(auto stone:stones) {
        q.push(stone);
    }
    
    for(int i = 0; i < k; i++) {
        int num = q.top();
        q.pop();
        num = ceil((float)num/2);
        q.push(num);
    }
    
    int ret = 0;
    while(!q.empty()) {
        ret += q.top();
        q.pop();
    }
    
    return ret;
}

int main() {
    printf("%d\n", find({5,4,9}, 2)); //12
    printf("%d\n", find({4,3,6,7}, 3)); //12
    return 0;
}
