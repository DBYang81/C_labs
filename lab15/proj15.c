#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define LEN 20


typedef struct chunk{
    uint8_t *data;
    uint16_t size;
    uint16_t capacity;
    uint16_t crc;
}CHUNK;

uint16_t crc16(const uint8_t* data_p, unsigned int length);

int main(void){
    char fname[LEN];
    CHUNK *ptr = NULL;
    FILE *file;
    char answer[3];

    do{
        int input_size = 0;
        int act_size = 0;
        int num_chunk = 0;
        printf("Enter file name (.txt):");
        scanf("%s", fname);
        printf("Chunk size as integer (> 0): ");
        scanf("%d", &input_size);
        if(input_size <= 0) {
            printf("Wrong Size!\n");
            return 1;
        }

        file = fopen(fname, "rb");
        if(file == NULL){
            printf("No such file exists!\n");
            return 1;
        }

        ptr = (CHUNK *) malloc(sizeof(CHUNK));
        if(ptr == NULL){
            free(ptr);
            printf("Allocating fails!\n");
            return 1;
        }

        do{
            ptr[num_chunk].data = (uint8_t *) malloc(input_size * sizeof(unsigned int));
            if(ptr[num_chunk].data == NULL){
                free(ptr[num_chunk].data);
                printf("Allocating fails!");
                return 1;
            }
            act_size = fread(ptr[num_chunk].data, 1, input_size, file);
            ptr[num_chunk].capacity = input_size;
            ptr[num_chunk].size = act_size;
            ptr[num_chunk].crc = crc16(ptr[num_chunk].data, act_size);
            printf("Chunk No. %d, Size: %d, Capacity: %d, CRC:%x\n", num_chunk, ptr[num_chunk].size, ptr[num_chunk].capacity, ptr[num_chunk].crc);
            num_chunk++;
            ptr = (CHUNK *) realloc(ptr, (num_chunk + 1) * sizeof(CHUNK));
        }while(!feof(file));

        for(int i = 0; i < num_chunk; i++){
            free(ptr[i].data);
        }

        free(ptr);
        fclose(file);

        do{
            printf("Open another file for reading? (yes or no): ");
            scanf("%s", answer);
        }while(answer[0] != 'y' && answer[0] != 'n');

    }while(answer[0] == 'y');

    return 0;
}

uint16_t crc16(const uint8_t* data_p, unsigned int length) {
    uint8_t x;
    uint16_t crc = 0xFFFF;
    while (length--){
    x = crc >> 8 ^ *data_p++;
    x ^= x>>4;
    crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}