#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <math.h>   // floor
#include <ctype.h> // islower

int main(int argc, char *argv[]) {
    /***********************************
                  int
    ***********************************/
    {
        int a = 20, b = 10;
        int c;
        c = a + b; // 30
        c = a - b; // 10
        c = a * b; // 200
        c = a / b; // 2
        c = a % b; // 0
        printf("c=%d\n", c);
        printf("and 0x%x\n", 0x0001 & 0xffff); //and 0x1
        printf("or 0x%x\n", 0x0001 | 0xffff);  //or  0xffff
        printf("xor 0x%x\n", 0x3333 ^ 0xcccc); //xor 0xffff
        printf("not 0x%x\n", ~0x1);            //not 0xfffffffe
        printf("<< 0x%x\n", 0x1 << 4);         //<< 0x10
        printf(">> 0x%x\n", 0x10 >> 4);        //>> 0x01

        c += a;
        c -= a;
        c *= a;
        c /= a;
        c %= a;
        c &= a;
        c |= a;
        c ^= a;
        c++;
        ++c;
        c--;
        --c;
        printf("!!!!!!!!! %d\n", 0xa^0x2); // 1100   0010
    }

    {
        int a = -10;
        printf("abs=%d\n", abs(a));
        // abs=10
    }

    /***********************************
                  float
    ***********************************/
    {
        float a = 10, b = 3;
        float c;
        c = a + b; // 13.000
        c = a - b; // 7.000
        c = a / b; // 3.3333
        //c = a % b; // error: invalid operands to binary % (have ‘float’ and ‘float’)
        printf("c=%f\n", c);
    }

    {
        // math.h
        // add -lm to Makefile
        float f = 1.5;
        float f2 = -123.456;
        printf("floor=%lf\n", floor(f));// floor=1.000000
        printf("ceil=%lf\n", ceil(f));  // ceil=2.000000
        printf("fabs=%lf\n", fabs(f2)); // fabs=123.456001
        printf("log=%lf\n", log(f));    // log=0.405465
        printf("log10=%lf\n", log10(f));// log10=0.176091
        printf("exp=%lf\n", exp(f));    // exp=4.481689
        printf("sqrt=%lf\n", sqrt(f));  // sqrt=1.224745
        printf("pow=%lf\n", pow(2, 3)); // pow=8.000000
    }

    return 0;
}
