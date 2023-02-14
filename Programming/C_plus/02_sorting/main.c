#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void dump_array(int* data, int n) {
    printf("dump_array n=%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("  i=%02d data=%d\n", i, data[i]);
    }
}

void dump_vector(vector<int> &v) {
    printf("dump_vector size=%lu\n", v.size());
    for (auto val : v) {
        printf("  val=%d\n", val);
    }
}

bool my_compare(int x, int y){
    return x < y;
}

bool my_compare_reverse(int x, int y) {
    return x > y;
}

void demo_sort_array() {
    #define MAX_ARRAY_NUM 7
    int data[MAX_ARRAY_NUM] = {5,4,3,1,2,7,6};
    
    
    sort(data, data + MAX_ARRAY_NUM); // data={1,2,3,4,5,6,7}
    sort(data, data + MAX_ARRAY_NUM, my_compare); //data={1,2,3,4,5,6,7}
    sort(data, data + MAX_ARRAY_NUM, my_compare_reverse); //data={7,6,5,4,3,2,1}
    sort(data, data + MAX_ARRAY_NUM, [](int x, int y) { return x < y; }); //data={1,2,3,4,5,6,7}
    
    dump_array(data, MAX_ARRAY_NUM);
}



void demo_sort_vector() {
    vector<int> data = {7,6,5,4,3,2,1};

    sort(data.begin(), data.end()); //data={1,2,3,4,5,6,7}
    sort(data.begin(), data.end(), my_compare); //data={1,2,3,4,5,6,7}
    sort(data.begin(), data.end(), my_compare_reverse); //data={7,6,5,4,3,2,1}
    sort(data.begin(), data.end(), [](int x, int y) { return x < y; }); //data={1,2,3,4,5,6,7}
    
    dump_vector(data);
}

/**********************************
            class
 **********************************/

class Node {
public:
    string name;
    int data;

    Node(const char* name, int data) {
        this->name = name;
        this->data = data;
    }
};

class Data {
public:
    vector<Node> v;

    Data() {
        v.push_back(Node("abc", 3));
        v.push_back(Node("def", 4));
        v.push_back(Node("aaa", 2));
        v.push_back(Node("kkk", 1));
    }
    
    void dump() {
        printf("size=%lu\n", v.size());
        for (unsigned int i = 0; i < v.size(); i++) {
            printf("  i=%02d data=%d name=[%s]\n",
                i, v[i].data, v[i].name.c_str());
        }
    }
};

bool my_class_compare(Node n1, Node n2) {
    return n1.data < n2.data;
}

void demo_sort_class() {
    Data data;
    data.dump();

    sort(data.v.begin(), data.v.end(), my_class_compare);
    sort(data.v.begin(), data.v.end(), [](Node n1, Node n2) { return n1.data > n2.data; });
    sort(data.v.begin(), data.v.end(), [](Node n1, Node n2) { return n1.name < n2.name; });
    
    data.dump();
}

/**********************************
            main
 **********************************/
int main(int argc, char *argv[]) {
    demo_sort_array();
    demo_sort_vector();
    demo_sort_class();
    return 0;
}

