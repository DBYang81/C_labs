#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 20
#define SIZE 5
#define CARFILE "carInfo.txt"

typedef struct car_info{
    char maker[LEN];
    char model[LEN];
    int price;
    float emission;
}CAR;

int get_fsize(void);
void get_print(CAR *ptr, int size);
void get_added(CAR *ptr, int size);
void get_read(CAR *ptr, int size);
void file_load(CAR *ptr);

int main(void){
    int ans = 0;
    int file_size = 0;
    CAR tmp[20] = { };
    CAR records[SIZE] = {
            {"Ford", "Focus", 45000, 120.2},
            {"Hyundai", "i30", 23000,110.5},
            {"Fiat", "Tipo Estate", 22300, 140.3},
            {"Chevrolet", "Cruze", 33500, 112.8},
            {"Kia","Picanto", 15000, 151.4},
        };

    printf("Follow the Instruction:\n");

    do{
        printf("\n");
        printf("1.print all records of cars into the file\n"
               "2.add a new car to the file\n"
               "3.display the list of car info from a file\n"
               "4.upload car info from a file\n"
               "5.quit the program\n\n");
        printf("Your selection: ");
        scanf("%d", &ans);
        printf("\n");

        switch(ans){
            case 1:
                get_print(records, SIZE);
                break;
            case 2:
                get_added(tmp, 1);
                break;
            case 3:
                file_size = get_fsize();
                get_read(tmp, file_size);
                break;
            case 4:
                file_load(tmp);
            case 5:
                break;
            default:
                printf("Please enter the option number again!\n");
                break;
        }
    }while(ans != 5);
    return 0;
}

void get_print(CAR *ptr, int size){
    FILE *file;
    file = fopen(CARFILE, "ab");
    if(file == NULL){
        printf("Not Exists!\n");
        exit(1);
    }
    fwrite(ptr, sizeof(CAR), size, file);
    fclose(file);
}

void get_read(CAR *ptr, int size){
    char titl[5][10] = {"Make", "Model","Price", "CO2"};
    FILE *file = fopen(CARFILE, "r");
    if(file == NULL){
        printf("Not Exists!\n");
        exit (1);
    }
    fread(ptr, sizeof(CAR), size, file);

    printf("%-15s | %-20s | %-10s | %-10s\n", titl[0], titl[1], titl[2], titl[3]);

    for(int i = 0; i < size; i++){
        printf("%-15s | %-20s | %-10d | %-.2f\n", ptr[i].maker, ptr[i].model, ptr[i].price, ptr[i].emission);
    }
    fclose(file);
}

void get_added(CAR *ptr, int size){
    FILE *file;
    char buff[15];
    file = fopen(CARFILE, "ab");
    if(file == NULL){
        printf("Not Exists!\n");
        exit(1);
    }
    printf("New Car Info:\n\n");
    printf("Enter New make of the car: ");
    fgetc(stdin);
    if(fgets(buff, 20, stdin) != NULL){
        sscanf(buff,"%[^\n]", ptr->maker);
    };
    printf("Enter new car model: ");
    if(fgets(buff, 20, stdin) != NULL){
        sscanf(buff,"%[^\n]", ptr->model);
    };
    printf("Enter new car price: ");
    if(fgets(buff, 20, stdin) != NULL){
        sscanf(buff,"%d", &ptr->price);
    };
    printf("Enter new car emission: ");
    if(fgets(buff, 20, stdin) != NULL){
        sscanf(buff,"%f", &ptr->emission);
    };
    fwrite(ptr, sizeof(CAR), size, file);
    fclose(file);
}

int get_fsize(void){
    int itm = 0;
    FILE *file = fopen(CARFILE, "rb");
    if(file == NULL){
        printf("No Records Exists!\n");
        exit (1);
    }
    fseek(file, 0, SEEK_END);
    itm = ftell(file) / sizeof(CAR);
    fclose(file);
    return itm;
}

void file_load(CAR *ptr){
    char *buff_str = NULL;
    long length;
    char fname[LEN];
    FILE *fpt;
    FILE *in_file;
    printf("Enter the file name: ");
    scanf("%s", fname);
    fpt = fopen(fname, "r");
    if(fpt == NULL){
        printf("File can not be opened!");
        exit(1);
    }else{
        fseek(fpt, 0, SEEK_END);
        length = ftell(fpt);
        fseek(fpt, 0, SEEK_SET);
        buff_str = (char *)malloc(length);
    }
    if(buff_str){
        fread(buff_str, 1, length, fpt);
    }
    char *m = strstr(buff_str, "make");
    if(m){
        sscanf(m + 7, "%4s", ptr->maker);
    }
    char *md = strstr(buff_str, "model");
    if(md){
        sscanf(md + 8, "%5s", ptr->model);
    }
    char *prs = strstr(buff_str, "price");
    if(prs){
        sscanf(prs + 7, "%d", &ptr->price);
    }
    char *emi = strstr(buff_str, "emission");
    if(emi){
        sscanf(emi + 10, "%f", &ptr->emission);
    }

    in_file = fopen(CARFILE, "ab");
    fwrite(ptr, sizeof(CAR), 1 , in_file);
    free(buff_str);
    fclose(fpt);
    fclose(in_file);

}
