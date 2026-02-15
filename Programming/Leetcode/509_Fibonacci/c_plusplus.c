#include <stdio.h>
#include <stdlib.h>

// Time Complexity: O(2^n)
long long fibnoacci(int num) {
    if (num <= 0) return 0;
    if (num == 1) return 1;
    
    return fibnoacci(num - 1) + fibnoacci(num - 2);
}

// Time Complexity: O(n)
long long fibnoacci2(int num) {
    if (num <= 0) return 0;
    if (num == 1) return 1;
    
    long long f1_num = 0;
    long long f2_num = 1;
    long long f3_num = 0;
    int i;
    for(i = 2; i <= num ; i++) {
        f3_num = f1_num + f2_num;
        f1_num = f2_num;
        f2_num = f3_num;
    }
    
    return f3_num;
}

int main() {
    int i;
    for(i = 0; i < 300; i++) {
        printf("i=%d ret=%lld\n", i, fibnoacci2(i));
    }
    /*
    i=0 ret=0
    i=1 ret=1
    i=2 ret=1
    i=3 ret=2
    i=4 ret=3
    i=5 ret=5
    i=6 ret=8
    i=7 ret=13
    i=8 ret=21
    i=9 ret=34
    i=10 ret=55
    i=11 ret=89
    i=12 ret=144
    i=13 ret=233
    i=14 ret=377
    i=15 ret=610
    i=16 ret=987
    i=17 ret=1597
    i=18 ret=2584
    i=19 ret=4181
    i=20 ret=6765
    i=21 ret=10946
    i=22 ret=17711
    i=23 ret=28657
    i=24 ret=46368
    i=25 ret=75025
    i=26 ret=121393
    i=27 ret=196418
    i=28 ret=317811
    i=29 ret=514229
    i=30 ret=832040
    i=31 ret=1346269
    i=32 ret=2178309
    i=33 ret=3524578
    i=34 ret=5702887
    i=35 ret=9227465
    i=36 ret=14930352
    i=37 ret=24157817
    i=38 ret=39088169
    i=39 ret=63245986
    i=40 ret=102334155
    i=41 ret=165580141
    i=42 ret=267914296
    i=43 ret=433494437
    i=44 ret=701408733
    i=45 ret=1134903170
    i=46 ret=1836311903
    i=47 ret=2971215073
    i=48 ret=4807526976
    i=49 ret=7778742049
    i=50 ret=12586269025
    i=51 ret=20365011074
    i=52 ret=32951280099
    i=53 ret=53316291173
    i=54 ret=86267571272
    i=55 ret=139583862445
    i=56 ret=225851433717
    i=57 ret=365435296162
    i=58 ret=591286729879
    i=59 ret=956722026041
    i=60 ret=1548008755920
    i=61 ret=2504730781961
    i=62 ret=4052739537881
    i=63 ret=6557470319842
    i=64 ret=10610209857723
    i=65 ret=17167680177565
    i=66 ret=27777890035288
    i=67 ret=44945570212853
    i=68 ret=72723460248141
    i=69 ret=117669030460994
    i=70 ret=190392490709135
    i=71 ret=308061521170129
    i=72 ret=498454011879264
    i=73 ret=806515533049393
    i=74 ret=1304969544928657
    i=75 ret=2111485077978050
    i=76 ret=3416454622906707
    i=77 ret=5527939700884757
    i=78 ret=8944394323791464
    i=79 ret=14472334024676221
    i=80 ret=23416728348467685
    i=81 ret=37889062373143906
    i=82 ret=61305790721611591
    i=83 ret=99194853094755497
    i=84 ret=160500643816367088
    i=85 ret=259695496911122585
    i=86 ret=420196140727489673
    i=87 ret=679891637638612258
    i=88 ret=1100087778366101931
    i=89 ret=1779979416004714189
    i=90 ret=2880067194370816120
    i=91 ret=4660046610375530309
    i=92 ret=7540113804746346429
    i=93 ret=-6246583658587674878
    */
    
    return 0;
}
