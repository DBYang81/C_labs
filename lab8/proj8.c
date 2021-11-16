#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define SIZE 100

void get_uppercase(char *str, int size);
int main(void){
    char text[SIZE];
    char buffer[SIZE];
    char cmp[5], ch;
    char stp[] = "STOP";

    do{
        printf("Please enter your text messages: ");
        fgets(buffer, SIZE, stdin);
        for(int i = 0; i < 4; i++){
            ch = buffer[i];
            cmp[i] = toupper(ch);
        }
        if(strcmp(cmp, stp) != 0){
            strcat(text, buffer);
        }
    }while(strcmp(cmp, stp) != 0);

    get_uppercase(text, SIZE);

    for(int i = 0; i < strlen(text); i++){
        printf("%c", text[i]);
    }
    printf("\n");

    return 0;
}

void get_uppercase(char *str, int size){
    char ch;
    ch = toupper(str[0]);
    str[0] = ch;
    for(int i = 1; i < strlen(str); i++){
        ch = str[i];
        if(isspace (ch)){
            ch = toupper(str[i + 1]);
            str[i + 1] = ch;
        }
    }
}