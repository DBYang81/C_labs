#include<stdio.h>
#define MAX_STUDENT_COUNT 10
#define INDEX 45000

float getAverage(int arr[], int size);

int main(void){
    int grade[MAX_STUDENT_COUNT] = {};
    int amount_of_students;
    int grade_value;

    do{
        printf("How many students are graded?: ");
        scanf("%d", &amount_of_students);
        if(amount_of_students > MAX_STUDENT_COUNT){
            printf("Warning!! too many students!! reducing the amount!!\n");
        }

    }while(amount_of_students > MAX_STUDENT_COUNT);

    for(int i = 0; i < amount_of_students; i++){
        printf("Please enter a student (No.%d) grade: ", INDEX + i);
        scanf("%d", &grade_value);
        if(grade_value >= 0 && grade_value <= 5){
            grade[i] = grade_value;
        }else{
            printf("invalid grade!\n");
            i--;
        }
    }
    getAverage (grade, amount_of_students);
    return 0;
}

float getAverage(int arr[], int size){
    float average = 0;
    float sum = 0;

    for(int i = 0; i < size; i++){
        sum += arr[i];
    }
    average = sum / size;
    printf("The average of course grades: %.2f\n", average);
    return average;
}