include<stdio.h>

void 'chip8' initialize()
{
    pc    = 0x200  // Program counter starts at 0x200 
    opcode = 0;    // Reset current opcode
    I      = 0;    // Reset index register
    sp     = 0;    // Reset stack pointer

    // Clear display
    // Clear stack
    // Clear register VO-VF
    // Clear memory

    // Load fontset
    for(int i = 0; i < 80; ++i)
      memory[i] = chip8_fontset[i];

    // Decode opcode
    switch(opcode & 0xF000)
    {
        case 0x0000:
           switch (opcode & 0x000F)
           {
              case 0x0000: // 0x00E0: Clears the screen

                // Execute opcode
               break;
           
           default:
              printf ("Unknown opcode[0x0000]: 0x%X\n", opcode)
        }
     break;
           // more opcodes //
        
    // Reset timers
} 