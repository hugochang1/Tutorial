#include <stdio.h>
#include <vector>
#include <deque>

using namespace std;

//735_AsteroidCollision
//Time complexity: O(n)
vector<int> find(vector<int> nums) {
    vector<int> ret;
    deque<int> q;
    
    for(int i = 0; i < nums.size(); i++) {
        if(q.empty()) {
            q.push_back(nums[i]);
            continue;
        }
        if(nums[i] > 0) {
            q.push_back(nums[i]);
            continue;
        }
        while(!q.empty() && q.back() > 0 && q.back() < abs(nums[i])) {
            q.pop_back();
        }
        if(q.empty()) {
            q.push_back(nums[i]);
            continue;
        }
        if(q.back() > 0 && q.back() == abs(nums[i])) {
            q.pop_back();
        } else if(q.back() > 0 && q.back() > abs(nums[i])) {
        } else {
            q.push_back(nums[i]);
        }
    }
    
    for(auto a:q) {
        ret.push_back(a);
    }
    
    return ret;
}

int main() {
    vector<int> ret;
    
    ret = find({5,10,-5});//{5,10}
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = find({8, -8});//{}
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    
    ret = find({10, 2, -5});//{10}
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    return 0;
}

