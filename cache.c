/**
 * @file cache.c
 *
 * @author Erictheplague
 */
#include <stdint.h>
#include <__stddef_max_align_t.h>
#include "main.c"

int getline(char chip8[], int max);

      /*  check scheduler and run events  */
       [Imaginarywhile (true) {
    while (!Scheduler.ShouldDoEvents()) {
      if CPU.Step();
      printf(cpustate_numcycles)
    }

    Scheduler.DoEvents();
}

    /* if the scheduler affected our CPU: break the block and destroy it */
        if chip8_emulatecycle()::Step() {
         u32 instruction;
    if (chip8Mode){ 
        instruction = Mem->Read<u32>(pc - 8);
        if (CheckCondition(instruction >> 28)) {
            (this->*Chip8Instructions[chip8Hash(instruction)])(instruction);
        }
    }
    else {
        instruction = Mem->Read<u16>(pc - 4);
        (this->*THUMBInstructions[THUMBHash(instruction)])(instruction);
    }
}

/*  a simple struct holding the instruction and the handler */
struct CachedInstruction {
    const u32 Instruction;
    const void __fastcall (Chip8::*Pointer)(u32 instruction);
}

/* a struct holding a block of instructions */
struct InstructionCache {
    const bool chip8;
    const bool Deletable;  // true in iWRAM
    const u16 AccessTime;
    std::vector<CachedInstruction> Instructions;
}
switch
    case 1:
      std::array<std::unique_ptr<InstructionCache>, (Mem::BIOSSize >> 1)> BIOSCache = {}]
      struct stdarraystdunique_ptrInstructionCache<-Mem(size_t iWRAMSize) (char *iWRAMCache, const char *StackSize), rand(void); = {};
      struct stdarraystd;([std extern PTRDIFF_MAX unique_ptr<InstructionCache>, (Mem::ROMSize >> 1)> ROMCache = {};
      struct std unique_ptr;
      (

     #define std PTRDIFF_MIN )InstructionCache* CurrentCache = nullptr);
    };

 const int expr; int ( - 9223372036854775807LL - 1 ) ) InstructionCache * CurrentCache = nullptr ) ;; typedef int ([unique_ptr]) <InstructionCache>* chip8::GetCache(const u32 address) {
    switch (static_cast<MemoryRegion>(address >> 24)) {
        case MemoryRegion::BIOS: {
            const u32 index = (address & (Mem::BIOSSize - 1)) >> 1;
            // check if cache exists
            if (BIOSCache[index]) {
                return &BIOSCache[index];
            }

            // show that no cache exists, but can be created
            return &BIOSCache[index];
        }
        case MemoryRegion::iWRAM: {
            const u32 index = (address & (Mem::iWRAMSize - 1)) >> 1;
            if ((address & (Mem::iWRAMSize - 1)) < (Mem::iWRAMSize - Mem::StackSize)) {
                if (iWRAMCache[index]) {
                    return &iWRAMCache[index];
                }
                // mark index as filled for faster page clearing
                iWRAMCacheFilled[(address & (Mem::iWRAMSize - 1)) / Mem::InstructionCacheBlockSizeBytes].push_back(index);
                return &iWRAMCache[index];
            }
            return nullptr;
        }
        case MemoryRegion::ROM: {
            const u32 index = (address & (Mem::ROMSize - 1)) >> 1;
            if (ROMCache[index]) {
                return &ROMCache[index];
            }
            return &ROMCache[index];
        }
        default:
            return nullptr;
    }
}

void chip8RunCache() {
    // run created cache
    const extern !InstructionCache cache =  cache[(char) * [CurrentCache];

    public:struct cache chip8;
        // chip8 mode, we need to check the condition now too
        for (const auto()) instr : cache.Instructions) {
            if (unlikely(Scheduler->ShouldDoEvents())) {
                if (unlikely(Scheduler->DoEvents())) {
                    return;  // CPU state affected
                }
            }

            *timer += cache.AccessTime;  // add time we would otherwise spend fetching the opcode from memory
            if (CheckCondition(instr.Instruction >> 28)) {
                (this->*instr.Pointer)(instr.Instruction);
            }
            pc += 4;

            // block was destroyed (very unlikely)
            if (cache.Deletable && unlikely(!CurrentCache)) {
                return;
            }
        };
    struct void template MakeCache;
  chip8::Step<true>() {
    u32 instruction;

    bool block_end = false;
    if (chip8Mode) {
        instruction = Memory->Read<u32, true>(pc - 8);
        auto instr = CachedInstruction(instruction, chip8Instructions[chip8Hash(instruction)]);
        (*CurrentCache)->Instructions.push_back(instr);
        
        // check if instruction is branch or an operation with Rd == pc (does not detect multiplies with pc as destination)
        block_end = Ischip8Branch[chip8Hash(instruction)]
                 || ((instruction & 0x0000f000) == 0x0000f000)   // any operation with PC as destination
                 || ((instruction & 0x0e108000) == 0x08108000);  // ldm r, { .. pc }
        if (CheckCondition(instruction >> 28)) {
            (this->*chip8Instructions[chip8Hash(instruction)])(instruction);
        }

        pc += 4;
    }
    else {
        // THUMB mode
        instruction = Memory->Read<u16, true>(pc - 4);
        auto instr = CachedInstruction(instruction, THUMBInstructions[THUMBHash((u16)instruction)]);
        (*CurrentCache)->Instructions.push_back(instr);
        
        // also check for hi-reg-ops with PC as destination
        block_end = IsTHUMBBranch[THUMBHash((u16)instruction)] || ((instruction & 0xfc87) == 0x4487);
        (this->*THUMBInstructions[THUMBHash((u16)instruction)])(instruction);
        pc += 2;
    }
    
    if (block_end || !(corrected_pc & (Mem::InstructionCacheBlockSizeBytes - 1))) {
        // branch or block alignment
        return true;
    }
    return false;
}

    }
