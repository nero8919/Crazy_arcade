/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Transformed by choiJUngHyun
UPdate log :player add

have to do : 	1 init error debug
				2item didn't get 
				3 block clip 


*/

#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);
static void drawBackground(void);
static void drawmap_background(void);
static void resetStage(void);
static void doBlock(void);
static void doItem(Entity *block);
static void drawItem(void);
static void initItem(void);
static void initBlock(void);
static void drawBlock(void);
static int bulletHitBlock(Entity *b);
static void spawnBlock(int i, int j);
static void doGetItem(void);
static void chooseMap(void);
static void clipPlayer(void);
static void clipPlayerFromBox(void);

//static int bulletHitItem(Entity *b);

static void EventManagerupdate();


static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *background;
static SDL_Texture *map_background;
static SDL_Texture *bulletTexture;
static SDL_Texture *playerstaticTexture;
static SDL_Texture *playerupTexture;
static SDL_Texture *playerdownTexture;
static SDL_Texture *playerleftTexture;
static SDL_Texture *playerrightTexture;


static SDL_Texture *item;
static SDL_Texture *Box;
//static Item *item; 

static int itemX;
static int backgroundX;
static int map_backgroundX;
static int mapNumber= 2;
static int enemySpawnTimer =0;
static SDL_Texture *mapBlock[MAPTILENUM];
static SDL_Texture *itemType[ITEMNUM];
static int mapArray[15][15];

void initStage(void)
{
	int i, j;
	
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	
	resetStage();
	
	initPlayer();

	initItem();

	chooseMap();



	for(i=0 ; i<mapTileY ; i++)
	{
		for(j=0 ; j<mapTileX ; j++)
		{
			spawnBlock(i,j);	//init linked list 
		}
	}
	 


	bulletTexture = loadTexture("gfx/playerBullet.png");
	switch(mapNumber){
		case 1:
			map_background = loadTexture("gfx/mapbg1.png");
			break;
		case 2:
			map_background = loadTexture("gfx/mapbg2.png");
			break;
	}
	
	background = loadTexture("gfx/play_bg.png");
	bulletTexture = loadTexture("gfx/playerBullet.png");
	
	playerstaticTexture = loadTexture("gfx/bazzi_front.png");
	playerupTexture = loadTexture("gfx/bazziUp.png");
	playerdownTexture = loadTexture("gfx/bazziDown.png");
	playerleftTexture = loadTexture("gfx/bazziLeft.png");
	playerrightTexture = loadTexture("gfx/bazziRight.png");


}

static void chooseMap(void)
{
	int i; 

	for(i = 0; i<MAPTILENUM; i++)
	{
		mapBlock[i] = (SDL_Texture *)SDL_calloc(1, sizeof(Box));
		memset(&mapBlock[i], 0, sizeof(Box));
	}

	switch(mapNumber){

		case 1:

			mapBlock[BOXTYPE1] = loadTexture("item/cookie1.png");
			mapBlock[BOXTYPE2] = loadTexture("item/cookie2.png");
			break;
		case 2:
			mapBlock[BOXTYPE1] = loadTexture("item/box1.png");
			mapBlock[BOXTYPE2] = loadTexture("item/box2.png");
			break;
	}

	mapLoad(mapArray, mapNumber);


}


static void initBlock(void)
{

	
}



static void initItem(void)
{
	int i;

	for(i = 0; i<ITEMNUM; i++)
	{
		itemType[i] = (SDL_Texture *)SDL_calloc(1, sizeof(Box));
		memset(&itemType[i], 0, sizeof(Box));
	}

	itemType[ITEMSKATE] = loadTexture("item/skate.png");
	itemType[ITEMPOTION] = loadTexture("item/potion.png");
	itemType[ITEMBALLON] = loadTexture("item/ballon.png");
	itemType[ITEMPOWERMAX] = loadTexture("item/powerMax.png");
	 
	/*
	app.player_surface = SDL_LoadBMP("item/powerMax.bmp");
	SDL_SetColorKey(app.player_surface, 1, SDL_MapRGB(app.player_surface->format, 255, 0, 255));
    app.window_surface = SDL_GetWindowSurface(app.window);

	if (app.player_surface ==NULL)
	{
		printf("unable to loac screen: %s\n", SDL_GetError);
		return 1;
	}
	*/

}

