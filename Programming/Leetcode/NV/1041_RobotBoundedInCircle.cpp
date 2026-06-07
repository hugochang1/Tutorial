#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//1041_RobotBoundedInCircle

bool find(string dirs) {
    int x = 0, y = 0;
    int cnt = 0;
    
    vector<vector<int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};
    
    for(auto dir:dirs) {
        if(dir == 'L') {
            cnt = (cnt + 3) % 4;
        } else if(dir == 'R') {
            cnt = (cnt + 1) % 4;
        } else {
            x += moves[cnt][0];
            y += moves[cnt][1];
        }
    }
    
    if(x==0 && y==0) return true;
    if(cnt == 0) return false;
    return true;
}

int main() {
    printf("%d\n", find("GGLLGG"));  //1
    printf("%d\n", find("GG"));  //0
    printf("%d\n", find("GL"));  //1
    printf("%d\n", find("LLLL"));  //1
    return 0;
}
