#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// time complexity: O(n!), space complexity: O(n!)
void permutateRecu(vector<int> &input, int pos, vector<vector<int>> &out) {
    if (pos == (input.size() - 1)) {
        out.push_back(input);
    } else {
        int i;
        for (i = pos; i < input.size(); i++) {
            swap(input[pos], input[i]);
            if (input[pos] % (pos + 1) == 0 || (pos + 1) % input[pos] == 0)
                permutateRecu(input, pos + 1, out);
            swap(input[pos], input[i]);
        }
    }
}

vector<vector<int>> permutate(vector<int> input) {
    vector<vector<int>> out;
    permutateRecu(input, 0, out);
    return out;
}

int main() {
    vector<int> v = {1,2,3,4};
    vector<vector<int>> ret = permutate(v);
    for(auto a:ret) {
        for(auto b:a) {
            printf("%d ", b);
        }
        printf("\n");
    }
    /*
    1 2 3 4 
    1 4 3 2 
    2 1 3 4 
    2 4 3 1 
    2 4 1 3 
    3 2 1 4 
    3 4 1 2 
    4 2 3 1 
    4 2 1 3 
    4 1 3 2 
    */
    return 0;
}
