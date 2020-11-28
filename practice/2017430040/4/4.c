/*
date : 20201116
name :JungHyun Choi
description : get char and show packing sequence 
*/

#include <stdio.h>

#define CHAR_BIT 8

void printU(unsigned int uc){
    int b[32], i;
    unsigned int step = 0x80000000; //unsigned char max bit

    //mask
    for(i=0;i<32;i++){
        if(uc & step) b[i] = 1;
        else b[i] = 0;
        step >>= 1;
    }
    

    printf("Binary expression :");
    for(i=0;i<32;i++){
        if(i%4 == 0) printf(" ");
        printf("%d", b[i]);
    }
    printf("\n");
}


int main(){

    //init
    unsigned int uc = 0;
    char c[4];
    char* namespace[4] ={"first", "second","third","fourth"};
    int i ;

    for(i = 0 ; i<4 ; i++ ){
        printf("%s character: " , namespace[i]);
        scanf(" %c",&c[i]);
        
        //packing
        uc = (c[i] << CHAR_BIT*i) | uc;
        printU(uc);
        
    }

    printf("You entered: %u\n" , uc);

}

