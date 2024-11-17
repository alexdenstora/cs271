/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"

int main(int argc, const char *argv[])
{		
	/* 
	checks number of arguments
	if more or less than one, exits program
	else, continues
	*/
	if(argc < 2 && argc > 0){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
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
		perror("Unable to open input file!");
		exit(EXIT_FAILURE);
	}

	
	parse(fin); //calls parse method passing in the file
	
	fclose(fin); //closes file when done
			
}


