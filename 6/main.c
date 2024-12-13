/****************************************
 * Project 6 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{
	//printf("Before malloc of instructions in main\n");
	instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
	//printf("After malloc of instructions in main\n");
	int num_instructions;
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

	num_instructions = parse(fin, instructions); //calls parse method passing in the file
	fclose(fin); //closes file when done
	assemble(argv[1], instructions, num_instructions);
	free(instructions);
}


