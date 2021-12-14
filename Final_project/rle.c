#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdarg.h>

#define SIZE 50
#define SPEC 0x80
#define LIM 0xFF

char* get_extension(char * filename);
char* get_new_name(char *filename);
uint16_t get_crc_verify(char* newname);
uint16_t rle_compress(char *filename, char *outfile);
uint16_t rle_decompress(char *filename, char *outfile);
uint16_t crc16(uint8_t* data_p, unsigned int length);
void print_log(char *fname, const char* fmt,...);

int main(int argc, char *argv[]){
    char *filename;
    char *newname;
    uint16_t crc = 0;
    uint16_t crc_unp = 0;
    if(argc > 2){
        if(strcmp (argv[1], "pack") == 0){
            filename = argv[2];
            newname = get_extension(filename);
            crc = rle_compress(filename, newname);
            if(crc){
                printf("Compress Successful.\n");
            }else{
                printf("Compress Unsuccessful!\n");
                return 1;
            }
        }else if(strcmp (argv[1], "unpack") == 0){
            filename = argv[2];
            newname = get_new_name(filename);
            crc_unp = rle_decompress(filename, newname);
            crc = get_crc_verify(newname);

            if(crc == crc_unp){
                printf("Unpack Succeed.\n");
            }else{
                printf("Unpack Fails.\n");
            }
        }else{
            printf("Method is not Found!\n");
            return 1;
        }
    }else{
        printf("Specify Methods and File!\n");
        return 1;
    }
    free(newname);
    return 0;
}

/***************************** PACK FUNCTION *****************************************/

uint16_t rle_compress(char *filename, char *outfile){

    FILE *source = fopen(filename, "rb");
    fseek(source, 0, SEEK_END);
    long orgin_size = ftell(source);
    fseek(source, 0, SEEK_SET);

    FILE *comprd_file = fopen(outfile, "wb");
    if(source == NULL || comprd_file == NULL){
        printf("File can not be opened!\n");
        return 1;
    }

    uint8_t data[orgin_size];
    fread(data, 1, orgin_size, source);
    fseek(source, 0, SEEK_SET);
    uint16_t crc = crc16(data, orgin_size);
    fwrite(&crc, sizeof(uint16_t), 1, comprd_file);

    const char spec = SPEC;
    char currChar;
    char prevChar = EOF;
    unsigned char reptCnt = 0;//check repCnt is not go beyond 255, if does, restart new secondary block
    unsigned char speCnt = 0;

    do{
        currChar = fgetc(source);
        if(prevChar != currChar || reptCnt == LIM){
            if(reptCnt > 3 ){
                fwrite(&spec, sizeof(char), 1, comprd_file);
                fwrite(&reptCnt, 1, 1, comprd_file);
                fwrite(&prevChar, sizeof(char), 1, comprd_file);
            }else{
                if(prevChar == spec && speCnt > 0) {
                        fwrite(&spec, sizeof(char), 1, comprd_file);
                        fwrite(&speCnt, 1, 1 , comprd_file);
                        fwrite(&spec,sizeof(char), 1, comprd_file);
                }else{
                    for(int i = 0; i < reptCnt; i++){
                        fwrite(&prevChar, sizeof(char), 1, comprd_file);
                    }
                }
            }

            if(currChar == spec){
                speCnt = 1;
            }else{
                reptCnt = 1;
            }
            prevChar = currChar;

        }else{
            if(currChar == spec){
                speCnt++;
            }else{
                reptCnt++;
            }
        }
    }while(currChar != EOF);

    fseek(comprd_file, 0, SEEK_END);
    long comprd_size = ftell(comprd_file);
    rewind(comprd_file);

    print_log("logfile.txt", "File_name: %s, org_size: %lu, CRC: %x, Comprd_size: %lu, Packed_name: %s\n\n", filename, orgin_size, crc, comprd_size, outfile);

    fclose(source);
    fclose(comprd_file);

    return crc;
}

/****************************************** CRC FUNCTION ******************************/

uint16_t crc16(uint8_t* data_p, unsigned int length) {
    uint8_t x;
    uint16_t crc = 0xFFFF;
    while (length--){
    x = crc >> 8 ^ *data_p++;
    x ^= x>>4;
    crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}

/****************************************** UNPACK FUNCTION *****************************/

uint16_t rle_decompress(char *filename, char *outfile){

    FILE *cmprd_source = fopen(filename, "rb");
    FILE *decomprd_file = fopen(outfile, "wb");
    if(cmprd_source == NULL || decomprd_file == NULL){
        printf("File can not be opened!\n");
        return 1;
    }
    const char spec = SPEC;
    int count = 0;
    char currChar;

    uint16_t crc = 0;
    fread(&crc, sizeof(uint16_t), 1, cmprd_source);

    while(!feof(cmprd_source)){
        if((currChar = fgetc(cmprd_source)) != EOF){
            if(currChar == spec){
                count = fgetc(cmprd_source);
                currChar = fgetc(cmprd_source);
                for(int i = 0; i < count; i++){
                    fwrite(&currChar, sizeof(char), 1, decomprd_file);
                }
            }else{
                fwrite(&currChar, sizeof(char), 1, decomprd_file);
            }
        }
    }

    print_log("logfile.txt", "File_name: %s, CRC: %x, Packed_name: %s\n\n", outfile, crc, filename);

    fclose(decomprd_file);
    fclose(cmprd_source);

    return crc;
}

/**************************************** FILE EXTENSION *************************************/

char* get_extension(char *filename){
    char* newname;
    int len = strlen(filename);
    newname = malloc(len + 5);
    strncpy(newname, filename, len);
    strcpy(newname + len, ".rle");

    return newname;
}


char* get_new_name(char *filename){
    char *newname;
    char *ptr = strrchr(filename, '.');
    int len = strlen(filename) - strlen(ptr);
    newname = malloc(len + 4);
    strcpy(newname, "new-");
    strncpy(newname + 4, filename, len);

    return newname;
}

/******************************************** VERIFICAITON ********************************/

uint16_t get_crc_verify(char* newname){
    FILE *fp = fopen(newname, "rb");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    uint8_t data[size];
    fread(data, 1, size, fp);
    fseek(fp, 0, SEEK_SET);
    uint16_t crc = crc16(data, size);

    return crc;
}


/**************************************** LOG PRINT **********************************/

void print_log(char*fname, const char* fmt,...){

    FILE *logfile = fopen(fname, "a");

    va_list argptr;
    char pbuf[256];

    va_start (argptr, fmt);
    vsprintf(pbuf, fmt, argptr);
    va_end(argptr);

    fputs(pbuf, stdout);
    if(logfile != NULL){
        fputs(pbuf, logfile);
        fflush(logfile);
    }

}