static void resetStage(void)
{
	Entity *e;
	
	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}
	
	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}
	
	
	while (stage.pointsHead.next)
	{
		e = stage.pointsHead.next;
		stage.pointsHead.next = e->next;
		free(e);
	}

	while (stage.blockHead.next)
	{
		e = stage.blockHead.next;
		stage.blockHead.next = e->next;
		free(e);
	}
	
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.blockTail = &stage.blockHead;
}
/* make start position randomly , i will soon update it
static int initPosition(void)
{
	int i, j, zeroNum;
	for(i=0 ; i<mapTileY ; i++)
	{
		for(j=0 ; j<mapTileX ; j++)
		{
			if(mapArray[i][j] ==0) zeroNum++;
		}
	}

}
*/
static void initPlayer(void) //player init 
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	
	player->health = 1;
	
	player->x = MAP_X+(MAP_WIDTH/15)*(4);
	player->y = MAP_Y+(MAP_HEIGHT/15)*(2);

	player->texture = playerstaticTexture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	player->direction =INIT;
	
	
	//init error occur 
}



static void logic(void)
{
	
	doPlayer();
	
	doBullets();
	
	doBlock();

	doGetItem();

	clipPlayer();

	clipPlayerFromBox();

}

static void doBlock(void)
{
	Entity *block, *prev;
		
	prev = &stage.blockHead;
	
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		
		
		if( block->item.health==0 && block->health ==0 )
		{ 	
			
			if (block == stage.blockTail)
			{
				stage.blockTail = prev;
			}
			
			prev->next = block->next;
			free(block);
			block = prev;
		}
		
		prev = block;
	}


}


static void doPlayer(void)
{
	
	player->dx = player->dy = 0;
	
	if (player->reload > 0)
	{
		player->reload--;
	}
	
	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
		if(player->direction !=UP) 
		{
			player->texture = playerupTexture;
			player->direction =UP;
		}
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
		if(player->direction !=DOWN) 
		{
			player->texture = playerdownTexture;
			player->direction =DOWN;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
		if(player->direction !=LEFT)
		{
			player->texture = playerleftTexture;
			player->direction =LEFT;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
		if(player->direction !=RIGHT) 
		{
			player->texture = playerrightTexture;
			player->direction =RIGHT;
		}
	}
	
	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload <= 0)
	{
		fireBullet();
	}
	
	if(!app.keyboard[SDL_SCANCODE_UP] && !app.keyboard[SDL_SCANCODE_DOWN] && !app.keyboard[SDL_SCANCODE_LEFT] && !app.keyboard[SDL_SCANCODE_RIGHT])
	{	//HOLD condition
		if(player->direction !=HOLD) 
		{
			player->direction =HOLD;

			
		}

	}
	
	player->x += player->dx;
	player->y += player->dy;
}

static void fireBullet(void)
{
	Entity *bullet;
	
	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;
	
	bullet->x = player->x;
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->side = SIDE_PLAYER;

	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet-> w, &bullet-> h);
	
	bullet-> y += (player-> h / 2) - (bullet-> h / 2);
	
	player->reload = 4;
}
	
static void doBullets(void)
{
	Entity *b, *prev;
	
	prev = &stage.bulletHead;
	
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		
		if (bulletHitBlock(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}
			
			prev->next = b->next;
			free(b);
			b = prev;
		}
		
		prev = b;
	}
}



