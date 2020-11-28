/*
date : 20201116
name :JungHyun Choi
description : chose direction and change in binaray
*/
#include <stdio.h>


unsigned char shiftU(unsigned char uc, int dir, int size){
    unsigned char temp;
    
    //check shift dircetion 
    temp = dir == 1 ? uc>>size : uc<<size; 
    
    return temp;
}


void printU(unsigned char uc){
    int b[8], i;
    unsigned char step = 0x80; //unsigned char max bit

    //mask
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
    int dir, size;
    //get input and check number
    printf("Input unsigned char: ");
    scanf("%hhu", &uc);
    printU(uc);

    //when dir is not 0 or 1, infintite loop broken 
    while(1){
        printf("Input direction and shift size: ");
        scanf("%d %d",&dir ,&size);
        //other case end function 
        if(dir != 1 && dir != 0) break;

        uc =shiftU(uc , dir, size);
        printU(uc);
    }
}