/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

enum instr_type{
	invalid = -1,
	atype,
	ctype
};

typedef int16_t hack_addr;
typedef int16_t opcode;
typedef struct c_instruction{
	opcode a:1;
	opcode comp:7;
	opcode dest:3;
	opcode jump:3;
} c_instruction;

typedef struct a_instruction{
	
	union atypes{
		hack_addr address;
		char * label;
	} atypes;
	
	bool is_addr;
	
} a_instruction;

typedef struct instruction{
	union instrs{
		a_instruction ainst;
		c_instruction cinst;
	} atypes;
	enum instr_type type;
} instruction;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *line);

bool is_label(const char *line);

bool is_Ctype(const char *line);

char *extract_label(const char *line, char* label);
