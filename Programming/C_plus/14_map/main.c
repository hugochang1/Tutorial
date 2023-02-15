#include <iostream>
#include <map>

using namespace std;

int main() {
    /*************************************
        init
    **************************************/
    map<int, string> m;
    map<int, string> m1 = {{1, "a"}, {2, "b"}, {3, "c"}};
    
    /*************************************
        access
    **************************************/
    cout << m1[1] << endl; // a
    cout << m1[2] << endl; // b
    cout << m1[10] << endl; // (empty)

    m1[1] = "k"; //{{1, "k"}, {2, "b"}, {3, "c"}, {10,}}
    m1[1] = "a"; //{{1, "a"}, {2, "b"}, {3, "c"}, {10,}}
    m1[4] = "g"; //{{1, "a"}, {2, "b"}, {3, "c"}, {4, "g"}, {10,}}

    /*************************************
        traverse
    **************************************/
    for (pair<int, string> a : m1) {
        cout << a.first << " " << a.second << endl;
        // 1 a
        // 2 b
        // 3 c
        // 4 g
        // 10 (empty)
    }
    
    /*************************************
        find
    **************************************/
    map<int, string>::iterator it;
    it = m1.find(1);
    if (it != m1.end()) {
        cout << "found 1" << endl;
        cout << (*it).first << " " << (*it).second << endl; // 1 a
    }
    
    it = m1.find(99);
    if (it == m1.end()) {
        cout << "not found 99" << endl;
    }
    
    /*************************************
        erase
    **************************************/
    m1.erase(1); //{{2, "b"}, {3, "c"}, {4, "g"}, {10,}}
    m1.erase(10); //{{2, "b"}, {3, "c"}, {4, "g"}}
    for (pair<int, string> a : m1) {
        cout << a.first << " " << a.second << endl;
    }

    /*************************************
        size
    **************************************/
    cout << m1.size() << endl; // 5
    cout << m1.empty() << endl; // 0

    m1.clear();

    cout << m1.size() << endl; // 0
    cout << m1.empty() << endl; // 1
    cout << m1.max_size() << endl;

    return 0;
}
