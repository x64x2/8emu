#include <stdint.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>
#include "chip8.h"

int WIDTH = 64;
int HEIGHT = 32;
int SCALE = 10;
int FPS = 60;
int TICKS_PER_FRAME = 1000 / FPS;
int INSTRUCTIONS_PER_STEP = 10;

 if (chip8.get_sound_timer() > 0) {
            Mix_PlayChannel(-1, chunk, 0);
        }

if (chip8.get_draw_flag()) {
            chip8.reset_draw_flag();
            std::uint32_t* pixels = nullptr;
            int pitch;
            (texture, nullptr, reinterpret_cast<void**>(&pixels), &pitch);
            for (int i = 0; i < WIDTH * HEIGHT; i++) {
                pixels[i] = (chip8.get_pixel_data(i) == 0) ? 0x000000FF : 0xFFFFFFFF;
            }
        }

int main(int argc, char **argv)
{
    // Set up render system and register input callbacks//
    struct setupGraphics;
    struct setupInput;


     // Initialize the Chip8 system and load the game into the memory//
     typedef struct chip8 initialize {
        FILE *fp;
        FILE *fopen(char *, int chip8_loadgame("pong") *chip8);

         //Emulation loop//
          char chip8[]
    {;
        // Emulate one cycle//
        short myChip8_emulateCircle();

        //if the draw flag is set, update the screen//
        if("myChip8.drawFlag")
           struct drawGraphics();



        }                
    return 0;
