#include "error.h"
#include <stdio.h> 
#include <stdlib.h> 

const char *error_messages[] =
{
	[EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
	[EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
	[EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions",
	[EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
	[EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
	[EXIT_INVALID_A_INSTR] = "Line %u: %s : Invalid A-instruction operand",
	[EXIT_INVALID_C_DEST] = "Line %u: %s : Invalid destination part of C-instruction",
	[EXIT_INVALID_C_COMP] = "Line %u: %s : Invalid compare part of C-instruction",
	[EXIT_INVALID_C_JUMP] = "Line %u: %s : Invalid jump part of C-instruction",
};

void exit_program(enum exitcode code, ...){
	//printf("Debug:  exit_program called with code %d\n", code);
	//printf("Array size: %zu\n", sizeof(error_messages) / sizeof(error_messages[0]));

	va_list arguments;
	va_start(arguments, code);

	printf("ERROR: ");
	/*if(code < 0 || code >= sizeof(error_messages) / sizeof(error_messages[0])) {
		printf("Invalid error code\n");
	}
	else {
		vfprintf(stdout, error_messages[code], arguments);
	}*/
	vfprintf(stdout, error_messages[code], arguments);
	printf("\n");

	va_end(arguments);
	exit(code);
}