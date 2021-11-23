#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MYFILE "proj13.txt"
#define SIZE 10

int main(void){
    int act_size, size;
    int count = 0;
    char *pt, *ptr;
    FILE *in_file;

    in_file = fopen(MYFILE, "w");
    if(in_file == NULL){
        printf("File does not exist\n");
        return 1;
    }
    pt = (char *) malloc(SIZE * sizeof(char));
    if(pt == NULL){
        printf("Memory allocation failed.");
        return 1;
    }

    do{
        printf("Write your text here ('.' to quit):");
        fgets(pt, SIZE, stdin);

        if(strncmp(pt, ".", 1) == 0){
            printf("program exits...\n");
        }else{
            while(pt[strlen(pt) - 1] != '\n'){
                size = strlen(pt);
                pt = realloc(pt, (size + SIZE) * sizeof(char)); // realloc new memory need to take previous malloc space into
                                                                //account, which is on basis of previous space then adding extra space.
                fgets(pt + strlen(pt), SIZE, stdin); //when fgets new data, point to need to moved to new location not from beganing
            }
            if(pt[strlen(pt) - 1] == '\n'){
                pt[strlen(pt) - 1] = '\0';
            }
            act_size = strlen(pt);
            fprintf(in_file, "%d:%s\n", act_size, pt);
        }
    }while(strncmp(pt, ".", 1) != 0);

    free(pt);
    fclose(in_file);

    return 0;
}