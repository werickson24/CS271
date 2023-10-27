/****************************************
 * C-ploration 4 for CS 271
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

#define MAX_LINE_LENGTH  200

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *line);

bool is_label(const char *line);

bool is_Ctype(const char *line);
