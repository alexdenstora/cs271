#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>

enum exitcode{
	/*
	*	Error code 1 represents the number of given arguments is incorrect
	* 	Error code 2 represents that given file does not exist
	* 	Error code 3 represents that the number of instructions in the file has exceeded the max
	*	Error code 4 represents that the value is not a valid label
	*	Error code 5 represents that the label already exists in the hash table
	*/
	EXIT_INCORRECT_ARGUMENTS = 1,
	EXIT_CANNOT_OPEN_FILE = 2,
	EXIT_TOO_MANY_INSTRUCTIONS = 3,
	EXIT_INVALID_LABEL = 4,
	EXIT_SYMBOL_ALREADY_EXISTS = 5,
	EXIT_INVALID_A_INSTR = 6,
	EXIT_INVALID_C_DEST = 7,
	EXIT_INVALID_C_COMP = 8,
	EXIT_INVALID_C_JUMP = 9,

};

void exit_program(enum exitcode code, ...);

#endif