#include <iostream>
#include <vector>
#include <string>

using namespace std;

void demo_cout() {
    int a = 123;
    float f = 12.34;
    char str[] = "hello world";
    cout << "hello world" << endl; //hello world
    cout << "a" << "b" << endl; //ab
    cout << a << " " << f << " " << str << endl; // 123 12.34 hello world
}

void dump_vector(auto v) {
    cout <<  "vector size=" << v.size() << endl;
    for (size_t i = 0; i < v.size(); i++) {
        cout << " i=" << i << " " << v[i] << endl;
    }
}

void demo_vector() {
    vector<int> v1;
    vector<int> v2 = {1,2,3};
    
    cout << v1.size() << endl;     // 0
    cout << v1.capacity() << endl; // 0
    
    cout << v2.size() << endl;     // 3
    cout << v2.capacity() << endl; // 3

    // auto is int
    for (auto value : v2) {
        cout << value << endl;
        /*
        1
        2
        3
        */
    }

    for (size_t i = 0; i < v2.size(); i++) {
        cout << v2[i] << endl;
        /*
        1
        2
        3
        */
    }

    // auto is vector<int>::iterator
    for (auto it = v2.begin(); it != v2.end(); it++) {
        cout << *it << endl;
        /*
        1
        2
        3
        */
    }

    v1.push_back(1); //{1}
    v1.push_back(2); //{1,2}
    v1.push_back(3); //{1,2,3}
    dump_vector(v1);
    v1.pop_back();  //{1,2}
    v1.pop_back();  //{1}
    v1.pop_back();  //{}


    //vector<int>::iterator it;
    auto it = v2.begin();
    cout << *(it+0) << endl; // 1
    cout << *(it+1) << endl; // 2
    cout << *(it+2) << endl; // 3
    v2.insert(v2.begin(), 99); // {99,1,2,3}
    v2.erase(v2.begin()+1); // {99,2,3}
    dump_vector(v2);
}

void demo_string() {
    string str;
    cout << str.size() << endl; // 0
    cout << str.length() << endl; // 0
    cout << str << endl;  //

    str = "hello";
    cout << str.size() << endl; // 5
    cout << str.length() << endl; // 5
    cout << str << endl;  // hello

    str += " world";
    cout << str.size() << endl; // 11
    cout << str.length() << endl; // 11
    cout << str << endl;  // hello world

    //string.substr(start, offset)
    cout << str.substr(0, 5) << endl; //hello
    cout << str.substr(2, 3) << endl; //llo
    cout << str.substr(6, 5) << endl; //world
    cout << str.substr(6, 50) << endl; //world

    //string.erase(start, offset)
    str.erase(6, 2);
    cout << str << endl;  // hello rld

    for (char ch : str) {
        cout << ch << endl;
        /*
        h
        e
        l
        l
        o
        d
        */
    }

    string str1("abc");
    string str3 = "gg";
    string str4(str3);

    cout << (str == str1) << endl; // 0
    cout << (str != str1) << endl; // 1
    cout << (str > str1) << endl; // 1
    cout << (str < str1) << endl; // 0

    cout << str.find("a") << endl; //18446744073709551615 is string::npos
    cout << string::npos << endl;

    string strs[] = {"123", "abc"};
    for (auto s : strs) {
        cout << s << endl;
        /*
        123
        abc
        */
    }
}

int main(int argc, char *argv[]) {
    //demo_cout();
    //demo_vector();
    demo_string();
    return 0;
}

