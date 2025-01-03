/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] ALEXANDER SAHLSTROM
 * [TERM] FALL 2024
 * 
 ****************************************/
#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SYMBOL_TABLE_SIZE  1000

typedef int16_t hack_addr;

typedef struct Symbol {
	hack_addr addr;
	char *name;

} Symbol;

int hash(char *str);
struct Symbol *symtable_find(char * key);
void symtable_insert(char *key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif