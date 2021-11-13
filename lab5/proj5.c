#include<stdio.h>


void getPrinted (int arr[][3], int rows);
void multp_matrix(int vec[][3], int mat[][3], int resl[][3]);
int i, j, t;

int main(void){
    int matrix[3][3] = { };
    int vector[1][3] = { };
    int result[1][3] = { };
    char input[20];
    int tmp = 0;
    char end;

    printf("Enter vector values: \n");
    for(i = 0; i < 1; i++){
        for(j = 0; j < 3; j++){
            int ret = 0;
            printf("[%d][%d]: ",i, j);
            fgets(input, 20, stdin);
            ret = sscanf(input, "%d%c", &tmp, &end);
            if(ret != 2 || end != '\n'){
                printf("invalid number!!\n");
                --j;
            }else{
                vector[i][j] = tmp;
            }
        }
    }
    getPrinted(vector, 1);

    printf("\n");

    printf("Enter matrix value: \n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            int ret = 0;
            printf("[%d][%d]: ", i, j);
            fgets(input, 20, stdin);
            ret = sscanf(input, "%d%c", &tmp, &end);
            if(ret != 2 || end !='\n'){
                printf("invalid number!\n");
                j--;
            }else{
                matrix[i][j] = tmp;
            }
        }
    }
    getPrinted(matrix, 3);

    multp_matrix(matrix, vector, result);
    printf("The result of multiplication: \n");
    getPrinted(result, 1);

    return 0;
}

void multp_matrix(int mat[][3], int vec[][3], int resl[][3]){
    int sum = 0;
    for(i = 0; i < 1; i++){
        for(j = 0; j < 3; j++){
            for(t = 0; t < 3; t++){
                sum += mat[j][t] * vec[i][t];
            }
            resl[i][j] = sum;
            sum = 0;
        }
    }
}

void getPrinted (int arr[][3], int rows){
    for(i = 0; i < rows; i++){
        for(j = 0; j < 3 ; j++){
            printf("%d,", arr[i][j]);
        }
        printf("\n");
    }
}