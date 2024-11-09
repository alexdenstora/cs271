/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>


#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2



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
void parse(FILE * file){

	// defines string line
	char line[MAX_LINE_LENGTH] = {0};
	
	/* While file is not NULL:
	 * Strips white space and comments from each line of the file
	 *
	 * Then assigns each line a char marking it 
	 * as an address, label, or c type function
	 *
	 * Prints the line with the correct formatting & label
	 */
	while(fgets(line, sizeof(line), file) != NULL){
		strip(line); //calling strip() method on line
		

		// checks if the pointer reaches the end of the line
		if(*line == '\0'){
			continue;
		}
		// declaring and initializing char var inst_type 
		// as an empty char
		char inst_type = ' ';

		// sets inst_type char to respective type 
		// if any of the booleans return true
		if(is_Atype(line)){
			inst_type = 'A';
		}
		if(is_label(line)){
			inst_type = 'L';
			char label[MAX_LABEL_LENGTH];
			extract_label(line, label);
			printf("%c  %s\n", inst_type, label);
			continue;

		}
		if(is_Ctype(line)){
			inst_type = 'C';
		}

		// prints char and line from file after being 
		// stripped & assigned a type
		printf("%c  %s\n", inst_type, line);

	}
	
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
