/*
 * screen.c
 * 
 * Copyright 2025 x64x2 <x64x2@mango>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "screen.h"

int init_screen()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL");
		return 1;
	}

	SDL_SetCaption("Jip8", "Jip8");

	if (!(screen = SDL_SetVideoMode(640, 320, 0, 0)))//32, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return 1;
	}

	white = SDL_MapRGB(screen->format, 255, 255, 255);
	black = SDL_MapRGB(screen->format, 0, 0, 0);
	ytimesw = screen->pitch/BPP;
	return 0;
}

void draw_screen()
{
	if(SDL_LOCK(screen))
	{
		if(SDL_LockSurface(screen) < 0)
		{
			return;
		}
	}

	int x, y;
	unsigned char pixel_width = screen->w/SCREEN_WIDTH;
	unsigned char pixel_height = screen->h/SCREEN_HEIGHT;
	for (x=0; x<SCREEN_WIDTH; x++)
	{
		for (y=0; y<SCREEN_HEIGHT; y++)
		{
			if (video_memory[x][y])
			{
				set_pixel(screen, x*pixel_width, y*pixel_height, &white);
			}
			else
			{
				set_pixel(screen, x*pixel_width, y*pixel_height, &black);
			}
		}
	}

	if(SDL_MUSTLOCK(screen))
	{
		SDL_UnlockSurface(screen);
	}

	SDL_Flip(screen);
}

void set_pixel(SDL_Surface *screen, int x, int y, Uint32 *color)
{
    Uint32 *pixmem32;

    int xo = 0;
    int yo = 0;
    for (xo=0;xo<10; xo++)
    {
    	for (yo=0;yo<10; yo++)
    	{
    		pixmem32 = (Uint32*) screen->pixels + (y+yo)*ytimesw + x + xo;
    		*pixmem32 = *color;
    	}
    }
}
