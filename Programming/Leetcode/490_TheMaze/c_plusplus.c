#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define X_NUM 5
#define Y_NUM 6

int visited[Y_NUM][X_NUM];
int dirs[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

bool dfs(int maze[][X_NUM], int startx, int starty, int endx, int endy) {
    if (startx == endx && starty == endy) return true;
    if (visited[starty][startx]) return false;
    if (maze[starty][startx]) return false;
    
    visited[starty][startx] = 1;
    int i;
    for(i = 0; i < 4; i++) {
        int nx = startx + dirs[i][1];
        int ny = starty + dirs[i][0];
        
        if (nx >= 0 && nx < X_NUM && ny >= 0 && ny < Y_NUM) {
            bool ret = dfs(maze, nx, ny, endx, endy);
            if (ret) return true;
        }
    }
    return false;
}

bool hasPath(int maze[][X_NUM], int startx, int starty, int endx, int endy) {
    memset(visited, 0, sizeof(visited));
    return dfs(maze, startx, starty, endx, endy);
}

int main() {
    int maze[][X_NUM] = {
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
    };
    
    bool ret = hasPath(maze, 0, 0, 5, 5);
    printf("ret=%d\n", ret);
    
    return 0;
}
