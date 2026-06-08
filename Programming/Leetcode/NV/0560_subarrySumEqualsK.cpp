#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;
//0560_subarrySumEqualsK

//time complexity: O(n)
int solution(vector<int> nums, int k) {
    int cnt = 0;
    int sum = 0;
    unordered_map<int, int> m; //sum, count
    m[0] = 1;

    for(auto& num:nums) {
        sum += num;
        if(m.count(sum - k)) {
            cnt += m[sum - k];
        }
        m[sum]++;
    }
    return cnt;
}

int main() {
    printf("%d\n", solution({1,1,1}, 2)); //2
    printf("%d\n", solution({1,2,3}, 3)); //2
    return 0;
}
