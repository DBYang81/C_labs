#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>

#define availtostr(x) ((x) ? "Available":"Reserved")

typedef struct rentalCarInfo{
    char num[5];
    char carMaker[20];
    char model[20];
    char category[2];
    char regisPlate[20];
    int currMile;
    bool avail;
}car;

void carDisplay(car *str, int size);
char* search(car *str, int size);
bool set_status(char *s, car *str, int size);

int main(void){
    char *plate;
    char atv[3];
    char *ch;
    bool T,F;
    bool AoR;
    do{
        car garage[15] = {
            {"#1","Ford", "Focus", "C", "GTC-279", 45000, true},
            {"#2","Hyundai", "i30","C", "WZI-723", 23000,false},
            {"#3","Fiat", "Tipo Estate", "C", "ZTP-227", 92300, true},
            {"#4","Chevrolet", "Cruze", "I", "QSB-514", 3500, true},
            {"#5","Kia","Picanto", "M", "CAT-674", 5000, true},
            {"#6","Citroen", "C3", "E", "TNT-691", 2140, true},
            {"#7","Volkswagen", "Passat", "N", "WRX-336", 12030, true},
            {"#8","Volkswagen", "Jetta", "S", "GRX-176", 15200, true},
            {"#9","Peugeot", "508 Estate", "S", "GWC-311", 22030, false},
            {"#10","Vauxhall/Opel", "Insignia Estate", "P", "LPO-741", 35030, false},
            {"#11","BMW", "S3", "F", "BMO-101", 12030, true},
            {"#12","Mercedes Benz", "E-Class Estate", "N", "PPT-151", 42030, false},
            {"#13","Jaguar", "XE", "P", "LUX-111", 8030, true},
            {"#14","Honda", "CR-V", "X", "SUV-248", 32030, true},
            {"#15","Nissan", "Pathfinder", "F", "CRC-611", 3730, false}
        };
        printf("\n");
        do{
            printf("Program starts (press enter to continue, q to quit): ");
            fgets(atv, 3, stdin);
        }while(atv[0] != 'q' && atv[0] != '\n');
        if(atv[0] == 'q' || strlen(atv) != 1) return false;

        carDisplay(garage, 15);
        plate = search(garage, 15);
        AoR = set_status(plate, garage, 15);

        if(AoR == true){
            printf("\n");
            printf("Status Changed:\n");
            for(int i = 0; i < 15; i++){
                ch = garage[i].regisPlate;
                T = garage[i].avail;
                if(T == AoR && ch == plate){
                    printf("%-3s | %-15s | %-15s | %-5s | %-10s | %7d |%-10s\n", garage[i].num, garage[i].carMaker, garage[i].model, garage[i].category, garage[i].regisPlate, garage[i].currMile, availtostr(garage[i].avail));
                }
            }
        }else{
            printf("\n");
            printf("Status Changed:\n");
            for(int i = 0; i < 15; i++){
                ch = garage[i].regisPlate;
                F = garage[i].avail;
                if(F == AoR && ch == plate){
                    printf("%-3s | %-15s | %-15s | %-5s | %-10s | %7d | %-10s\n", garage[i].num, garage[i].carMaker, garage[i].model, garage[i].category, garage[i].regisPlate, garage[i].currMile, availtostr(garage[i].avail));
                }
            }
        }
    }while(atv[0] != 'q' || strlen(atv) != 1);

    return 0;
}

void carDisplay(car *str, int size){
    char filter[10];
    char *ch;
    int cat_size = 2;
    char catList[10] = {'M','N','E','C','I','S','F','P','X'};
    char *all = "*";
    bool j = false;
    char *row[7] = {"No.","Brand","Model","Catg.","Reg-plate","Miles","Status"};

    do{
        printf("\n");
        printf("Filter out cars by category (*-all): ");
        fgets(filter, 10, stdin);
        if(filter[strlen(filter) - 1 ] == '\n'){
            filter[strlen(filter) - 1] = '\0';
        }
        printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s\n", -3, row[0], -15, row[1], -15, row[2], -5, row[3], -10, row[4], 7, row[5], -10, row[6]);
        printf("\n");
        filter[0] = toupper(filter[0]);
        for(int i = 0; i < strlen(catList); i++){
            if(catList[i] == filter[0])
                j = true;
        }
        if(strlen(filter) != cat_size - 1){
            printf("Invalid Category!\n");
        }else if (j != 1 && filter[0] != '*'){
            printf("Category Not Available!\n");
        }
        for(int i = 0; i < size; i++){
            ch = str[i].category;
            if(strcmp(filter, ch) == 0){
                if(str[i].avail == true){
                    printf("%-3s | %-15s | %-15s | %-5s | %-10s | %7d |%-10s\n", str[i].num, str[i].carMaker, str[i].model, str[i].category, str[i].regisPlate, str[i].currMile, availtostr(str[i].avail));
                }
            }
            if(strcmp(filter, all) == 0){
                printf("%-3s | %-15s | %-15s | %-5s | %-10s | %7d |%-10s\n", str[i].num, str[i].carMaker, str[i].model, str[i].category, str[i].regisPlate, str[i].currMile, availtostr(str[i].avail));
            }
        }
    }while((j == false && filter[0] != '*' ) || strlen(filter) != cat_size -1);
}


char* search(car *str, int size){
    char input[10];
    char *ret;
    bool contain = false;

    do{
        printf("\n");
        printf("Plate-Number lookup (eg.ABC-xxx): ");
        fgets(input, 10, stdin);
        if(input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] = '\0';
        }
        for(int i = 0; i < 3; i++){
            char tmp = toupper(input[i]);
            input[i] = tmp;
        }
        for(int i = 0; i < size; i++){
            if(strcmp(input, str[i].regisPlate) == 0){
                ret = str[i].regisPlate;
                contain = true;
                printf("%-3s | %-15s | %-15s | %-5s | %-10s | %7d |%-10s\n", str[i].num, str[i].carMaker, str[i].model, str[i].category, str[i].regisPlate, str[i].currMile, availtostr(str[i].avail));
            }
        }
        if(contain == false){
            printf("Plate Number Not Exist!\n");
        }
    }while(contain != true);

    return ret;
}

bool set_status(char *s, car *str, int size){
    char set[10], ch;
    int status_size = 2;
    bool b = false;

    do{
        printf("\n");
        printf("Set the Status(A/R): ");
        fgets(set, 10, stdin);
        if(set[strlen(set) - 1] == '\n'){
            set[strlen(set) - 1] ='\0';
        }
        ch = toupper(set[0]);
        if(strlen(set) != status_size - 1){
            printf("Invalid!\n");
        }
    }while((ch != 'A' && ch != 'R') || strlen(set) != status_size - 1);

    for(int i = 0; i < size; i++){
        if(ch == 'A'){
            if(strcmp(s, str[i].regisPlate) == 0){
                str[i].avail = true;
                b = str[i].avail;
            }
        }else if(ch == 'R'){
            if(strcmp(s, str[i].regisPlate) == 0){
                str[i].avail = false;
                b = str[i].avail;
            }
        }
    }
    return b;
}