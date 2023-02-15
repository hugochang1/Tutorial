#include <iostream>
#include <string>

using namespace std;

int main() {
    //
    /*************************************
        init
    **************************************/
    string s;          // (empty)
    string s1("abc");  // "abc"
    string s2(s1);     // "abc"
    string s3 = "def"; //"def"

    char p[] = "01234567890";
    string s4(p);      // "01234567890"
    string s5(p,5);    // "01234"
    string s6(p,6);    // "012345"

    string s7(3, 'A');   // "AAA"
    string s8(4, 'A');   // "AAAA

    /*************************************
        comparison
    **************************************/
    string str1 = "hello";
    string str2 = "world";
    cout << (str1 == str2) << endl; // 0
    cout << (str1 != str2) << endl; // 1
    cout << (str1 > str2) << endl;  // 0
    cout << (str1 < str2) << endl;  // 1
    cout << (str1 == "hello") << endl; // 1
    cout << str1.compare(str2) << endl; // -1
    cout << str1.compare("hello") << endl; // 0

    /*************************************
        traverse
    **************************************/
    for (char ch : str1) {
        cout << ch << endl; // h e l l o
    }
    
    for (size_t i = 0; i < str1.size(); i++) {
        cout << str1[i] << endl; // h e l l o
    }

    const char* p1 = str1.c_str();
    for (size_t i = 0; i < str1.size(); i++) {
        cout << p1[i] << endl; // h e l l o
    }

    /*************************************
        substr(start, offset)
    **************************************/
    str1 = "hello world";
    cout << str1.substr(0) << endl; //hello world
    cout << str1.substr(1) << endl; //ello world
    cout << str1.substr(0,1) << endl; //h
    cout << str1.substr(0,2) << endl; //he

    /*************************************
        find(string) search from left
    **************************************/
    size_t pos = str1.find("world");
    cout << str1.substr(pos) << endl; //world

    str1 = "0123456789";
    pos = str1.find("0");
    cout << pos << endl; // 0
    pos = str1.find("9");
    cout << pos << endl; // 9
    pos = str1.find("a");
    cout << pos << endl; // 18446744073709551615 string::npos
    cout << (pos == string::npos) << endl; // 1
    
    /*************************************
        rfind(string) search from right
    **************************************/
    str1 = "abcda";
    pos = str1.rfind("a");
    cout << pos << endl; // 4
    
    /*************************************
        strcat
    **************************************/
    str1 = "hello";
    str2 = "world";
    cout << str1 + str2 << endl; // helloworld
    str1 += str2;
    cout << str1 << endl; // helloworld

    /*************************************
        strlen
    **************************************/
    cout << str1.size() << endl;   // 10
    cout << str1.length() << endl; // 10

    /*************************************
        clear
    **************************************/
    cout << str1.empty() << endl; // 0
    str1.clear();
    cout << str1.size() << endl;  // 0
    cout << str1.empty() << endl; // 1

    return 0;
}
