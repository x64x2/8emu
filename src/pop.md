
* Set Vx = Vx AND Vy */
/* Quirk mode: Reset flag register */
void
OP_8xy2()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	if (qvf) {
		registers[0xF] = 0;
	}

	registers[Vx] &= registers[Vy];
}

/* Set Vx = Vx XOR Vy */
/* Quirk mode: Reset flag register */
void
OP_8xy3()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	if (qvf) {
		registers[0xF] = 0;
	}

	registers[Vx] ^= registers[Vy];
}

/* Set Vx = Vx + Vy, set VF = carry */
void
OP_8xy4()
{
	uint8_t carry = 0;
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint16_t sum = registers[Vx] + registers[Vy];

	if (sum > 255) {
		carry = 1;
	}

	registers[Vx] = sum & 0xFF;
	registers[0xF] = carry;
}

/* Set Vx = Vx - Vy, set VF = NOT borrow */
void
OP_8xy5()
{
	uint8_t carry = 1;
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t diff = registers[Vx] - registers[Vy];

	if (registers[Vx] < registers[Vy]) {
		carry = 0;
	}

	registers[Vx] = diff;
	registers[0xF] = carry;
}

/* Shift Vx right by 1
 * Quirk mode: Copy Vy to Vx and shift Vx right by 1 */
void
OP_8xy6()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t lsb;

	/* Save least significant bit in VF */
	lsb = (registers[Vx] & 0x1);

	if (!qshift) {
		registers[Vx] = registers[Vy];
	}

	registers[Vx] >>= 1;
	registers[0xF] = lsb;
}

/* Set Vx = Vy - Vx, set VF = NOT borrow */
void
OP_8xy7()
{
	uint8_t carry = 1;
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t diff = registers[Vy] - registers[Vx];

	if (registers[Vy] < registers[Vx]) {
		carry = 0;
	}

	registers[Vx] = diff;
	registers[0xF] = carry;
}


/* Shift Vx left by 1
 * Quirk mode: Copy Vy to Vx and shift Vx left by 1 */
void
OP_8xyE()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t lsb;

	/* Save least significant bit in VF */
	lsb = (registers[Vx] & 0x80) >> 7;

	if (!qshift) {
		registers[Vx] = registers[Vy];
	}

	registers[Vx] <<= 1;
	registers[0xF] = lsb;
}

/* Skip next instruction if Vx != Vy */
void
OP_9xy0()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	if (registers[Vx] != registers[Vy]) {
		pc += 2;
	}
}


/* Set Vx = random byte AND kk */
void
OP_Cxkk()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = opcode & 0x00FF;

	registers[Vx] = (rand() % 256) & byte;
}


* Skip next instruction if key with value of Vx is pressed */
void
OP_Ex9E()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t key = registers[Vx];

	if (keypad[key]) {
		pc += 2;
	}
}

/* Skip next instruction if key with value of Vx is not pressed */
void
OP_ExA1()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t key = registers[Vx];

	if (!keypad[key]) {
		pc += 2;
	}
}

/* Set Vx = delay timer value */
void
OP_Fx07()
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	registers[Vx] = delayTimer;
}