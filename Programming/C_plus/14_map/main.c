#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> m1 = {
        {1, 10},
        {2, 20},
        {3, 30},
    };

    /**************************************
        find(), O(logn)
    **************************************/
    map<int, int>::iterator it = m1.find(1);
    if (it != m1.end()) {
        cout << "1 is in mp1" << endl;
    }
    it = m1.find(4);
    if (it == m1.end()) {
        cout << "4 is not in mp1" << endl;
    }

    /**************************************
        insert(), O(logn)
    **************************************/
    m1.insert(pair<int, int>(4, 40)); // {{1,10},{2,20},{3,30},{4,40}}
    m1.insert(pair<int, int>(5, 50)); // {{1,10},{2,20},{3,30},{4,40},{5,50}}

    /**************************************
        erase(), O(logn)
    **************************************/
    int ret = m1.erase(1); // {{2,20},{3,30},{4,40},{5,50}}
    cout << ret << endl; // 1 means delete key 1 and its value successfully
    ret = m1.erase(1);
    cout << ret << endl; // 0 means there is key 1 in map

    /**************************************
        traverse
    **************************************/
    for (pair<int, int> i : m1) {
        cout << i.first << " " << i.second << endl;
    }

    cout << m1.size() << endl; // 4
    cout << m1.empty() << endl; // 0

    m1.clear();

    cout << m1.size() << endl; // 0
    cout << m1.empty() << endl; // 1

    return 0;
}
