#include<stdio.h>

#define LINESIZE 10


float get_average(float sum, int count);

int main(void){
    FILE *file;
    int count = 0;
    char line[LINESIZE];
    int fvalue;
    float value = 0;
    float sum = 0;
    float average;

    file = fopen("numbers.txt", "r");
    if(file == NULL){
        printf("Unable to open the file!\n");
    }else{
        printf("Reading numbers from %s...\n", "number.txt");
        if(fgets(line, sizeof(line), file) != NULL){
            sscanf(line, "%d", &fvalue);
        }else{
            printf("Invalid line\n");
            return 1;
        }
        while(fgets(line, sizeof(line), file) != NULL){
            if(sscanf(line, "%f", &value) == 1){
                sum += value;
                count++;
            }else{
                break;
            }
        }
        if(fvalue != count){
            average = get_average(sum, count);
            printf("Error! Try to read %d numbers, %d numbers were read.\n", fvalue, count);
            printf("Average of %d numbers is: %.2f\n", fvalue, average);
        }else{
            average = get_average(sum, count);
            printf("Average of %d numbers is: %.2f\n", fvalue, average);
        }
    }
    fclose(file);
    return 0;
}


float get_average(float sum, int count){
    float average;
    average = sum / count;
    return average;
}