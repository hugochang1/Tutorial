#include <stdio.h>
#include <string.h>
#include <ctype.h> // islower
#include <stdlib.h> //atof

void demo_string_basic() {
    char a = '^';
    // #include <ctype.h>
    printf("islower=%d\n", islower(a));
    printf("isupper=%d\n", isupper(a));
    printf("isspace=%d\n", isspace(a));  // space \n \t \v \r \f
    printf("isdigit=%d\n", isdigit(a));  // numbers 0-9
    printf("isalnum=%d\n", isalnum(a));  // alphabet + numbers
    printf("isdigit=%d\n", isdigit(a));  // numbers 0-9 + 'A'-'F' + 'a'-'F'
    printf("isprint=%d\n", isprint(a));  // any printable key with whitespace
    printf("isgraph=%d\n", isgraph(a));  // any printable key without whitespace
    printf("tolower=%c\n", tolower('A')); // tolower=a
    printf("toupper=%c\n", toupper('a')); // tolower=A

    // #include <stdlib.h>
    printf("atof(\"1.11\")=%lf\n", atof("1.11"));  // double
    printf("atoi(\"123\")=%d\n", atoi("123"));     // int
    printf("atol(\"123\")=%ld\n", atol("123"));    // long
}

void demo_single_string1() {
    char str[20] = "hello";
    //char str[] = "hello"; //sizeof(str)=6
    char* p = str;
    
    /* ------- sizeof ------- */
    size_t size = sizeof(str);

    /* ------- strlen ------- */
    size_t len = strlen(str);

    printf("str=%s\n", str);  //str=hello
    printf("size=%zu\n", size); //size=6
    printf("len=%zu\n", len);   //len=5

    strcpy(str, "world");
    printf("str=%s\n", str); //str=world

    strncpy(str, "gg", len);
    printf("str=%s\n", str); //str=gg

    str[0] = 'G';
    printf("str=%s\n", str); //str=Gg

    /* ------- strcmp ------- */
    //int strcmp(const char * str1, const char * str2);
    printf("strcmp=%d\n", strcmp(str, "gg")); //strcmp=0
    printf("strcmp=%d\n", strcmp(str, "ag")); //strcmp=1
    printf("strcmp=%d\n", strcmp(str, "zg")); //strcmp=-1
    
    //int strncmp(const char *str1, const char *str2, size_t n)
    printf("strncmp=%d\n", strncmp(str, "gg", len)); //strncmp=0

    strcpy(str, "hello world");
    len = strlen(str);
    for (int i = 0; i < len; i++) {
        char ch = *(p+i);
        printf("index=%d ascii=0x%02x %c\n", i, ch, ch);
        /*
        index=0 ascii=0x68 h
        index=1 ascii=0x65 e
        index=2 ascii=0x6c l
        index=3 ascii=0x6c l
        index=4 ascii=0x6f o
        index=5 ascii=0x20
        index=6 ascii=0x77 w
        index=7 ascii=0x6f o
        index=8 ascii=0x72 r
        index=9 ascii=0x6c l
        index=10 ascii=0x64 d
        */
    }
}

void demo_single_string2() {
    char *str = "hello"; // hello is in the read-only memory
    size_t size = sizeof(str);
    size_t len = strlen(str);
    printf("str=%s\n", str);      //str=hello
    printf("sizeof=%zu\n", size); //sizeof=8
    printf("strlen=%zu\n", len);  //strlen=5

    //Segmentation fault due to read-only memory
    //strcpy(str, "hello world"); 
    //str[0] = 'H';
}

void demo_multi_string_func(char **strs, int n) {
    for (int i = 0; i < n; i++) {
        printf("func str[%d]=[%s] len=[%zu]\n", i, strs[i], strlen(strs[i]));
    }
}

