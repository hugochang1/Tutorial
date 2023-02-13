#include <stdio.h>
#include <string.h>

void demo_sscanf() {
    // int sscanf(const char *str, const char *format, ...)
    char c = 'A';
    short s = 0;
    unsigned short us = 0;
    int i = 0;
    int i2 = 0, i3 = 0;
    unsigned int ui = 0;
    long l = 0;
    unsigned long ul = 0;
    long long ll = 0;
    unsigned long long ull = 0;
    float f = 0;
    double d = 0;
    char str[128] = {0};
    int ret = 0;

    //                    char short  ushort   int         uint       long      ulong        long long           u long long
    char input_str[512] = "B     12   255     1234567890 4294967295 1234567890 4294967295 9223372036854775807 9223372036854775808";
    ret = sscanf(input_str, "%c %hd %hu %d %u %ld %lu %lld %llu", &c, &s, &us, &i, &ui, &l, &ul, &ll, &ull);
    printf("ret=%d c=%c s=%hd us=%hu i=%d ui=%u l=%ld ul=%lu ll=%lld ull=%llu\n",
        ret, c, s, us, i, ui, l, ul, ll, ull);
    // output: ret=9 c=B s=12 us=255 i=1234567890 ui=4294967295 l=1234567890 ul=4294967295 ll=9223372036854775807 ull=9223372036854775808

    //                  float  double   str  
    strcpy(input_str, "1.1234 -456.789 hello world");
    ret = sscanf(input_str, "%f %lf %s", &f, &d, str);
    printf("ret=%d f=%f d=%lf str=%s\n", ret, f, d, str);
    //output: ret=3 f=1.123400 d=-456.789000 str=hello

    //                 10     hex    oct
    strcpy(input_str, "16     16     16");
    ret = sscanf(input_str, "%d %x %o", &i, &i2, &i3);
    printf("ret=%d i=%d i2=%d i3=%d\n", ret, i, i2, i3);
    //output: ret=3 i=16 i2=22 i3=14
}

void demo_gets() {
    //char *gets(char *str)
    char str[128] = {0};
    printf("input something:");
    gets(str);
    printf("str=[%s]\n", str);
    /*
    input something:abc def
    str=[abc def]
    */
}

void demo_getchar() {
    //int getchar(void)
    // getchar() will display the input in the console
    char ch = '0';

    printf("input something: ");
    while (ch != '\n') {
        ch = getchar();
        printf("ch=%c dec=%d hex=%x\n", ch, ch, ch);
        /*
        input something: ab 01
        ch=a dec=97 hex=61
        ch=b dec=98 hex=62
        ch=  dec=32 hex=20
        ch=0 dec=48 hex=30
        ch=1 dec=49 hex=31
        ch=
        */
    }
}

void demo_getch() {
    //int getch(void);
    // getch() won't display the input in the console
    char ch = '0';

    printf("input something: ");
    while (ch != '\r') {
        ch = getch();
        printf("ch=%c dec=%d hex=%x\n", ch, ch, ch);
        /*
        input something: ch=1 dec=49 hex=31
        ch=2 dec=50 hex=32
        ch=3 dec=51 hex=33
        ch=a dec=97 hex=61
        ch=b dec=98 hex=62
        ch=c dec=99 hex=63
        dec=13 hex=d
        */
    }
}

/*********************************
           main
 ********************************/
int main() {
    demo_sscanf();
    //demo_gets();
    //demo_getchar();
    demo_getch();
    return 0;
}
