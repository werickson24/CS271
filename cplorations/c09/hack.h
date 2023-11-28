#ifndef __HACK_H__
#define __HACK_H__

#define NUM_PREDEFINED_SYMBOLS 23

typedef enum symbol_id {
	SYM_R0 = 0,
	SYM_R1,
	SYM_R2,
	SYM_R3,
	SYM_R4,
	SYM_R5,
	SYM_R6,
	SYM_R7,
	SYM_R8,
	SYM_R9,
	SYM_R10,
	SYM_R11,
	SYM_R12,
	SYM_R13,
	SYM_R14,
	SYM_R15,
	
	SYM_SP = 0,
	SYM_LCL,
	SYM_ARG,
	SYM_THIS,
	SYM_THAT,
	
	SYM_SCREEN = 16384,
	SYM_KBD = 24576
	
} symbol_id;

typedef struct predefined_symbol {
	//mentioned in the instructions but not sure what it means yet
	//Make sure your string is long enough to hold the longest name among the predefined symbols.
	char * name[11],
	int16_t address
} predefined_symbol;

#endif