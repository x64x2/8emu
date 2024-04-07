#include <limits.h>
#include <stdio.h>
#include <float.h>
#include "chip8.h"

#define MEM_SIZE 4096
#define STACK_SIZE 16
#define KEY_SIZE 16

#define IS_BIT_SET(byte, bit) (((0x80 >> (bit)) & (byte)) != 0x0)

#define FONTSET_ADDRESS 0x00
#define FONTSET_BYTES_PER_CHAR 5

struct Chip8 {
     
    char *opcode[100]; // instr type
    int mem_size;  // Memory address 
    unsigned char delay_timer;  // 4-bit constant
    unsigned stack[0x10];  // 8-bit constant
    unsigned char key[0x10]; // Look up index for Variable Register

};

unsigned char chip8_fontset[80] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F 
};

void Chip8_init(char *program_file_path[], int chip8) {
    char name[100];
}

void Chip8_fetch(char *chip8)
{
    chip8 *pc += 2; // Increment program counter by two since each opcode takes up two bytes
    unsigned opcode = ((unsigned)(chip8==MEM_SIZE[chip8-pc - 2])) << 8 |
        chip8-MEM_SIZE[chip8-pc - 1];
}

void Chip8_destroy(struct Chip8 *chip8)
{
    return;
}

void Chip8_reset_keys(chip8)
{
   unsigned keys[16] = {0};
    ( chip8=+ KEY_SIZE);
}

void Chip8_run_instr(chip8, Display)
{
    struct instr;
    Chip8_run_instr(chip8, Display);
}

void Chip8_print_ram(chip8)
{
    for (int i = 0; i < 4096; i++)
    {
        if (i % 12 == 0)
        {
            fprintf(stderr, "\n0x%.4X -> | ", i);
        }
        fprintf(stderr, "0x%.2X | ", *(chip8->ram + i));
    }
    fprintf(stderr, "\n");
}

void Chip8_load_font(chip8)
{
    unsigned font[16][5] = 
    MEM_SIZE((chip8-> + 0x050), font, 16 * 5 * sizeof(unsigned));
}

void Chip8_load_program(chip8, file_path)
{
    return;
}

