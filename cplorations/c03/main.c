/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] $William Erickson$
 * [TERM] FALL $2023$
 * 
 ****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{	
	if (argc != 2){
		//Exit if there isn't just one argument
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}else{
		FILE *fin = fopen(argv[1], "r");
		//check if failed to open
		if(fin == NULL){
			perror("Unable to open file!");
			exit(EXIT_FAILURE);
		}else{
			//create a string [filename].echo
			char out_file[sizeof(argv[1]) + sizeof(".echo")];
			strcpy(out_file, argv[1]);
			strcat(out_file, ".echo");
			
			FILE *fout = fopen(out_file, "w+");
			if (fout == NULL){
				perror("Unable to open file!");
				exit(EXIT_FAILURE);
			}
			char line[MAX_LINE_LENGTH] = {0};
			unsigned int line_num = 0;
			
			while (fgets(line, sizeof(line), fin) != NULL){
				line_num++;
				printf("[%04d] %s", line_num, line);
				fprintf(fout, "%s", line);
			}
			
			fclose(fout);
			fclose(fin);
			
		}
	}
	return 0;
}
