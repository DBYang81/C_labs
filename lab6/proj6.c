#include<stdio.h>
#include<string.h>
#include<ctype.h>


void getEncrypted(char arr[], int key);

int main (void){
    char message[100], cha;
    int key;
    printf("Enter a message to encrypt: ");
    fgets(message, 100, stdin);
    printf("Shift key (0-26): ");
    scanf("%d", &key);
    printf("\n");

    for(int i = 0, n = strlen(message); i < n; i++){
        cha = message[i];
        message[i] = toupper(cha);
        printf("%c", message[i]);
    }
    printf("\n");
    printf("Encrypted message: \n");
    getEncrypted(message, key);
    printf("\n");
    printf("Decrypted message: \n");
    getEncrypted(message, -key);
    return 0;
}

void getEncrypted(char arr[], int key){
    char ch;
    for(int i = 0, n = strlen(arr); i < n; i++){
        ch = arr[i];
        if(ch >= 'A' && ch <= 'Z'){
            ch += key;
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }else if(ch < 'A'){
                ch = 'Z' - ('A' - ch) + 1;
            }
        }
        printf("%c", ch);
        arr[i] = ch;
    }
}