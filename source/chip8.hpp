#ifndef chip8_hpp
#define chip8_hpp

#include <stdio.h>
#include <string>
#include <iostream>

class Chip8 {
private:
    unsigned short opcode;
    unsigned char memory[0xFFF];
    unsigned char V[16];
    unsigned short I;
    unsigned short pc;
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short stack[16];
    unsigned short sp;
public:
    void initialize();
    void loadGame(std::string);
    void emulateCycle();
    void setKeys();
    void debugRender();
    bool drawFlag = false;
    unsigned char gfx[64 * 32];
    unsigned char key[16];
};

#endif /* chip8_hpp */
