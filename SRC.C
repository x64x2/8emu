#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define KEY_SIZE 16

#define IS_BIT_SET(byte, bit) (((0x80 >> (bit)) & (byte)) != 0x0)

#define FONTSET_ADDRESS 0x00
#define FONTSET_BYTES_PER_CHAR 5

void Chip8_init(char *program_file_path[], int chip8)

#define FONTSET_BYTES_PER_CHAR 5
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
}

static inline uint8_t randbyte() { return (rand() % 256);

uint16_t Chip8_fetch(Chip8 *chip8)
{
    uint16_t instr = 0;
    instr = instr | *(chip8->pc++);
    instr = instr << 8;
    instr = instr | *(chip8->pc++);
    return instr;
}

void Chip8_destroy(Chip8 *chip8)
{
    free(chip8->ram);
    free(chip8->stack);
    free(chip8->vregister);
}

void Chip8_reset_keys(Chip8 *chip8)
{
    uint8_t keys[16] = {0};
    memcpy(chip8->keys_pressed, keys, 16 * sizeof(uint8_t));
}

void Chip8_run_instr(Chip8 *chip8, Display *display)
{
    uint16_t instr = Chip8_fetch(chip8);
    Chip8_decode_execute(chip8, display, instr);
}

void Chip8_print_ram(Chip8 *chip8)
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

void Chip8_load_font(Chip8 *chip8)
{
    uint8_t font[16][5] = 
    memcpy((chip8->ram + 0x050), font, 16 * 5 * sizeof(uint8_t));
}

void Chip8_load_program(Chip8 *chip8, char *file_path)
{
    FILE *program_file = fopen(file_path, "rb");
    uint8_t *ramptr = chip8->ram + 0x200;

    fseek(program_file, 0, SEEK_END);
    long program_size = ftell(program_file);
    rewind(program_file);
    assert(program_size <= 3232L);

    fread(ramptr, (size_t)program_size, 1, program_file);
    fclose(program_file);

    dprintf("Program Size: %lu bytes\n\n", program_size);
}

uint16_t Chip8_fetch(Chip8 *chip8)
{
    uint16_t instr = 0;
    instr = instr | *(chip8->pc++);
    instr = instr << 8;
    instr = instr | *(chip8->pc++);
    return instr;
}

void Chip8_decode_execute(Chip8 *chip8, Display *display, uint16_t instr)
{
    // Different nibbles in the instr represent:
    uint16_t T   = instr & 0xF000;  // instr type
    uint16_t X   = (instr & 0x0F00) >> 0x8;  // Look up index for Variable Register
    uint16_t Y   = (instr & 0x00F0) >> 0x4;  // Look up index for Variable Register
    uint16_t N   = instr & 0x000F;  // 4-bit constant
    uint16_t NN  = instr & 0x00FF;  // 8-bit constant
    uint16_t NNN = instr & 0x0FFF;  // Memory address

    if (T == 0x0000)
    {
        if (NN == 0xE0)
        {
            Display_reset(display);
        }
        else if (NN == 0xEE)
        {
            // Add offset from stack to chip8 ram address
            chip8->pc = chip8->ram + *(--chip8->stack);
        }
        else if (instr != 0x0000)
        {
            dprintf("Instruction 0NNN encountered; skipping.\n");
        }
        else
        {
            eprintf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (T == 0x1000)
    {   
        // 1NNN: Jump to instr at location NNN
        chip8->pc = (chip8->ram + NNN);
    }
    else if (T == 0x2000)
    {
        // 2NNN: Call subroutine at location NNN
        *(chip8->stack++) = (uint16_t)(chip8->pc - chip8->ram);
        chip8->pc = (chip8->ram + NNN);
    }
    else if (T == 0x3000)
    {
        // 3XNN: Skip instr if Variable Register X == NN
        if (chip8->vregister[X] == NN)
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x4000)
    {
        // 4XNN: Skip instr if Variable Register X != NN
        if (chip8->vregister[X] != NN)
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x5000)
    {
        // 5XY0: Skip instr if VRegister X == VRegister Y
        if (chip8->vregister[X] == chip8->vregister[Y])
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0x6000)
    {
        // 6XNN: Set the VRegister X to the value NN
        chip8->vregister[X] = (uint8_t)NN;
    }
    else if (T == 0x7000)
    {
        // 7XNN: Increment the VRegister X value by NN
        chip8->vregister[X] += (uint8_t)NN;
    }
    else if (T == 0x8000)
    {
        // 8XY0: Set VRegister X to the value of VRegister Y
        if (N == 0)
        {
            chip8->vregister[X] = chip8->vregister[Y];
        }
        // 8XY1: Set VX to VX | VY
        else if (N == 1)
        {
            chip8->vregister[X] = chip8->vregister[X] | chip8->vregister[Y];
        }
        // 8XY2: Set VX to VX & VY
        else if (N == 2)
        {
            chip8->vregister[X] = chip8->vregister[X] & chip8->vregister[Y];
        }
        // 8XY3: Set VX to VX ^ VY
        else if (N == 3)
        {
            chip8->vregister[X] = chip8->vregister[X] ^ chip8->vregister[Y];
        }
        // 8XY4: Set VX to VX + VY, then sets VF to 1 if VX > 255
        else if (N == 4)
        {
            uint8_t sum = chip8->vregister[X] + chip8->vregister[Y];
            if (chip8->vregister[X] > sum)
            {
                chip8->vregister[0xF] = 1;
            }
            else
            {
                chip8->vregister[0xF] = 0;
            }
            chip8->vregister[X] = sum;
        }
        // 8XY5: Set VX to VX - VY, then sets VF to 1 if VX > VY
        else if (N == 5)
        {
            uint8_t diff = chip8->vregister[X] - chip8->vregister[Y];
            if (chip8->vregister[X] > chip8->vregister[Y])
            {
                chip8->vregister[0xF] = 1;
            }
            else
            {
                chip8->vregister[0xF] = 0;
            }
            chip8->vregister[X] = diff;
        }
        // 8XY6: Set VX to VY, shift VX >> 1, then sets VF to the bit shifted out
        else if (N == 6)
        {
            if (ORIG_8XY6)
            {
                chip8->vregister[X] = chip8->vregister[Y];
            }
            uint8_t shifted_out = chip8->vregister[X] & 0x01;
            chip8->vregister[X] = chip8->vregister[X] >> 1;
            chip8->vregister[0xF] = shifted_out;
        }
        // 8XY7: Set VX to VY - VX, then sets VF to 1 if VY > VX
        else if (N == 7)
        {
            uint8_t diff = chip8->vregister[Y] - chip8->vregister[X];
            if (chip8->vregister[Y] > chip8->vregister[X])
            {
                chip8->vregister[0xF] = 1;
            }
            else
            {
                chip8->vregister[0xF] = 0;
            }
            chip8->vregister[X] = diff;
        }
        // 8XYE: Set VX to VY, shift VX << 1, then sets VF to the bit shifted out
        else if (N == 0xE)
        {
            if (ORIG_8XYE)
            {
                chip8->vregister[X] = chip8->vregister[Y];
            }
            uint8_t shifted_out = (chip8->vregister[X] >> 7) & 0x01;
            chip8->vregister[X] = chip8->vregister[X] << 1;
            chip8->vregister[0xF] = shifted_out;
        }
        else
        {
            eprintf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (T == 0x9000)
    {
        // 9XY0: Skip instr if VRegister X != VRegister Y
        if (chip8->vregister[X] != chip8->vregister[Y])
        {
            chip8->pc++;
            chip8->pc++;
        }
    }
    else if (T == 0xA000)
    {
        // ANNN: Set the Index Register to the value NNN
        chip8->ir = chip8->ram + NNN;
    }
    else if (T == 0xB000)
    {
        // BNNN: Jump to the instr at location (NNN + VRegister 0)
        if (ORIG_BNNN)
        {
            chip8->pc = chip8->ram + NNN + chip8->vregister[0x0];
        }
        else
        {
            chip8->pc = chip8->ram + NNN + chip8->vregister[X];
        }
    }
    else if (T == 0xC000)
    {
        // CXNN: Store the result of (randomNumber & NN) into VRegister X
        chip8->vregister[X] = (uint8_t)(rand() & NN);
    }
    else if (T == 0xD000)
    {
        // DXYN: Draw an N-pixel tall sprite at the position (VRegister X, VRegister Y)
        //    -> Also set VRegister F to 1 if any pixels were toggled off
        int xpos = chip8->vregister[X] % DISPLAY_WIDTH;
        int ypos = chip8->vregister[Y] % DISPLAY_HEIGHT;
        chip8->vregister[0xF] = 0;

        for (int i = 0; i < N; i++)
        {
            uint8_t data = *(chip8->ir + i);
            Chip8_draw(chip8, display, xpos, ypos, data);
            ypos = (ypos + 1) % DISPLAY_HEIGHT;
        }

        SDL_Delay(17);
        Display_update(display);
    }
    else if (T == 0xE000)
    {
        // EX9E: Skip an instr if the key corresponding to VRegister X is pressed
        if (NN == 0x9E)
        {
            if (chip8->keys_pressed[chip8->vregister[X]])
            {
                chip8->pc++;
                chip8->pc++;
            }
        }
        // EXA1: Skip an instr if the key corresponding to VRegister X is NOT pressed
        else if (NN == 0xA1)
        {
            if (!chip8->keys_pressed[chip8->vregister[X]])
            {
                chip8->pc++;
                chip8->pc++;
            }
        }
        else
        {
            eprintf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else if (T == 0xF000)
    {
        // FX07: Set VRegister X to the value of Delay Timer
        if (NN == 0x07)
        {
            chip8->vregister[X] = chip8->dtimer;
        }
        // FX15: Set Delay Timer to value in VRegister X
        else if (NN == 0x15)
        {
            chip8->dtimer = chip8->vregister[X];
        }
        // FX18: Set Sound Timer to value in VRegister X
        else if (NN == 0x18)
        {
            chip8->stimer = chip8->vregister[X];
        }
        // FX1E: Increment the value at Index Register by VRegister X
        else if (NN == 0x1E)
        {
            // Might be wrong; the instruction desc is ambiguous    
            //*(chip8->ir) = *(chip8->ir) + chip8->vregister[X];
            chip8->ir += chip8->vregister[X];
        }
        // FX0A: Get User Input and store it in VRegister X
        else if (NN == 0x0A)
        {
            for (uint8_t i = 0; i < 16; i++)
            {
                if (chip8->keys_pressed[i])
                {
                    chip8->vregister[X] = i;
                    return;
                } 
            }
            chip8->pc--;
            chip8->pc--;
        }
        // FX29: Set Index Register to the address of the font character at VRegister X
        else if (NN == 0x29)
        {
            chip8->ir = chip8->ram + 0x50 + chip8->vregister[X];
        }
        // FX33: Store digits of number in VRegister X to addresses starting at Index Register
        else if (NN == 0x33)
        {
            uint8_t number = chip8->vregister[X];
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
        // FX55: Store values of VRegisters 0-X in addresses starting at Index Register
        else if (NN == 0x55)
        {
            for (uint8_t i = 0; i <= X; i++)
            {
                if (ORIG_FX55)
                {
                    *(chip8->ir++) = chip8->vregister[i];
                }
                else
                {
                    *(chip8->ir + i) = chip8->vregister[i];
                }
            }
        }
        // FX65: Load memory from addresses starting at Index Register into VRegisters 0-X
        else if (NN == 0x65)
        {
            for (uint8_t i = 0; i <= X; i++)
            {
                if (ORIG_FX65)
                {
                    chip8->vregister[i] = *(chip8->ir++);
                }
                else
                {
                    chip8->vregister[i] = *(chip8->ir + i);
                }
            }
        }
        else
        {
            eprintf("Invalid instruction encountered %4X\n", instr);
            exit(1);
        }
    }
    else
    {
        eprintf("Invalid instruction encountered %4X\n", instr);
        exit(1);
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
            chip8->vregister[0xF] = 1;
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

void chip8_tick() {
    // update timers
    if (delay_timer > 0) {
        --delay_timer;
    }
    if (sound_timer > 0) {
        --sound_timer;
        if (sound_timer == 0) {
            printf("BEEP!\n");
        }
    }
}
