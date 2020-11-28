/*




made by choi 



this file make player's stats contorl 
it almost used with item







*/

#include "playerstatus.h"




void statusControl(Entity *block  )
{
    block->item.health =0;

    switch(block->item.itemType)
    {
        case ITEMSKATE:
            if(status.speed<10)    status.speed += 1;
            break;
        case ITEMPOTION:
            if(status.bombPower<10) status.bombPower +=1;
            break;
        case ITEMBALLON:
            if(status.bombNum <10)  status.bombNum += 1;
            break;
        case ITEMPOWERMAX:
            status.bombPower = 10;




    }




}
