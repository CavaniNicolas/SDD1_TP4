/* -------------------------------------------------------------------------- */
/* Nom du fichier : tools.c                                                   */
/* Date de creation : Juin 2020                                               */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Outils divers                                                   */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include "tools.h"
#include <ctype.h>


FILE * openFile(char const * filename) {
	FILE * file = NULL;
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("Incorrect filename\n");
	}
	return file;
}


int editWord(char * word) {
	int size = 0; /* Taille du mot */

	// Calcul de la longueur du mot
	// Au cours du parcours, les caracteres sont mit en minuscules
	while (word[size] != '\0') {
		word[size] = tolower(word[size]);
		size++;
	}

	// Si le dernier caractere est un '.', il est supprime
	if (word[size-1] == '.') {
		word[size-1] = '\0';
		size -= 1;
	}

	return size;
}
