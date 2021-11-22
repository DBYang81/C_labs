#include<stdio.h>
#include<string.h>

#define MY_FILENAME "proj11.txt"
#define SIZE 10

void sort(float *arr, int size);

int main(void){
    FILE *my_file;
    char line[SIZE];
    char buffer[SIZE];
    float arr[3] = {0};
    int i = 0;

    my_file = fopen (MY_FILENAME, "r+");
    if(my_file == NULL){
        printf("Unable to open %s\n", MY_FILENAME);
        return 1;
    }else{
        printf("Reading from %s...\n", MY_FILENAME);
        while (fgets(line, SIZE, my_file) != NULL){
            if(sscanf(line, "%f", &arr[i]) == 1){
               i++;
            }else{
                printf("Invalid line!\n");
                return 1;
            }
        }
        sort(arr, 3);
        rewind(my_file);
        for(int t = 0; t < 3; t++){
            sprintf(buffer, "%.2f\n", arr[t]);
            fwrite(buffer, strlen(buffer), 1, my_file);
        }
    }
    fclose(my_file);
    return 0;
}

void sort(float *arr, int size){
    float tmp;
    for(int y = 0; y < size; y++){
        for(int j = y + 1; j < size; j++){
            if(arr[j] < arr[y]){
                tmp = arr[y];
                arr[y] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}