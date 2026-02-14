#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define X_NUM 5
#define Y_NUM 5

int visisted[Y_NUM][X_NUM];
int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// Time Complexity: O(N x M x max(N, M)), N is the number of row, M is the number of column
bool dfs(int maze[][X_NUM], int startx, int starty, int endx, int endy) {
    if (startx == endx && starty == endy) return true;
    if (maze[starty][startx]) return false;
    if (visisted[starty][startx]) return false;
    
    visisted[starty][startx] = 1;
    int i;
    for(i = 0; i < 4; i++) {
        int nx = startx;
        int ny = starty;
        
        while (nx >= 0 && nx < X_NUM && ny >= 0 && ny < Y_NUM && maze[nx][ny] == 0) {
            nx += dirs[i][1];
            ny += dirs[i][0];
        }
        
        // step back
        nx -= dirs[i][1];
        ny -= dirs[i][0];
        
        if (nx >= 0 && nx < X_NUM && ny >= 0 && ny < Y_NUM) {
            bool ret = dfs(maze, nx, ny, endx, endy);
            if (ret) return true;
        }
    }
    return false;
}

bool hasPath(int maze[][X_NUM], int startx, int starty, int endx, int endy) {
    memset(visisted, 0, sizeof(visisted));
    return dfs(maze, startx, starty, endx, endy);
}

//3:53 -> 3:58

int main() {
    int maze[][X_NUM] = {
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
    };
    
    bool ret = hasPath(maze, 0, 0, 4, 4);
    printf("ret=%d\n", ret); // ret=1
    
    return 0;
}
