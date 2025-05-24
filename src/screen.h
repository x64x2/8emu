/*
 * screen.h
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
#include <SDL/SDL.h>
#include <stdbool.h>
#include <limits.h>

#ifndef SCREEN_H_
#define SCREEN_H_

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define BPP 4

bool video_memory[SCREEN_WIDTH][SCREEN_HEIGHT];
SDL_Surface *screen;
int32_t white;
int32_t black;
int ytimesw;

int init_screen();
void draw_screen();
void set_pixel(SDL_Surface *screen, int x, int y, int32_t* color);

