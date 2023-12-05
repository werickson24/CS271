#include "symtable.h"

Symbol * hashArray[SYMBOL_TABLE_SIZE];

//Hash function
int hash_string(char * str){
	//djb2 hash algorithm
	unsigned long hash = 5381;
	int c;
	
	while((c = *str++)){
		hash = ((hash << 5) + hash) + c;
	}
	
	return hash % SYMBOL_TABLE_SIZE;
}

int index_wrap(int index){
	return index % SYMBOL_TABLE_SIZE;
}

int get_hash(char * str){
	return hash_string(str);
}
//Hash functions end

Symbol * symtable_find(char * key){
	int hashIndex = get_hash(key);
	//printf("symtable_find: looking for key: %s with hash: %d, result:\n", key, hashIndex);
	while(hashArray[hashIndex] != NULL){
		//this breaks when the second R1 comes through
		//current situation:
		//R1 key breaks this, hashIndex of r1 is 664
		if(strcmp(hashArray[hashIndex]->key, key) == 0){
			//printf("found\n");
			return hashArray[hashIndex];
		}
		hashIndex++;
		hashIndex = index_wrap(hashIndex);
	}
	//printf("not found\n");
	return NULL;
}

void symtable_insert(char * key, hack_addr addr){
	Symbol * item = (Symbol *) malloc(sizeof(Symbol));
	item->addr = addr;
	item->key = strdup(key);//avoid scope memory deletion, WARNING: MEMORY LEAK POSSIBLE
	
	int hashIndex = get_hash(key);
	while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != NULL){
		hashIndex++;
		hashIndex = index_wrap(hashIndex);
	}
	hashArray[hashIndex] = item;
}

void symtable_display_table(){
	
	for(int i = 0; i < SYMBOL_TABLE_SIZE; i++){
		if(hashArray[i] != NULL){
			printf(" (%s,%d)", hashArray[i]->key, hashArray[i]->addr);
			
		}else{
			printf(" ~~");
		}
	}
	
	printf("\n");
}

void symtable_print_labels(){ 
    for(int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
			printf("{%s,%d}\n",hashArray[i]->key,hashArray[i]->addr);
        }
    }
}
