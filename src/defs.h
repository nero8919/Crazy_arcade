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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define SIDE_PLAYER 0
<<<<<<< HEAD
#define MAX_LINE_LENGTH 1024

#define SCALE 1.0


#define SCREEN_WIDTH   1040
#define SCREEN_HEIGHT  780 

#define MAP_WIDTH   780
#define MAP_HEIGHT  680
#define MAP_X   26
#define MAP_Y   53



#define START_LOGO_X 380
#define START_LOGO_Y 30

#define PLAYER_SPEED          2
=======


#define SCALE 1.0


#define SCREEN_WIDTH   1040*SCALE
#define SCREEN_HEIGHT  780 *SCALE

#define MAP_WIDTH   780*SCALE
#define MAP_HEIGHT  680*SCALE
#define MAP_X   26*SCALE
#define MAP_Y   53*SCALE


#define START_LOGO_X 380*SCALE
#define START_LOGO_Y 30*SCALE

#define PLAYER_SPEED          4
>>>>>>> master
#define PLAYER_BULLET_SPEED   20

#define MAX_KEYBOARD_KEYS 350

#define FPS 60

<<<<<<< HEAD
#define mapTileX 15
#define mapTileY 15

#define characterPNGsize 7

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

#define LOBBY_MAP_BUTTON_X 844
#define LOBBY_MAP_BUTTON_Y 558
#define LOBBY_MAP_BUTTON_W 163
#define LOBBY_MAP_BUTTON_H 65

#define LOBBY_START_BUTTON_X 674
#define LOBBY_START_BUTTON_Y 647
#define LOBBY_START_BUTTON_W 243
#define LOBBY_START_BUTTON_H 68

#define TITLE_START_LOGO_X 446
#define TITLE_START_LOGO_Y 76
#define TITLE_START_LOGO_W 176
#define TITLE_START_LOGO_H 135

#define QUIT_BUTTON_X 843
#define QUIT_BUTTON_Y 730
#define QUIT_BUTTON_W 179
#define QUIT_BUTTON_H 40


#define MOUSE_INPUT 3

#define MAX_SND_CHANNELS 8


enum BoxNumber {
    BOXTYPE1 ,
    BOXTYPE2 ,
    MAPTILENUM 
    
};

enum ItemType{
    ITEMSKATE,
    ITEMBALLON,
    ITEMPOTION,
    ITEMPOWERMAX,
    ITEMNUM

};

enum Sequence{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INIT,
    HOLD=99

};

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

enum
{
    mouseUPDOWN,mouse_X,mouse_Y
};

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_FIRE
};
enum
{
	SND_PLAYER_FIRE,
	SND_LOSE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_MAX
};


enum{
	UPLINE,
	DOWNLINE,
	LEFTLINE,
	RIGHTLINE,
	CENTERLINE
};
=======
>>>>>>> master
