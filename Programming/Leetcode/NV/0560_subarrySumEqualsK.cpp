#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

// time complexity: O(n), space complexity: O(n)
int solution(vector<int> input, int target) {
    int i = 0;
    int sum = 0;
    int count = 0;
    unordered_map<int, int> m; // sum, count
    // I record all sum data from iteration i to unordered_map
    // if I can find the summary from unordered_map, j which means 
    // index j+1 to index i can be sumed to target value
    
    m[0] = 1;
    
    for (i = 0; i < input.size(); i++) {
        sum += input[i];
        if (m.count(sum - target)) {
            count += m.count(sum - target);
        }
        m[sum]++;
    }
    return count;
}

int main() {
    vector<int> v = {1,2,3,3,3,2,1};
    int ret = solution(v, 3);
    printf("ret=%d\n", ret);
    return 0;
}
