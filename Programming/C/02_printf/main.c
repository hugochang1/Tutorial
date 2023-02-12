#include <stdio.h>  // printf
#include <stdlib.h> // malloc

int main(int argc, char *argv[]) {
    /**************************************
                 printf
     **************************************/

    //print "
    printf("\"");
    //print '
    printf("\'");
    // print "\"
    printf("\\");
    // print %
    printf("%%");

    printf("\r\n");
    printf("123" "456\r\n");
    //output: 123456

    {
        char c = 'A';
        //char c = 65;  // OK, it equals to 'A'
        //char c = "A"; // It's not OK, compile warning initialization makes integer from pointer without a cast [-Wint-conversion]
        short s = 12;
        int i = 123;
        long l = 12345679;
        long long ll = 1234567901234L;
        float f = 12.34; // or 12.34f
        double d = 98.76;
        char str[] = "hello world";

        printf("c=%c s=%hd i=%d l=%ld ll=%lld f=%f d=%lf str=%s\r\n", c, s, i, l, ll, f, d, str);
        //output: c=A s=12 i=123 l=12345679 ll=1234567901234 f=12.340000 str=hello world

        //print hexadecimal
        printf("%x\r\n", i);
        //output: 7b
    }

    {
        float a = 0.123456789;
        printf("a=%.2f\r\n", a);
        //output: a=0.12
    }

    {
        //print unsigned
        unsigned short s = 12;
        unsigned int i = 123;
        unsigned long l = 12345;
        unsigned long long ll = 1234567890123L;
        
        printf("s=%u i=%u l=%lu ll=%llu\r\n", s, i, l, ll);
        //output: s=12 i=123 l=12345 ll=1234567890123
    }

    {
        //print pointer
        int* a = malloc(sizeof(int));
        printf("%p\r\n", a);
        //output: 0x561a3bf47670
        free(a);
    }

    {
        //print size_t
        size_t size = sizeof(int);
        printf("%zu\r\n", size);
    }

    /**************************************
                 scanf
     **************************************/
    {
        char ch = 'A';
        //scanf("%c", &ch);  //scan from the keyboard
        printf("ch=%c\n", ch);
    }

    /**************************************
                 sscanf
     **************************************/
    {
        int i = 0;
        float f = 0;
        char str[10] = {0};
        char input_str[] = "100 12.34 hello";
        sscanf(input_str, "%d %f %s", &i, &f, str);
        printf("i=%d f=%f str=%s\r\n", i, f, str);
        //output: i=100 f=12.340000 str=hello
    }

    return 0;
}
