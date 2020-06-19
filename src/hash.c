/* -------------------------------------------------------------------------- */
/* Nom du fichier : hash.c                                                    */
/* Date de creation : Juin 2020                                               */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Gerer la table de hachage                                       */
/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "hash.h"
#include "tools.h"


/* Fonction de hachage de D.J. Bernstein */
unsigned int hash_string(const char *str) {
	unsigned int hash = 5381;
	const char *s;

	for (s = str; *s; s++) {
		hash = ((hash << 5) + hash) + tolower(*s);
	}

	return (hash & 0x7FFFFFFF) % HASH_MAX;
}


cell_t ** initHashTable() {
	cell_t ** hashTable = (cell_t **)malloc(HASH_MAX * sizeof(cell_t *));

	if (hashTable) {
		for (int i=0; i<HASH_MAX; i++) {
			hashTable[i] = NULL;
		}
	}

	return hashTable;
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


cell_t ** createTableFromFile(FILE * file) {
	char errorCode = 0;
	char word[27];
	int size = 0;

	cell_t ** hashTable = initHashTable();

	while (!feof(file)) {
		fscanf(file, "%s", word);
		size = editWord(word);

		errorCode = addWordInTable(hashTable, word, size);
	}

	if (errorCode) {
		freeHashTable(hashTable);
	}

	return hashTable;
}


char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size) {
	char errorCode = 0;
	int wordKey = hash_string(word);
	cell_t ** cell = NULL;

	// Il faut trouver l'emplacement dans la table pour le nouveau mot
	cell = findWordInChainedList(&(hashTable[wordKey]), word);

	// Si le mot est deja dans la table, on incremente son compteur
	if (*cell != NULL) {
		(*cell)->number += 1;

	// Si il n'est pas dans la table, il faut agrandir la liste chainee
	} else {
		(*cell) = mallocNewCell();
		if (*cell != NULL) {
			errorCode = createNewWordInTable(*cell, word, size);
		}
	}

	return errorCode;
}


char createNewWordInTable(cell_t * newCell, char * word, int size) {
	char errorCode = 0;

	newCell->word = (char *)malloc((size+1) * sizeof(char));

	if (newCell->word != NULL) {
		strcpy(newCell->word, word);
		newCell->number += 1;

	} else {
		printf("Error when malloc the field for word (char *)\n");
		errorCode = 1;
	}

	return errorCode;
}


cell_t ** findWordInChainedList(cell_t ** prev, char * word) {
	cell_t * curr = *prev;
	char found = 0;

	while (!found && curr != NULL) {
		if (curr != NULL) {
			if (!strcmp(curr->word, word)) {
				found = 1;
			}
		}
		if (!found) {
			prev = &(curr->next);
			curr = curr->next;
		}
	}

	return prev;
}


void displayTable(cell_t ** hashTable) {
	cell_t * curr = NULL; /* Pointeur courant parcourant la liste chainee */
	char isFirst = 1;
	/* Booleen, indique si l'element que pointe curr est le premier de la liste
	chainee ou non */

	for (int i=0; i<HASH_MAX; i++) {

		curr = hashTable[i];
		while (curr != NULL) {

			// Si c'est le premier element de cette clef
			if (isFirst) {
				printf("%d: (%s,%d)", i, curr->word, curr->number);
				isFirst = 0;

			// Si on est dans la liste chainee, premier element exclu
			} else {
				printf("->(%s,%d)", curr->word, curr->number);
			}

			curr = curr->next;
		}
		// On saute une ligne que si des elements ont ete affiches
		if (!isFirst) {
			printf("\n");
		}
		isFirst = 1;
	}

}


void freeHashTable(cell_t ** hashTable) {
	for (int i=0; i<HASH_MAX; i++) {
		freeChainedList(hashTable[i]);
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
