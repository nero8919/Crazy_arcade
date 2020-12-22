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

Transformed by LeeJaewon ,choiJUngHyun

UPdate log :final
				


*/

#include "stage.h"
#define Debug

#define bombexplosionTimer (FPS*3)


int MAPNUMBER=1;

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void initPlayer2(void);
static void fireBullet(Entity *player);
static void doPlayer(void);
static void doPlayer2(void);
static void doBullets(Entity *player);
static void drawPlayer(void);
static void drawPlayer2(void);
static void drawBullets(void);
static void drawBackground(void);
static void drawmap_background(void);
static void resetStage(void);
static void doBlock(void);
static void doItem(Entity *block);
static void drawItem(void);
static void initItem(void);
static void drawBlock(void);
static int bulletHitBlock(Entity *water);
static int waterHitBomb(Entity *water);
static int waterHitPlayer(Entity *water ,Entity *player);
static void spawnBlock(int i, int j);
static void doGetItem(Entity *player);
static void chooseMap(void);
static void clipPlayer(Entity *player);
static void clipPlayerFromBox();
static void clipPlayer2FromBox();
static void drawHud(void);
static void drawDraw(void);
static void firewaterlinecenter(Entity *player, Entity *bullet);
static void firewaterline(Entity *player,Entity *bullet,int num,int waterLinePower);
static void drawWaterline(void);
static void doWaterline(Entity *player);
static void waterlineinit(void);
static void quitButton(void);


static void diePlayer(void);
static void diePlayer2(void);
static void drawResultplayer1(Entity *player);
static void drawResultplayer2(Entity *player);
static void initResult(void);
static void restart(void);



//static int bulletHitItem(Entity *b);

static void EventManagerupdate();


static Entity *player;
static Entity *player2;
static SDL_Texture *bulletTexture;
static SDL_Texture *background;
static SDL_Texture *map_background;

static SDL_Texture *playerstaticTexture;
static SDL_Texture *playerupTexture;
static SDL_Texture *playerdownTexture;
static SDL_Texture *playerleftTexture;
static SDL_Texture *playerrightTexture;

static SDL_Texture *player2staticTexture;
static SDL_Texture *player2upTexture;
static SDL_Texture *player2downTexture;
static SDL_Texture *player2leftTexture;
static SDL_Texture *player2rightTexture;



static SDL_Texture *item;
static SDL_Texture *Box;
static SDL_Texture *waterline;
static SDL_Texture *waterLine[5];

static SDL_Texture *playerdieTexture;
static SDL_Texture *player2dieTexture;
static SDL_Texture *winTexture;
static SDL_Texture *loseTexture;
static SDL_Texture *p1Texture;
static SDL_Texture *p2Texture;



static int itemX;
static int backgroundX;
static int map_backgroundX;

static int enemySpawnTimer =0;
static int enemySpawnTimer2 =0;
static SDL_Texture *mapBlock[MAPTILENUM];
static SDL_Texture *itemType[ITEMNUM];
static int mapArray[15][15];
static int BombXArea = MAP_WIDTH/mapTileX;
static int BombYArea = MAP_HEIGHT/mapTileY;

static int timeout=FPS*5;
static int GameReset;

