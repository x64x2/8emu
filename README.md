 The CHIP-8 was used on computers in the 1970s and 1980s. It was mainly used to make simple games and was popular on the COSMAC VIP, Telmac 1800, and other home computers.
 
# Building and Running

To build the emulator, you will need a C compiler. Navigate to the root directory of the emulator and run the following command:

 > make

This will build the emulator and create an executable file called chip8. To run the emulator, simply pass the path to a CHIP-8 ROM as an argument:

> ./chip8 path/to/rom

## Controls

The CHIP-8 has a hexadecimal keypad with the following layout:

1 2 3 C
4 5 6 D
7 8 9 E
A 0 B F

To use the emulator, you can use the corresponding keys on your keyboard to input commands.

### Additional Features

In addition to basic CHIP-8 emulation, this emulator also includes the following features:

    A dynamic recompiler
    Support for loading ROMs from the command line
    A cached interpreter

### Credits

This emulator was developed by Eric and is based on the CHIP-8 specification provided by Cowgod's Chip-8 Technical Reference.



