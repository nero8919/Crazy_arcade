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
            if(stage.status1.speed<10)    stage.status1.speed += 1;
            break;
        case ITEMPOTION:
            if(stage.status1.bombPower<10) stage.status1.bombPower +=1;
            break;
        case ITEMBALLON:
            if(stage.status1.bombNum <10)  stage.status1.bombNum += 1;
            break;
        case ITEMPOWERMAX:
            stage.status1.bombPower = 10;

    }




}
