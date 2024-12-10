/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

//void parse(FILE * file, instruction *instructions);
void add_predefined_symbols();

bool is_Atype(const char *line); // return true if address
bool is_label(const char *line); // return true if label
bool is_Ctype(const char *line); // return true if not an address or a label



char *extract_label(const char *line, char *label);


/** enums **/
enum instr_type{
	INVALID = -1,
	A_TYPE,
	C_TYPE,
};

/** structs **/
typedef struct c_instruction{
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;

} c_instruction;

typedef struct a_instruction{
	union{
		hack_addr address;
		char *label;
		//char *type_label;
	};
	bool is_addr;
}a_instruction;

typedef struct instruction{
	enum instr_type itype;
	union{
		a_instruction a_instr;
		c_instruction c_instr;
	};
}instruction;

//void parse(FILE * file, instruction *instructions);
int parse(FILE * file, instruction *instructions);

bool parse_A_instruction(const char *line, a_instruction *instr);

void parse_C_instruction(char *line, c_instruction *instr);

#endif





