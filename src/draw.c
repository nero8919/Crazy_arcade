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

#include "draw.h"

<<<<<<< HEAD



=======
>>>>>>> master
void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}


void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;
	
	SDL_RenderCopy(app.renderer, texture, src, &dest);
<<<<<<< HEAD
}

void moveani(SDL_Texture *texture, int x, int y ,int step,int pngSize)
{
	
	SDL_Rect dst,src;
	
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.w=src.w/pngSize;
	dst.h=src.h;
	src.x=(src.w/pngSize)*step;
	src.y = 0;
	src.w=src.w/pngSize;
	
	SDL_RenderCopy(app.renderer, texture, &src, &dst);

	
}


void waterMoveAni(SDL_Texture *texture, int x, int y ,int step,int pngSize)
{
	
	SDL_Rect dst,src;
	
	dst.x = x;
	dst.y = y;

	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);

	src.w = MAP_WIDTH/15*pngSize;
	src.h = MAP_HEIGHT/15;
	dst.w=src.w/pngSize;
	dst.h=src.h;
	src.x=(src.w/pngSize)*step;
	src.y = 0;
	src.w=src.w/pngSize;
	
	SDL_RenderCopy(app.renderer, texture, &src, &dst);

	
=======
>>>>>>> master
}