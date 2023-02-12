#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <math.h>
#include <stdbool.h> //true, false

int main(int argc, char *argv[]) {
    /*********************************
               if
     ********************************/
    {
        int a = 1, b = 2;
        if (a < b) {}
        if (a > b) {}
        if (a == b) {}
        if (a != b) {}
        if (a <= b) {}
        if (a >= b) {}
        if (a && b) {} // and
        if (a || b) {} // or
        if (!a) {}     // not
    }

    /*********************************
               if else
     ********************************/
    {
        int a = 1, b = 2;
        //nested
        if (a == b) {
            if (a == b) {}
        }
        
        if (a < b) {}
        else {}

        if (a < b) {}
        else if (a < b) {}
        else {}

        if (a < b) {}
        else if (a < b) {}
    }

    /*********************************
               switch
     ********************************/
    {
        int a = 1;
        switch(a) {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    }


    /*********************************
               for
     ********************************/
    {
        for (int i = 0; i < 3; i++) {
            printf("i=%d\n", i);
            /*
            i=0
            i=1
            i=2
            */
        }


        for (int i = 0; i < 3; i++) {
            continue;
            break;
        }

        for (;;) {
            break;
        }
    }

    /*********************************
               while
     ********************************/
    {
        int i = 0;
        while (i < 10) {
            i++;
        }

        while (true) {
            break;
        }
    }

    /*********************************
               while
     ********************************/
    {
        int i = 0;
        do {
            i++;
        } while (i < 3);
    }


    return 0;
}
