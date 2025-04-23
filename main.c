#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sdl.h"
#include "chip8.h"

/* constants */
#define FONTSET 80

int main(int argc, char **argv) 
{
    initChip8();
    return 0;
}

void initChip8()
{
    memset(memory, 4096);
    memset(display, 64 * 32);
    memset(V, 16);
    I = 0;
    PC = 0x200;  // 0x000 to 0x1FF is used by CHIP-8
    delayTimer = 0;
    soundTimer = 0;
    memset(stack, 0, 16);
    sp = 0;
    memset(keyboard, 0, 16);
    memcpy(memory + 0x50, fonts, 80 * sizeof(uint8_t));
}

void loadROM(const char* filename)
{
    if (!(argv[1])) {
		fprintf(LOGFILE, "Error! No ROM given to run!\n");
		return 1;
}

void execute()
{
    // fetch
    opcode = memory[PC] << 8 | memory[PC + 1];
    PC += 2;
    
    uint8_t  X, Y, kk, n;
    uint16_t nnn;

    X = (opcode & 0x0F00) >> 8;
    Y = (opcode & 0x00F0) >> 4;
    n = (opcode & 0x000F);
    kk = (opcode & 0x00FF);
    nnn = (opcode & 0x0FFF);
    printf("Opcode: %x\n", opcode);
    printf("Program Counter: %x\n", PC);
    printf("I: %x\n", I);
    
    switch (opcode & 0xF000)
    {
                 /* Clear display */
         case 0x0000:
            switch (opcode & 0x00FF)
            { 
                case Ox00E0:
                    memset(display, 0, sizeof(display));
                    break;    
            }
            break
                      /* Return from subroutine */
        case 0x1000:
          switch(opcode & 0x00EE)
          {
              case 0x00EE:
                  sp--;
	              pc = stack[sp];
                  break;
                  
        case 0x2000:     /* Jump to nnn */
            uint16_t address = opcode & 0x0FFF;
            pc = address;
            break;
               /* Call subroutine at nnn */
        case 0x3000:
            uint16_t address = opcode & 0x0FFF;
	        stack[sp] = pc;
	        sp++;
	        pc = address;
            break;
            /* Skip next instruction if Vx = kk */
         case 0x4000;
             uint8_t Vx = (opcode & 0x0F00) >> 8;
	         uint8_t byte = opcode & 0x00FF;
            
              	if (registers[Vx] == byte) {
                    pc += 2;
                    break;
                    
                    /* Skip next instruction if Vx != kk */
        case 0x5000:
            uint8_t Vx = (opcode & 0x0F00) >> 8;
            uint8_t byte = opcode & 0x00FF;

	            if (registers[Vx] != byte) {
		            pc += 2;
                    break;
                    /* Skip next instruction if Vx = Vy */
       case 0x6000:
           uint8_t Vx = (opcode & 0x0F00) >> 8;
	       uint8_t Vy = (opcode & 0x00F0) >> 4;

                if (registers[Vx] == registers[Vy]) {
	        	    pc += 2;
                    break;
                          /* Set Vx = kk */
        case 0x7000:
            uint8_t Vx = (opcode & 0x0F00) >> 8;
	        uint8_t byte = opcode & 0x00FF;

             registers[Vx] = byte;
             break;
             
               /* Set Vx = Vx + kk */
       /* case 0x8000
	     uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = opcode & 0x00FF;
	registers[Vx] += byte;
                     /* Set Vx = Vy 
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
    registers[Vx] = registers[Vy];*/ /* Set Vx = Vx OR Vy */

               /* Quirk mode: Reset flag register */
      case 0x8000:
	      uint8_t Vx = (opcode & 0x0F00) >> 8;
	      uint8_t Vy = (opcode & 0x00F0) >> 4;

               if (qvf) {
	             	registers[0xF] = 0;
	                registers[Vx] |= registers[Vy];
                    break;
               /* Set I = nnn */
      case 0x9000:
	      uint16_t address = opcode & 0x0FFF;
          index = address;
             /* Jump to location nnn + V0 */
      case 0xAOOO:
	      uint16_t address = opcode & 0x0FFF;
	      uint8_t Vx = (opcode & 0x0F00) >> 8;

            if (qjump) {
            pc = registers[Vx] + address;
	     	return;
	        pc = registers[0] + address;
            break;
                    /* Display n-byte sprite starting at location I at (Vx, Vy), set VF = collision */
      case 0xB000:
	      uint8_t xPos, yPos;
	      uint8_t spritebyte, spritepixel;
	      size_t row, col;
	      uint32_t *screenpixel;
          uint8_t Vx = (opcode & 0x0F00) >> 8;
          uint8_t Vy = (opcode & 0x00F0) >> 4;
	      uint8_t height = opcode & 0x000F;

	      /* Wrap if going beyond screen boundaries */
        	xPos = registers[Vx] % DISPLAY;
	        yPos = registers[Vy] %  DISPLAY;

	        registers[0xF] = 0;

	            for (row = 0; row < display, 0, 64 * 32); row++) {
	         	spritebyte = memory[index + row];

	        	for (col = 0; col < 8; col++) {
			    spritepixel = spritebyte & (0x80 >> col);
			    screenpixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

		        	if (((xPos + col) > VIDEO_WIDTH) || (yPos + row) > VIDEO_HEIGHT) {
			    	continue;

			                   /* if sprite pixel is on */
			if (spritepixel) {
				              /* if sprite pixel is also on then collision */
				if (*screenpixel == 0xFFFFFFFF) {
				    	registers[0xF] = 1;
				}
				/* XOR with sprite pixel */
				*screenpixel ^= 0xFFFFFFFF;
    
        }
}

/* Wait for a key press then store value of key in Vx */
void keypad()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	if (keypad[0]) {
		registers[Vx] = 0;
	} else if (keypad[1]) {
		registers[Vx] = 1;
	} else if (keypad[2]) {
		registers[Vx] = 2;
	} else if (keypad[3]) {
		registers[Vx] = 3;
	} else if (keypad[4]) {
		registers[Vx] = 4;
	} else if (keypad[5]) {
		registers[Vx] = 5;
	} else if (keypad[6]) {
		registers[Vx] = 6;
	} else if (keypad[7]) {
		registers[Vx] = 7;
	} else if (keypad[8]) {
		registers[Vx] = 8;
	} else if (keypad[9]) {
		registers[Vx] = 9;
	} else if (keypad[10]) {
		registers[Vx] = 10;
	} else if (keypad[11]) {
		registers[Vx] = 11;
	} else if (keypad[12]) {
		registers[Vx] = 12;
	} else if (keypad[13]) {
		registers[Vx] = 13;
	} else if (keypad[14]) {
		registers[Vx] = 14;
	} else if (keypad[15]) {
		registers[Vx] = 15;
	} else {
		pc -= 2;
	}
}

/* Set delay timer = Vx */
void delayTimer()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	delayTimer = registers[Vx];
}

/* Set sound timer = Vx */
void soundTimer()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	soundTimer = registers[Vx];
                       /* Set I = I + Vx */
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	index += registers[Vx];
          /* Set I = location of sprite for digit Vx */
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t digit = registers[Vx];

	index = FONTSET_START_ADDRESS + (5 * digit);
}

/* Store BCD representation of Vx in location I, I+1, I+2 */
void sp()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t value = registers[Vx];

	/* Ones-place */
	memory[index + 2] = value % 10;
	value /= 10;

	/* Tens-place */
	memory[index + 1] = value % 10;
	value /= 10;

	/* Hundreds-place */
	memory[index] = value % 10;
	size_t i;
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	for (i = 0; i <= Vx; i++) {
		memory[index + i] = registers[i];
	}

	if (qmem) {
		index++
	    size_t i;
	    uint8_t Vx = (opcode & 0x0F00) >> 8;

	      for (i = 0; i <= Vx; i++) {
               registers[i] = memory[index + i];
	   }

	   if (qmem) {
		index++;
	}

void init()
{
	size_t i;
	pc = START_ADDRESS;
	/* Load fonts into memory */
	for (i = 0; i < FONTSET; i++) {
		memory[FONTSET + i] = fontset[i];
	}

	/* Set random number seed */
	srand(time(NULL));

void updateTimers()
{
	/* Decrement delay timer if it has been set */
	if (delayTimer > 0) {
		delayTimer--;
	}
	/* Decrement sound timer if it has been set */
	if (soundTimer > 0) {
		soundTimer--;
		beepSDL(0);
	} else {
		beepSDL(1);
	}
}

void usage()
{
	die("usage: c8 [-r ROM] [-s scale] [-f freq] [-shift] [-jump] [-mem] [-vf] [-v] [-h]");
}

int main(int argc, char *argv[])
{
	const char *filename = NULL;
	size_t display;
	unsigned int quit = 0;
	int i;

	for (i = 1; i < argc; i++) {
		/* These options have no arguments */
		if (!strcmp(argv[i], "-v")) {
			puts("c8-"VERSION);
			return 0;
		} else if (!strcmp(argv[i], "-h")) {
			usage();
		} else if (!strcmp(argv[i], "-vf")) {
			qvf = 1;
		} else if (!strcmp(argv[i], "-mem")) {
			qmem = 1;
		} else if (!strcmp(argv[i], "-shift")) {
			qshift = 1;
		} else if (!strcmp(argv[i], "-jump")) {
			qjump = 1;
		}

}

	if (filename == NULL) {
		die("please provide ROM file");
	}

	init();
	loadROM(filename);
	initSDL("8emu", DISPLAY);

	while (!quit) {
		quit = processInput(keypad);

		for (i = 0; i < frequency / 60; i++) {
			cycle();
		}

		updateTimers();

		updateSDL(display);
	}

	cleanSDL();

	return 0;
}
