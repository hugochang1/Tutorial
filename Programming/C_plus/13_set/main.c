#include <iostream>
#include <set>

using namespace std;

int main() {
    set<int> s = {1,2,3};
    
    /**************************************
        insert() erase(), O(logn)
    **************************************/
    s.insert(4);  // {1,2,3,4}
    s.insert(5);  // {1,2,3,4,5}
    s.insert(5);  // {1,2,3,4,5}
    
    s.erase(3);   // {1,2,4,5}
    s.erase(3);   // {1,2,4,5} it's ok
    s.erase(2);   // {1,4,5}

    /**************************************
        find(), O(logn)
    **************************************/
    set<int>::iterator it = s.find(1);
    if (it != s.end()) {
        cout << "found 1" << endl;
    }

    it = s.find(2);
    if (it == s.end()) {
        cout << "not found 2" << endl;
    }

    for(int i : s) {
        cout << i << endl;
    }

    cout << s.empty() << endl; // 0
    cout << s.size() << endl;  // 3

    s.clear();

    cout << s.empty() << endl; // 1
    cout << s.size() << endl;  // 0

    return 0;
}
