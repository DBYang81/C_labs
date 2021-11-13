#include <stdio.h>
#define DIVIDER 12.5
#define ELEMT 12

int main(void){
    float element[ELEMT];
    float input, value = 0, total = 0;


    printf("Enter annual gross income: ");
    scanf("%f", &input);

    for(int i = 0; i < ELEMT; i++){
        value = input / DIVIDER;
        if(i == 6){
            value = value * 1.5;
        }
        element[i] = value;
        total += element[i];
    }

    for(int j = 0; j < ELEMT; j++){
        printf("element[%2d] =%12.4f\n\n", j, element[j]);
    }
    printf("total       =%12.4f\n", total);
    return 0;
}