/*---------------------------------------------------------------------------------------
*****************************************************************************************


											init line

*****************************************************************************************
----------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------
											init stage
----------------------------------------------------------------------------------------*/
void initStage(void)
{
	int i, j;
	
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	
	resetStage();
	
	initPlayer();

	initPlayer2();

	initItem();

	chooseMap();

	waterlineinit();

	initResult();	

	for(i=0 ; i<mapTileY ; i++)
	{
		for(j=0 ; j<mapTileX ; j++)
		{
			spawnBlock(i,j);	//init linked list 
		}
	}
	 


	bulletTexture = loadTexture("gfx/bomb.png");

	switch(MAPNUMBER){
		case 1:
			map_background = loadTexture("gfx/mapbg1.png");
			loadMusic("sound/map1.ogg");
			playMusic(1);
			break;
		case 2:
			map_background = loadTexture("gfx/mapbg2.png");
			loadMusic("sound/forest_map_1.ogg");
			playMusic(1);
			break;
	}
	
	background = loadTexture("gfx/play_bg.png");
	
	playerstaticTexture = loadTexture("gfx/bazzi_front.png");
	playerupTexture = loadTexture("ani/bazziUp.png");
	playerdownTexture = loadTexture("ani/bazziDown.png");
	playerleftTexture = loadTexture("ani/bazziLeft.png");
	playerrightTexture = loadTexture("ani/bazziRight.png");
	playerdieTexture = loadTexture("ani/bazziDie.png");


	player2staticTexture = loadTexture("gfx/dao_front.png");
	player2upTexture = loadTexture("ani/daoUp.png");
	player2downTexture = loadTexture("ani/daoDown.png");
	player2leftTexture = loadTexture("ani/daoLeft.png");
	player2rightTexture = loadTexture("ani/daoRight.png");
	player2dieTexture = loadTexture("ani/daoDie.png");

	
	GameReset =0;
	stage.time = 120;
	//bombexplosionTimer=FPS*5;

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
	while (stage.fighter2Head.next)
	{
		e = stage.fighter2Head.next;
		stage.fighter2Head.next = e->next;
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
	stage.fighter2Tail = &stage.fighter2Head;
	stage.bulletTail = &stage.bulletHead;
	stage.blockTail = &stage.blockHead;
	stage.waterTail = &stage.waterHead;

}

/*---------------------------------------------------------------------------------------
								init map and spawn block
----------------------------------------------------------------------------------------*/

static void chooseMap(void)
{
	int i; 

	for(i = 0; i<MAPTILENUM; i++)
	{
		mapBlock[i] = (SDL_Texture *)SDL_calloc(1, sizeof(Box));
		memset(&mapBlock[i], 0, sizeof(Box));
	}

	switch(MAPNUMBER){

		case 1:
			mapBlock[BOXTYPE1] = loadTexture("item/cookie1.png");
			mapBlock[BOXTYPE2] = loadTexture("item/cookie2.png");
			break;
		case 2:
			mapBlock[BOXTYPE1] = loadTexture("item/box1.png");
			mapBlock[BOXTYPE2] = loadTexture("item/box2.png");
			break;
	}
	mapLoad(mapArray, MAPNUMBER);


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

/*---------------------------------------------------------------------------------------
								init block,bomb,waterline
----------------------------------------------------------------------------------------*/

static void initResult(void)
{
	winTexture=loadTexture("gfx/win.png");
	loseTexture=loadTexture("gfx/LOSE.png");
	p1Texture=loadTexture("gfx/player1_final.png");
	p2Texture=loadTexture("gfx/player2_final.png");
}

static void waterlineinit(void)
{
	int i;

	for(i = 0; i<5; i++)
	{
		waterLine[i] = (SDL_Texture *)SDL_calloc(1, sizeof(waterline));
		memset(&waterLine[i], 0, sizeof(waterline));
	}

	waterLine[UPLINE] = loadTexture("gfx/boom_up.png");
	waterLine[DOWNLINE] =loadTexture("gfx/boom_down.png");
	waterLine[LEFTLINE] = loadTexture("gfx/boom_left.png");
	waterLine[RIGHTLINE] = loadTexture("gfx/boom_right.png");
	waterLine[CENTERLINE] = loadTexture("gfx/boom_center.png");
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
	 

}

/*---------------------------------------------------------------------------------------
											init player
----------------------------------------------------------------------------------------*/

static void initPlayer(void) //player init 
{
	CharictarStatus *stat;

	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));

	stat = malloc(sizeof(CharictarStatus));
	memset(stat, 0, sizeof(CharictarStatus));

	stage.fighterTail->next = player;
	stage.fighterTail = player;
	
	player->health = 1;
	
	player->x = MAP_X+(MAP_WIDTH/15)*(13);
	player->y = MAP_Y+(MAP_HEIGHT/15)*(14)-20;
	player->direction =INIT;
	player->texture = playerstaticTexture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	
	
	player->w = MAP_WIDTH/15;
	player->h = MAP_HEIGHT/15*2;

	stat->bombNum = 2;
	stat->speed =1;
	stat->bombPower =1;
	player->status=stat;
}

