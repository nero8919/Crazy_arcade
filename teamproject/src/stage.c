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

UPdate log :make block and 


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
static void spawnBlock(void);
static void doGetItem(void);


static void EventManagerupdate();


static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *background;
static SDL_Texture *map_background;
static SDL_Texture *bulletTexture;
static SDL_Texture *itemSkate;
static SDL_Texture *itemPotion;
static SDL_Texture *itemBallon;
static SDL_Texture *itemPowerMax;

static SDL_Texture *block1;
//static Item *item; 

static int itemX;
static int backgroundX;
static int map_backgroundX;
static int enemySpawnTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	
	resetStage();
	
	initPlayer();

	initItem();

	initBlock();

	bulletTexture = loadTexture("gfx/playerBullet.png");
	map_background = loadTexture("gfx/mapbg1.png");
	background = loadTexture("gfx/play_bg.png");
	bulletTexture = loadTexture("gfx/playerBullet.png");
	
	enemySpawnTimer =0;

}

static void initBlock(void)
{

	block1 = loadTexture("item/block_1.png");

}


static void initItem(void)
{


	itemSkate = loadTexture("item/skate.png");
	itemPotion = loadTexture("item/potion.png");
	itemBallon = loadTexture("item/ballon.png");
	itemPowerMax = loadTexture("item/powerMax.png");
	 
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


static void initPlayer()
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;
	
	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}



static void logic(void)
{
	doPlayer();
	
	doBullets();

	spawnBlock();

	//doBlock();

	doGetItem();
}

static void doBlock(void)
{
	Entity *block, *prev;
		
		prev = &stage.blockHead;
		
		for (block = stage.blockHead.next ; block != NULL ; block = block->next)
		{
			
			
			/*error zone : idont know why this is happening
					to make this 
			if (block == player)
			{
				player = NULL;
			}*/
			if( block->item.health==0 && block->health ==0 )
			{ 	
				if (block == player)
				{
				player = NULL;
				}
				
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
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
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
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	
	bullet->y += (player->h / 2) - (bullet->h / 2);
	
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
		if ( collision(b->x, b->y, b->w, b->h, block->x, block->y, block->w, block->h))
		{
			
			b->health = 0;
			block->health = 0;
			

			if (block == player)
			{

			}
			else{
			
			doItem(block);
			//addPointsPod(e->x + e->w / 2, e->y + e->h / 2);			
			}
			return 1;
			
		}

	}
	return 0;
}


static void spawnBlock(void)
{
	Entity *block;

	if (--enemySpawnTimer <= 0)
	{
		block = malloc(sizeof(Entity));
		memset(block, 0, sizeof(Entity));
		stage.blockTail->next = block;
		stage.blockTail= block;



		block->x = MAP_X+(MAP_WIDTH/15)*(rand()%15);
		block->y = MAP_Y+(MAP_HEIGHT/15)*(rand()%15);
		block->w =MAP_WIDTH/15;
		block->h =MAP_HEIGHT/15;
		block->texture = block1;
		SDL_QueryTexture(block->texture, NULL, NULL, &block->w, &block->h);


		block->side = 1;
		block->health = 1;
	
		enemySpawnTimer= 30 + (rand() % FPS);

		
	}


}
	
static void doItem(Entity *block)
{
	block->item.x =block->x;
	block->item.y =block->y;
	block->item.texture = itemPowerMax;
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

static void doGetItem(void)
{
	Entity *block;
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(block->health ==0)
		{
			if (player != NULL && collision(block->x, block->y, block->w, block->h, player->x, player->y, player->w, player->h))
			{
				
				block->item.health = 0;
			}
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

	
		for (block = stage.blockHead.next ; block != NULL ; block = block->next)
		{
			if(block->health !=0){
				blit(block->texture, block->x, block->y);
			}
		}

}

static void drawItem(void)
{
	Entity *block;	//use block entity

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{	if(block->item.health !=0){
			blit(block->item.texture , block->x , block->y);
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
	blit(player->texture, player->x, player->y);
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
