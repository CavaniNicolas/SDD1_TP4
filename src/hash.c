
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "hash.h"
#include "tools.h"


unsigned int hash_string(const char *str) {
	unsigned int hash = 5381; /*  fonction de hachage de D.J. Bernstein*/
	const char *s;

	for (s = str; *s; s++) {
		hash = ((hash << 5) + hash) + tolower(*s);
	}

	return (hash & 0x7FFFFFFF) % HASH_MAX;
}


cell_t * initHashTable() {
	cell_t * hashTable = (cell_t *)malloc(HASH_MAX * sizeof(cell_t));

	if (hashTable) {
		for (int i=0; i<HASH_MAX; i++) {
			hashTable[i].word = NULL;
			hashTable[i].number = 0;
			hashTable[i].next = NULL;
		}
	}

	return hashTable;
}


void freeHashTable(cell_t * hashTable) {
	for (int i=0; i<HASH_MAX; i++) {
		free(hashTable[i].word);
		freeChainedList(hashTable[i].next);
	}
	free(hashTable);
}

void freeChainedList(cell_t * curr) {
	cell_t * prev = curr;
	while (curr != NULL) {
		curr = curr->next;
		free(prev->word);
		free(prev);
		prev = curr;
	}
}

cell_t * createTableFromFile(FILE * file) {
	char word[20];
	int size = 0;

	cell_t * hashTable = initHashTable();

	while (!feof(file)) {
		fscanf(file, "%s", word);
		size = editWord(word);

		addWordInTable(hashTable, word, size);

		printf("%s, %d\n", word, hash_string(word));
	}
	return hashTable;
}


char addWordInTable(cell_t * hashTable, char * word, int size) {
	char errorCode = 0;
	int wordKey = hash_string(word);
	cell_t ** cell = NULL;

	if (hashTable[wordKey].number == 0 || !strcmp(hashTable[wordKey].word, word)) {
		insertWordInTable(&(hashTable[wordKey]), word, size);

	} else {
		cell = findWordInChainedList(&(hashTable[wordKey]), word);
		
		if (*cell != NULL) {
			(*cell)->number += 1;
		} else {
			(*cell) = mallocNewCell();
			if (*cell != NULL) {
				errorCode = insertWordInTable(*cell, word, size);
			}
		}
	}

	return errorCode;
}


cell_t * mallocNewCell() {
	cell_t * cell = (cell_t *)malloc(sizeof(cell_t));

	if (cell) {
		cell->word = NULL;
		cell->number = 0;
		cell->next = NULL;
	}
	return cell;
}


cell_t ** findWordInChainedList(cell_t * curr, char * word) {
	cell_t * prev = curr;
	char found = 0;

	while (!found && curr != NULL) {
		prev = curr;
		curr = curr->next;
		if (curr != NULL) {
			if (!strcmp(curr->word, word)) {
				found = 1;
			}
		}
	}

	return &(prev->next);
}


char insertWordInTable(cell_t * newCell, char * word, int size) {
	char errorCode = 0;

	if (newCell->word != NULL) {
		newCell->number += 1;

	} else {
		newCell->word = (char *)malloc((size+1) * sizeof(char));

		if (newCell->word != NULL) {
			strcpy(newCell->word, word);
			newCell->number += 1;

		} else {
			printf("Error when malloc the field for word (char *)\n");
			errorCode = 1;
		}
	}

	return errorCode;
}


void displayTable(cell_t * hashTable) {
	cell_t * curr = NULL;

	for (int i=0; i<HASH_MAX; i++) {
		if (hashTable[i].number != 0) {
			printf("%d: (%s,%d)", i, hashTable[i].word, hashTable[i].number);
			curr = hashTable[i].next;
			while (curr != NULL) {
				printf("->(%s,%d)", curr->word, curr->number);
				curr = curr->next;
			}
			printf("\n");
		}
	}
}