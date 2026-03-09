#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

//1610_MaxNumberOfVisiblePoints

// use atan2 to get the angle for each point
// sort angles by ascending order
// go through angles to check the max count of angles within angle given

int solution(vector<vector<int>> points, int angle, vector<int> location) {
    int x = location[0];
    int y = location[1];
    int collocated_count = 0;
    int max_angle_count = 0;
    vector<double> angles;
    
    for(auto point:points) {
        if(point[0] == x && point[1] == y) {
            collocated_count++;
        } else {
            double ang = atan2(point[1] - y,point[0] - x) * 180 / M_PI;
            if(ang < 0) ang += 360;
            angles.push_back(ang);
        }
    }
    
    sort(angles.begin(), angles.end());
    int size = angles.size();
    //duplicate angles to handle wrap-around
    for(int i = 0; i < size; i++) {
        angles.push_back(angles[i] + 360);
    }
    
    for(int i = 0; i < size; i++) {
        int j = i + 1;
        while(angles[j] - angles[i] <= angle) j++;
        //printf("i=%d j=%d %f %f %d\n", i, j, angles[i], angles[j], angle);
        max_angle_count = max(max_angle_count, j - i);
    }
    
    return collocated_count + max_angle_count;
}

int main() {
    printf("%d\n", solution({{2,1},{2,2},{3,3}}, 90, {1,1})); // 3
    printf("%d\n", solution({{2,1},{2,2},{3,4},{1,1}}, 90, {1,1})); // 4
    printf("%d\n", solution({{1,0},{2,1}}, 13, {1,1})); // 1
    printf("%d\n", solution({{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}, 90, {0,0})); // 3
    return 0;
}
