#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <vector>

using namespace std;

# if 0
// TODO the output result is not expected
/*
result:
1 2 3 4 
1 4 3 2 
2 3 4 1 
2 4 3 1 
3 2 4 1 
4 2 3 1

expected result:
1 2 3 4 
1 4 3 2 
2 1 3 4 
2 4 3 1 
3 2 1 4 
3 4 1 2 
4 2 3 1 
4 1 3 2 
*/
// Time Complexity: O(n!)
void permutatRecu(vector<int>& input, int pos, vector<vector<int>>& out, bool *visited) {
    if (pos == (input.size() - 1)) {
        for(auto a:input) {
            printf("%d ", a);
        }
        printf("\n");
        out.push_back(input);
    } else {
        for(int i = pos; i < input.size(); i++) {
            swap(input[pos], input[i]);
            if(!visited[i] && (input[i] % (i+1) == 0 || (i+1) % input[i] == 0)) {
                printf("pos=%d i=%d value=%d\n", pos, i, input[i]);
                visited[i] = true;
                permutatRecu(input, pos + 1, out, visited);
                visited[i] = false;
            }
            swap(input[pos], input[i]);
        }
    }
}

vector<vector<int>> permutate(vector<int> input) {
    vector<vector<int>> out;
    bool *visited = (bool*)malloc(out.size());
    memset(visited, 0, sizeof(out.size()));
    permutatRecu(input, 0, out, visited);
    free(visited);
    return out;
}

#else

// Time Complexity: O(n! x n)
void permutatRecu(vector<int>& input, int pos, vector<vector<int>>& out) {
    if (pos == (input.size() - 1)) {
        bool pass = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] % (i+1) != 0 && (i+1) % input[i] != 0) {
                pass = false;
                break;
            }
        }
        if (pass) out.push_back(input);
        return;
    }
    int i;
    for (i = pos; i < input.size(); i++) {
        swap(input[pos], input[i]);
        permutatRecu(input, pos + 1, out);
        swap(input[pos], input[i]);
    }
}

vector<vector<int>> permutate(vector<int> input) {
    vector<vector<int>> out;
    permutatRecu(input, 0, out);
    return out;
}

#endif

int main() {
    //vector<int> input = {1,2,3};
    /* output
    1 2 3 
    2 1 3 
    3 2 1 
    */
    vector<int> input = {1,2,3,4};
    /* output
    1 2 3 4 
    1 4 3 2 
    2 1 3 4 
    2 4 3 1 
    3 2 1 4 
    3 4 1 2 
    4 2 3 1 
    4 1 3 2 
    */
    vector<vector<int>> ret = permutate(input);
    for(auto a:ret) {
        for(auto b:a) {
            printf("%d ", b);
        }
        printf("\n");
    }
    return 0;
}
