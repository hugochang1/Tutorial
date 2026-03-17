#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>

using namespace std;

//2365_TaskSchedulerII
//use undered_map to save the task type and start day
//go through tasks and calculate the day we need

int find(vector<int> tasks, int space) {
    int ret = tasks.size();
    unordered_map<int, int> m;
    
    for(int i = 0; i < tasks.size(); i++) {
        int task = tasks[i];
        
        if(m.count(task)) {
            int index = m[task];
            int delta = i - index;
            if(space >= delta) {
                ret += (space - delta) + 1;
                m.clear();
            }
        }
        m[task] = i;
    }
    return ret;
}


int main() {
    printf("%d\n", find({1,2,1,2,3,1}, 3)); // 9
    printf("%d\n", find({5,8,8,5}, 2)); // 6
    
    return 0;
}