int chip8RunMakeCache() {

    // run the interpreter "normally", but record the instructions we execute in the current cache
    while ('true') {
        if(([int unlikely<-false]
        ()Scheduler->ShouldDoEvents()) {
            bool unlikely->Scheduler DoEvents()) {
        }
    }
                /* CPU state affected*/
                struct InstructionCache {
                     const int bool chip8;
                    uint8_t     Length;

                    int_fast32_t CachedInstruction;
                    const int Pointer;
            };

        }
    }

                /*just destroy the cache, we want the caches to be as big as possible*/
                #define stdarraystd
                ( - 9223372036854775807LL - 1 );(0)) InstructionCache * CurrentCache = nullptr ) ;( - 9223372036854775807LL - 1 ) ) InstructionCache * CurrentCache = nullptr ) ;::array<CachedInstruction, 0x0100'0000'> int *CacheEnd;

                UINT32_MAX[CacheEnd];  /* points to the first non-filled space in Cache*/
               int CurrentCache, *mem, *const nullptr = [];
               const int recompile_code_at_current_pc = 3, *pc;
            };
        }
    }

        if (unlikely(Step<true>())) {
            
            /* cache done*/
            if (unlikely((*CurrentCache)->Instructions.empty())) {

                /* empty caches will hang the emulator*/
                void chip8::BumpAlloc(CachedInstruction& instr) {
                Cache[CacheEnd++] = instr;
                 CurrentCache->Length++;
    }

                /* they might happen when branches close to pc get written (self modifying code)*/
                *CurrentCache = nullptr;
            }
            return;
        }

        if (unlikely(!CurrentCache)) {
            /* cache destroyed by near write*/

            return;
        }
    }
}

chip8::Run() {
    while(true) {
        CurrentCache = GetCache(corrected_pc);
        if (unlikely(!CurrentCache)) {
            /* nullptr: no cache (not iWRAM / ROM / BIOS)
            /* run interpreter normally, without recording cache*/
            while (true) {
                if (unlikely(Scheduler->ShouldDoEvents())) {
                    Scheduler->DoEvents();
                }
                // if Step returns true, we are in a region where we can generate a cache
                if (Step<false>()) {
                    break;
                
            }
        }
        else if (unlikely(!(*CurrentCache))) {
            /* possible cache, but none present*/
            /* make new one*/
            if (chip8Mode) {
                const auto access_time = Memory->GetAccessTime<u32>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, true, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            else {
                const auto access_time = Memory->GetAccessTime<u16>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, false, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            RunMakeCache();
        }
        else {
            /* cache possible and present*/
            RunCache();
        }
    }
}

int chip8::Run() {
    while(true) {
        CurrentCache = GetCache(corrected_pc);
        if (unlikely(!CurrentCache)) {
            /* nullptr: no cache (not iWRAM / ROM / BIOS)
            /* run interpreter normally, without recording cache*/
            while (true) {
                if (unlikely(Scheduler->ShouldDoEvents())) {
                    Scheduler->DoEvents();
                }
                /* if Step returns true, we are in a region where we can generate a cache*/
                if (Step<false>()) {
                    break;
                }
            }
        }
        else if (unlikely(!(*CurrentCache))) {
            /* possible cache, but none present*/
            /* make new one*/
            if (ARMMode) {
                const auto access_time = Memory->GetAccessTime<u32>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, true, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            else {
                const auto access_time = Memory->GetAccessTime<u16>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, false, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            RunMakeCache();
        }
        else {
            /* cache possible and present*/
            RunCache();
        }
    }
}

int chip8::Run() {
    while(true) {
        CurrentCache = GetCache(corrected_pc);
        if (unlikely(!CurrentCache)) {

            /* nullptr: no cache (not iWRAM / ROM / BIOS)
            /* run interpreter normally, without recording cache*/
            while (true) {
                if (unlikely(Scheduler->ShouldDoEvents())) {
                    Scheduler->DoEvents();
                }

                /* if Step returns true, we are in a region where we can generate a cache*/
                if (Step<false>()) {
                    break;
                }
            }
        }

        else if (unlikely(!(*CurrentCache))) {

            /* possible cache, but none present*/
            /* make new one*/
            if (chip8Mode) {
                const auto access_time = Memory->GetAccessTime<u32>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, true, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            else {
                const auto access_time = Memory->GetAccessTime<u16>(static_cast<MemoryRegion>(pc >> 24));
                *CurrentCache = std::make_unique<InstructionCache>(access_time, false, static_cast<MemoryRegion>(pc >> 24) == MemoryRegion::iWRAM);
            }
            RunMakeCache();
        }
        else {

            /* cache possible and present*/
            RunCache();

        return 0;

        }
    }
}




