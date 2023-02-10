#include <stdio.h>
#include <string.h>

void demo_single_string1() {
    char str[20] = "hello";
    //char str[] = "hello"; //sizeof(str)=6
    size_t size = sizeof(str);
    size_t len = strlen(str);
    char* p = str;

    printf("str=%s\n", str);  //str=hello
    printf("size=%zu\n", size); //size=6
    printf("len=%zu\n", len);   //len=5

    strcpy(str, "world");
    printf("str=%s\n", str); //str=world

    strncpy(str, "gg", len);
    printf("str=%s\n", str); //str=gg

    str[0] = 'G';
    printf("str=%s\n", str); //str=Gg

    printf("strcmp=%d\n", strcmp(str, "gg")); //strcmp=0
    printf("strcmp=%d\n", strcmp(str, "ag")); //strcmp=1
    printf("strcmp=%d\n", strcmp(str, "zg")); //strcmp=-1
    
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
    printf("sizeof(strs)=%d\n", size); //sizeof(strs)=30

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
    printf("sizeof(strs)=%d\n", strs); //sizeof(strs)=6421952

    for (int i = 0; i < 3; i++) {
        printf("strs[%d]=[%s] sizeof=[%d] strlen=[%d] pointer=%p\n",
            i, strs[i], sizeof(strs[i]), strlen(strs[i]), strs[i]);
        /*
        strs[0]=[Geek] sizeof=[8] strlen=[4]
        strs[1]=[Geeks] sizeof=[8] strlen=[5]
        strs[2]=[Geekfor] sizeof=[8] strlen=[7]
        */
    }
    // Segmentation fault due to read-only memory
    //strcpy(strs[0], "gg"); 
    //strs[0][0] = 'A';
    demo_multi_string_func(strs, 3);
}

int main() {
    demo_single_string1();
    demo_single_string2();
    demo_multi_string1();
    demo_multi_string2();
    return 0;
}
