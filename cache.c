#include <stdint.h>
#include <stdlib.h>
#include <arm64intr.h>
#include "main.c"

void Chip8::OP_00E0()
{
	memset(video, 0, sizeof(video));
}

void Chip8::OP_00EE()
{
	--sp;
	pc = stack[sp];
}

void Chip8::OP_2nnn()
{
	uint16_t address = opcode & 0x0FFFu;

	stack[sp] = pc;
	++sp;
	pc = address;
}

void Chip8::OP_3xkk()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	if (registers[Vx] == byte)
	{
		pc += 2;
	}
}

void Chip8::OP_5xy0()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;

	if (registers[Vx] == registers[Vy])
	{
		pc += 2;
	}
}

void Chip8::OP_8xy4()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;

	uint16_t sum = registers[Vx] + registers[Vy];

	if (sum > 255U)
	{
		registers[0xF] = 1;
	}
	else
	{
		registers[0xF] = 0;
	}

	registers[Vx] = sum & 0xFFu;
}
     // Cached interpreter for Chip-8 assembly code
    void interpret(unsigned short opcode) {
    // Check cache for previously interpreted instruction
    void (*cached_instruction)(void) = checkCache(opcode);
    if(cached_instruction != NULL) {
    // Execute cached instruction
    cached_instruction();
    } else {
        switch(opcode & 0xF000) {
            case 0x0000:
                switch(opcode & 0x00FF) {
                    case 0x00E0: // 00E0 - Clear screen
                        clearScreen();
                        break;
                    case 0x00EE: // 00EE - Return from subroutine
                        returnFromSubroutine();
                        break;
                    default:
                        // Invalid opcode
                        break;
                }
                break;
            case 0x1000: // 1NNN - Jump to address NNN
                jumpToAddress(opcode & 0x0FFF);
                break;
            case 0x2000: // 2NNN - Call subroutine at NNN
                callSubroutine(opcode & 0x0FFF);
                break;
            // Other opcode cases here
        }
        // Add executed instruction to cache
        addToCache(opcode, cached_instruction);
    }
}
