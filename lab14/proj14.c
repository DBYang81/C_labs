#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define MAXSIZE 100
#define DATASIZE 64

typedef struct chunk{
    uint8_t data [DATASIZE];
    uint16_t size;
    uint16_t crc;
}CHUNK;

uint16_t crc16(const uint8_t* data_p, unsigned int length);

int main(void){
    char fname[MAXSIZE];
    FILE *file;
    CHUNK *ptr = NULL;
    int num_chunk = 0, act_size;

    printf("Enter file name (.txt):");
    scanf("%s", fname);
    file = fopen(fname, "rb");
    if(file == NULL){
        printf("No such file exists!\n");
        return 1;
    }

    ptr = (CHUNK *) malloc(sizeof(CHUNK));
    if(ptr == NULL){
        printf("Allocating Fails!");
        return 1;
    }

    do{
        //read 1 byte DATASIZE(64) times, return amount of
        //read-elements successfully
        act_size = fread(ptr->data, 1, DATASIZE, file);
        ptr->size = act_size;
        ptr->crc = crc16(ptr->data, DATASIZE);
        num_chunk++;
        printf("chunk NO.%d, data size:%d, CRC:%x\n", num_chunk, ptr->size, ptr->crc);
        ptr = (CHUNK *) realloc(ptr, sizeof(CHUNK));

        /*act_size = fread(ptr[num_chunk].data, 1, DATASIZE, file);
        ptr[num_chunk].size = act_size;
        ptr[num_chunk].crc = crc16(ptr[num_chunk].data, DATASIZE);
        printf("chunk NO.%d, data size:%d, CRC:%x\n", num_chunk, ptr[num_chunk].size, ptr[num_chunk].crc);
        num_chunk++;
        ptr = (CHUNK *) realloc(ptr, (num_chunk + 1) * sizeof(CHUNK));
        */
    }while(!feof(file));


    free(ptr);
    fclose(file);

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