/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "hack.h"

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
int parse(FILE * file, instruction * instructions){
	
	char line[MAX_LINE_LENGTH];
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	instruction instr;
	
	add_predefined_symbols();
	
	while (fgets(line, sizeof(line), file) != NULL){
		//Likely off by one error in max compare
		if(instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		//printf("Line_num: %d, line: %s", line_num, line);
		strip(line);
		
		line_num++;
		if(*line){
			char inst_type = is_Atype(line) ? 'A' : '\0';
			inst_type = is_label(line) ? 'L' : inst_type;
			inst_type = is_Ctype(line) ? 'C' : inst_type;
			
			if(inst_type == 'L'){
				char label_line[MAX_LABEL_LENGTH];
				extract_label(line, label_line);
				strcpy(line, label_line);
				

				if(!isalpha(line[0])){
					exit_program(EXIT_INVALID_LABEL, line_num, line);
				}
				
				if(symtable_find(line) != NULL){
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
				}
				
				symtable_insert(line, instr_num);
			}else{
				if(inst_type == 'A'){
					if(parse_A_instruction(line, &instr.instrs.ainst)){
						instr.type = atype;
					}else{
						exit_program(EXIT_INVALID_A_INSTR, line_num, line);
					}
					instr_num++;
					
					
					//output for tester
					if(instr.instrs.ainst.is_addr){
						printf("A: %d\n", instr.instrs.ainst.atypes.address);
					}else{
						printf("A: %s\n", instr.instrs.ainst.atypes.label);
					}
					
				}else if(inst_type == 'C'){
					char tmp_line[MAX_LINE_LENGTH];
					strcpy(tmp_line, line);//copy line to avoid manipulating the original
					parse_C_instruction(tmp_line, &instr.instrs.cinst);
					instr.type = ctype;
					
					if(instr.instrs.cinst.dest == DEST_INVALID){
						//printf("dest invalid with value: %d\n", instr.instrs.cinst.dest);
						exit_program(EXIT_INVALID_C_DEST, line_num, line);
					}else if(instr.instrs.cinst.comp == COMP_INVALID){
						
						exit_program(EXIT_INVALID_C_COMP, line_num, line);
					}else if(instr.instrs.cinst.jump == JMP_INVALID){
						exit_program(EXIT_INVALID_C_JUMP, line_num, line);
					}
					
					//tester output
					printf("C: d=%d, c=%d, j=%d\n", instr.instrs.cinst.dest, instr.instrs.cinst.comp, instr.instrs.cinst.jump);
					instr_num++;
				}
				instructions[instr_num] = instr;
			}
		}
		
	}
	return instr_num;
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

bool parse_A_instruction(const char *line, a_instruction *instr){
	int line_length = strlen(line);
	char * s = (char *)malloc(line_length);
	
	/*for(int i = 1; i <= line_length; i++){
		s[i - 1] = line[i];
	}*/
	strcpy(s, line+1);
	
	char * s_end = NULL;
	long result = strtol(s, &s_end, 10);
	
	if(s == s_end){
		instr->atypes.label = (char *)malloc(line_length);
		strcpy(instr->atypes.label, s);
		instr->is_addr = false;
	}else if(*s_end != 0){
		return false;
	}else{
		instr->atypes.address = result;
		instr->is_addr = true;
	}
	return true;
	
}

void parse_C_instruction(char *line, c_instruction *instr){
	//tokenization process 
	// D = D + A;JMP
	// first token splits jump from instruction
	// D = D + A |;| JMP
	// second token splits instruction into dest and comp
	// D |=| D+A |;| JMP
	
	
	//split off instruction token
	char * instr_token = strtok(line, ";");
	//printf("instr_tokenization token: %s\n", instr_token);
	
	//store jump token
	char * jump_token = strtok(NULL, ";");
	//printf("jump_tokenization token: %s\n", jump_token);
	
	//split dest off instruction token
	char * dest_token = strtok(instr_token, "=");
	//printf("dest_tokenization token: %s\n", dest_token);
	
	//store comp token
	char * comp_token = strtok(NULL, "=");
	//printf("comp_tokenization token: %s\n", comp_token);

	//if comp is null, then we use dest in its place
	if(comp_token == NULL){
		comp_token = dest_token;
		dest_token = NULL;
	}
	
	int a = -1;
	instr->comp = str_to_compid(comp_token, &a);
	instr->a = a;
	
	instr->dest = str_to_destid(dest_token);
	
	instr->jump = str_to_jumpid(jump_token);
	
}

void add_predefined_symbols(){
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		predefined_symbol new_symbol = predefined_symbols[i];// watch that this is working properly
		symtable_insert(new_symbol.name, new_symbol.address);
	}
}