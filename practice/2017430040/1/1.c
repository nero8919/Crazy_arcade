/*
date : 20201116
name : JungHyun Choi
description : explain the result
*/
#include <stdio.h>

void printU(unsigned char uc){
    int b[8], i;
    unsigned int step = 0x80;

    for(i=0;i<8;i++){
        if(uc & step) b[i] = 1;
        else b[i] = 0;
        step >>= 1;
    }
    
    printf("Binary expression:");
    for(i=0;i<8;i++){
        if(i%4 == 0) printf(" ");
        printf("%d", b[i]);
    }
    printf("\n");
}

int main(){
    unsigned char uc;
   
    printf("Input unsigned char: ");
    scanf("%hhu", &uc);
    printU(uc);

    
}