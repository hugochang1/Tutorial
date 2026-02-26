#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//1041_RobotBoundedInCircle
//time complexity: O(n) which n is the length of instruction string
bool find(string instructions) {
    vector<vector<int>> moves = {{0,1}, {1,0}, {0,-1}, {-1,0}}; //north, east, south, west
    vector<int> pos = {0, 0};
    int dir = 0; // 0=north, 1=east, 2=south, 3=west
    
    for(char c:instructions) {
        switch(c) {
            case 'G':
                pos[0] += moves[dir][0];
                pos[1] += moves[dir][1];
                break;
            case 'R':
                dir = (dir + 1) % 4;
                break;
            case 'L':
                dir = (dir + 3) % 4;
                break;
        }
    }
    if(pos[0] == 0 && pos[1] == 0) return true;
    if(dir != 0) return true;
    return false;
}

int main() {
    printf("%d\n", find("GGLLGG"));  //1
    printf("%d\n", find("GG"));  //0
    printf("%d\n", find("GL"));  //0
    return 0;
}
