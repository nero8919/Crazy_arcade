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

#include "util.h"

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}
<<<<<<< HEAD

//in block check collision with same x,y
int blockCollison(int x1, int y1, int x2, int y2)
{	
	return abs(x1-x2)<MAP_WIDTH/30 && abs(y1-y2)<MAP_HEIGHT/30;
}

int mouseButton(int x, int y ,int w, int h)
{
	//checking buttonbox click
	if(app.mouse[mouse_X]> x && app.mouse[mouse_X]< x+w &&app.mouse[mouse_Y]> y && app.mouse[mouse_Y]< y+h)
	{
		return 1; 
	}
	else return 0;

}
=======
>>>>>>> master
/*
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = MAX(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}
<<<<<<< HEAD
*/


=======
*/
>>>>>>> master
