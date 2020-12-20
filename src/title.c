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

<<<<<<< HEAD
using shooter title.c and modified
=======
>>>>>>> master
*/

#include "title.h"

static void logic(void);
static void draw(void);
//static void drawLogo(void);
static void drawStartScene(void);
<<<<<<< HEAD
static int checkingbox(SDL_Texture *texture ,SDL_MouseButtonEvent *event);
static void mapChoiceTitle(void);
static void initLobby(void);
static void drawLobbyScene(void);
static void doStartLogo(void);
static void mapChoiceButton(void);
static void mapCheck(void);
=======
static void drawStartLogo(void);
static int checkingbox(SDL_Texture *texture ,SDL_MouseButtonEvent *event);

>>>>>>> master


//static SDL_Texture *sdl2Texture;
static SDL_Texture *startSceneBg;
static SDL_Texture *startLogo;
static SDL_Texture *startLogoClick;
<<<<<<< HEAD
static SDL_Texture *lobbyScene;
static SDL_Texture *map1Demo;
static SDL_Texture *map2Demo;


static int reveal = 0;
static int timeout;
static int startSceneBgX;
static int lobbySceneX;
static int map1DemoX =0;
static int map2DemoX = 0;
static int click; 
static int checkingLobby =0;
static int mapMenu=0;


/*---------------------------------------------------------------------------------------
											init Title
----------------------------------------------------------------------------------------*/

=======
static int reveal = 0;
static int timeout;
static int startSceneBgX;
static int click; 


>>>>>>> master
void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
<<<<<<< HEAD

	loadMusic("music/mainstart.ogg");
	
	playMusic(1);
=======
>>>>>>> master
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	
	startLogo = loadTexture("gfx/gamestart.png");
	startLogoClick = loadTexture("gfx/clickgamestart.png");
	startSceneBg = loadTexture("gfx/start_scene_bg.png");
<<<<<<< HEAD
	lobbyScene = loadTexture("gfx/lobby_scene_bg.png");
	map1Demo = loadTexture("gfx/map1Demo.png");
	map2Demo = loadTexture("gfx/map2Demo.png");

=======
	
>>>>>>> master
	timeout = FPS * 5;
}


static void logic(void)
{
<<<<<<< HEAD
	doStartLogo();
}
	

/*---------------------------------------------------------------------------------------
											goto lobby
----------------------------------------------------------------------------------------*/
static void doStartLogo(void)
{

	if(app.mouse[mouseUPDOWN] && click ==0){
		//will be give a click effects
		click =1;
		loadMusic("sound/WaitingRoom.ogg");

		playMusic(1);
	}
	if( click){
		initLobby();
		
		
	}
}

/*---------------------------------------------------------------------------------------
											init lobby 
----------------------------------------------------------------------------------------*/

static void initLobby(void)
{
	checkingLobby =1;
	//lobby setting

	

	//map choice
	if(mouseButton(LOBBY_MAP_BUTTON_X,LOBBY_MAP_BUTTON_Y,LOBBY_MAP_BUTTON_W,LOBBY_MAP_BUTTON_H))
	{
		mapMenu =1;
	}
	//start button
	if(mouseButton(LOBBY_START_BUTTON_X,LOBBY_START_BUTTON_Y,LOBBY_START_BUTTON_W,LOBBY_START_BUTTON_H))
	{
		click =0;
		initStage();
	}

}



/*---------------------------------------------------------------------------------------
											Draw
----------------------------------------------------------------------------------------*/


=======
	/*
	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
	}
	
	if (--timeout <= 0)
	{
		initHighscores();
	}
	*/
	if(app.mouse){
		//will be give a click effects
		click =1;
		
	}
	if(app.mouse ==0 && click ==1){
		
		initStage();
	}
}


>>>>>>> master
static void draw(void)
{
	drawStartScene();

<<<<<<< HEAD
	if(checkingLobby) drawLobbyScene();
	
	if(mapMenu)
	{

	mapChoiceButton();

	mapCheck();

	}

=======
	drawStartLogo();
	/*
	drawBackground();
	
	drawStarfield();
	
	drawLogo();
	
	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
	}
*/
>>>>>>> master
}

static void drawStartScene(void)
{
	SDL_Rect dest;
	int x;
	
	for (x = startSceneBgX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;
		
		SDL_RenderCopy(app.renderer, startSceneBg, NULL, &dest);
	}
}


<<<<<<< HEAD

static void drawLobbyScene(void)
{
	SDL_Rect dest;
	int x;
	
	for (x = lobbySceneX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;
		
		SDL_RenderCopy(app.renderer, lobbyScene, NULL, &dest);
	}
}

/*---------------------------------------------------------------------------------------
											MAP choice 
----------------------------------------------------------------------------------------*/

//MAPNUMBER is extern VALUE
static void mapCheck(void)
{
	if(app.mouse[mouseUPDOWN])
	{
	if(app.mouse[mouse_X]<SCREEN_WIDTH/2)
	{
		MAPNUMBER=1; //global
		mapMenu =0;
	}
	else
	{
		MAPNUMBER=2;	//global
		mapMenu=0;
	}
	}
}

static void mapChoiceButton(void)
{
	SDL_Rect dest;
	int x;
	checkingLobby =0;
	for (x = map1DemoX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = SCREEN_HEIGHT/4;
		dest.w = SCREEN_WIDTH/2;
		dest.h = SCREEN_HEIGHT/2;
		
		SDL_RenderCopy(app.renderer, map1Demo, NULL, &dest);
	}
	
	for (x = map2DemoX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x+SCREEN_WIDTH/2;
		dest.y = SCREEN_HEIGHT/4;
		dest.w = SCREEN_WIDTH/2;
		dest.h = SCREEN_HEIGHT/2;
		
		SDL_RenderCopy(app.renderer, map2Demo, NULL, &dest);
	}

}
=======
static void drawStartLogo(void)
{
	SDL_Rect r;
	
	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(startLogo, NULL, NULL, (&r.w), &r.h);
	
	r.w *= SCALE;
	r.h *= SCALE; 
	
	blitRect(startLogo, &r, START_LOGO_X ,START_LOGO_Y);
	
}

/*
keeping (making a box click)
static int checkingbox(SDL_Texture *texture ,SDL_MouseButtonEvent *event)
{
	SDL_Rect r;


	SDL_QueryTexture(texture, NULL, NULL, (&r.w), &r.h);

	if(event->x <(START_LOGO_X+r.w) && event->x > (START_LOGO_X) && event->y < START_LOGO_Y && event->y > (START_LOGO_Y + r.h){

		return 1;
	}
	else {
		return 0;
	}
}
*/
>>>>>>> master
