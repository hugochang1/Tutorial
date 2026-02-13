#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int main() {
    
    try {
        vector<int> v = {1,2,3};
        v.at(5);
    } catch (exception &e) {
        cout << "catch exception: " << e.what() << endl;
        // catch exception: vector::_M_range_check: __n (which is 5) >= this->size() (which is 3)
    }

    /*
    C++ 的 try-catch 块不能直接捕捉到 Segmentation fault (段错误)。
     try-catch 仅能捕获 C++ 语言层面的异常，
    而段错误属于操作系统底层的 SIGSEGV 信号或访问权限冲突，
    会导致程序直接崩溃。如需处理，通常需要使用信号处理函数（Signal Handler）
    来捕获 SIGSEGV。 
    */      
    return 0;
}
