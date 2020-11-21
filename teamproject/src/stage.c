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
//static void doItem(void);
static void drawItem(SDL_Texture *texture);
static void initItem(void);


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

static int itemX;
static int backgroundX;
static int map_backgroundX;


void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	
	resetStage();
	
	initPlayer();

	initItem();

	bulletTexture = loadTexture("gfx/playerBullet.png");
	map_background = loadTexture("gfx/mapbg1.png");
	background = loadTexture("gfx/play_bg.png");
	bulletTexture = loadTexture("gfx/playerBullet.png");
	

}

static void initItem(void)
{


	itemSkate = loadTexture("item/skate.png");
	itemPotion = loadTexture("item/Potion.png");
	itemBallon = loadTexture("item/Ballon.png");
	itemPowerMax = loadTexture("item/powerMax.png");

	

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
	
	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	
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
}

static void doItem(void)
{



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
		
		if ( b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
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

static void draw(void)
{
	
	drawBackground();

	drawmap_background();

	drawPlayer();
	
	drawBullets();

	drawItem(itemPowerMax);
}

static void drawItem(SDL_Texture *texture)
{
	SDL_Rect itemX;

	itemX.x =500;
	itemX.y =500;

	SDL_RenderCopy(app.renderer, texture, NULL, &itemX);


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
