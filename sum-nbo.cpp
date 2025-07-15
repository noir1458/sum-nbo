#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>
#include <cstdlib>
#include <string.h>
#include <malloc.h>

using namespace::std;

//unsigned char -> uint32_t func
uint32_t my_bin32(unsigned char buffer[]){
    uint32_t tmp = 0x00000000;
    for (int i=0;i<4;i++){
        tmp += buffer[i] << (8*i);
        printf("%08x\n",tmp);
    }
    return htonl(tmp);
}

int main(int argc, char *argv[]){
    FILE* ptr;
    unsigned char buffer[4];
    uint32_t sum = 0;

    for(int i=1;i<argc;i++){
        ptr = fopen(argv[i],"rb");
        if (ptr == NULL){
            printf("\nfile error");
            exit(1);
        }

        fread(buffer,4,1,ptr);

        fseek(ptr,0,SEEK_END);
        long int size = ftell(ptr);
        //printf("%ld\n",size);
        if (size < 4){
            printf("\nfile size small");
            exit(1);
        }


        uint32_t tmp = my_bin32(buffer);
        printf("%d(0x%08x)",tmp,tmp);
        sum += tmp;
        if (i!=argc-1){
            printf(" + ");
        }
    }
    printf(" = %d(0x%08x)",sum,sum);

    fclose(ptr);
    return 0;

}
