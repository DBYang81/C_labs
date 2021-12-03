#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

#define ASCII 128
#define SIZE 10

void passwd_generator(char *pt, int size, const char *p[]);

int main(void){
    srand(time(NULL));
    char passwds[30] = {0};
    const char *words[SIZE] = {"Payday","Hollywood","David","China","Macdonald","October","Code","Babyboy","Turkey","Porject"};
    int i = 0;

    printf("3 random passwords:\n\n");
    while(i < 3){
        passwd_generator(passwds, SIZE, words);
        printf("%s\n\n", passwds);
        i++;
    }
    return 0;
}

void passwd_generator(char *pt, int size, const char *p[]){
    int index = 0;
    int radm;
    char ch;
    for(int i = 0; i < size; i++){
        index = rand() % ASCII;
        if(isprint(index)){
            ch = index;
            pt[i] = ch;
        }else{
            i--;
        }
    }
    radm = rand() % size;
    strcpy(pt + 10, p[radm]);
}