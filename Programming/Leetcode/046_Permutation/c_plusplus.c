#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

void permutateRecu(vector<int>& input, int left, int right, vector<vector<int>>& out) {
    if (left == right) {
        out.push_back(input);
    } else {
        int i;
        for (i = left; i < input.size(); i++) {
            swap(input[left], input[i]);
            permutateRecu(input, left+1, right, out);
            swap(input[left], input[i]);
        }
    }
}

vector<vector<int>> permutation(vector<int> input) {
    vector<vector<int>> out;
    permutateRecu(input, 0, input.size(), out);
    return out;
}

int main() {
    auto ret = permutation({1,2,3});
    
    for (auto a: ret) {
        for (auto b: a) {
            printf("%d ", b);
        }
        printf("\n");
    }
    /*
    1 2 3 
    1 3 2 
    2 1 3 
    2 3 1 
    3 2 1 
    3 1 2 
    */
    
    return 0;
}

