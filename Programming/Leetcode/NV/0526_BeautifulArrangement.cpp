#include <stdio.h>
#include <vector>

using namespace std;
//526_BeautifulArrangement

void recur(vector<int>& v, int index, vector<vector<int>>& out) {
    if(index == v.size()) {
        bool check = true;
        for(int i = 0; i < v.size(); i++) {
            if(v[i] % (i+1) != 0 && (i+1) % v[i] != 0) {
                check = false;
                break;
            }
        }
        if(check) {
            out.push_back(v);
        }
    }
    for(int i = index; i < v.size(); i++) {
        swap(v[i], v[index]);
        recur(v, index + 1, out);
        swap(v[i], v[index]);
    }
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> ret;
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    recur(v, 0, ret);
    return ret;
}

int main() {
    vector<vector<int>> ret;
    ret = solution(4);
    printf("size=%d\n", ret.size());
    for(auto& r:ret) {
        printf("{");
        for(auto& a:r) {
            printf("%d ", a);
        }
        printf("}\n");
    }
    printf("\n");
    /*
    size=8
    {1 2 3 4 }
    {1 4 3 2 }
    {2 1 3 4 }
    {2 4 3 1 }
    {3 2 1 4 }
    {3 4 1 2 }
    {4 2 3 1 }
    {4 1 3 2 }
    */
    return 0;
}
