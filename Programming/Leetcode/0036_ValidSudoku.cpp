#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;
//0036_ValidSudoku

bool solution(vector<vector<string>> m) {
    //each row
    for(int i = 0; i < m.size(); i++) {
        unordered_set<string> v;
        for(int j = 0; j < m[0].size(); j++) {
            if(m[i][j][0] != '.') {
                if(v.count(m[i][j]) > 0) return false;
                v.insert(m[i][j]);
            }
        }
    }
    
    //each column
    for(int i = 0; i < m.size(); i++) {
        unordered_set<string> v;
        for(int j = 0; j < m[0].size(); j++) {
            if(m[j][i][0] != '.') {
                if(v.count(m[j][i]) > 0) return false;
                v.insert(m[j][i]);
            }
        }
    }
    
    //each 3x3
    for(int i = 0; i < m.size(); i+=3) {
        for(int j = 0; j < m.size(); j+=3) {
            unordered_set<string> v;
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    int a = i+k;
                    int b = j+l;
                    if(m[a][b][0] != '.') {
                        if(v.count(m[a][b]) > 0) return false;
                        v.insert(m[a][b]);
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    printf("%d\n", solution(
        {{"5","3",".",".","7",".",".",".","."}
        ,{"6",".",".","1","9","5",".",".","."}
        ,{".","9","8",".",".",".",".","6","."}
        ,{"8",".",".",".","6",".",".",".","3"}
        ,{"4",".",".","8",".","3",".",".","1"}
        ,{"7",".",".",".","2",".",".",".","6"}
        ,{".","6",".",".",".",".","2","8","."}
        ,{".",".",".","4","1","9",".",".","5"}
        ,{".",".",".",".","8",".",".","7","9"}}
    ));
    printf("%d\n", solution(
        {{"8","3",".",".","7",".",".",".","."}
        ,{"6",".",".","1","9","5",".",".","."}
        ,{".","9","8",".",".",".",".","6","."}
        ,{"8",".",".",".","6",".",".",".","3"}
        ,{"4",".",".","8",".","3",".",".","1"}
        ,{"7",".",".",".","2",".",".",".","6"}
        ,{".","6",".",".",".",".","2","8","."}
        ,{".",".",".","4","1","9",".",".","5"}
        ,{".",".",".",".","8",".",".","7","9"}}
    ));
    
    return 0;
}
