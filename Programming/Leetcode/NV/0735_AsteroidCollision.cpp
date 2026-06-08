#include <stdio.h>
#include <vector>
#include <stack>
#include <cmath>
//735_AsteroidCollision

using namespace std;

vector<int> find(vector<int> as) {
    vector<int> ret;
    deque<int> q;
    int i = 0;

    while(i < as.size()) {
        if(q.empty()) {
            if(as[i] < 0) {
                ret.push_back(as[i]);
                i++;
            } else {
                q.push_back(as[i]);
                i++;
            }
        } else {
            if(as[i] > 0) {
                q.push_back(as[i]);
                i++;
            } else {
                while(!q.empty() && q.back() < abs(as[i])) {
                    q.pop_back();
                }
                if(q.empty()) {
                    ret.push_back(as[i]);
                    i++;
                } else if(!q.empty() && q.back() == abs(as[i])) {
                    q.pop_back();
                    i++;
                } else {
                    i++;
                }
            }
        }
    }

    for(auto& data:q) {
        ret.push_back(data);
    }

    return ret;
}

int main() {
    vector<int> ret;
    
    ret = find({5,10,-5});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");//{5,10}
    
    ret = find({8, -8});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");//{}
    
    ret = find({10, 2, -5});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");//{10}
    
    ret = find({-1, -2, 10, 2, -5});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");//{-1, -2, 10}
    return 0;
}
