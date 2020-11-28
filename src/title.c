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

#include "title.h"

static void logic(void);
static void draw(void);
//static void drawLogo(void);
static void drawStartScene(void);
static void drawStartLogo(void);
static int checkingbox(SDL_Texture *texture ,SDL_MouseButtonEvent *event);
static void mapChoiceTitle(void);


//static SDL_Texture *sdl2Texture;
static SDL_Texture *startSceneBg;
static SDL_Texture *startLogo;
static SDL_Texture *startLogoClick;
static SDL_Texture *lobbyScene;

static int reveal = 0;
static int timeout;
static int startSceneBgX;
static int lobbySceneX;
static int click; 


void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	
	startLogo = loadTexture("gfx/gamestart.png");
	startLogoClick = loadTexture("gfx/clickgamestart.png");
	startSceneBg = loadTexture("gfx/start_scene_bg.png");
	lobbyScene = loadTexture("gfx/lobby_scene_bg.png");

	timeout = FPS * 5;
}


static void logic(void)
{
	
	if(app.mouse){
		//will be give a click effects
		click =1;
		
	}
	if(app.mouse ==0 && click ==1){
		
		initStage();
	}
}

static void mapChoiceTitle(void)
{


}

static void draw(void)
{
	drawStartScene();

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