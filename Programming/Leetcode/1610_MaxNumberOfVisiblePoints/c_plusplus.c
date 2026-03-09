#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath> // atan2

using namespace std;

//1610_MaxNumberOfVisiblePoints

int solution(vector<vector<int>> points, int angle, vector<int> location) {
    int posx = location[0];
    int posy = location[1];
    vector<double> angles;
    
    int collocated_count = 0;
    int max_angle_count = 0;
    
    for(vector<int> point:points) {
        if(point[0] == posx && point[1] == posy) {
            collocated_count++;
        } else {
            int px = point[0] - posx;
            int py = point[1] - posy;
            double a = atan2(py, px) * 180 / M_PI;
            
            if (a < 0) {
                a += 360;
            }
            angles.push_back(a);
        }
    }

    sort(angles.begin(), angles.end());
    
    int angle_size = angles.size();
    for(int i = 0; i < angle_size; i++) {
        angles.push_back(angles[i] + 360);
    }
    
    for(int i = 0; i < angle_size; i++) {
        int angle_count = 1;
        for(int j = i + 1; j < angle_size; j++) {
            //printf("i=%d j=%d %f %f %d angle=%d\n", i, j, angles[i], angles[j], angle_count, angle);
            if(angles[j] - angles[i] < angle) {
                angle_count++;
            } else {
                break;
            }
        }
        max_angle_count = max(max_angle_count, angle_count);
    }
    //printf("collocated_count=%d max_angle_count=%d\n", collocated_count, max_angle_count);
    return collocated_count + max_angle_count;
}

int main() {
    printf("%d\n", solution({{2,1},{2,2},{3,3}}, 90, {1,1})); // 3
    printf("%d\n", solution({{2,1},{2,2},{3,4},{1,1}}, 90, {1,1})); // 4
    printf("%d\n", solution({{1,0},{2,1}}, 13, {1,1})); // 1
    printf("%d\n", solution({{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}}, 90, {0,0})); // 2
    return 0;
}
