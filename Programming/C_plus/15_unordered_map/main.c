#include <iostream>
#include <unordered_map>

using namespace std;

void dump(unordered_map<int, int>& m) {
    printf("dump map: ");
    for (auto e : m) {
        cout << e.first << "/" << e.second << " ";
    }
    printf("\n");
}

int main() {
    unordered_map<int, int> m = {
        {1, 11}, {2, 22}, {3, 33},
    };
    
    dump(m); // dump map: 3/33 2/22 1/11
    
    m[4] = 44;
    m[5] = 55;
    dump(m); // 5/55 4/44 1/11 2/22 3/33

    auto r = m.erase(1);
    cout << "erase result:" << r << endl; // erase result:1
    r = m.erase(1);
    cout << "erase result:" << r << endl; // erase result:0
    
    auto r2 = m.insert(pair<int, int>(1, 11));
    cout << "insert result:" << r2.second << endl; // insert result:1
    r2 = m.insert(pair<int, int>(1, 11));
    cout << "insert result:" << r2.second << endl; // insert result:0

    m.clear();
    dump(m); // dump map:
    
    return 0;
}
