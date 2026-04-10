#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <numeric>

using namespace std;

//1071_GreatestCommonDivisorOfStrings

string find(string str1, string str2) {
    if(str1 + str2 != str2 + str1) {
        return "";
    }
    int g = gcd(str1.size(), str2.size());
    return str1.substr(0, g);
}

int main() {
    printf("%s\n", find("ABCABC", "ABC").c_str()); // ABC
    printf("%s\n", find("ABABAB", "ABAB").c_str()); // AB
    printf("%s\n", find("ABC", "DEF").c_str()); //
    return 0;
}
