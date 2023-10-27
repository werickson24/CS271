/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	char s_new[strlen(s) + 1];
	
	int i = 0;
	
	for(char *s2 = s; *s2; s2++){
		if(*s2 == '/' && *(s2 + 1) == '/'){
			break;
		}else if(isspace(*s2)){
			continue;
		}else{
			s_new[i++] = *s2;
		}
		//printf("processing char %c at index %d", *s2, i);
	}
	
	s_new[i] = '\0';
	
	strcpy(s, s_new);
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	
	char line[MAX_LINE_LENGTH];
	
	while (fgets(line, sizeof(line), file) != NULL){
		
		strip(line);
		
		if(*line){
			char inst_type = is_Atype(line) ? 'A' : '\0';
			inst_type = is_label(line) ? 'L' : inst_type;
			inst_type = is_Ctype(line) ? 'C' : inst_type;
			printf("%c  ", inst_type);
			printf("%s\n", line);
		}
		
	}
	
}

bool is_Atype(const char *line){
	char Astart = '@';
	return (*line == Astart);
}

bool is_label(const char *line){
	int end_index = strlen(line) - 1;
	if(*line == '(' && *(line + end_index) == ')'){
		return true;
	}else{
		return false;
	}
	
}

bool is_Ctype(const char *line){
	if(!is_Atype(line) && !is_label(line)){
		return true;
	}else{
		return false;
	}
}