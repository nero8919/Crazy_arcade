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

#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

extern SDL_Texture *loadTexture(char *filename);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern int bulletHitFighter(Entity *b);
<<<<<<< HEAD
extern void mapLoad(int numberArray[][15], int mapNumber);
extern void statusControl(Entity *block ,Entity *player );
extern void moveani(SDL_Texture *texture, int x, int y ,int step, int pngSize);
extern void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);
extern void waterMoveAni(SDL_Texture *texture, int x, int y ,int step,int pngSize);
extern int blockCollison(int x1, int y1, int x2, int y2);
extern int mouseButton(int x, int y ,int w, int h);
extern void loadMusic(char *filename);
extern void playMusic(int loop);
extern void playSound(int id, int channel);
extern void initTitle(void);

=======
>>>>>>> master

extern App app;
extern Stage stage;

