#include<stdio.h>


#define SIZE 20

int main(void){
    char fname[SIZE];
    FILE *file;
    long fsize;
    long offset;
    long count;


    printf("Enter Name of File (.txt): ");
    scanf("%s", fname);

    file = fopen(fname, "rb");
    if(file == NULL){
        printf("The file dose not exists\n");
    }
    fseek(file, 0L, SEEK_END);
    fsize = ftell(file);
    char byte [fsize];

    printf("The size of file is %ld bytes\n", fsize);
    printf("Remove from beginning of file: ");
    scanf("%ld", &offset);
    if(offset < 0 || offset > fsize){
        printf("invalid offset!\n");
        return 1;
    }

    fseek(file, offset, SEEK_SET);
    for(count = 0; count < fsize; count++){
        fseek(file, offset + count, SEEK_SET);
        byte [count] = getc(file);
    }
    fclose(file);

    file = fopen(fname, "wb");
    fwrite(byte, 1, fsize - offset, file);
    fclose(file);

    return 0;
}