static void initPlayer2(void) //player init 
{
	CharictarStatus *stat;

	player2 = malloc(sizeof(Entity));
	memset(player2, 0, sizeof(Entity));

	stat = malloc(sizeof(CharictarStatus));
	memset(stat, 0, sizeof(CharictarStatus));

	stage.fighter2Tail->next = player2;
	stage.fighter2Tail = player2;
	
	player2->health = 1;
	
	player2->x = MAP_X+(MAP_WIDTH/15)*(5);
	player2->y = MAP_Y+(MAP_HEIGHT/15)*(0) - 20  ;
	player2->direction =INIT;
	player2->texture = player2staticTexture;
	SDL_QueryTexture(player2->texture, NULL, NULL, &player2->w, &player2->h);
	
	
	player2->w = MAP_WIDTH/15;
	player2->h = MAP_HEIGHT/15*2;

	stat->bombNum = 2;
	stat->speed =1;
	stat->bombPower =1;
	player2->status=stat;
}

/*---------------------------------------------------------------------------------------
*****************************************************************************************


											DO

*****************************************************************************************
----------------------------------------------------------------------------------------*/

static void logic(void)
{
	
	doPlayer();
	
	doPlayer2();
	
	doBullets(player);

	doBullets(player2);
	
	doBlock();

	doGetItem(player);

	doGetItem(player2);

	doWaterline(player);

	doWaterline(player2);

	clipPlayer(player);

	clipPlayer(player2);

	clipPlayerFromBox();

	clipPlayer2FromBox();

	quitButton();

	if(GameReset) restart();

}

/*---------------------------------------------------------------------------------------
								QUIT mouse button
----------------------------------------------------------------------------------------*/
static void quitButton(void)
{
	if(mouseButton(QUIT_BUTTON_X,QUIT_BUTTON_Y,QUIT_BUTTON_W,QUIT_BUTTON_H))
	{
		printf("end\n");		
		exit(0);
	}

}


