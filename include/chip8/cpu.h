#ifndef CPU_H
#define CPU_H

#include <raylib.h>
#include <cstdint>
#include <iostream>

class Cpu {

public:
    Cpu();
    ~Cpu() = default;
    int upload_file_to_ram(const char *path);
    void run();
    void step();
   unsigned fetch_insn();
    void process_insn(unsigned op);

private:
    unsigned V[16];
    unsigned memory[4096];
    unsigned SP;

    unsigned delayTimer;
    unsigned soundTimer;
    unsigned frameBuffer[2048];

   unsigned stack[16];
   unsigned I;
   unsigned PC;

    bool keyPressed;

};

#endif
