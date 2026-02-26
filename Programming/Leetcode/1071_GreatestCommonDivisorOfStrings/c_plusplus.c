#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <numeric>

using namespace std;

//1071_GreatestCommonDivisorOfStrings

string find(string str1, string str2) {
    if (str1 + str2 != str2 + str1) return "";
    
    int size1 = str1.size();
    int size2 = str2.size();
    int g = gcd(size1, size2);
    
    return str1.substr(0, g);
}

int main() {
    string str1, str2;
    str1 = "ABCABC"; str2 = "ABC";
    printf("%s\n", find(str1, str2).c_str()); // ABC
    
    str1 = "ABAB"; str2 = "AB";
    printf("%s\n", find(str1, str2).c_str()); // AB
    
    str1 = "ABC"; str2 = "DEF";
    printf("%s\n", find(str1, str2).c_str()); //
    
    return 0;
}