void demo_multi_string1() {
    char strs[3][10] = {"Geek", "Geeks", "Geekfor"};
    //char strs[][10] = {"Geek", "Geeks", "Geekfor"};
    /*
    index   0  1  2  3  4  5  6  7  8  9 
    strs[0] G  e  e  k \0
    strs[1] G  e  e  k  s \0
    strs[2] G  e  e  k  f  o  r \0
    */
    size_t size = sizeof(strs);
    printf("sizeof(strs)=%zu\n", size); //sizeof(strs)=30

    for (int i = 0; i < 3; i++) {
        printf("strs[%d]=[%s]\n", i, strs[i]);
        /*
        strs[0]=[Geek]
        strs[1]=[Geeks]
        strs[2]=[Geekfor]
        */
    }

    strcpy(strs[0], "hello");
    printf("strs[0]=[%s]\n", strs[0]); //strs[0]=[hello]

    // Segmentation fault inside demo_multi_string_func()
    //demo_multi_string_func(strs, 3);
}

void demo_multi_string2() {
    char *strs[] = { "Geek", "Geeks", "Geekfor" };
    /*
    pointer    read-only memory
    strs[0] -> Geek\0
    strs[1] -> Geeks\0
    strs[2] -> Geekfor\0
    */
    size_t size = sizeof(strs);
    printf("sizeof(size)=%zu\n", size); //sizeof(strs)=6421952

    for (int i = 0; i < 3; i++) {
        printf("strs[%d]=[%s] sizeof=[%zu] strlen=[%zu] pointer=%p\n",
            i, strs[i], sizeof(strs[i]), strlen(strs[i]), strs[i]);
        /*
        strs[0]=[Geek] sizeof=[8] strlen=[4] pointer=00000000004050BE
        strs[1]=[Geeks] sizeof=[8] strlen=[5] pointer=00000000004050C3
        strs[2]=[Geekfor] sizeof=[8] strlen=[7] pointer=00000000004050C9
        */
    }
    // Segmentation fault due to read-only memory
    //strcpy(strs[0], "gg"); 
    //strs[0][0] = 'A';
    demo_multi_string_func(strs, 3);
}

void demo_string_advance() {
    char str[100] = "hello world, Here I'm, GG.";
    char *p = NULL;

    /* ------- strtok ------- */
    //char * strtok(char * str, const char * delimiters);
    p = strtok(str, ",");
    while (p != NULL) {
        printf("%s\n", p);
        p = strtok(NULL, ",");
        /*
        hello world
         Here I'm
         GG.
        */
    }

    /* ------- strstr ------- */
    //char * strstr(char * str1, const char * str2);
    p = strstr(str, "Here");
    printf("p=[%s]\n", p); //p=[Here I'm, GG.]
    
    p = strstr(str, "AAAAA");
    printf("p=[%s]\n", p); //p=[(null)]
    
    /* ------- strcat ------- */
    //char * strcat(char * destination, const char * source);
    p = strcat(str, "!!!!!!!!");
    printf("str=[%s]\n", str); //str=[hello world, Here I'm, GG.!!!!!!!!]
    printf("p=[%s]\n", str); //p=[hello world, Here I'm, GG.!!!!!!!!]

    //char *strncat(char *dest, const char *src, size_t n)
    p = strncat(str, "1234567890", 5);
    printf("str=[%s]\n", str); //str=[hello world, Here I'm, GG.!!!!!!!!12345]
    printf("p=[%s]\n", str); //p=[hello world, Here I'm, GG.!!!!!!!!12345]

    /* ------- strcpy ------- */
    //char * strcpy(char * destination, const char * source);
    p = strcpy(str, "hello");
    printf("str=[%s]\n", str); //str=[hello]
    printf("p=[%s]\n", str); //p=[hello]

    //char *strncpy( char *dest, const char *src, size_t count );
    p = strncpy(str, "1234567890", 5);
    printf("str=[%s]\n", str); //str=[12345]
    printf("p=[%s]\n", str); //p=[12345]
}

int main() {
    demo_string_basic();
#if 0
    demo_single_string1();
    demo_single_string2();
    demo_multi_string1();
    demo_multi_string2();
    demo_string_advance();
#endif
    return 0;
}