static int bulletHitBlock(Entity *b)
{
	Entity *block;
	
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(block->health == 1)
		{
			if ( collision(b->x, b->y, b->w, b->h, block->x, block->y, block->w, block->h)) //block bomb
			{
				
				b->health = 0;
				block->health = 0;
				
				doItem(block);
		
				return 1;
			}
		}
		else //item burn by bomb
			{
				if ( collision(b->x, b->y, b->w, b->h, block->item.x, block->item.y, block->item.w, block->item.h))
				{
					b->health = 0;
					block->item.health = 0;
					
					return 1;
				}
			}

	}
	return 0;
}


static void spawnBlock(int i , int j)
{
	Entity *block;
	SDL_Rect *rect;

		block = malloc(sizeof(Entity));
		memset(block, 0, sizeof(Entity));
		rect = malloc(sizeof(SDL_Rect));
		memset(rect, 0 , sizeof(SDL_Rect));

		stage.blockTail->next = block;
		stage.blockTail= block;

		
		if(mapArray[i][j] != 0)
		{
			block->x = MAP_X+(MAP_WIDTH/15)*(i);
			block->y = MAP_Y+(MAP_HEIGHT/15)*(j);
			block->w =MAP_WIDTH/15;
			block->h =MAP_HEIGHT/15;
			block->side = 1;
			block->health = 1;

			rect->w =MAP_WIDTH/15;
			rect->h =MAP_HEIGHT/15;

			if(mapArray[i][j] == 1 )
			{ 
				block->texture = mapBlock[BOXTYPE1];
			}
			if(mapArray[i][j] == 2 ) 
			{
				block->texture = mapBlock[BOXTYPE2];
			
			}
			SDL_QueryTexture(block->texture, NULL, NULL, &block->w, &block->h);
			
			//blit(block->texture , block->x, block-> y);
			blitRect(block->texture , rect , block->x ,block->y);
		}



}
	
static void doItem(Entity *block)
{
	char temp;
	temp = rand()%4;
	block->item.x =block->x;
	block->item.y =block->y;
	block->item.texture = itemType[temp];
	block->item.itemType = temp;
	block->item.w =MAP_WIDTH/15;
	block->item.h =MAP_HEIGHT/15;
	block->item.health = 1;

	SDL_QueryTexture(block->item.texture, NULL, NULL, &block->w, &block->h);
}
/*
static void doItem(void)
{

	Entity *b, *prev;
	
	prev = &stage.bulletHead;
	
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		
		if (bulletHitBlock(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}
			
			prev->next = b->next;
			free(b);
			b = prev;
		}
		
		prev = b;
	}

}*/

static void doGetItem(void)//playser get item
{
	Entity *block;
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(block->health ==0) 
		{
			//have to fix
			if (collision(block->item.x, block->item.y, block->item.w, block->item.h, player->x, player->y, player->w, player->h))
			{
				
				block->item.health =0;
				//statusControl(block);
		
			}
		}
	}
}

static void clipPlayerFromBox(void) // must be debugging
{
	Entity *block;
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		//block colmn clip
		if (player->x > block->x && player->x <(block->x+block->w))
		{
			
			if (player->y > block->y)
			{
				player->y = block->y;
			}
			
			if (player->y < (block->y+block->h))
			{
				player->y =(block->y+block->h);
			}
		
		}
		
		if (player->y < block->y && player->y >(block->y+block->h))
		{
			if (player->x < block->x)
			{
				player->x = block->x;
			}
			
			if (player->x > (block->x+block->w))
			{
				player->x =(block->x+block->w);
			}
		}
		
	}


}


static void clipPlayer(void)
{
	if (player != NULL)
	{
		if (player->x < MAP_X)
		{
			player->x = MAP_X;
		}
		
		if (player->y < MAP_Y)
		{
			player->y = MAP_Y;
		}
		
		if (player->x >MAP_WIDTH)
		{
			player->x = MAP_WIDTH;
		}
		
		if (player->y > MAP_HEIGHT)
		{
			player->y = MAP_HEIGHT;
		}
	}
}



