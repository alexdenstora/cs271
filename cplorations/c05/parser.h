/****************************************
 * C-ploration 5 for CS 271
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

#define MAX_LINE_LENGTH  200

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *line); // return true if address
bool is_label(const char *line); // return true if label
bool is_Ctype(const char *line); // return true if not an address or a label
