#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Time complexity: O(N), N is the number of elements in list
// Space complexity: O(K) or O(N), K is the number of bucket in unordered_map
bool TwoSum(int target, int* list, int size, int *pos1, int *pos2) {
    unordered_map<int, int> m;
    
    for (int i = 0; i < size; i++) {
        auto ret = m.find(list[i]);
        if (ret != m.end()) {
            *pos1 = ret->second;
            *pos2 = i;
            return true;
        }
        m[target - list[i]] = i;
    }
    return false;
}

vector<pair<int, int>> TwoSum(int target, int *list, int size) {
    vector<pair<int, int>> rets;
    unordered_map<int, int> m;
    
    for(int i = 0; i < size; i++) {
        auto it = m.find(list[i]);
        if(it != m.end()) {
            rets.push_back({it->second, i});
        }
        m[target - list[i]] = i;
    }
    
    return rets;
}

int main() {
    int target = 5;
    int v[] = {0, 1, 2, 3, 4, 5};
    
    int pos1 = 0, pos2 = 0;
    bool ret = TwoSum(target, v, sizeof(v)/4, &pos1, &pos2);
    printf("ret=%d %d %d\n", ret, pos1, pos2); // ret=1 2 3
    
    auto rets = TwoSum(target, v, sizeof(v)/4);
    for (auto a : rets) {
        cout << a.first << " " << a.second << endl;
        /*
        2 3
        1 4
        0 5
        */
    }
    
    return 0;
}
