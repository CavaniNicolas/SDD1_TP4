
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


// Supprime le '.' a la fin du mot si il existe
// Lower tous les caracteres
// Et renvoie la longueur du mot
int editWord(char * word) {
	int size = 0;

	while (word[size] != '\0') {
		word[size] = tolower(word[size]);
		size++;
	}

	if (word[size-1] == '.') {
		word[size-1] = '\0';
		size -= 1;
	}

	return size;
}
