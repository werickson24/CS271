/****************************************
 * C-ploration 7 for CS 271
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
	int line_num = 0;
	
	while (fgets(line, sizeof(line), file) != NULL){
		
		strip(line);
		
		if(*line){
			line_num++;
			char inst_type = is_Atype(line) ? 'A' : '\0';
			inst_type = is_label(line) ? 'L' : inst_type;
			inst_type = is_Ctype(line) ? 'C' : inst_type;
			
			if(inst_type == 'L'){
				line_num--;
				char label_line[MAX_LABEL_LENGTH];
				extract_label(line, label_line);
				strcpy(line, label_line);
				
				symtable_insert(line, line_num);
			}
			
			
			printf("%u: %c  %s\n", line_num, inst_type, line);
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

char *extract_label(const char *line, char* label){
	int i = 0;
	//Line is taking i + 1 to simply ignore the lines first (
	while(line[i + 1] != ')' && i < MAX_LABEL_LENGTH){
		label[i] = line[i + 1];
		i++;
	}
	label[i] = '\0';
	return label;
}