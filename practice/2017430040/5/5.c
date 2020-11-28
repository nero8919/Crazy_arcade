/*
date : 20201116
name :JungHyun Choi
description : print sied and diagonal using enum 
*/

#include <stdio.h>

enum FigureType{
    none,
    point,
    rect = 4,
    line = 2,
    tri
};
typedef enum FigureType FigureType;

struct Polygon{
    FigureType type;
    int side;
    int diagonal;
} polygon;

int main(){
    printf("Enter number of figure's point: ");
    /*
    idont know why pointer need 
    enum may be a pointer   
    */
    scanf("%d", (int *)&polygon.type);
    switch (polygon.type)
    {
        case none : 
          printf("This figure is not polygon.\n");
          break;
        case point :
          printf("This figure is not polygon.\n");
          break;
        case line :
          printf("This figure is not polygon.\n");
          break;
        case tri :
          polygon.side =3 ;
          polygon.diagonal =0 ;
          printf("number of polygon's side is %d.\n", polygon.side);
          printf("number of polygon's diagonal is %d.\n", polygon.diagonal);
          break;
        case rect :
          polygon.side =4;
          polygon.diagonal =2;
          printf("number of polygon's side is %d.\n", polygon.side);
          printf("number of polygon's diagonal is %d.\n", polygon.diagonal);
          break;
    }
    
}