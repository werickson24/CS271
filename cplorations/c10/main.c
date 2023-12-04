/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{
	if(argc == 2){
		
		FILE *fin = fopen(argv[1], "r");
		
		if(fin != NULL){
			instruction * instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
			
			//int num_instructions = 
			parse(fin, instructions);
			
			//symtable_print_labels();
			
			//printf("num_instructions: %d", num_instructions);
			fclose(fin);
			free(instructions);
		}else{
			exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
		}
	}else{
		// incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]); 
	}
}