static void draw(void)
{
	
	drawBackground();

	drawmap_background();

	drawPlayer();
	
	drawBullets();

	drawItem();

	drawBlock();
}

/*
static void drawBlock(void)
{
	SDL_Rect block;

	block.x =MAP_X;
	block.y =MAP_Y;
	block.w =MAP_WIDTH/15;
	block.h =MAP_HEIGHT/15;

	SDL_RenderCopy(app.renderer, block1, NULL, &block);

}*/

static void drawBlock(void)
{
	Entity *block;
	SDL_Rect *rect;

	rect = malloc(sizeof(SDL_Rect));
	memset(rect, 0 , sizeof(SDL_Rect));

	rect->w =MAP_WIDTH/15;
	rect->h =MAP_HEIGHT/15;

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(block->health != 0)
		{
			blitRect(block->texture,rect, block->x, block->y);
			//blit(block->texture , block->x, block-> y);
		}
	}
}

static void drawItem(void)
{
	Entity *block;	//use block entity
	static int step=0;

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{	if(block->item.health != 0)
		{
			blit(block->item.texture , block->x , block->y);
			//moveani(block->item.texture , block->x , block->y, 2);
		}
	}

	/*
	SDL_Rect rcSprite ;
	SDL_Rect item = {MAP_X ,MAP_Y,MAP_WIDTH/15 ,MAP_HEIGHT/15};
	static int i=0;
	int player_idx = 0;
	rcSprite.x =MAP_WIDTH/15*i;
	rcSprite.y =MAP_Y;
	
	rcSprite.w = 2*MAP_WIDTH/15;
	rcSprite.h = MAP_HEIGHT/15;
	
	if(i==0) i=1;
	if(i==1) i=0;
	SDL_BlitSurface(app.player_surface, &rcSprite, app.window_surface, NULL);
	*/
}


static void drawPlayer(void)
{	
	static int step=0;

	if(player->direction == INIT)
	{
		blit(player->texture , player->x , player->y);
	}
	
	moveani(player->texture ,player->x , player->y ,step, characterPNGsize);
	
	if(player->direction !=HOLD){

		if(--enemySpawnTimer <= 0)
		{
			step = step<5 ? step+1 : 0;

			enemySpawnTimer = 5;

		}
	}

	//blit(player->texture ,player->x , player->y);
	
	
	/*static int step = 0;
	
	
	SDL_Rect dst,src;
	
	dst.x = player->x;
	dst.y = player->y;

	SDL_QueryTexture(player->texture, NULL, NULL, &src.w, &src.h);

	dst.w=src.w/7;
	dst.h=src.h;
	src.x=(src.w/7)*step;
	src.y = 0;
	src.w=src.w/7;
	
	SDL_RenderCopy(app.renderer, player->texture, &src, &dst);

	if(--enemySpawnTimer <= 0)
	{
		step = step<5 ? step+1 : 0;

		enemySpawnTimer = 5;

	}*/
}

static void drawBullets(void)
{
	Entity *b;
	
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		
	
		blit(b->texture, b->x, b->y);
		

	}
}


static void drawBackground(void)
{
	SDL_Rect dest;
	int x;
	
	for (x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;
		
		SDL_RenderCopy(app.renderer, background, NULL, &dest);
	}
}

static void drawmap_background(void)
{
	SDL_Rect dest;
	int x;
	
	for (x = map_backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = MAP_X;
		dest.y = MAP_Y;
		dest.w = MAP_WIDTH;
		dest.h = MAP_HEIGHT;
		
		SDL_RenderCopy(app.renderer, map_background, NULL, &dest);
	}
}



//checking pixel
/*
void EventManagerupdate(){
    SDL_Event e;
	
		if(!e.button.clicks){
			printf("x : %d y: %d",e.button.x ,e.button.y);
			//mousePress(e.button);
			e.button.clicks=0;
		}
        
    
}*/
