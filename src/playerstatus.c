/*




made by choi 



this file make player's stats contorl 
it almost used with item







*/

#include "playerstatus.h"




void statusControl(Entity *block ,Entity *player )
{
    block->item.health =0;
    
    switch(block->item.itemType)
    {
        case ITEMSKATE:
            if(player->status->speed<10)   player->status->speed += 1;
            break;
        case ITEMPOTION:
            if(player->status->bombPower<7) player->status->bombPower +=1;
            break;
        case ITEMBALLON:
            if(player->status->bombNum <7)  player->status->bombNum += 1;
            break;
        case ITEMPOWERMAX:
            player->status->bombPower = 7;

    }


}
