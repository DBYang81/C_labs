#include<stdio.h>

#define SIZE 5
#define DEBUGMSG 1

#if DEBUGMSG
    #define DEBUG_PRT(X,Y)\
    printf("LOG:INT %d AT LOCATION %d\n", X, Y)
#else
    #define DEBUG_PRT(X,Y)
#endif

int main(void){
    int arr[SIZE];

    for(int i = 0; i < SIZE; i++){
        printf("Enter a integer: ");
        scanf("%d", &arr[i]);

        DEBUG_PRT(arr[i], i);
    }
    printf("Array:");
    for(int i = 0; i < SIZE; i++){
       printf(" %d", arr[i]);
    }
    printf("\n");
    return 0;
}
