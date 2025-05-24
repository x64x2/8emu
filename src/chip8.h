/*
 * chip8.h
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


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "screen.h"
#include "io.h"

#ifndef CHIP8_H
#define CHIP8_H

#define MEMORY_SIZE 0xFFF
#define STACK_SIZE 16
#define FPS 100
#define FPS_TIMEOUT (1000*1000/FPS)

unsigned char memory[MEMORY_SIZE];

struct chip8
{
	unsigned char registers[0x10]; /// registers V0 to VF
	unsigned short address; /// usually used for memory addresses
	unsigned char delay_timer_register;
	unsigned char sound_timer_register;
	unsigned short program_counter;
	signed int stack_pointer;	/// points to the current index in the stack
	unsigned short stack[STACK_SIZE];		/// stack for subroutine calls, allows up to 16 levels of subroutines
	bool keys[0x10];
	bool running;
	bool chip8;
} chip8;

void initChip8);
void load_character_sprites();
void run_chip8();
unsigned short fetch_opcode();
void skip_instruction();

/// actual opcode processing methods
void process0NNN(unsigned short opcode);
void process1NNN(unsigned short opcode);
void process2NNN(unsigned short opcode);
void process3XNN(unsigned short opcode);
void process4XNN(unsigned short opcode);
void process5XY0(unsigned short opcode);
void process6XNN(unsigned short opcode);
void process7XNN(unsigned short opcode);
void process8XYN(unsigned short opcode);
void process9XY0(unsigned short opcode);
void processANNN(unsigned short opcode);
void processBNNN(unsigned short opcode);
void processCXNN(unsigned short opcode);
void processDXYN(unsigned short opcode);
void processEXNN(unsigned short opcode);
void processFXNN(unsigned short opcode);



