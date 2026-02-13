#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Time complexity: O(N), N is the number of elements in list
// Space complexity: O(K) or O(N), K is the number of bucket in unordered_map
vector<pair<int, int>> TwoSum(int target, int* v, int size) {
    vector<pair<int, int>> rets; // positions
    unordered_map<int, int> m; //  remaind value, positions
    int i;
    
    for(i = 0; i < size; i++) {
        auto ret = m.find(v[i]);
        if (ret != m.end()) {
            rets.push_back({ret->second, i});
        }
        m[target - v[i]] = i;
    }
    
    return rets;
}

int main() {
    int target = 5;
    int v[] = {0, 1, 2, 3, 4, 5};
    
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
