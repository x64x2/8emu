
Z3 - an emulator of a Zuse Z3 computer.


Introduction
-------------

This is about the invention of the first real computers by Konrad Zuse.
For more informations read and see here:

[](https://en.wikipedia.org/wiki/Konrad_Zuse)
[](https://en.wikipedia.org/wiki/Z3_(computer))


Start the emulator:
-------------------
main.c [ARGUMENTS]

run and compile

to run the emulator,
display all comments (-d) and display a dump at end (-dump)


Arguments:
----------
-p[FILENAME]      - punch tape reader, specify the file which is read by
                    the emulator, the file which holds the program code
                    you want to run.
-t                - trace, turns on the trace and displays every line from
                    the punch tape which is executed.
-d                - display comments. Comments in the punch tape file, starting
                    with # will be displayed at run time.
-dump             - display a post mortem dump at end of the program
-v                - displays the version of the emulator

Technical specification:
------------------------
Registers          - 2 floating point numbers, r1 and r2
Memory             - 64 floating point numbers (0-63)
Input              - one punch tape reader for the program souce code
                   - keyboard for numerical input (floating point)
Output             - is displayed on screen


Assembler commands:
-------------------
These are the assembler commands the Z3 emulator understands.

PR z    - load memory cell z into register 1 or 2, depending on if r1 is
          already occupied or not
PS z    - store register 1 in memory cell z
LA      - add r1 and r2, result is stored in r1, r2 cleared
LS      - subtract r2 from r1, result is stored in r1, r2 cleared
LM      - multiply r1 with r2, result is stored in r1, r2 cleared
LI      - divide r1 by r2, result is stored in r1, r2 cleared
LW      - calculate the square root of r1, result is in r1
LU      - read floating point number from keyboard into r1 or r2, depending on 
          if r1 is already occupied or not
LD      - display register 1 as a floating point number.
          (the Z3 could only display binary)
          Both registers, r1 and r2, are cleared, un-occupied

Occupied???
-----------
Yes, the two registers of the Z3 can be occupied, filled with content, or not.

So, LU reads a number from keyboard into register 1. If register 1 is already
occupied, has a value, the number is stored in register 2.
This behaviour is somehow like a stack.

LA adds r1 and r2, stores the result in r1 and clears, un-occupies, r2.
r1 is still occupied, it has the result of the addition.

LD displays the content of r1 and clears both registers, r1 and r2.
So the next read from keyboard goes into r1, because both registers are
not occupied.
Then, the next read from keyboard goes into register 2, because r1 is already
occupied.


To do:
------
Find out if this is really compatible with a real Z3.
It seems to be really hard to get informations how the Z3 was used or at least some source code they used with the punch tapes.

Z4, please let me know :)

