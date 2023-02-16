#include <iostream>

using namespace std;

class Point {
public:
    int x;
    int y;

    Point() { x = 0; y = 0; }
    Point(int x, int y) : x(x), y(y) {}

    void dump() {
        cout << "x=" << x << " y=" << y << endl;
    }
};

int main() {
    Point p;
    p.dump();

    return 0;
}
