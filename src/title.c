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

using shooter title.c and modified
*/

#include "title.h"

static void logic(void);
static void draw(void);
//static void drawLogo(void);
static void drawStartScene(void);
static int checkingbox(SDL_Texture *texture ,SDL_MouseButtonEvent *event);
static void mapChoiceTitle(void);
static void initLobby(void);
static void drawLobbyScene(void);
static void doStartLogo(void);
static void mapChoiceButton(void);
static void mapCheck(void);


//static SDL_Texture *sdl2Texture;
static SDL_Texture *startSceneBg;
static SDL_Texture *startLogo;
static SDL_Texture *startLogoClick;
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

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	loadMusic("music/mainstart.ogg");
	
	playMusic(1);
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	
	startLogo = loadTexture("gfx/gamestart.png");
	startLogoClick = loadTexture("gfx/clickgamestart.png");
	startSceneBg = loadTexture("gfx/start_scene_bg.png");
	lobbyScene = loadTexture("gfx/lobby_scene_bg.png");
	map1Demo = loadTexture("gfx/map1Demo.png");
	map2Demo = loadTexture("gfx/map2Demo.png");

	timeout = FPS * 5;
}


static void logic(void)
{
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


static void draw(void)
{
	drawStartScene();

	if(checkingLobby) drawLobbyScene();
	
	if(mapMenu)
	{

	mapChoiceButton();

	mapCheck();

	}

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