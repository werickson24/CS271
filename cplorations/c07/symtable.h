#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct Symbol{
	char * key;
	hack_addr addr;
} Symbol;

//api
int hash_string(char * str);
int index_wrap(int index);
int get_hash(char * str);

struct Symbol * symtable_find(char * key);
void symtable_insert(char * key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();





//hash stuff (ok this goes in .c
/*
int hashCode(int key){
	return key % SYMBOL_TABLE_SIZE;
}

struct DataItem * search(int key){
	int hashIndex = hashCode(key);
	
	while(hashArray[hashIndex] != NULL){
		if(hashArray[hashIndex]->key == key){
			return hashArray[hashIndex];
		}
		hashIndex++;
		
		hashIndex %= SYMBOL_TABLE_SIZE;
	}
	return NULL;
}*/