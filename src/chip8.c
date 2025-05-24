/*
 * chip8.c
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


#include "chip8.h"

/**
 * Initializes the cpu structure, memory etc.
 */
void initChip8()
{
	/// clear the memory
	int i = 0;
	for (i=0; i<0xFFF; i++)
	{
		memory[i] = 0;
	}

	load_character_sprites();

	pc = 0x200; /// load roms starting from 0x200

	/ reset registers
	for (i=0; i<STACK_SIZE; i++)
	{
		chip8.registers[i] = 0;
		chip8.stack[i] = 0;
	}
	for (i=0; i<0xF; i++)
	{
		chip8.keys[i] = false;
	}
	chip8.delay_timer = 0;
	chip8.sound_timer = 0;
	chip8.address = 0;
	chip8.stack_pointer = -1;
	chip8.running = true;
}

/**
 * Fetches the next opcode at the program counter. After execution, the program counter is increased by 2.
 */
unsigned short fetch_opcode()
{
	unsigned char high_byte = memory[chip8.pc++];
	unsigned char low_byte = memory[chip8.pc++];
	return (high_byte<<8) | (low_byte);
}

/**
 * Skips the next instruction by incrementing the program counter by 2.
 */
void skip_instruction()
{
	chip8.pc += 2;
}

void run_chip8()
{
	int num_of_instructions = 0;
	char refresh_screen = true;

	while (chip8.pc < MEMORY_SIZE && chip8.running)
	{
		unsigned short opcode = fetch_opcode();
		// depending on the first 4 bits of the opcode, decide how to process it
		switch (opcode & 0xF000)
		{
		case 0x0000:
			process0NNN(opcode);
			break;
		case 0x1000:
			process1NNN(opcode);
			break;
		case 0x2000:
			process2NNN(opcode);
			break;
		case 0x3000:
			process3XNN(opcode);
			break;
		case 0x4000:
			process4XNN(opcode);
			break;
		case 0x5000:
			process5XY0(opcode);
			break;
		case 0x6000:
			process6XNN(opcode);
			break;
		case 0x7000:
			process7XNN(opcode);
			break;
		case 0x8000:
			process8XYN(opcode);
			break;
		case 0x9000:
			process9XY0(opcode);
			break;
		case 0xA000:
			processANNN(opcode);
			break;
		case 0xB000:
			processBNNN(opcode);
			break;
		case 0xC000:
			processCXNN(opcode);
			break;
		case 0xD000:
			processDXYN(opcode);
			refresh_screen = true;
			break;
		case 0xE000:
			processEXNN(opcode);
			break;
		case 0xF000:
			processFXNN(opcode);
			break;
		}

		if (chip8.delay_timer > 0)
		{
			chip8.delay_timer--;
		}
		if (chip8.sound_timer > 0)
		{
			chip8.sound_timer--;
			/// TODO: Play sound
		}
		if (refresh_screen)
		{
			refresh_screen = false;
			draw_screen();
		}

		sleep(FPS_TIMEOUT);
	}
	printf("executed %d nr of instructions\n", num_of_instructions);
}

void process0NNN(unsigned short opcode)
{
	int x = 0;
	int y = 0;
	switch (opcode)
	{
	/// CLS: Clear the screen
	case 0x00E0:
		for (x=0; x<SCREEN_WIDTH; x++)
		{
			for (y=0; y<SCREEN_HEIGHT; y++)
			{
				video_memory[x][y] = false;
			}
		}
		break;
	/// RET - return from a subroutine
	case 0x00EE:
		if (chip8.stack_pointer >= 0 && chip8.stack_pointer < STACK_SIZE)
		{
			chip8.pc = chip8.stack[chip8.stack_pointer];
			chip8.stack_pointer--;
		}
		else
		{
			dump_chip8("Stack fault, stack pointer out of bounds. Probably a RET opcode without CALL.");
			printf("An unexpected error occurred. This rom is probably not going to work as intended. Please refer to error.log for more details.\n");
		}
		break;
	default:
		if (opcode == 0x0000)
		{
			dump_chip8("Opcode 0x0000 detected, end of rom.");
			printf("End of rom detected, Jip8 is now shutting down.\n");
			exit(1);
		}
		else
		{
			printf("Opcode 0x%04x detected. 1802 calls are not supported.\n", opcode);
		}
		break;
	}
}

/**
 * JP addr - Jumps to address NNN specified in the opcode.
 */
void process1NNN(unsigned short opcode)
{
	chip8.pc = (opcode & 0x0FFF);
}

/**
 * CALL addr - Calls the subroutine at NNN.
 */
