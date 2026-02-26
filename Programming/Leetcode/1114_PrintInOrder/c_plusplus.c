#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> //usleep
#include <thread>
#include <mutex>

using namespace std;

//1114_PrintInOrder

class Foo {
    mutex m1;
    mutex m2;
public:
    Foo() {
        m1.lock();
        m2.lock();
    }

    void first() {
        printf("first");
        m1.unlock();
    }
    void second() {
        m1.lock();
        printf("second");
        m2.unlock();
    }
    void third() {
        m2.lock();
        printf("third");
    }
};

Foo f;

void task1() {
    f.third();
}

void task2() {
    f.second();
}

void task3() {
    f.first();
}

int main() {
    thread t1(task1);
    thread t2(task2);
    thread t3(task3);
    
    t3.join();
    t2.join();
    t1.join();
    
    printf("\n");
    return 0;
}
