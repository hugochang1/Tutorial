#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> q = {1,2,3};

    /**************************************
        push_back() push_front(), O(1)
    **************************************/
    q.push_back(4);  // {1,2,3,4}
    q.push_back(5);  // {1,2,3,4,5}
    q.push_front(0); // {0,1,2,3,4,5}

    /**************************************
        pop_back() pop_front(), O(1)
    **************************************/
    q.pop_back();    // {0,1,2,3,4}
    q.pop_back();    // {0,1,2,3}
    q.pop_front();   // {1,2,3}
    q.pop_front();   // {2,3}

    q[0] = 10;       // {10,3}
    q[0] = 2;        // {2,3}

    /**************************************
        insert() erase(), O(n)
    **************************************/
    q.insert(q.begin(), 1); // {1,2,3}
    q.insert(q.begin()+1, 10); // {1,10,2,3}
    q.erase(q.begin());   // {10,2,3}
    q.erase(q.begin()+1); // {10,3}

    cout << q.size() << endl;  // 2
    cout << q.empty() << endl; // 0

    /**************************************
        traverse
    **************************************/
    for (int a : q) {
        cout << a << endl; //10 3
    }

    return 0;
}
