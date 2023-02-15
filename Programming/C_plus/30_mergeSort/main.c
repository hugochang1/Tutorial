#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void merge_sort(vector<int>& v, int left, int right) {
    if (left >= right) return;
    int mid = (left+right)/2;
    merge_sort(v, left, mid);
    merge_sort(v, mid+1, right);

    deque<int> l(v.begin()+left, v.begin()+mid+1);
    deque<int> r(v.begin()+mid+1, v.begin()+right+1);
    int k = left;

    while(l.size() && r.size()) {
        if (l[0] <= r[0]) {
            v[k] = l[0];
            l.pop_front();
        } else {
            v[k] = r[0];
            r.pop_front();
        }
        k++;
    }
    while(l.size()) {
        v[k] = l[0];
        l.pop_front();
        k++;
    }
    while(r.size()) {
        v[k] = r[0];
        r.pop_front();
        k++;
    }
    
}

int main() {
    vector<int> v = {5,4,3,2,1};
    merge_sort(v, 0, v.size()-1);
    for (auto i : v) {
        cout << i << endl;
    }
    return 0;
}
