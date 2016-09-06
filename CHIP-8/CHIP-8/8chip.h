#pragma once

#ifndef CHIP8_BIT
#define	CHIP8_BIT

class chip8 
{
	// Current opcode
	unsigned short opcode;			
	// Registers (V0-VF)
	unsigned char V[16];		

	// Index register and Program counter from 0x000 to 0xFFF
	unsigned short I;			
	unsigned short pc;			

	// Memory (4K)
	unsigned char memory[4096];	

	// Timers
	unsigned char delay_timer;
	unsigned char sound_timer;

	// Stack and stack pointer
	unsigned short stack[16];
	unsigned short sp;
	
public:
	// Graphics, Black and White with 2048 pixels of screen (64x32)
	unsigned char gfx[64 * 32];
	// Keypad
	unsigned char key[16];

	bool drawFlag;

	chip8();
	~chip8();
	void init();
	void emulateCycle();
	void debugRender();
	bool loadApplication(const char * filename);
};

/* NOTES
-	Memory map
		0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
		0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
		0x200-0xFFF - Program ROM and work RAM	

-	The Chip 8 has 35 opcodes.
-	CPU registers: The Chip 8 has 15 8-bit general purpose registers named V0,V1 up to VE.
	The 16th register is used  for the ‘carry flag’

-	Interupts and hardware registers. The Chip 8 has none, but there are two timer registers that count at 60 Hz.
	When set above zero they will count down to zero.

-	The graphics system: The chip 8 has one instruction that draws sprite to the screen.
	Drawing is done in XOR mode and if a pixel is turned off as a result of drawing, the VF register is set.
	This is used for collision detection.

-	The system’s buzzer sounds whenever the sound timer reaches zero.
*/

#endif // !CHIP8_BIT