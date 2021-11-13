#include<stdio.h>

#define SIZE 10

int validateTime(int hour, int mins);
void read_currTime(void);
void read_slpTime(void);
void getMins(int a, int b);
void getHours(int a, int b);

char input_str[SIZE];
int hour = 0;
int mins = 0;
int sleep_hour = 0;
int sleep_mins = 0;
int valid = 0;
int wakeUp_hour = 0;
int wakeUp_mins = 0;
int temp_hour = 0;
int temp_mins = 0;
int i = 0;

int main(void){
    do{
        read_currTime();
        valid = validateTime(hour, mins);
        if(valid != 0){
            printf("Invalid Time, Try Again!\n");
        }
    }while(valid != 0);

    do{
        read_slpTime();
        valid = validateTime(sleep_hour, sleep_mins);
        if(valid != 0){
            printf("Invalid Time, Try Again!\n");
        }
    }while(valid != 0);

    getMins(mins, sleep_mins);
    getHours(hour,sleep_hour);
    printf("If you go to bed now you must wake up at %d:%02d\n ", wakeUp_hour, wakeUp_mins);
    return 0;
}

void read_currTime(void){
    printf("Enter current time in 24h format (hh:mm): ");
    fgets(input_str, SIZE, stdin);
    i = sscanf(input_str, "%02d:%02d", &hour, &mins);
}

void read_slpTime(void){
    printf("How long do you want to sleep (h:mm): ");
    fgets(input_str, SIZE, stdin);
    i = sscanf(input_str, "%02d:%02d", &sleep_hour, &sleep_mins);
}

void getMins(int a, int b){
    temp_mins = mins + sleep_mins;
    if(temp_mins >= 60){
        wakeUp_mins = temp_mins - 60;
        temp_hour += 1;
    }else{
        wakeUp_mins = temp_mins;
    }
}

void getHours(int a, int b){
    temp_hour += hour + sleep_hour;
    if(temp_hour >= 24){
        wakeUp_hour = temp_hour - 24;
    }else{
        wakeUp_hour = temp_hour;
    }
}

int validateTime(int h, int m){
    int ret = 0;
    if(i != 2) ret = 1;
    if(h> 24 || h < 0) ret = 1;
    if(m > 60 || m < 0) ret = 1;
    return ret;
}
