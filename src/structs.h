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

typedef struct Entity Entity;


typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;

	SDL_Surface* window_surface;	//ANIMATION
  	SDL_Surface* player_surface;

	int keyboard[MAX_KEYBOARD_KEYS];
	int mouse[MOUSE_INPUT];	//  	[0] up:0 down:1 , [1] mouse.x [2]mouse.y  
	
} App;

typedef struct{
	float x;
	float y;
	int w;
	int h;
	int health;
	char itemType;
	SDL_Texture *texture;
} Item;

typedef struct {

	int speed; 
	int bombNum;
	int bombPower;


} CharictarStatus;

struct Entity {
	
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	int direction;
	float updatespeed;
	CharictarStatus *status;
	Item item;
	SDL_Texture *texture;
	Entity *next;
};



typedef struct {
	Entity fighterHead, *fighterTail;
	Entity fighter2Head, *fighter2Tail;
	Entity bulletHead, *bulletTail;
	Entity pointsHead, *pointsTail;
	Entity blockHead , *blockTail;
	Entity waterHead, *waterTail;
	int time;
	int stageNumber;
} Stage;


