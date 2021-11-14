#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define SIZE 100

void getConvted(char *str, int size);
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

    getConvted(text, SIZE);

    for(int i = 0; i < strlen(text); i++){
        printf("%c", text[i]);
    }
    printf("\n");

    return 0;
}

void getConvted(char *str, int size){
    char chart;
    for(int i = 0; i < strlen(str); i++){
        chart = str[i];
        if(isspace (chart)){
            chart = '_';
            str[i] = chart;
        }
    }
}