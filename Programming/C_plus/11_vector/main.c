#include <iostream>
#include <vector>

using namespace std;

int main() {
    //vector is a contigous memory 
    /*************************************
        init
    **************************************/
    vector<int> v; // {}
    vector<int> v1 = {1,2,3}; // {1,2,3}
    vector<int> v2({1,2,3}); // {1,2,3}
    vector<int> v3 = v2;
    int n[] = {1,2,3};
    vector<int> v4(n, n+3); // {1,2,3}
    vector<int> v5(n+1, n+2); // {2}

    /**************************************
        access, O(1)
    **************************************/
    //cout << v[0] << endl; // Segmentation fault
    cout << v1[0] << endl; // 1
    cout << v1[1] << endl; // 2
    cout << v1[2] << endl; // 3

    v1[1] = 10; // {1,10,3}
    v1[1] = 2;  // {1,2,3}

    /**************************************
        traverse
    **************************************/
    for (int v : v1) {
        cout << v << endl; // 1 2 3
    }

    for (size_t i = 0; i < v1.size(); i++) {
        cout << v1[i] << endl; // 1 2 3
    }

    /**************************************
        add new at the end, O(1)
    **************************************/
    v1.push_back(4); // {1,2,3,4}
    v1.push_back(5); // {1,2,3,4,5}

    /**************************************
        remove from the end, O(1)
    **************************************/
    v1.pop_back(); // {1,2,3,4}
    v1.pop_back(); // {1,2,3}

    /**************************************
        insert, O(n)
    **************************************/
    v1.insert(v1.begin(), 10);   // {10,1,2,3}
    v1.insert(v1.begin()+2, 11); // {10,1,11,2,3}

    /**************************************
        erase, O(n)
    **************************************/
    v1.erase(v1.begin());  // {1,11,2,3}
    v1.erase(v1.begin()+1);  // {1,2,3}

    return 0;
}
