#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

//0012_IntegerToRoman
//input1~3999
//I=1
//V=5
//X=10
//L=50
//C=100
//D=500
//M=1000

string solution(int n) {
    if(n > 3999) return "";
    string ret;
    vector<vector<string>> v;
    vector<string> tmp;
    v.push_back({"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}); //0-9
    v.push_back({"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}); //10-90
    v.push_back({"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}); //100-900
    v.push_back({"", "M","MM","MMM"}); //1000
    
    int cnt = 0;
    while(n > 0) {
        tmp.push_back(v[cnt][n % 10]);
        cnt++;
        n /= 10;
    }
    
    while(tmp.size() > 0) {
        ret += tmp.back();
        tmp.pop_back();
    }
    return ret;
}

int main() {
    printf("%s\n", solution(3749).c_str()); // MMMDCCXLIX
    //3000 = MMM
    //700 = 500 + 100 + 100 = DCC
    //40 = 50 - 10 = XL
    //9 = 10 - 1 = IX
    
    return 0;
}
