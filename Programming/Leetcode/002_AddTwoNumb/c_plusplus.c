#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> AddTwonNum(const vector<int>& v1, const vector<int>& v2) {
    vector<int> ret;
    int m = max(v1.size(), v2.size());
    int carry = 0;
    int sum = 0;
    
    for(int i = 0; i <= m; i++) {
        sum = carry;
        carry = 0;
        if (i < v1.size()) {
            sum += v1[i];
        }
        if (i < v2.size()) {
            sum += v2[i];
        }
        carry = sum/10;
        sum = sum % 10;
        
        if (i == m && sum == 0 && carry == 0) break;
        ret.push_back(sum);
    }
    return ret;
}

int main() {
    vector<int> v1 = {3,4,3};
    vector<int> v2 = {2,6,4};
    
    vector<int> ret = AddTwonNum(v1, v2);
    for (auto a : ret) {
        printf("%d ", a); // 5 0 8 
    }
    printf("\n");
    
    return 0;
}
