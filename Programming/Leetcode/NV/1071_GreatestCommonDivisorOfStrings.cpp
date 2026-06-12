#include <stdio.h>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

//1071_GreatestCommonDivisorOfStrings

string find(string s1, string s2) {
    if(s1 + s2 != s2 + s1) return "";
    return s1.substr(0, gcd(s1.size(), s2.size()));
}

int main() {
    printf("%s\n", find("ABCABC", "ABC").c_str()); // ABC
    printf("%s\n", find("ABABAB", "ABAB").c_str()); // AB
    printf("%s\n", find("ABC", "DEF").c_str()); //
    return 0;
}
