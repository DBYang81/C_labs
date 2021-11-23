#include<stdio.h>
#include<string.h>

#define INDEX 50
#define SIZE 100

typedef struct priceInfo{
    float price;
    char name[80];
}item;

int main(void){
    FILE *fp;
    char line[SIZE];
    char fname[SIZE];
    int count = 0;
    item storage[INDEX];
    char *title[2] = {"Name","Price"};

    printf("Enter the file(.txt): ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if(fp == NULL){
        printf("No such file exists!\n");
        return 1;
    }else{
        while(fgets(line, sizeof(line), fp) != NULL){
            if(sscanf(line, "%f;%[^\n]", &storage[count].price, storage[count].name) == 2){
            count++;
            }
        }
    }
    printf("\n");
    printf("Read %d numbers of item successfully...\n\n", count);
    printf("%-35s%11s\n\n",title[0], title[1]);
    for(int i = 0; i < count; i++){
        printf("%-35s %10.2f\n",storage[i].name, storage[i].price);
    }
    fclose(fp);
    return 0;
}