/*---------------------------------------------------------------------------------------
								remove linked list
----------------------------------------------------------------------------------------*/
static void doBlock(void)
{
	Entity *block, *prev;
		
	prev = &stage.blockHead;
	
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		
		if( block->item.health<=0 && block->health <=0 )
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


/*---------------------------------------------------------------------------------------
									player controler 
----------------------------------------------------------------------------------------*/
static void doPlayer(void)
{
	static int countbomb=0; 
	static int bombResetTimer = bombexplosionTimer;

	player->dx = player->dy = 0;
	player->updatespeed = PLAYER_SPEED + (0.5)*player->status->speed;
	
//timer reset
	if(countbomb>0) 
	{
		if(--bombResetTimer<0 && countbomb<=player->status->bombNum)
		{
			countbomb = 0; 
			bombResetTimer = bombexplosionTimer;
		}
	}
//timer start
	

	if (player->reload > 0)
	{
		player->reload--;
	}
//key input	
	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -player->updatespeed;
		if(player->direction !=UP) 
		{
			player->texture = playerupTexture;
			player->direction =UP;
		}
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = player->updatespeed;
		if(player->direction !=DOWN) 
		{
			player->texture = playerdownTexture;
			player->direction =DOWN;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -player->updatespeed;
		if(player->direction !=LEFT)
		{
			player->texture = playerleftTexture;
			player->direction =LEFT;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = player->updatespeed;
		if(player->direction !=RIGHT) 
		{
			player->direction =RIGHT;
			player->texture = playerrightTexture;

		}
	}
	if(countbomb<player->status->bombNum )
	{
		if (app.keyboard[SDL_SCANCODE_RSHIFT] && player->reload <= 0)
		{
			fireBullet(player);
			countbomb++;
		}

	}
	
	if(player->direction != INIT)
	{
		if(!app.keyboard[SDL_SCANCODE_UP] && !app.keyboard[SDL_SCANCODE_DOWN] && !app.keyboard[SDL_SCANCODE_LEFT] && !app.keyboard[SDL_SCANCODE_RIGHT])
		{	//HOLD condition
			if(player->direction !=HOLD) 
			{
				player->direction =HOLD;

			}

		}
	}

	player->x += player->dx;
	player->y += player->dy;
}



static void doPlayer2(void)
{
	static int countbomb=0; 
	static int bombResetTimer = bombexplosionTimer;

	player2->dx = player2->dy = 0;
	player2->updatespeed = PLAYER_SPEED + (0.5)*player2->status->speed;
	
	if(countbomb>0) 
	{
		if(--bombResetTimer<0 && countbomb<=player2->status->bombNum)
		{
			countbomb = 0; 
			bombResetTimer = bombexplosionTimer;
		}
	}

	if (player2->reload > 0)
	{
		player2->reload--;
	}
	
	if (app.keyboard[SDL_SCANCODE_W])
	{
		player2->dy = -player2->updatespeed;
		if(player2->direction !=UP) 
		{
			player2->texture = player2upTexture;
			player2->direction =UP;
		}
	}
	
	if (app.keyboard[SDL_SCANCODE_S])
	{
		player2->dy = player2->updatespeed;
		if(player2->direction !=DOWN) 
		{
			player2->texture = player2downTexture;
			player2->direction =DOWN;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_A])
	{
		player2->dx = -player2->updatespeed;
		if(player2->direction !=LEFT)
		{
			player2->texture = player2leftTexture;
			player2->direction =LEFT;
		}	
	}
	
	if (app.keyboard[SDL_SCANCODE_D])
	{
		player2->dx = player2->updatespeed;
		if(player2->direction !=RIGHT) 
		{
			player2->direction =RIGHT;
			player2->texture = player2rightTexture;

		}
	}

	if(countbomb<player2->status->bombNum)
	{
		if (app.keyboard[SDL_SCANCODE_LSHIFT] && player2->reload <= 0)
		{
			
			fireBullet(player2);
			countbomb++;
		}
	}

	if(player2->direction != INIT)
	{
		if(!app.keyboard[SDL_SCANCODE_W] && !app.keyboard[SDL_SCANCODE_S] && !app.keyboard[SDL_SCANCODE_A] && !app.keyboard[SDL_SCANCODE_D])
		{	//HOLD condition
			if(player2->direction !=HOLD) 
			{
				player2->direction =HOLD;

			}

		}
	}
	

	player2->x += player2->dx;
	player2->y += player2->dy;
}


/*---------------------------------------------------------------------------------------
								waterline maker 
----------------------------------------------------------------------------------------*/

static void firewaterline(Entity *player, Entity *bullet, int num,int waterLinePower)// define water line
{
	Entity *waterline;
	


	waterline = malloc(sizeof(Entity));
	memset(waterline, 0, sizeof(Entity));

	stage.waterTail->next = waterline;
	stage.waterTail = waterline;

	switch(num)
	{
		case UPLINE:
			waterline->y = (int)(bullet->y)-(BombYArea*waterLinePower);
			waterline->x = (int)(bullet->x);
			waterline->direction =UPLINE;

			break;
		case DOWNLINE:
			waterline->y = (int)(bullet->y)+(BombYArea*waterLinePower);
			waterline->x = (int)(bullet->x);
			waterline->direction =DOWNLINE;

			break;
		case LEFTLINE:
			waterline->x = (int)(bullet->x)-(BombYArea*waterLinePower);
			waterline->y = (int)(bullet->y);
			waterline->direction =LEFTLINE;

			break;
		case RIGHTLINE:
			waterline->x =  (int)(bullet->x)+(BombYArea*waterLinePower);
			waterline->y = (int)(bullet->y);
			waterline->direction =RIGHTLINE;
			break;

	}
	
	waterline->dx = 1;
	waterline->dy = 1;
	waterline->health = FPS;
	
	waterline->texture = waterLine[num];
	SDL_QueryTexture(waterline->texture, NULL, NULL, &waterline->w, &waterline->h);
	waterline->w =MAP_WIDTH/15;
	waterline->h =MAP_HEIGHT/15;
	//waterline->y += (player->h / 2) - (waterline->h / 2);
	player->reload = 24;
	

}

static void firewaterlinecenter(Entity *player, Entity *bullet)// define water line
{
	Entity *waterline;
	
	waterline = malloc(sizeof(Entity));
	memset(waterline, 0, sizeof(Entity));

	stage.waterTail->next = waterline;
	stage.waterTail = waterline;
	
	waterline->x = (int)(bullet->x);
	waterline->y = (int)(bullet->y);
	
	waterline->dx = 1;
	waterline->dy = 1;
	waterline->health = FPS;
	
	waterline->texture = waterLine[CENTERLINE];
	SDL_QueryTexture(waterline->texture, NULL, NULL, &waterline->w, &waterline->h);
	waterline->w =MAP_WIDTH/15;
	waterline->h =MAP_HEIGHT/15;
	//waterline->y += (player->h / 2) - (waterline->h / 2);
	player->reload = 24;
}


/*---------------------------------------------------------------------------------------
								waterline remover
----------------------------------------------------------------------------------------*/
static void doWaterline(Entity *player) //remove water line
{
	Entity  *w, *prev2  ;
	int direction[4]={0};
	static int dead;
	
	prev2 = &stage.waterHead;
	
	for (w = stage.waterHead.next ; w!=NULL ; w = w->next)
	{
		--w->health;
		if(direction[w->direction]) w->health =0;

		//break block and bomb and player   
			if ( bulletHitBlock(w) || waterHitPlayer(w,player) || waterHitBomb(w)||  w->health<=0 || w->x > MAP_X+MAP_WIDTH || w->y > MAP_Y+MAP_HEIGHT|| w->x < MAP_X || w->y < MAP_Y)
			{
				{//sound
					if(dead ==0 && player->health != 0)
					{
						playSound(SND_PLAYER_FIRE, CH_PLAYER);
					}
					else dead =1;
					
					if(GameReset ==1) dead =0;
				}
				switch (w->direction)
				{
					case UPLINE:
						direction[UPLINE]=1;
						break;
					case DOWNLINE:
						direction[DOWNLINE]=1;
						break;
					case LEFTLINE:
						direction[LEFTLINE]=1;
						break;
					case RIGHTLINE:
						direction[RIGHTLINE]=1;
						break;

				}

				if (w == stage.waterTail)
				{
					stage.waterTail = prev2;
				}

				prev2->next=w->next;
				free(w);
				w=prev2;
				
			}
			prev2 = w;
		}


}


//water line HIt block
static int bulletHitBlock(Entity *water)
{
	Entity *block;

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{

		if(block->health > 0 && water->health >0)
		{	//water size use block size

			if ( blockCollison(water->x, water->y ,block->x, block->y)) //block bomb
			{
				water->health =0;
				block->health = 0;
				//when water break block, item show 

				if(rand()%3>0) doItem(block); //66%drop
	
				return 1;
			}
		}
		
		if(block->item.health >0 && water->health > 0  ) //item burn by bomb
		{
			if ( blockCollison(water->x, water->y ,block->x, block->y))
			{

				water->health = 0;
				block->item.health = 0;

				return 1;
			}
		}
		
	}
	return 0;
}

//chain explosion
static int waterHitBomb(Entity *water)
{
	Entity *bomb;
	
	for (bomb = stage.bulletHead.next ; bomb != NULL ; bomb = bomb->next)
	{
		if(bomb->health >0)
		{	//water size use block size

			if ( blockCollison(water->x, water->y ,bomb->x, bomb->y)) //block bomb
			{
				water->health = 0;
				bomb->health = 0;
				
	
				return 1;
			}
		}
		
	}
	return 0;
}

//water attack 
static int waterHitPlayer(Entity *water, Entity *player)
{
	
	if ( blockCollison(water->x, water->y ,player->x, player->y+(player->h/2))) //block bomb
	{
		playSound(SND_LOSE, CH_PLAYER);
		water->health = 0;
		player->health = 0;
		
		return 1;
	}
		
	
	return 0;
}




/*---------------------------------------------------------------------------------------
								fire bomb
----------------------------------------------------------------------------------------*/

static void fireBullet(Entity *player)
{
	Entity *bullet;


	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;
	//checking detail need
	bullet->x = MAP_X+(int)(player->x)/BombXArea*BombXArea +5;//centering
	bullet->y = MAP_Y+ (int)(player->y)/BombYArea*BombYArea+2;
	bullet->w =MAP_WIDTH/15;
	bullet->h =MAP_HEIGHT/15;

	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->dy = PLAYER_BULLET_SPEED;
	bullet->health = bombexplosionTimer;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
	
	//bullet->y += (player->h / 2) - (bullet->h / 2);
	
	player->reload = 24;
	

}


/*---------------------------------------------------------------------------------------
							remove bomb and make waterline 
----------------------------------------------------------------------------------------*/
static void doBullets(Entity *player)
{
	
	Entity *b, *prev;
	int updownleftright,waterlinePower;

	prev = &stage.bulletHead;
	
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{

		if(--b->health<=0)
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			firewaterlinecenter(player,b);
			
			for( updownleftright=0;updownleftright<4;updownleftright++)
			{
				for(waterlinePower=1 ;waterlinePower<=player->status->bombPower; waterlinePower++)
				{	
				
					firewaterline(player,b,updownleftright,waterlinePower); //water line each direction 
					
				}
			}
			prev->next = b->next;
			free(b);
			b = prev;
		}
		updownleftright =0;
		waterlinePower =1;
		prev = b;
	}
}

/*---------------------------------------------------------------------------------------
								make item spawn 
----------------------------------------------------------------------------------------*/
	
static void doItem(Entity *block)
{
	SDL_Rect *rect;
	char temp,randomNum;
	//srand((unsigned int)time(NULL));
	rect = malloc(sizeof(SDL_Rect));
	memset(rect, 0 , sizeof(SDL_Rect));

	randomNum = rand()%10;
	//probability item
	if(randomNum<3) 	temp = ITEMBALLON;
	if(randomNum>3 && randomNum<6) 	temp = ITEMSKATE;
	if(randomNum>6 && randomNum<9) 	temp = ITEMPOTION;
	if(randomNum==9) 	temp = ITEMPOWERMAX;


	block->item.x =block->x;
	block->item.y =block->y;
	block->item.itemType = temp;
	block->item.texture = itemType[temp];
	block->item.w =MAP_WIDTH/15;
	block->item.h =MAP_HEIGHT/15;
	block->item.health = FPS;

	rect->w =MAP_WIDTH/15;
	rect->h =MAP_HEIGHT/15;

	SDL_QueryTexture(block->item.texture, NULL, NULL, &block->item.w, &block->item.h);
	//blitRect(block->item.texture , rect , block->item.x ,block->item.y);

}


/*---------------------------------------------------------------------------------------
									item remove
----------------------------------------------------------------------------------------*/

static void doGetItem(Entity *player)//playser get item
{
	Entity *block;
	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(block->health <=0) 
		{
			//player touch item
			if (collision(block->x, block->y, block->w, block->h, player->x, player->y, player->w, player->h))
			{
				
				//block->item.health =0;
				//item and playerstatus connection
				statusControl(block, player);
		
			}
		}
	}
}


