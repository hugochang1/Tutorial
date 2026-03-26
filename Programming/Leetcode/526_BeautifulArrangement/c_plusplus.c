#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//526_BeautifulArrangement
// time complexity: O(n!)
void perm(vector<int>& v, int index, int &cnt) {
    int size = v.size();
    if(index == size - 1) {
        cnt++;
        return;
    }
    for(int i = index; i < size; i++) {
        swap(v[i], v[index]);
        if((v[i] % (i+1) == 0 || (i+1) % v[i] == 0) &&
            (v[index] % (index+1) == 0 || (index+1) % v[index] == 0)) {
            perm(v, index+1, cnt);
        }
        swap(v[i], v[index]);
    }
    
}

int find(int n) {
    int cnt = 0;
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    perm(v, 0, cnt);
    return cnt;
}


int main() {
    printf(" %d\n", find(1)); //1
    printf(" %d\n", find(2)); //2
    printf(" %d\n", find(3)); //3
    printf(" %d\n", find(4)); //8
    return 0;
}
