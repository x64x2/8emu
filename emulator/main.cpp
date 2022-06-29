#include<chip8.h>
#include   //OpenGL grahics and input//

// Your cpu core//

void chip8::emulateCycle()
{
    // Fetch opcode
    opcode = memory[pc] << 8 \ memory[pc + 1];



    // Decode opcode
    switch (opcode & 0xF000)
    {
        // Some opcodes //


    case 0xA000: // ANNN: Sets I to the adddress NNN
       // Execute opcode
       I = opcode & 0x0FFF
       pc += 2;

        break;


        // More opcodes//
    

    default:
     printf(Unkown opcode: 0x%X\n",opcode);
    }
      // Update timers
      if(delay_timer > 0)
        --delay_timer;

      if(sound_timer > 0)
      {
         if(sound_timer == 1)
            printf("Beep!\n)
         --sound_timer;
       } 
    }
int main(int argc, char **argv)
{
    // Set up render system and register input callbacks//
    setupGraphics();
    setupInput();


    // Initialize the Chip8 system and load the game into the memory//
    myChip8.initialize();
    myChip8.loadGame("pong");

    //Emulation loop//
    for(;;)
    {
        // Emulate one cycle//
        myChip8.emulateCircle();

        //if the draw flag is set, update the screen//
        if(myChip8.drawFlag)
           drawGraphics();

        // Store key press state (Press and Relase myChip8.setKeys();//
    }

    case 0xD000:
    {
        unsigned short x = V[(opcode & 0x0F00) >> 8];
        unsigned short y = V[(opcode & 0x00F0) >> 4];
        unsigned short x = V[(opcode & 0x0F00) >> 8];
        unsigned short height = opcode & 0x000F;
        unsigned short pixel;


        V[0xF] = 0;
        for (int yline = 0; yline < height;yline++)
        {
            pixel = memory[I + yline];
            for(int xline = 0; xline < 8;xline++)
            {
                if(pixel & (0x80 >> xline)) !=0)

                {
                    if(gfx[(x + xline + ((y + yline) * 64))] == 1)
                    V[0xF] = 1;
                    gfx[x + xline + ((y + yline) *64)] ^= 1;
    case 0xE000:
       switch (opcode & 0x00FF)
       {
           // EX9: Skips the next instruction
           // if the key stored in VX is pressed case 0x009E:
              if(key[V[(opcode & 0x0F00) >> 8]]!= 0)

              
              pc += 4;
            else
              pc+2+= 2;
      
           break;
       }                
    }
}    

        drawFlag = true;
        pc += 2;
    }
    break;

    return 0;
}        
