/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

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
	opcode dest:3;
	opcode jump:3;

} c_instruction;

typedef struct a_instruction{
	union{
		hack_addr address;
		char *type_label;
	};
	bool is_addr;
}a_instruction;

typedef struct instruction{
	union{
		a_instruction a_instr;
		c_instruction c_instr;
	};
}instruction;






