#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//2433_FindTheOriginalArrayOfPrefixXOR
//pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]

//pref[0] = arr[0]
//  arr[0] = pref[0]

//pref[1] = arr[0] ^ arr[1]
//  arr[1] = arr[0] ^ pref[1]
//  arr[1] = pref[0] ^ pref[1]

//pref[2] = arr[0] ^ arr[1] ^ arr[2]
//  arr[2] = arr[0] ^ arr[1] ^ pref[2]
//  arr[2] = pref[1] ^ pref[2]

// time complexity: O(n)
vector<int> find(vector<int> pref) {
    vector<int> out;
    if(pref.size() == 0) return out;
    
    int pre = pref[0];
    out.push_back(pref[0]);
    
    for(int i = 1; i < pref.size(); i++) {
        out.push_back(pre ^ pref[i]);
        pre = pref[i];
    }
    return out;
}

int main() {
    vector<int> ret;
    
    ret = find({5,2,0,3,1});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    // {5,7,2,3,2}
    
    ret = find({13});
    for(auto a:ret) {
        printf("%d ", a);
    }
    printf("\n");
    // {13}
    
    return 0;
}
