#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque q = {1,2,3};

    q.push_back(4);  // {1,2,3,4}
    q.push_back(5);  // {1,2,3,4,5}
    q.push_front(0); // {0,1,2,3,4,5}

    q.pop_back();    // {0,1,2,3,4}
    q.pop_back();    // {0,1,2,3}
    q.pop_front();   // {1,2,3}
    q.pop_front();   // {2,3}

    q[0] = 10;       // {10,3}
    q[0] = 2;        // {2,3}

    q.insert(q.begin(), 1); // {1,2,3}
    q.insert(q.begin()+1, 10); // {1,10,2,3}
    q.erase(q.begin());   // {10,2,3}
    q.erase(q.begin()+1); // {10,3}

    cout << q.size() << endl;  // 2
    cout << q.empty() << endl; // 0

    for (auto a : q) {
        cout << a << endl; //10 3
    }

    return 0;
}