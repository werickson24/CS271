/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{
	if(argc == 2){
		
		FILE *fin = fopen(argv[1], "r");
		
		if(fin != NULL){
			
			parse(fin);
			symtable_print_labels();
			
			fclose(fin);
			
		}else{
			perror("Unable to open file!");
			exit(EXIT_FAILURE);
		}
	}else{
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}