/*---------------------------------------------------------------------------------------
									clip player 
----------------------------------------------------------------------------------------*/

static void clipPlayerFromBox() // must be debugging
{
	Entity *block;
	player->updatespeed = PLAYER_SPEED + (0.5)*player->status->speed;

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(collision(block->x, block->y, block->w, block->h, player->x, player->y+(player->h/3), player->w, player->h/3))
		{
			player->dx = player->dy = 0;
			
			if (app.keyboard[SDL_SCANCODE_UP])
			{
				player->dy = player->updatespeed;

			}
			
			if (app.keyboard[SDL_SCANCODE_DOWN])
			{
				player->dy = -player->updatespeed;

			}
			if (app.keyboard[SDL_SCANCODE_LEFT])
			{
				player->dx = player->updatespeed;
			}
			
			if (app.keyboard[SDL_SCANCODE_RIGHT])
			{
				player->dx = -player->updatespeed;
				
			}
			
			player->x += player->dx;
			player->y += player->dy;
		}
	}
	
}


static void clipPlayer2FromBox() // must be debugging
{
	Entity *block;
	player2->updatespeed = PLAYER_SPEED + (0.5)*player2->status->speed;

	for (block = stage.blockHead.next ; block != NULL ; block = block->next)
	{
		if(collision(block->x, block->y, block->w, block->h, player2->x, player2->y+(player2->h/3), player2->w, player->h/3))
		{
			player2->dx = player2->dy = 0;
			
			if (app.keyboard[SDL_SCANCODE_W])
			{
				player2->dy = player2->updatespeed;

			}
			
			if (app.keyboard[SDL_SCANCODE_S])
			{
				player2->dy = -player2->updatespeed;

			}
			if (app.keyboard[SDL_SCANCODE_A])
			{
				player2->dx = player2->updatespeed;
			}
			
			if (app.keyboard[SDL_SCANCODE_D])
			{
				player2->dx = -player2->updatespeed;
				
			}
			
			player2->x += player2->dx;
			player2->y += player2->dy;
		}
	}
	
}

