/*
 * io.c
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
#include "io.h"

void load_rom(char *name)
{
	FILE *file;
	unsigned char *buffer;
	int file_length;

	///Open file
	file = fopen(name, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", name);
		return;
	}

	fseek(file, 0, SEEK_END);
	file_length=ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = (unsigned char *)malloc(file_length+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
		fclose(file);
		return;
	}

	fread(buffer, file_length, 1, file);
	fclose(file);

	int i = 0;
	for (i=0; i<file_length; i++)
	{
		memory[0x200+i] = buffer[i];
	}

	free(buffer);
}

void init_Key()
{
	pthread_t key_thread;
	pthread_create(&key_thread, NULL, wait_for_input, NULL);
}

void *wait_for_input(void *dummy)
{
	SDL_Event event;
	while (cpu.running)
	{
		if (SDL_WaitEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				cpu.running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_1)
				{
					cpu.keys[0x1] = true;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					cpu.keys[0x2] = true;
				}
				if (event.key.keysym.sym == SDLK_3)
				{
					cpu.keys[0x3] = true;
				}
				if (event.key.keysym.sym == SDLK_4)
				{
					cpu.keys[0xC] = true;
				}
				if (event.key.keysym.sym == SDLK_q)
				{
					cpu.keys[0x4] = true;
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					cpu.keys[0x5] = true;
				}
				if (event.key.keysym.sym == SDLK_e)
				{
					cpu.keys[0x6] = true;
				}
				if (event.key.keysym.sym == SDLK_r)
				{
					cpu.keys[0xD] = true;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					cpu.keys[0x7] = true;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					cpu.keys[0x8] = true;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					cpu.keys[0x9] = true;
				}
				if (event.key.keysym.sym == SDLK_f)
				{
					cpu.keys[0xE] = true;
				}
				if (event.key.keysym.sym == SDLK_y)
				{
					cpu.keys[0xA] = true;
				}
				if (event.key.keysym.sym == SDLK_x)
				{
					cpu.keys[0x0] = true;
				}
				if (event.key.keysym.sym == SDLK_c)
				{
					cpu.keys[0xB] = true;
				}
				if (event.key.keysym.sym == SDLK_v)
				{
					cpu.keys[0xF] = true;
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_1)
				{
					cpu.keys[0x1] = false;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					cpu.keys[0x2] = false;
				}
				if (event.key.keysym.sym == SDLK_3)
				{
					cpu.keys[0x3] = false;
				}
				if (event.key.keysym.sym == SDLK_4)
				{
					cpu.keys[0xC] = false;
				}
				if (event.key.keysym.sym == SDLK_q)
				{
					cpu.keys[0x4] = false;
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					cpu.keys[0x5] = false;
				}
				if (event.key.keysym.sym == SDLK_e)
				{
					cpu.keys[0x6] = false;
				}
				if (event.key.keysym.sym == SDLK_r)
				{
					cpu.keys[0xD] = false;
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					cpu.keys[0x7] = false;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					cpu.keys[0x8] = false;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					cpu.keys[0x9] = false;
				}
				if (event.key.keysym.sym == SDLK_f)
				{
					cpu.keys[0xE] = false;
				}
				if (event.key.keysym.sym == SDLK_y)
				{
					cpu.keys[0xA] = false;
				}
				if (event.key.keysym.sym == SDLK_x)
				{
					cpu.keys[0x0] = false;
				}
				if (event.key.keysym.sym == SDLK_c)
				{
					cpu.keys[0xB] = false;
				}
				if (event.key.keysym.sym == SDLK_v)
				{
					cpu.keys[0xF] = false;
				}
				break;
			}
		}
	}
	return NULL;
}

void dump_cpu(char* reason)
{
	FILE* file = fopen("error.log", "a");
	if (file == NULL)
	{
		printf("Could not open error.log");
	}
	else
	{
		int i = 0;
		char buff[100];
		time_t now = time(NULL);
		strftime (buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));

		fprintf(file, "Writing error log at %s\n", buff);
		fprintf(file, "Caller reason: %s\n", reason);
		fprintf(file, "-c\t\t= %d\n", cpu.compatibility);
		fprintf(file, "PC\t\t= 0x%04x\n", cpu.program_counter);
		fprintf(file, "I\t\t= 0x%04x\n", cpu.address);
		fprintf(file, "DT\t\t= 0x%02x\n", cpu.delay_timer_register);
		fprintf(file, "ST\t\t= 0x%02x\n", cpu.sound_timer_register);
		fprintf(file, "SP\t\t= %d\n", cpu.stack_pointer);
		for (i=0; i<STACK_SIZE; i++)
		{
			fprintf(file, "stack[%d]\t= 0x%04x\n", i, cpu.stack[i]);
		}
		for (i=0; i<0x10; i++)
		{
			fprintf(file, "V%x\t\t= 0x%02x\n", i, cpu.registers[i]);
		}
		for (i=0; i<MEMORY_SIZE; i++)
		{
			fprintf(file, "memory[0x%04x]\t= 0x%02x\n", i, memory[i]);
		}
		fprintf(file, "\n\n\n");
		fclose(file);
	}
}
