#ifndef __PARSER_H__
#define __PARSER_H__


/****************************************
 * C-ploration 10 for CS 271
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
#include "error.h"
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

enum instr_type{
	invalid = -1,
	atype,
	ctype
};

typedef int16_t hack_addr;
typedef int16_t opcode;
typedef struct c_instruction{
	opcode a:1;
	opcode comp:6;//THESE WERE +1 FOR SOME REASON, MAke SURE THIS still WOR NOW
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
	} instrs;
	enum instr_type type;
} instruction;

/** function prototypes **/
char *strip(char *s);

int parse(FILE * file, instruction * instructions);

void assemble(const char * file_name, instruction* instructions, int num_instructions);

opcode instruction_to_opcode(c_instruction instr);

bool is_Atype(const char *line);

bool is_label(const char *line);

bool is_Ctype(const char *line);

char *extract_label(const char *line, char* label);

bool parse_A_instruction(const char *line, a_instruction *instr);

void parse_C_instruction(char *line, c_instruction *instr);

void add_predefined_symbols();

#endif