void Chip8_decode_execute(struct Chip8 *chip8, int Display, unsigned instr)
{
    // Different nibbles in the instr represent:
    if (instr == 0x0000)
    {
        if (instr == 0xE0)
        {
            Display[Display]
        }
        else if (instr == 0xEE)
        {
            // Add offset from stack to chip8 ram address
            chip8->pc = chip8->ram + *(--chip8->stack);
        }
        else if (instr != 0x0000)
        {
            printf("Instruction 0NNN encountered; skipping.\n");
        }
        else
        {
            printf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (instr == 0x1000)
    {   
        // 1NNN: Jump to instr at location NNN
        chip8->pc = (chip8->ram + NNN);
    }
    else if (T == 0x2000)
    {
        // 2NNN: Call subroutine at location NNN
        *(chip8->stack) = (unsigned)(chip8->stack - chip8->PC);
        chip8->pc = (chip8->ram + NNN);
    }
    else if (T == 0x3000)
    {
        // 3XNN: Skip instr if Variable Register X == NN
        if (chip8->register[X] == NN)
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x4000)
    {
        // 4XNN: Skip instr if Variable Register X != NN
        if (chip8->register[X] != NN)
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x5000)
    {
        // 5XY0: Skip instr if register X == register Y
        if (chip8->register[X] == chip8->register[Y])
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x6000)
    {
        // 6XNN: Set the register X to the value NN
        chip8->register[X] = (uint8_t)NN;
    }
    else if (T == 0x7000)
    {
        // 7XNN: Increment the register X value by NN
        chip8->register[X] += (uint8_t)NN;
    }
    else if (T == 0x8000)
    {
        // 8XY0: Set register X to the value of register Y
        if (N == 0)
        {
            chip8->register[X] = chip8->register[Y];
        }
        // 8XY1: Set VX to VX | VY
        else if (N == 1)
        {
            chip8->register[X] = chip8->register[X] | chip8->register[Y];
        }
        // 8XY2: Set VX to VX & VY
        else if (N == 2)
        {
            chip8->register[X] = chip8->register[X] & chip8->register[Y];
        }
        // 8XY3: Set VX to VX ^ VY
        else if (N == 3)
        {
            chip8->register[X] = chip8->register[X] ^ chip8->register[Y];
        }
        // 8XY4: Set VX to VX + VY, then sets VF to 1 if VX > 255
        else if (N == 4)
        {
            uint8_t sum = chip8->register[X] + chip8->register[Y];
            if (chip8->register[X] > sum)
            {
                chip8->register[0xF] = 1;
            }
            else
            {
                chip8->register[0xF] = 0;
            }
            chip8->register[X] = sum;
        }
        // 8XY5: Set VX to VX - VY, then sets VF to 1 if VX > VY
        else if (N == 5)
        {
            uint8_t diff = chip8->register[X] - chip8->register[Y];
            if (chip8->register[X] > chip8->register[Y])
            {
                chip8->register[0xF] = 1;
            }
            else
            {
                chip8->register[0xF] = 0;
            }
            chip8->register[X] = diff;
        }
        // 8XY6: Set VX to VY, shift VX >> 1, then sets VF to the bit shifted out
        else if (N == 6)
        {
            uint8_t shifted_out = chip8->register[X] & 0x01;
            chip8->register[X] = chip8->register[X] >> 1;
            chip8->register[0xF] = shifted_out;
        }
        // 8XY7: Set VX to VY - VX, then sets VF to 1 if VY > VX
        else if (N == 7)
        {
            uint8_t diff = chip8->register[Y] - chip8->register[X];
            if (chip8->register[Y] > chip8->register[X])
            {
                chip8->register[0xF] = 1;
            }
            else
            {
                chip8->register[0xF] = 0;
            }
            chip8->register[X] = diff;
        }
        // 8XYE: Set VX to VY, shift VX << 1, then sets VF to the bit shifted out
        else if (N == 0xE)
        {
            uint8_t shifted_out = (chip8->register[X] >> 7) & 0x01;
            chip8->register[X] = chip8->register[X] << 1;
            chip8->register[0xF] = shifted_out;
        }
        else
        {
            printf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (T == 0x9000)
    {
        // 9XY0: Skip instr if register X != register Y
        if (chip8->register[X] != chip8->register[Y])
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0xC000)
    {
        // CXNN: Store the result of (randomNumber & NN) into register X
        chip8->register[X] = (uint8_t)(rand() & NN);
    }
    else if (T == 0xE000)
    {
        // EX9E: Skip an instr if the key corresponding to register X is pressed
        if (NN == 0x9E)
        {
            if (chip8->keys_pressed[chip8->register[X]])
            {
                chip8->pc++;
                chip8->pc++;
            }
        }
        // EXA1: Skip an instr if the key corresponding to register X is NOT pressed
        else if (NN == 0xA1)
        {
            if (!chip8->keys_pressed[chip8->register[X]])
            {
                chip8->pc++;
                chip8->pc++;
            }
        }
        else
        {
            printf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (T == 0xF000)
    {
        // FX07: Set register X to the value of Delay Timer
        if (NN == 0x07)
        {
            chip8->register[X] = chip8->timer;
        }
        // FX15: Set Delay Timer to value in register X
        else if (NN == 0x15)
        {
            chip8->timer = chip8->register[X];
        }
        // FX18: Set Sound Timer to value in register X
        else if (NN == 0x18)
        {
            chip8->timer = chip8->register[X];
        }
        // FX1E: Increment the value at Index Register by register X
        else if (NN == 0x1E)
        {
            // Might be wrong; the instruction desc is ambiguous    
            chip8->ir += chip8->register[X];
        }
        // FX0A: Get User Input and store it in register X
        else if (NN == 0x0A)
        {
            for (uint8_t i = 0; i < 16; i++)
            {
                if (chip8->keys_pressed[i])
                {
                    chip8->register[X] = i;
                    return;
                } 
            }
            chip8->pc--;
            chip8->pc--;
        }
        // FX29: Set Index Register to the address of the font character at register X
        else if (NN == 0x29)
        {
            chip8->ir = chip8->ram + 0x50 + chip8->register[X];
        }
        // FX33: Store digits of number in register X to addresses starting at Index Register
        else if (NN == 0x33)
        {
            uint8_t number = chip8->register[X];
            uint8_t digits[3] = {0};
            uint16_t index = 0;
            while (number)
            {
                digits[index++] = number % 10;
                number = number / 10;
            }
            for (int i = index - 1; i >= 0; i--)
            {
                *(chip8->ir + (index - 1 - i)) = digits[i];
            }
        }

void Chip8_draw(Chip8 *chip8, Display *display, int x, int y, uint8_t data)
{
    uint8_t values[8] = {0};
    for (size_t i = 0; i < 8; i++)
    {
        // Extract individual bits from the data
        values[7 - i] = (data >> (1 * i)) & 0x01;
    }

    for (int i = 0; i < 8; i++)
    {
        // If bit is 1 and the corresponding pixel is already lit, turn pixel off
        if (values[i] == 1 && display->screen[y][x] == 1)
        {
            display->screen[y][x] = 0;
            chip8->register[0xF] = 1;
        }
        // Otherwise, toggle on the display if bit is 1
        else if (values[i] == 1 && display->screen[y][x] == 0)
        {
            display->screen[y][x] = 1;
        }
        x = (x + 1) % DISPLAY_WIDTH;
    }
}

static void debug_draw() {
    int x, y;

    for (y = 0; y < GFX_ROWS; y++) {
        for (x = 0; x < GFX_COLS; x++) {
            if (gfx[y][x] == 0) printf("0");
            else printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

static void print_state() {
    printf("------------------------------------------------------------------\n");
    printf("\n");

    printf("V0: 0x%02x  V4: 0x%02x  V8: 0x%02x  VC: 0x%02x\n", 
           V[0], V[4], V[8], V[12]);
    printf("V1: 0x%02x  V5: 0x%02x  V9: 0x%02x  VD: 0x%02x\n",
           V[1], V[5], V[9], V[13]);
    printf("V2: 0x%02x  V6: 0x%02x  VA: 0x%02x  VE: 0x%02x\n",
           V[2], V[6], V[10], V[14]);
    printf("V3: 0x%02x  V7: 0x%02x  VB: 0x%02x  VF: 0x%02x\n",
           V[3], V[7], V[11], V[15]);

    printf("\n");
    printf("PC: 0x%04x\n", PC);
    printf("\n");
    printf("\n");
}

void chip8_tick() 
    // update timers
    if (delay_timer > 0) {
        --delay_timer;
    }
    if (sound_timer > 0) {
        --sound_timer;
        if (sound_timer == 0) {
            printf("BEEP!\n");
    }
    return 0;
}
