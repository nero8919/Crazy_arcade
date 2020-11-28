







#include "map.h"


void mapLoad(int numberArray[][15] , int mapNumber)
{
 FILE *myFile;
    switch(mapNumber){

        case 1 : 
            myFile = fopen("map/map1.txt", "r");
            break;
        case 2 : 
            myFile = fopen("map/map2.txt", "r");
            break;
    }
   

    //read file into array
    int i , j;

    for (i = 0; i < mapTileY; i++)
    {
        for( j = 0 ; j<mapTileX ; j++)
        {
            fscanf(myFile, "%d", &numberArray[i][j]);
        }
    }

}

void mapSelection(void){


    
}