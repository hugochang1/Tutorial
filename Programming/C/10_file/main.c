#include <stdio.h>
#include <string.h>
#include <errno.h>

const char FILE_NAME[] = "test.txt";
const char FILE_NAME2[] = "test2.txt";

#define NUM_OF_DATA 4

void demo_write_file(const char* filename) {
    FILE *fp = NULL;
    int data[NUM_OF_DATA] = {1,2,3,4};

    //FILE *fopen(const char *filename, const char *mode)
    //  mode can be "r", "w", or "a"
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("fopen(test.txt, w) failed, reason=[%s]%d\n",
            strerror(errno), errno);
        return;
    }
    printf("fopen(test.txt, w) success\n");

    // int fputc(int char, FILE *stream)
    if (fputc('A', fp) == EOF) {
        printf("fputc() failed\n");
    }
    if (fputc('\n', fp) == EOF) {
        printf("fputc() failed\n");
    }

    //int fputs(const char *str, FILE *stream)
    if (fputs("hello world\n", fp) == EOF) {
        printf("fputs() failed\n");
    }

    //int fprintf(FILE *stream, const char *format, ...)
    if (fprintf(fp, "%d %f %s\n", 123, 456.789, "GG") < 0) {
        printf("fprintf() failed\n");
    }

    //long int ftell(FILE *stream)
    printf("ftell(fp)=%ld\n", ftell(fp)); //ftell(fp)=35

    //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
    if (fwrite(data, sizeof(data[0]), NUM_OF_DATA, fp) == 0) {
        printf("fwrite() failed\n");
    }

    //long int ftell(FILE *stream)
    printf("ftell(fp)=%ld\n", ftell(fp)); //ftell(fp)=51

    // int fflush(FILE *stream) 
    if (fflush(fp) == EOF) {
        printf("fflush() failed\n");
    }

    //int fclose(FILE *stream)
    fclose(fp);
}

void demo_read_file(const char* filename) {
    FILE *fp = NULL;
    char ch;
    int i;
    float f;
    char buff[128] = {0};
    int data[NUM_OF_DATA] = {0};

    //FILE *fopen(const char *filename, const char *mode)
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("fopen(test.txt, r) failed, reason=[%s]%d\n",
            strerror(errno), errno);
        return;
    }

    //int fgetc(FILE *stream)
    ch = fgetc(fp);
    printf("fgetc() ch=%c %d\n", ch, ch);
    
    ch = fgetc(fp);
    printf("fgetc() ch=%c %d\n", ch, ch);

    //char *fgets(char *str, int n, FILE *stream)
    if (fgets(buff, sizeof(buff), fp) == NULL) {
        printf("fgets() failed\n");
    }
    printf("fgets() buff=[%s]\n", buff);

    //int fscanf(FILE *stream, const char *format, ...)
    if (fscanf(fp, "%d %f %s\n", &i, &f, buff) == 0) {
        printf("fscanf() failed\n");
    }
    printf("fscanf() success, i=%d f=%f str=[%s]\n", i, f, buff);

    //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    if (fread(data, sizeof(data[0]), NUM_OF_DATA, fp) == 0) {
        printf("fread() failed\n");
    }
    for (int i = 0; i < NUM_OF_DATA; i++) {
        printf("data[%d]=%lld\n", i, data[i]);
    }

    //long int ftell(FILE *stream)
    printf("ftell(fp)=%ld\n", ftell(fp)); //ftell(fp)=51

    //int fseek(FILE *stream, long int offset, int whence)
    // whence can be either of below
    //  SEEK_SET: Beginning of file
    //  SEEK_CUR: Current position of the file yiibaier
    //  SEEK_END: End of file
    if (fseek(fp, 35, SEEK_SET) != 0) {
        printf("fseek() failed\n");
    }
    printf("ftell(fp)=%ld\n", ftell(fp)); //ftell(fp)=35

    //read data again
    if (fread(data, sizeof(data[0]), NUM_OF_DATA, fp) == 0) {
        printf("fread() failed\n");
    }
    for (int i = 0; i < NUM_OF_DATA; i++) {
        printf("data[%d]=%lld\n", i, data[i]);
    }

    //int fclose(FILE *stream)
    fclose(fp);
}

void demo_rename_file(const char* old_filename, const char* new_filename) {
    //int rename(const char *old_filename, const char *new_filename)
    if (rename(old_filename, new_filename) == -1) {
        printf("rename(%s, %s) failed, reason=[%s]%d\n",
            old_filename, new_filename, strerror(errno), errno);
    }
    printf("rename(%s, %s) success\n", old_filename, new_filename);
}

void demo_remove_file(const char* filename) {
    //int remove(const char *filename)
    if (remove(filename) == -1) {
        printf("remove(%s) failed, reason=[%s]%d\n",
            filename, strerror(errno), errno);
        return;
    }
    printf("remove(%s) success\n", filename);
}

/*********************************
           main
 ********************************/
int main() {
    demo_write_file(FILE_NAME);
    demo_read_file(FILE_NAME);
    demo_rename_file(FILE_NAME, FILE_NAME2);
    demo_remove_file(FILE_NAME2);
    return 0;
}
