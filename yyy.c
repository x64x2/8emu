#include <stdio.h>
#include <stdint.h>
#include <dynarec/dynarec.h>

// Define the Chip-8 instruction set
enum {
    OP_CLR = 0x00,
    OP_SET = 0x01,
    OP_ADD = 0x02,
    OP_SUB = 0x03,
    OP_MUL = 0x04,
    OP_DIV = 0x05,
    OP_MOD = 0x06,
    OP_SHL = 0x07,
    OP_SHR = 0x08,
    OP_AND = 0x09,
    OP_OR = 0x0A,
    OP_XOR = 0x0B,
    OP_NOT = 0x0C,
};

// Represent a Chip-8 register
typedef uint8_t reg_t;

// Represent a Chip-8 instruction
struct instruction {
    uint8_t opcode;
    reg_t r1;
    reg_t r2;
    reg_t r3;
};

// Compile a Chip-8 instruction into IR code
void compile_instruction(struct instruction *instr, void **ir_out) {
    // Switch on the opcode
    switch (instr->opcode) {
        case OP_CLR:
            // Emit a mov r0, #0 instruction
            *ir_out = dynarec_emit_mov(NULL, 0, 0, 0);
            break;
        case OP_SET:
            // Emit a mov r0, r1 instruction
            *ir_out = dynarec_emit_mov(NULL, instr->r1, 0, 0);
            break;
        case OP_ADD:
            // Emit a add r0, r1, r2 instruction
            *ir_out = dynarec_emit_mov(NULL, instr+>r1, 0+r2)


    }
    return 0;
}

   