static void clipPlayer(Entity *player)
{
	if (player != NULL)
	{
		if (player->x < MAP_X-(player->w/4)) //error control value
		{
			player->x = MAP_X-(player->w/4);
		}
		
		if (player->y < MAP_Y-(player->h/3))
		{
			player->y = MAP_Y-(player->h/3);
		}
		
		if (player->x > MAP_X+MAP_WIDTH-(player->w))
		{
			player->x = MAP_X +MAP_WIDTH-(player->w);
		}
		
		if (player->y > MAP_Y+MAP_HEIGHT-(player->h)*2/3)
		{
			player->y = MAP_Y+MAP_HEIGHT-(player->h)*2/3;
		}
	}
}

/*---------------------------------------------------------------------------------------
*****************************************************************************************


											Draw

*****************************************************************************************
----------------------------------------------------------------------------------------*/

static void draw(void)
{
	
	drawBackground();

	drawmap_background();

	drawWaterline();
	
	drawBlock();

	drawItem();

	drawBullets();	
	
	drawPlayer();
	
	drawPlayer2();

	drawHud();

	diePlayer();
	
	diePlayer2();

	drawDraw();
	
	drawResultplayer1(player);

	drawResultplayer2(player2);
}


/*---------------------------------------------------------------------------------------
								block, item , draw
----------------------------------------------------------------------------------------*/

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
	SDL_Rect *rect;

	rect = malloc(sizeof(SDL_Rect));
	memset(rect, 0 , sizeof(SDL_Rect));
	
	rect->w =MAP_WIDTH/15;

	//step = block->item.health;
	for(block = stage.blockHead.next ; block != NULL ; block = block->next)
	{	if(block->item.health != 0)
		{
			rect->h =block->item.h;

			//blit(block->item.texture , block->x , block->y);
			blitRect(block->item.texture,rect, block->x, block->y-(block->h/2));
			//moveani(block->item.texture , block->x , block->y,step, 2);
		}
	}
	
}