void process2NNN(unsigned short opcode)
{
	if (chip8.stack_pointer < STACK_SIZE)
	{
		chip8.stack[chip8.stack_pointer+1] = chip8.pc;
		chip8.stack_pointer++;
		chip8.pc = (opcode & 0x0FFF);
	}
	else
	{
		dump_chip8("Stack fault, stack pointer is too large");
		printf("An unexpected error occurred. This rom is probably not going to work as intended. Please refer to error.log for more details.\n");
	}
}

/**
 * Skips the next instruction if Vx == NN
 */
void process3XNN(unsigned short opcode)
{
	if (chip8.registers[((opcode & 0x0F00) >> 8)] == (opcode & 0xFF))
	{
		skip_instruction();
	}
}

/**
 * Skips the next instruction if Vx != NN
 */
void process4XNN(unsigned short opcode)
{
	if (chip8.registers[((opcode & 0x0F00) >> 8)] != (opcode & 0xFF))
	{
		skip_instruction();
	}
}

/**
 * Skips the next instruction if Vx == Vy
 */
void process5XY0(unsigned short opcode)
{
	if (chip8.registers[((opcode & 0x0F00) >> 8)] == chip8.registers[((opcode & 0x00F0) >> 4)])
	{
		skip_instruction();
	}
}

/**
 * Sets the register Vx to NN
 */
void process6XNN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	chip8.registers[v_x] = (opcode & 0x00FF);
}

/**
 * Adds the value NN to the register Vx. The result is stored in Vx
 */
void process7XNN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	chip8.registers[v_x] = (chip8.registers[v_x] + (opcode & 0x00FF));
}

void process8XYN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	unsigned char v_y = ((opcode & 0x00F0) >> 4);
	switch (opcode & 0x000F)
	{
	/// set Vx = Vy
	case 0x0:
		chip8.registers[v_x] = chip8.registers[v_y];
		break;
	/// sets Vx = Vx OR Vy
	case 0x1:
		chip8.registers[v_x] = chip8.registers[v_x] | chip8.registers[v_y];
		break;
	/// sets Vx = Vx AND Vy
	case 0x2:
		chip8.registers[v_x] = chip8.registers[v_x] & chip8.registers[v_y];
		break;
	/// sets Vx = Vx XOR Vy
	case 0x3:
		chip8.registers[v_x] = chip8.registers[v_x] ^ chip8.registers[v_y];
		break;
	/// sets Vx = Vx + Vy, if the result is > 1 byte, then VF is set = 1, otherwise VF = 0.
	case 0x4:
		if ( (chip8.registers[v_x] + chip8.registers[v_y]) > 0xFF)
		{
			chip8.registers[0xF] = 1;
		}
		else
		{
			chip8.registers[0xF] = 0;
		}
		chip8.registers[v_x] = chip8.registers[v_x] + chip8.registers[v_y];
		break;
	/// sets Vx = Vx - Vy. If there is NO borrow, VF is set = 1, if there is a borrow, VF is set = 0
	case 0x5:
		if (chip8.registers[v_x] >= chip8.registers[v_y])
		{
			chip8.registers[0xF] = 1;
		}
		else
		{
			chip8.registers[0xF] = 0;
		}
		chip8.registers[v_x] = chip8.registers[v_x] - chip8.registers[v_y];
		break;
	/// VF is set to the least significant bit of Vx, then Vx is shifted 1 bit to the right.
	case 0x6:
		/// shift Vx on modern interpreters
		if (!chip8.compatibility)
		{
			chip8.registers[0xF] = chip8.registers[v_x] & 0x01;
			chip8.registers[v_x] = (chip8.registers[v_x] >> 1);
		}
		/// if compatibility mode is enabled, shift Vy instead
		else
		{
			/// we don't need to store the least significant bit, as Vy still exists
			chip8.registers[v_x] = (chip8.registers[v_y] >> 1);
		}
		break;
	/// sets Vx = Vy - Vx. If there is NO borrow, VF is set = 1, if there is a borrow, VF is set = 0
	case 0x7:
		if (chip8.registers[v_y] >= chip8.registers[v_x])
		{
			chip8.registers[0xF] = 1;
		}
		else
		{
			chip8.registers[0xF] = 0;
		}
		chip8.registers[v_x] = chip8.registers[v_y] - chip8.registers[v_x];
		break;
	/// VF is set to the most significant bit of Vx, then Vx is shifted 1 bit to the left.
	case 0xE:
		/// usually shift Vx
		if (!chip8.compatibility)
		{
			chip8.registers[0xF] = (chip8.registers[v_x] & 0x80) >> 7;
			chip8.registers[v_x] = (chip8.registers[v_x] << 1);
		}
		/// shift Vy and don't store the most significant bit (it can still be read from Vy)
		else
		{
			chip8.registers[v_x] = (chip8.registers[v_y] << 1);
		}
		break;

	}
}

