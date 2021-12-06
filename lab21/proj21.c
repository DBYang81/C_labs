#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 10
#define ALPHA 26

typedef struct frequency{
    char ch;
    int freq;
}ORDER;

int compare(const void *p1, const void *p2);

int main(void){
    char fname[SIZE];
    ORDER list[ALPHA] = {0};
    long length;
    int len = 0;
    FILE *file;

    printf("Enter the file (.txt): ");
    scanf("%s", fname);
    file = fopen(fname, "rb");
    if(file == NULL){
        printf("File can not be opened!\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buff[length];
    len = fread(buff, 1, length, file);

    for(int i = 0; i < len; i++){
        if(buff[i] != ' '){
           if(buff[i] >= 'a' && buff[i] <= 'z'){
                list[buff[i] - 97].ch = buff[i];
                list[buff[i] - 97].freq++;
            }else if(buff[i] >= 'A' && buff[i] <= 'Z'){
                list[buff[i] - 65].ch = buff[i] + 32;
                list[buff[i] - 65].freq++;
            }
        }
    }

    qsort(list, ALPHA, sizeof(ORDER), compare);

    for(int i = 0; i < SIZE; i++){
        printf("%c : %d\n", list[i].ch, list[i].freq);
    }
    return 0;
}

int compare(const void *p1, const void *p2){
    ORDER *c1 = (ORDER *) p1;
    ORDER *c2 = (ORDER *) p2;
    int freq_rate = c1->freq < c2->freq;
    return freq_rate;
}