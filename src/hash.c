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


void initHashTable(cell_t * hashTable[HASH_MAX]) {

	// Tous les pointeurs de la table de hachage sont initialises a NULL
	for (int i=0; i<HASH_MAX; i++) {
		hashTable[i] = NULL;
	}

}


cell_t * mallocNewCell() {
	// Nouvelle cellule a ajouter a une liste chainee de la table
	cell_t * cell = (cell_t *)malloc(sizeof(cell_t));

	// Initialisation des champs
	if (cell) {
		cell->word = NULL;
		cell->number = 0;
		cell->next = NULL;
	}

	return cell;
}


char createTableFromFile(FILE * file, cell_t ** hashTable) {
	char errorCode = 0; /* Code Erreur */
	char word[27];      /* Mot contenu dans la cellule */
	int size = 0;       /* Longueur du mot de cette cellule */

	// Tant qu'on a pas finit de lire le fichier et qu'il n'y a pas eu d'erreur
	while (!feof(file) && !errorCode) {
		// On lit un mot
		fscanf(file, "%s", word);
		// On calcul sa taille en supprimant le '.' si il y en a un
		size = editWord(word);

		// On ajoutele mot dans la table
		errorCode = addWordInTable(hashTable, word, size);
	}

	// Si il y a eu une erreur lors de l'ajout, on libere la table
	if (errorCode) {
		freeHashTable(hashTable);
	}

	return errorCode;
}


char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size) {
	char errorCode = 0; /* Code Erreur */
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


int deleteWordFromTable(cell_t * hashTable[HASH_MAX], char * word) {
	int number = 0;
	int wordKey = hash_string(word);
	cell_t ** cell = NULL;

	// Il faut trouver l'emplacement du mot dans la table
	cell = findWordInChainedList(&(hashTable[wordKey]), word);

	// Si le mot est dans la table
	// On enregistre son nombre d'apparitions et on le supprime
	if (*cell != NULL) {
		number = (*cell)->number;
		deleteWordFromChainedList(cell);
	}

	return number;
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


void displayOneWordFromTable(cell_t ** hashTable, char * word) {
	int wordKey = hash_string(word);
	int number = 0;
	cell_t ** cell = NULL;

	// Il faut trouver l'emplacement du mot dans la table
	cell = findWordInChainedList(&(hashTable[wordKey]), word);

	if (*cell != NULL) {
		number = (*cell)->number;
	}

	printf("%s appeared %d times\n", word, number);
}


void displayCountVariousWords(cell_t * hashTable[HASH_MAX]) {
	cell_t * curr = NULL; /* Pointeur courant parcourant la liste chainee */
	int nbWords = 0;
	int nbVariousWords = 0;

	for (int i=0; i<HASH_MAX; i++) {

		curr = hashTable[i];
		while (curr != NULL) {
			nbVariousWords += 1;
			nbWords += curr->number;

			curr = curr->next;
		}
	}
	printf("Total Words : %d\nDifferent Words : %d\n", nbWords, nbVariousWords);
}


void freeHashTable(cell_t ** hashTable) {
	for (int i=0; i<HASH_MAX; i++) {
		freeChainedList(&(hashTable[i]));
	}
}


void freeChainedList(cell_t ** curr) {
	while (*curr != NULL) {
		deleteWordFromChainedList(curr);
	}
}


void deleteWordFromChainedList(cell_t ** prev) {
	cell_t * curr = *prev;
	*prev = (*prev)->next;
	free(curr->word);
	free(curr);
}
