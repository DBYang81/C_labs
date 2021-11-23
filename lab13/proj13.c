#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MYFILE "proj13.txt"
#define SIZE 10

int main(void){
    int act_size;
    char *pt;
    FILE *in_file;

    in_file = fopen(MYFILE, "w");
    if(in_file == NULL){
        printf("File does not exist\n");
        return 1;
    }
    pt = (char *) malloc(SIZE * sizeof(char));
    if(pt == NULL){
        free(pt);
        printf("Memory allocation failed.");
        return 1;
    }

    do{
        printf("Write your text here ('.' to quit):");
        fgets(pt, SIZE * sizeof(char), stdin);
       
        if(strncmp(pt, ".", 1) == 0){
            printf("program exits...\n");
            break;
        }
        while(pt[strlen(pt) - 1] != '\n'){
            pt = realloc(pt, (strlen(pt) + 2) * sizeof(char));
            fgets(pt + strlen(pt), 2 , stdin);
        }
        if(pt[strlen(pt) - 1] == '\n'){
            pt[strlen(pt) - 1] = '\0';
        }
        act_size = strlen(pt);
        fprintf(in_file, "%d:%s\n", act_size, pt);
        free(pt);
    }while(strncmp(pt, ".", 1) != 0);

    
    fclose(in_file);

    return 0;
}