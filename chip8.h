#pragma once


constexpr unsigned short MEMORY_SIZE = 4096;
constexpr unsigned char FONTSET_SIZE = 80;
constexpr unsigned char NUMBER_OF_REGISTERS = 16;
constexpr unsigned int STACK_SIZE = 16;
constexpr unsigned short DELAY_TIMER_MAX = 255;
constexpr unsigned short SOUND_TIMER_MAX = 255;
constexpr unsigned short SCREEN_WIDTH = 64;
constexpr unsigned short SCREEN_HEIGHT = 32;

constexpr unsigned short OPCODES_COUNT = MEMORY_SIZE / 2;
constexpr unsigned short CACHE_SIZE = OPCODES_COUNT / 16;

struct CacheEntry {
    uint16_t lastExecutedPc;
    uint8_t cyclesToExecuteLastTime;
};

using Cache = std::array<CacheEntry, CACHE_SIZE>;
struct Display {
    bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
};

struct Keypad {
    bool keys[NUMBER_OF_REGISTERS];
};

struct Timers {
    uint8_t delayTimer;
    uint8_t soundTimer;
};

struct Stack {
    uint16_t stack[STACK_SIZE];
    size_t top;
};

class Chip8 {
public:
    void initialize();
    void loadRom(const std::string& romPath);
    void emulateCycle();
    void handleInput();

private:
    // Update these lines...
    Cache cache;
    size_t cacheHits;
    size_t cacheMisses;

    // New private member function
    void storeCacheEntry(uint16_t pc, uint8_t cycles);
    bool retrieveCacheEntry(uint16_t pc, uint8_t& cycles);

    // Rest of the members remains the same...

private:
    // Memory
    uint8_t memory[MEMORY_SIZE];
    // Registers V0 - VF
    uint8_t V[NUMBER_OF_REGISTERS];
    // Program counter
    uint16_t pc;
    // Index register
    uint16_t I;
    // Stack
    Stack stack;
    // Delay timer
    Timers dt;
    // Sound timer
    Timers st;
    // Display
    Display display;
    // Opcode
    uint16_t opcode;
};

void Chip8::loadRom(const std::string& romPath) {
    std::ifstream file(romPath, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open ROM file");
    }

    auto fileSize = file.tellg();
    file.seekg(0);

    if (fileSize > MEMORY_SIZE - FONTSET_SIZE) {
        throw std::runtime_error("ROM file too large");
    }

    file.read(reinterpret_cast<char*>(memory + FONTSET_SIZE), static_cast<std::streamsize>(fileSize));
}

// Inside chip8.cpp
void Chip8::executeClearScreenOp() {
    memset(&display.pixels, false, sizeof(display.pixels));
    drawFlag = true;
}

void Chip8::executeReturnFromSubroutineOp() {
    --stack.top;
    pc = stack.stack[stack.top];
}

// ... more opcode handlers ...

void Chip8::emulateCycle() {
    fetchOpcode();
    executeInstruction();
}

void Chip8::fetchOpcode() {
    opcode = memory[pc] << 8 | memory[pc + 1];
}

void Chip8::executeInstruction() {
    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x00FF) {
                case 0xE0:
                    executeClearScreenOp();
                    break;
                case 0xEE:
                    executeReturnFromSubroutineOp();
                    break;
                default:
                    unhandledOpcode();
                    break;
            }
            break;
        // More cases go here...
        default:
            unhandledOpcode();
            break;
    }
}

void Chip8::unhandledOpcode() {
    printf("Unhandled opcode %04X at address %04X\n", opcode, pc);
    exit(-1);
}