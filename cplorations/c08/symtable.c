#include "symtable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str){
	unsigned long hash = 5381;
	int c = 0;

	while ((c = *str++)){
		hash = ((hash << 5) + hash) + c;
	}
	return hash % SYMBOL_TABLE_SIZE;
}

/** 
 * Search function
 */
struct Symbol *symtable_find(char* key){
	int hashIndex = hash(key);

	while(hashArray[hashIndex] != NULL){
		if(strcmp(hashArray[hashIndex] -> name, key) == 0){
			return hashArray[hashIndex];
		}

		hashIndex++;
		hashIndex %= SYMBOL_TABLE_SIZE;
	}
	return NULL;
}

/** 
 * Insert function
 */

void symtable_insert(char *key, hack_addr addr){
	struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
	if(item == NULL){
		perror("Memory allocation failed for symbol");
		exit(EXIT_FAILURE);
	}

	item -> addr = addr;
	item -> name = strdup(key);

	if (item->name == NULL) {
        perror("Memory allocation failed for symbol name");
        free(item);
        exit(EXIT_FAILURE);
    }

	int hashIndex = hash(key);

	while(hashArray[hashIndex] != NULL){
		hashIndex++;
		hashIndex %= SYMBOL_TABLE_SIZE;
	}

	hashArray[hashIndex] = item;
}

void symtable_display_table(){
	//int i = 0;
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
		if(hashArray[i] != NULL){
			printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->addr);
		}
		else{
			printf(" ~~ ");
		}
	}
	printf("\n");
}

void symtable_print_labels(){
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
		if(hashArray[i] != NULL){
			printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
		}
	}	
}

