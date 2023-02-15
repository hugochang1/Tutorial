#include <iostream>

using namespace std;

void demo_simple() {
    int* d1 = new int(); //new init with intial value 0
    cout << *d1 << endl; // 0x5620682a1e70
    delete d1;
    //delete d1; // it will cause (core dumped) happen for double delete

    int* d2 = new int(3); //new int with inital value 3
    cout << *d2 << endl; // 3
    delete d2;
}

void demo_one_dimension_array() {
    int* d1 = new int[5]; //new int array with inital value 0
    for (int i = 0; i < 5; i++) {
        cout << *(d1+i) << endl; // 0 0 0 0 0
    }
    delete d1;

    int* d2 = new int[5]{1,2,3,4,5};
    for (int i = 0; i < 5; i++) {
        cout << *(d2+i) << " "; // 1 2 3 4 5
    }
    cout << endl;
    delete d2;
}

void demo_two_dimension_array() {
    int** d1 = new int*[3];
    d1[0] = new int[5]{1,2,3,4,5};
    d1[1] = new int[5]{6,7,8,9,10};
    d1[2] = new int[5]{11,12,13,14,15};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            cout << d1[i][j] << " "; // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
        }
    }
    cout << endl;

    delete []d1[0];
    delete []d1[1];
    delete []d1[2];
    delete []d1;
}

typedef struct {
    int a1;
    int a2;
} my_struct;

void demo_struct() {
    my_struct* s1 = new my_struct(); // new and intial a1 and a2 to be 0
    delete s1;

    my_struct* s2 = new my_struct({5, 10}); // new and intial a1=5 and a2=10
    delete s2;

    my_struct* s3 = new my_struct[3]; // new and wihtout intial the array
    for (int i = 0; i < 3; i++) {
        cout << (*(s3+i)).a1 << " " << (*(s3+i)).a2 << endl;
        /*
        1980433120 21874
        0 0
        1980433120 21874
        */
    }
    s3[0].a1 = 10;
    s3[0].a2 = 11;
    s3[1].a1 = 20;
    s3[1].a2 = 21;
    s3[2].a1 = 30;
    s3[2].a2 = 31;
    for (int i = 0; i < 3; i++) {
        cout << (*(s3+i)).a1 << " " << (*(s3+i)).a2 << endl;
        /*
        10 11
        20 21
        30 31
        */
    }
    delete[] s3;

    my_struct* s4 = new my_struct[3]{{1,2},{3,4},{5,6}}; // new and intial the array with specific values
    for (int i = 0; i < 3; i++) {
        cout << (*(s4+i)).a1 << " " << (*(s4+i)).a2 << endl;
        /*
        1 2
        3 4
        5 6
        */
    }
    delete[] s4;
}

class MyClass {
public:
    int a;
    int b;
    
    MyClass() : a(0), b(0) {}

    void dump() {
        cout << a << " " << b << endl;
    }
};

void demo_class() {
    MyClass* c = new MyClass();
    delete c;

    MyClass* c2 = new MyClass[3];
    c2[0].a = 10;
    c2[0].b = 11;
    c2[1].a = 20;
    c2[1].b = 21;
    c2[2].a = 30;
    c2[2].b = 31;
    for (int i = 0; i < 3; i++) {
        cout << c2[i].a << " " << c2[i].b << endl;
        /*
        10 11
        20 21
        30 31
        */
    }
    delete []c2;
}

int main(int argc, char *argv[]) {
    demo_simple();
    demo_one_dimension_array();
    demo_two_dimension_array();
    demo_struct();
    demo_class();

    return 0;
}