/**
 * Skips the next instruction if Vx != Vy
 */
void process9XY0(unsigned short opcode)
{
	if (chip8.registers[(opcode & 0x0F00) >> 8] != chip8.registers[(opcode & 0x00F0) >> 4])
	{
		skip_instruction();
	}
}

/**
 * Sets the address register I to NNN.
 */
void processANNN(unsigned short opcode)
{
	chip8.address = opcode & 0x0FFF;
}

/**
 * Jumps to the address NNN + V0
 */
void processBNNN(unsigned short opcode)
{
	chip8.pc = (opcode & 0x0FFF) + chip8.registers[0x0];
}

/**
 * Sets Vx to a random number between 0 and 255 (both inclusive) and ANDs the value with NN
 */
void processCXNN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	unsigned char nn = (opcode & 0x00FF);
	srand(time(NULL));
	chip8.registers[v_x] = ((random()%256)&nn);
}

/**
 * Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a
 * height of N pixels. Each row of 8 pixels is read as bit-coded starting
 * from memory location I; I value doesn't change after the execution of
 * this instruction. VF is set to 1 if any screen pixels
 * are flipped from set to unset when the sprite is drawn, and to 0 if that
 * doesn't happen.
 * If the sprite is positioned so part of it is outside the coordinates of the display,
 * it wraps around to the opposite side of the screen.
 * Sprites are XORed onto the existing screen.
 */
void processDXYN(unsigned short opcode)
{
	unsigned char x_position = chip8.registers[(opcode & 0x0F00) >> 8];
	unsigned char y_position = chip8.registers[(opcode & 0x00F0) >> 4];
	unsigned char height = (opcode & 0x000F);
	unsigned short initial_address = chip8.address;
	bool pixels_unset = false;

	int y_offset = 0;
	for (y_offset=0; y_offset<height; y_offset++)
	{
		unsigned char row = memory[initial_address + y_offset];

		int x_offset = 0;
		for (x_offset=0; x_offset<8; x_offset++)
		{
			/// absolute positions are calculated from the start position (Vx, Vy) plus the drawing offset of the current pixel
			/// we % it with screen height/width to wrap sprites around screen borders
			unsigned char absolute_x = (x_position+x_offset) % SCREEN_WIDTH;
			unsigned char absolute_y = (y_position+y_offset) % SCREEN_HEIGHT;

			/// check whether any pixels are flipped while drawing the sprite
			bool current_value = video_memory[absolute_x][absolute_y];
			bool new_value = (row & (1<<(7-x_offset))); // the current bit of this row (from left to right)

			/// if the pixel is currently set and won't be afterwards
			if (current_value && !(current_value ^ new_value))
			{
				pixels_unset = true;
			}
			video_memory[absolute_x][absolute_y] = (current_value ^ new_value);
		}
	}

	if (pixels_unset)
	{
		chip8.registers[0xF] = 1;
	}
	else
	{
		chip8.registers[0xF] = 0;
	}
}

void processEXNN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	switch (opcode & 0x00FF)
	{
	case 0x9E:
		if (chip8.keys[chip8.registers[v_x]])
		{
			skip_instruction();
		}
		break;
	case 0xA1:
		if (!chip8.keys[chip8.registers[v_x]])
		{
			skip_instruction();
		}
		break;
	}
}

void processFXNN(unsigned short opcode)
{
	unsigned char v_x = ((opcode & 0x0F00) >> 8);
	unsigned char character = 0;
	int i = 0;
	bool key_stored = false;
	switch (opcode & 0x00FF)
	{
	/// set Vx to the value of the delay timer
	case 0x07:
		chip8.registers[v_x] = chip8.delay_timer_register;
		break;
	/// waiting for a key press and storing it in Vx
	case 0x0A:
		key_stored = false;
		for (i=0; i<0x10; i++)
		{
			if (chip8.keys[i])
			{
				chip8.registers[v_x] = i;
				key_stored = true;
				break;
			}
		}
		if (!key_stored)
		{
			/// repeat the instruction
			chip8.pc -= 2;
		}
		break;
	/// set the delay timer to Vx
	case 0x15:
		chip8.delay_timer = chip8.registers[v_x];
		break;
	/// set the sound timer to Vx
	case 0x18:
		chip8.sound_timer = chip8.registers[v_x];
		break;
	/// add Vx to the address register I
	case 0x1E:
		if ((chip8.address + chip8.registers[v_x]) > 0xFFF)
		{
			chip8.registers[0xF] = 1;
		}
		else
		{
			chip8.registers[0xF] = 0;
		}
		chip8.address = chip8.address + chip8.registers[v_x];
		break;
	/// sets the address register to the location of the character in Vx
	case 0x29:
		/// every character takes 5 bytes, starting at 0
		character = chip8.registers[v_x];
		chip8.address = character * 5;
		break;
	/// store the BCD representation of Vx in the address register I, I+1 and I+2 (most significant first)
	case 0x33:
		character = chip8.registers[v_x];

		memory[chip8.address] = (character/100);
		character -= ((character/100)*100);

		memory[chip8.address+1] = (character/10);
		character -= ((character/10)*10);

		memory[chip8.address+2] = character;
		break;
	/// store V0 to Vx in the memory starting at the address register I
	case 0x55:
		for (i=0; i<(v_x+1); i++)
		{
			memory[chip8.address+i] = chip8.registers[i];
		}
		if (chip8.compatibility)
		{
			chip8.address = chip8.address + v_x + 1;
		}
		break;
	/// fill V0 to Vx with values from the memory starting at the address register I
	case 0x65:
		for (i=0; i<(v_x+1); i++)
		{
			chip8.registers[i] = memory[chip8.address+i];
		}
		if (chip8.compatibility)
		{
			chip8.address = chip8.address + v_x + 1;
		}
		break;
	}
}

