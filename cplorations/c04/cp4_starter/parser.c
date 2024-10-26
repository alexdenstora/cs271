/****************************************
 * C-ploration 4 for CS 271
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

#define MAX_LINE_LENGTH 200



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
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	//prints if this method is successfully called
	//printf("Parsing file...\n");

	// defines string line
	char line[MAX_LINE_LENGTH] = {0};

	//defines int var line_num as 0
	//unsigned int line_num = 0;
	
	/*
	while loop that runs as long as the file is not NULL
	calls the strip method for each line in the file
	then prints the line with the correct formatting and
	line num
	*/
	while(fgets(line, sizeof(line), file) != NULL){
		strip(line); //calling strip() method on line
		//line_num++;

		// checks if the pointer reaches the end of the line
		if(*line == '\0'){
			continue;
		}
		printf("%s\n", line);

	}
	
}