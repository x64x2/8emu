/*
 * main.c
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


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sdl.h"
#include "chip8.h"

int main(int argc, char *argv[])
{
	initChip8();
	/* parse arguments*/
	while (argc > 1)
	{
		/* initialize chip8*/
		argc--;
		if (argv[argc][0] == '-')
		{
			
			if (argv[argc][1] == 'c')
			{
				initChip8();
			}
		}
	}

	int sdl_init = initialize_screen();
	if (sdl_init > 0)
	{
		return sdl_init;
	}

	initialize_cpu();
	initialize_keyboard();

   /*mem set ops*/
	memory[0x300] = 0x90; // H
	memory[0x301] = 0x90; // H
	memory[0x302] = 0xF0; // H
	memory[0x303] = 0x90; // H
	memory[0x304] = 0x90; // H

	memory[0x305] = 0x70; // I
	memory[0x306] = 0x20; // I
	memory[0x307] = 0x20; // I
	memory[0x308] = 0x20; // I
	memory[0x309] = 0x70; // I

	memory[0x305] = 0x20; // i
	memory[0x306] = 0x00; // i
	memory[0x307] = 0x60; // i
	memory[0x308] = 0x20; // i
	memory[0x309] = 0x70; // i

	memory[0x200] = 0x00; // CLS
	memory[0x201] = 0xE0;

	memory[0x202] = 0x60; // LD V0 0x10
	memory[0x203] = 0x01;
	memory[0x204] = 0x61; // LD V1 0x10
	memory[0x205] = 0x01;
	memory[0x206] = 0xA3; // LD I 0x300
	memory[0x207] = 0x00;
	memory[0x208] = 0xD0; // DRAW V0 V1 5
	memory[0x209] = 0x15;

	memory[0x20A] = 0x60; // LD V0 0x14
	memory[0x20B] = 0x05;
	memory[0x20C] = 0x61; // LD V1 0x10
	memory[0x20D] = 0x01;
	memory[0x20E] = 0xA3; // LD I 0x305
	memory[0x20F] = 0x05;
	memory[0x210] = 0xD0; // DRAW V0 V1 5
	memory[0x211] = 0x15;

	memory[0x212] = 0x12; // JP
	memory[0x213] = 0x12;
	execute_cpu();

	return EXIT_SUCCESS;
}
