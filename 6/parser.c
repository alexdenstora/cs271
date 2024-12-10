/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
//#include "hack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>


#define MAX_LINE_LENGTH 200
//#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

void add_predefined_symbols(){
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		const char *name = predefined_symbols[i].name;
		int16_t address = predefined_symbols[i].address;

		symtable_insert(name, address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s = malloc(strlen(line));
	char *s_end = NULL;
	strcpy(s, line + 1);

	long result = strtol(s, &s_end, 10);

	if(s == s_end){
		instr->label = malloc(strlen(line));
		strcpy(instr->label, s);
		instr->is_addr = false;
	}
	else if(*s_end != 0){
		return false;
	}
	else{
		instr->address = result;
		instr->is_addr = true;
	}
	return true;
}

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	//sets int var to length of s
	unsigned int SIZE_OF_S = strlen(s);

	// sets s_new pointer to size of s + 1 
	char *s_new = malloc(SIZE_OF_S + 1);

	// sets int i var to 0
	unsigned int i = 0;

	/* 
	for loop that creates a temp file pointer s2
	then iterates through s2 
	*/
	for(char *s2 = s; *s2; s2++){

		// stops at beginning of a comment
		if(*s2 == '/' && *(s2+1) == '/'){
			break;
		}
		// adds non-white space chars
		else if(!isspace(*s2)){
			s_new[i++] = *s2;
		}
	}

	s_new[i] = '\0'; //adds null terminate to end of s_new

	strcpy(s, s_new); //copys s_new to s
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace & comments,
 * then assign each line a char marking it as an 
 * address, label, or c type function
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
//void parse(FILE * file, instruction *instructions){
int parse(FILE * file, instruction *instructions){
	//printf("starting parse method\n");

	// defines string line
	char line[MAX_LINE_LENGTH] = {0};

	//hack_addr line_num = 0;
	unsigned int line_num = 0;
	unsigned int inst_num = 0;

	char *tmp_line[MAX_LINE_LENGTH] = {0};


	instruction instr;


	add_predefined_symbols();

	/* While file is not NULL:
	 * Strips white space and comments from each line of the file
	 *
	 * Then assigns each line a char marking it 
	 * as an address, label, or c type function
	 *
	 * Prints the line with the correct formatting & label
	 */
	while(fgets(line, sizeof(line), file) != NULL){
		line_num++;
		if(inst_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}

		strip(line); //calling strip() method on line
		

		// checks if the pointer reaches the end of the line
		if(*line == '\0'){
			continue;
		}
		
		// declaring and initializing char var inst_type 
		// as an empty char
		char inst_type;

		// sets inst_type char to respective type 
		// if any of the booleans return true
		if(is_label(line)){
			inst_type = 'L';
			char label[MAX_LABEL_LENGTH];
			extract_label(line, label);

			if(!isalpha(label[0])){
				exit_program(EXIT_INVALID_LABEL, line_num, label);
			}
			if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
			}

			symtable_insert(label, inst_num);
			//printf("%c  %s\n", inst_type, label);
			//printf("A: %s\n", label);
			continue;

		}
		//line_num++;
		if(is_Atype(line)){
			inst_type = 'A';
			
			if(!parse_A_instruction(line, &instr.a_instr)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}

			instr.itype = A_TYPE;

			
			printf("A: %s\n", line + 1/*instr.a_instr*/);
			
		}
		
		if(is_Ctype(line)){
			inst_type = 'C';
			//printf("Processing line %d: '%s'\n", inst_num, line);

			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.c_instr);

			//******** FIX THESE *******
			if(instr.c_instr.dest == -1){
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			else if(instr.c_instr.comp == -1){
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			else if(instr.c_instr.jump == -1){
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			//END OF ERROR TESTING
			else {
				instr.itype = C_TYPE;
				printf("C: d=%d, c=%d, j=%d\n", instr.c_instr.dest, instr.c_instr.comp, instr.c_instr.jump);
			}
		}

		// THISprintf("%u: %c  %s\n", inst_num, inst_type, line);
		instructions[inst_num++] = instr;

		/*if (is_Atype(line) || is_Ctype(line)) {
            line_num++;  // Increment PC for each instruction
        }*/

		// prints char and line from file after being 
		// stripped & assigned a type
		//printf("%c  %s\n", inst_type, line);
	}
	//free(tmp_line);
	//printf("finished parse method\n");
	return inst_num;
}

/*	Function is Address | is label | is c-type
 * -----------------------------------------
 * Address returns true if first char of line is '@'
 *
 * Label returns true if first & last char are '(' & ')'
 *
 * C-Type returns true if the line is not an address or a label
 *	
 * All booleans return false if line is NULL
 *
 */

bool is_Atype(const char *line){
	return line != NULL && line[0] == '@';

}

bool is_label(const char *line){
	return line != NULL && line[0] == '(' && line[strlen(line) - 1] == ')';
}

bool is_Ctype(const char *line){
	return line != NULL && !is_Atype(line) && !is_label(line);
}



char *extract_label(const char *line, char *label){
	//label = malloc(MAX_LABEL_LENGTH);

	if(is_label(line)){
		int16_t len = strlen(line) - 2;
		strncpy(label, line + 1, len);

		label[len] = '\0';

		return label;
	}
	else {
		return NULL;
	}
}


void parse_C_instruction(char *line, c_instruction *instr){
	//printf("starting parse_c_instruction\n");

	// If line is empty or only whitespace, return early
    /*if (line == NULL || strlen(line) == 0 || isspace(line[0])) {
        printf("ERROR: Invalid instruction string '%s'\n", line);
        exit_program(EXIT_INVALID_C_COMP);
    }*/

	char line_copy[MAX_LINE_LENGTH];
	//printf("parse_C_instruction received line: '%s'\n", line);
	strcpy(line_copy, line);
	line_copy[MAX_LINE_LENGTH - 1] = '\0';
	//printf("line_copy after strcpy: '%s'\n", line_copy);



	// initializing fields of instruction to default
	instr->a = 0;
	instr->comp = COMP_INVALID;
	instr->dest = DEST_INVALID;
	instr->jump = JMP_INVALID;

	// tokenizing the string into jump, dest, & comp parts
	char *temp = strtok(line_copy, ";");
	char *jump_part = strtok(NULL, ";");

	if(temp == NULL){
		fprintf(stderr, "ERROR: Invalid instruction string '%s'\n", line);
		exit_program(EXIT_INVALID_C_COMP);
	}
	

	char *dest_part = strtok(temp, "=");
	char *comp_part = strtok(NULL, "=");

	// Debugging print to see dest_part and comp_part
	//printf("DEBUG: Before validation - dest_part='%s', comp_part='%s'\n",
    //    dest_part ? dest_part : "(null)", comp_part ? comp_part : "(null)");

	// edge case where comp_part is actually dest_part
	if(comp_part == NULL){
		comp_part = dest_part;
		dest_part = NULL;
	}

	// Debugging print to confirm updated dest_part and comp_part
	// printf("DEBUG: After handling edge case - dest_part='%s', comp_part='%s'\n",
    //    dest_part ? dest_part : "(null)", comp_part ? comp_part : "(null)");

	// setting fields in the instruction
	int a_bit = 0;
	instr->comp = str_to_compid(comp_part, &a_bit);
	instr->dest = dest_part ? str_to_destid(dest_part) : DEST_NULL;
	// Debugging print to verify the destination ID
	//printf("DEBUG: Destination ID mapped for '%s' = %d\n",
    //    dest_part ? dest_part : "(null)", instr->dest);

	instr->jump = jump_part ? str_to_jumpid(jump_part) : JMP_NULL;
	instr->a = a_bit;

	//printf("finished parse_c_instruction\n");
	//printf("Parsed C-instruction: dest='%s', comp='%s', jump='%s'\n", 
    //        dest_part ? dest_part : "(null)", 
    //        comp_part ? comp_part : "(null)", 
    //        jump_part ? jump_part : "(null)");
}

void assemble(const char *file_name, instruction instructions, int num_instructions){
	const char *extension = ".hack";
	int newStringLength = strlen(file_name) + strlen(extension) + 1;
	
	char *new_file_name = (char*)malloc(newStringLength);
	
	strcpy(new_file_name, file_name);
	strcat(new_file_name, extension);

	int next_sym_index = 16;

	for(int i = 0; i < num_instructions; i ++){
		// if instruction is an address, check if address is a label
		// if true, search for opcode in symtable
		// if returns NULL, add label to symtable
		// else, 
		if(instructions[i].itype == A_TYPE){
			a_instruction a_instr = instructions[i].a_instr;
			if(!a_instr.is_addr){
				struct Symbol *symbol = symtable_find(a_instr.label);
				if(symbol == NULL){
					symtable_insert(a_instr.label, next_sym_index);
					instructions[i].opcode = next_sym_index++;
				}
				else{
					instructions[i].opcode = symbol->addr;
				}
			}
			else{
				instructions[i].opcode = a_instr.address;
			}
			
		}
		if else(instructions[i].itype == C_TYPE){

		}
	}
}

opcode instruction_to_opcode(c_instruction instr){
	opcode op = 0;
	op != (7 << 13);
	op != (a_bit << 12);
	op != (comp_part << 6);
	op != (dest_part << 3);
	op != (jump_part << 0);

	return op;
}





