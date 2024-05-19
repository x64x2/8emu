#include <iostream.h>
#include <cpu.h>
#include <unistd.h>
#include "chip8.hpp"


#define MEM_SIZE 4096
#define STACK_SIZE 16
#define KEY_SIZE 16

#define IS_BIT_SET(byte, bit) (((0x80 >> (bit)) & (byte)) != 0x0)

#define FONTSET_ADDRESS 0x00
#define FONTSET_BYTES_PER_CHAR 5

Chip8 mychip;

void opcode(void); // instr type
void mem_size(int, int); // memory address
void delay_timer(); // 4-bit constant
void stack(); // 8-bit constant
void key(unsigned char key, int x, int y); // Look up index for Variable Register

char* fileName = (char*)"/Volumes/Macintosh HD/OneDrive/Documenten/Chip8/PONG";

int main(int argc, char ** argv) {
    mychip.initialize();
    mychip.loadGame(fileName);

    return 0;
}

void display()
{
    mychip.emulateCycle();
    
    if(mychip.drawFlag) {

       unsigned values[8] = {0};     
        // Draw a rectangle for every 1 we find in the array
        for(int y = 0; y < 32; ++y) {
            for(int x = 0; x < 64; ++x)
            {
                if(mychip.gfx[(y*64) + x] != 0) {
        
                }
            }
        }
        mychip.drawFlag = false;
    }
    else {
        //usleep(10000);
    }
}

void mem_size(int width, int height) {}

void key(unsigned char key, int x, int y)
{
    if(key == 27) {   // esc
       return;
    }
    
    if(key == 0x7f) { // backspace
        mychip.initialize();
        mychip.loadGame(fileName);
    }
    
    if(key == '1')		mychip.key[0x1] = 1;
    else if(key == '2')	mychip.key[0x2] = 1;
    else if(key == '3')	mychip.key[0x3] = 1;
    else if(key == '4')	mychip.key[0xC] = 1;
    
    else if(key == 'q')	mychip.key[0x4] = 1;
    else if(key == 'w')	mychip.key[0x5] = 1;
    else if(key == 'e')	mychip.key[0x6] = 1;
    else if(key == 'r')	mychip.key[0xD] = 1;
    
    else if(key == 'a')	mychip.key[0x7] = 1;
    else if(key == 's')	mychip.key[0x8] = 1;
    else if(key == 'd')	mychip.key[0x9] = 1;
    else if(key == 'f')	mychip.key[0xE] = 1;
    
    else if(key == 'z')	mychip.key[0xA] = 1;
    else if(key == 'x')	mychip.key[0x0] = 1;
    else if(key == 'c')	mychip.key[0xB] = 1;
    else if(key == 'v')	mychip.key[0xF] = 1;
    
    //printf("Press key %c\n", key);
}

