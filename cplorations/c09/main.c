/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
instruction instr = {0};  // Initialize the whole instruction to zero


int main(int argc, const char *argv[])
{		
	/* 
	if incorrect number of arguments
	*/
	if(argc != 2){
		//printf("Usage: %s [filename]\n", argv[0]);
		//exit(EXIT_FAILURE);
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}

	/* 
	creates new file pointer and opens file
	given in argument in read setting
	*/
	FILE *fin = fopen( argv[1], "r" );

	/*
	if file is empty, exits program
	else, continues
	*/
	if(fin == NULL){
		//perror("Unable to open input file!");
		//exit(EXIT_FAILURE);
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}

	
	parse(fin); //calls parse method passing in the file
	symtable_print_labels();
	//symtable_display_table();
	fclose(fin); //closes file when done
			
}


