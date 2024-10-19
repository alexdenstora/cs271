/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH  200

int main(int argc, const char *argv[]){	

	//initialization of variables
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;

	// if incorrect number of arguments print error
	// and exit program
	if(argc < 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// create output file
	char out_file[MAX_LINE_LENGTH];
	strcpy(out_file, argv[1]); //copy file name to out_file 
	strcat(out_file, ".echo"); //concatentate .echo to out_file

	// attempt to open file specified by user arguments
	// with intention to read only (r)
	// if NULL, print error and exit program
	FILE *fin = fopen( argv[1], "r" );
	if(fin == NULL){
		perror("Unable to open input file!");
		exit(EXIT_FAILURE);
	}

	// attempt to open output file with intention to write (w+)
	// if NULL, print error and exit program
	FILE *fout = fopen( out_file, "w+" );
	if (fout == NULL){
		perror("Unable to open output file!");
		exit(EXIT_FAILURE);
	}


	while (fgets(line, sizeof(line), fin)) { //loops through input file line by line
		line_num++; // increments line_num by 1 each iteration
		printf("[%04d] %s", line_num, line); // prints line content and num to console
		fprintf(fout, "%s", line); // writes each line to output file
	}

	//closes input & output file
	fclose(fin);
	fclose(fout);
	


}