/*---------------------------------------------------------------------------------------
								bomb , waterline draw
----------------------------------------------------------------------------------------*/

static void drawBullets(void)
{
	Entity *b;
	
	for (b = stage.bulletHead.next ; b != NULL ; b = b->next)
	{
		blit(b->texture, b->x, b->y);

	}
}

static void drawWaterline(void) //show water line
{
	Entity *w;
	int step=0;
	
	for (w = stage.waterHead.next ; w != NULL ; w = w->next)
	{

		//use health each bomb timer 
		step = 8-(w->health)/7;
		assert(step>=0);

		if(w->health!=0)
		{
			moveani(w->texture, w->x, w->y,step,9);
			
		// speed up bug
			
		}
		
	}

}



/*---------------------------------------------------------------------------------------
								draw player 1,2
----------------------------------------------------------------------------------------*/

static void drawPlayer(void)
{	

	static int step=0;
	
	if(player->health>0)
	{
		if(player->direction ==INIT)
		{
			player->texture =playerstaticTexture;
			blit(player->texture, player->x+5, player->y+15); // error contorl
		}
		else
		{
			moveani(player->texture ,player->x , player->y ,step, characterPNGsize);

			if(player->direction != HOLD){

				if(--enemySpawnTimer <= 0)
				{
					step = step<6 ? step+1 : 0;

					enemySpawnTimer = 5;

				}
			}
		}
	}
	//restart init
	if(GameReset ==1) step =0;

}


static void drawPlayer2(void)
{	

	static int step=0;

	if(player2->health>0)
	{
		if(player2->direction ==INIT)
		{
			player2->texture =player2staticTexture;
			blit(player2->texture, player2->x, player2->y);
		}
		else
		{
			moveani(player2->texture ,player2->x , player2->y ,step, characterPNGsize);

			if(player2->direction != HOLD){

				if(--enemySpawnTimer2 <= 0)
				{
					step = step<6 ? step+1 : 0;

					enemySpawnTimer2 = 5;

				}
			}
		}
	}
	//restart init
	if(GameReset ==1) step =0;
}


/*---------------------------------------------------------------------------------------
								draw background
----------------------------------------------------------------------------------------*/

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


/*---------------------------------------------------------------------------------------
									draw Timer
----------------------------------------------------------------------------------------*/

static void drawHud(void)
{
	static int counter = 0;
	static int min, sec;
	min = stage.time/60;
	sec = stage.time %60;
	drawText(922, 95, 255, 255, 255, TEXT_LEFT, "%d :", min );
	drawText(980, 95, 255, 255, 255, TEXT_LEFT, "%d", sec);

	if(counter >FPS)
	{
		stage.time--;
		counter =0 ;
	} 
	counter ++;
}




