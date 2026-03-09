#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

//1610_MaxNumberOfVisiblePoints

// go through all points and use atan2(y,x) to get the angles
// use atan2(y,x) to get the angles
// sort the angles by ascending order
// go through all angles to see how many points inside the angle given

int solution(vector<vector<int>> points, int angle, vector<int> location) {
    int collocated_count = 0;
    int max_angle_count = 0;
    vector<double> angles;
    int x = location[0];
    int y = location[1];
    
    for(auto point:points) {
        if(point[0] == x && point[1] == y) {
            collocated_count++;
        } else {
            double a = atan2(point[1] - y, point[0] - x) * 180 / M_PI;
            if(a < 0) a += 360;
            angles.push_back(a);
        }
    }
    
    sort(angles.begin(), angles.end());
    // dedicate the angles with +360 degree to handle wrap-around
    int size = angles.size();
    for(int i = 0; i < size; i++) {
        angles.push_back(angles[i] + 360);
    }
    
    for(int i = 0; i < size; i++) {
        int j = i;
        printf("i=%d j=%d\n", i, j);
        while(angles[j] - angles[i] <= angle) {
            printf(" i=%d j=%d %f %f %d\n", i, j, angles[j], angles[i], angle);
            j++;
        }
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
