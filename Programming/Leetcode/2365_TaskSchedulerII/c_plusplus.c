#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2365_TaskSchedulerII

int find(vector<int> tasks, int space) {
    int current_day = 0;
    unordered_map<int, int> m; //task_id, start_day
    
    for(int task:tasks) {
        current_day++;
        
        if(m.count(task) && m[task] > current_day) {
            current_day = m[task];
        }
        m[task] = current_day + space + 1;
    }
    return current_day;
}


int main() {
    printf("%d\n", find({1,2,1,2,3,1}, 3)); // 9
    printf("%d\n", find({5,8,8,5}, 2)); // 6
    printf("%d\n", find({1,1,1,1}, 0)); // 4
    printf("%d\n", find({1,1,1,1}, 1)); // 7
    printf("%d\n", find({1,1,1,1}, 2)); // 10
    
    return 0;
}