/*---------------------------------------------------------------------------------------
									player die motion
----------------------------------------------------------------------------------------*/
static void diePlayer(void)
{	
	Entity *d, *prev;
	static int step=0;

		if(player->health==0)
		{		

			if(player->direction !=INIT)
			{
				player->texture=playerdieTexture;
				moveani(player->texture ,player->x , player->y ,step, 11);

					if(--enemySpawnTimer <= 0)
					{
						step++;
						enemySpawnTimer = 9;
					}
			}
		}
		
	
}

static void diePlayer2(void)
{	
	Entity *d, *prev;
	static int step=0;

		if(player2->health==0)
		{

			if(player2->direction !=INIT)
			{
				player2->texture=player2dieTexture;
				moveani(player2->texture ,player2->x , player2->y ,step, 11);

					if(--enemySpawnTimer <= 0 && step <10)
					{
						step++;

						enemySpawnTimer = 9;
						


					}
			}
		}		
	
}





/*---------------------------------------------------------------------------------------
								draw Match Result
----------------------------------------------------------------------------------------*/


static void drawDraw(void)
{
	
	if(stage.time<=0)
	{
		
		if(--timeout<=0)
		{
			
			
			GameReset =1;

		}
	}

}

static void drawResultplayer1(Entity *player)
{
	Entity *result, *p;
	SDL_Rect *rect1,*rect2;

	result=malloc(sizeof(Entity));
	memset(result, 0, sizeof(Entity));
	p=malloc(sizeof(Entity));
	memset(p, 0, sizeof(Entity));
	rect1=malloc(sizeof(SDL_Rect));
	memset(rect1, 0 , sizeof(SDL_Rect));
	rect2=malloc(sizeof(SDL_Rect));
	memset(rect2, 0 , sizeof(SDL_Rect));

	result->texture=loseTexture;
	result->x=MAP_WIDTH/2-150;
	result->y=MAP_HEIGHT/2-20;
	result->health=1;

	p->texture=p1Texture;
	p->x=MAP_WIDTH/2;
	p->y=MAP_HEIGHT/2-80;
	p->health=1;

	rect1->w=400;
	rect1->h=MAP_HEIGHT/10;

	rect2->w=70;
	rect2->h=MAP_HEIGHT/15;


	if(player->health==0)
	{
		static int timer = FPS*5;
		//playSound(SND_LOSE, CH_PLAYER);

		SDL_QueryTexture(result->texture, NULL,NULL, &result->w,&result->h);
		SDL_QueryTexture(p->texture, NULL,NULL, &p->w,&p->h);
		blitRect(result->texture, rect1, result->x,result->y);
		blitRect(p->texture, rect2, p->x,p->y);

		timer--;
		if(timer<0) 
		{
			timer = FPS*5;
			GameReset =1;
		}
	
	}
}


static void drawResultplayer2(Entity *player)
{
	Entity *result, *p;
	SDL_Rect *rect1,*rect2;

	result=malloc(sizeof(Entity));
	memset(result, 0, sizeof(Entity));
	p=malloc(sizeof(Entity));
	memset(p, 0, sizeof(Entity));
	rect1=malloc(sizeof(SDL_Rect));
	memset(rect1, 0 , sizeof(SDL_Rect));
	rect2=malloc(sizeof(SDL_Rect));
	memset(rect2, 0 , sizeof(SDL_Rect));

	result->texture=loseTexture;
	result->x=MAP_WIDTH/2-150;
	result->y=MAP_HEIGHT/2-20;
	result->health=1;

	p->texture=p2Texture;
	p->x=MAP_WIDTH/2;
	p->y=MAP_HEIGHT/2-80;
	p->health=1;

	rect1->w=400;
	rect1->h=MAP_HEIGHT/10;

	rect2->w=70;
	rect2->h=MAP_HEIGHT/15;


	if(player->health==0)
	{
		static int timer = FPS*5;
		//if(timer == FPS*5) 		

		SDL_QueryTexture(result->texture, NULL,NULL, &result->w,&result->h);
		SDL_QueryTexture(p->texture, NULL,NULL, &p->w,&p->h);
		blitRect(result->texture, rect1, result->x,result->y);
		blitRect(p->texture, rect2, p->x,p->y);

		timer--;
		if(timer<0) 
		{
			timer = FPS*5;
			GameReset =1;
		}
	}
}

static void restart(void)
{
	int enemySpawnTimer2 =0;
	int enemySpawnTimer1 =0;
	stage.time = 120;
	initTitle();

}
