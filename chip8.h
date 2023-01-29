#include <fstream>
#include <string.h>

#define true 1
#define false 0
#define bool int

#define MEM_SIZE 4096
#define GFX_ROWS 32
#define GFX_COLS 64
#define GFX_SIZE (GFX_ROWS * GFX_COLS)
#define STACK_SIZE 16
#define KEY_SIZE 16

#define GFX_INDEX(row, col) ((row)*GFX_COLS + (col))

#define MAX_GAME_SIZE (0x1000 - 0x200)

const unsigned int START_ADDRESS = 0x200;

void initialize();
void chip8_loadROm(char const *breakout);
void chip8_emulatecycle();
void chip8_setkeys();
void chip8_tick();
{
    pc    = START_ADDRESS // Program counter starts 
    opcode = 0;    // Reset current opcode
    I      = 0;    // Reset index register
    sp     = 0;    // Reset stack pointer

    // Open the file as a stream of binary and move the file pointer to the end
	  std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
	  {
        // Get size of file and allocate a buffer to hold the contents
		    std::streampos size = file.tellg();
		    char* buffer = new char[size];

	    	// Go back to the beginning of the file and fill the buffer
		    fseek(0, std::ios::beg);
		    fread(buffer, size);
		    fclose();

		   // Load the ROM contents into the Chip8's memory, starting at 0x200
		  for (long i = 0; i < size; ++i)
	    {
			   memory[START_ADDRESS + i] = buffer[i];
		  }

		  // Free the buffer
		  delete[] buffer;
    }
  
void Chip8::Cycle()
{
    // Load fontset
    for(int i = 0; i < 80; ++i)
      memory[i] = chip8_fontset[i];

    // Decode opcode
    ((*this)).*(table [ (opcode & 0xF000u) >> 12u]))();
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
              else if (delayTimer > 0)
              {
	                  	--delayTimer;
	            }
     break;
} 