/**
 * Loads the character sprites 0-9 and A-F into the memory starting from 0x00.
 */
void load_character_sprites()
{
	/// 0
	memory[0x00] = 0xF0;
	memory[0x01] = 0x90;
	memory[0x02] = 0x90;
	memory[0x03] = 0x90;
	memory[0x04] = 0xF0;

	/// 1
	memory[0x05] = 0x20;
	memory[0x06] = 0x60;
	memory[0x07] = 0x20;
	memory[0x08] = 0x20;
	memory[0x09] = 0x70;

	/// 2
	memory[0x0A] = 0xF0;
	memory[0x0B] = 0x10;
	memory[0x0C] = 0xF0;
	memory[0x0D] = 0x80;
	memory[0x0E] = 0xF0;

	/// 3
	memory[0x0F] = 0xF0;
	memory[0x10] = 0x10;
	memory[0x11] = 0xF0;
	memory[0x12] = 0x10;
	memory[0x13] = 0xF0;

	/// 4
	memory[0x14] = 0x90;
	memory[0x15] = 0x90;
	memory[0x16] = 0xF0;
	memory[0x17] = 0x10;
	memory[0x18] = 0x10;

	/// 5
	memory[0x19] = 0xF0;
	memory[0x1A] = 0x80;
	memory[0x1B] = 0xF0;
	memory[0x1C] = 0x10;
	memory[0x1D] = 0xF0;

	/// 6
	memory[0x1E] = 0xF0;
	memory[0x1F] = 0x80;
	memory[0x20] = 0xF0;
	memory[0x21] = 0x90;
	memory[0x22] = 0xF0;

	/// 7
	memory[0x23] = 0xF0;
	memory[0x24] = 0x10;
	memory[0x25] = 0x20;
	memory[0x26] = 0x40;
	memory[0x27] = 0x40;

	/// 8
	memory[0x28] = 0xF0;
	memory[0x29] = 0x90;
	memory[0x2A] = 0xF0;
	memory[0x2B] = 0x90;
	memory[0x2C] = 0xF0;

	/// 9
	memory[0x2D] = 0xF0;
	memory[0x2E] = 0x90;
	memory[0x2F] = 0xF0;
	memory[0x30] = 0x10;
	memory[0x31] = 0xF0;

	/// A
	memory[0x32] = 0xF0;
	memory[0x33] = 0x90;
	memory[0x34] = 0xF0;
	memory[0x35] = 0x90;
	memory[0x36] = 0x90;

	/// B
	memory[0x37] = 0xE0;
	memory[0x38] = 0x90;
	memory[0x39] = 0xE0;
	memory[0x3A] = 0x90;
	memory[0x3B] = 0xE0;

	/// C
	memory[0x3C] = 0xF0;
	memory[0x3D] = 0x80;
	memory[0x3E] = 0x80;
	memory[0x3F] = 0x80;
	memory[0x40] = 0xF0;

	/// D
	memory[0x41] = 0xE0;
	memory[0x42] = 0x90;
	memory[0x43] = 0x90;
	memory[0x44] = 0x90;
	memory[0x45] = 0xE0;

	/// E
	memory[0x46] = 0xF0;
	memory[0x47] = 0x80;
	memory[0x48] = 0xF0;
	memory[0x49] = 0x80;
	memory[0x4A] = 0xF0;

	/// F
	memory[0x4B] = 0xF0;
	memory[0x4C] = 0x80;
	memory[0x4D] = 0xF0;
	memory[0x4E] = 0x80;
	memory[0x4F] = 0x80;
}


