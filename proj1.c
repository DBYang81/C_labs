#include <stdio.h>

int main(void){

    printf("This program calculates the average of positive numbers that you entered.\n");
    float i = 0, sum = 0, average = 0;
    int counter = 0;

    do{
        printf("Enter the positive number (exit with 0): ");
        scanf("%f", &i);

        if(i > 0){
            counter++;
            sum += i;
        }else if(i < 0){
            printf("Entered number is not valid.\n");
        }
    }while (i != 0);

    average = sum / counter;
    printf("The average is %.2f.\n", average);
    return 0;
}