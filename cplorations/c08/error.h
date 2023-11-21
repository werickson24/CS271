#define __ERROR_H__
#ifndef __ERROR_H__

#include <stdarg.h>

typedef enum exitcode{
	/*
	* Error code 1 represents that given file does not exist.
	*/
	EXIT_INCORRECT_ARGUMENTS = 1,
	
} exitcode;

void exit_program(enum exitcode code, ...);

#endif