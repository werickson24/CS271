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

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0},
    {"R1", SYM_R1},
	{"R2", SYM_R2},
	{"R3", SYM_R3},
	{"R4", SYM_R4},
	{"R5", SYM_R5},
	{"R6", SYM_R6},
	{"R7", SYM_R7},
	{"R8", SYM_R8},
	{"R9", SYM_R9},
	{"R10", SYM_R10},
	{"R11", SYM_R11},
	{"R12", SYM_R12},
	{"R13", SYM_R13},
	{"R14", SYM_R14},
	{"R15", SYM_R15},
	
	{"SP", SYM_SP},
	{"LCL", SYM_LCL},
	{"ARG", SYM_ARG},
	{"THIS", SYM_THIS},
	{"THAT", SYM_THAT},
	
	{"SCREEN", SYM_SCREEN},
	{"KBD", SYM_KBD}
    
};

#endif