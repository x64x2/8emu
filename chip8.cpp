int main(int argc, const char* argv[]) {
    try {
        if (argc != 2) {
            printf("Usage: %s <chip8_rom>\n", argv[0]);
            return -1;
        }
     
        Chip8 chip8;
        chip8.initialize();
        chip8.loadRom(argv[1]);

        while (true) {
            chip8.handleInput();
            chip8.emulateCycle();
            chip8.drawGraphics();
        }
    } catch (const std::exception& ex) {
        fprintf(stderr, "Error: %s\n", ex.what());
        return -1;
    }
    
    // At the beginning of chip8.cpp, initialize counters to zero
cacheHits = 0;
cacheMisses = 0;

// Modify the constructor to initialize the cache entries
Chip8::Chip8() : cache{CacheEntry{0}} {}

bool Chip8::retrieveCacheEntry(uint16_t pc, uint8_t& cycles) {
    if (pc >= CACHE_SIZE * 2 || pc < 0x200) {
        return false;
    }

    auto cacheIndex = pc >> 4;
    if (cache[cacheIndex].lastExecutedPc == pc && !memory[pc] && !memory[pc + 1]) {
        cycles = cache[cacheIndex].cyclesToExecuteLastTime;
        ++cacheHits;
        return true;
    } else {
        ++cacheMisses;
        return false;
    }
}

void Chip8::storeCacheEntry(uint16_t pc, uint8_t cycles) {
    auto cacheIndex = pc >> 4;
    cache[cacheIndex] = {pc, cycles};
}

void Chip8::executeInstruction() {
    uint8_t cycles = 0;

    if (retrieveCacheEntry(pc, cycles)) {
        consumeCycles(cycles);
    } else {
        // Execute the original logic to determine which opcode handler to invoke...
        storeCacheEntry(pc, cyclesTaken);
    }
    
    // Consume calculated cycles
    consumeCycles(cycles);
}
    return 0;
}