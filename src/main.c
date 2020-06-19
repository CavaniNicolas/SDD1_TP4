
#include <stdio.h>
#include "hash.h"
#include "tools.h"

#include <stdlib.h>
#include <string.h>

int main() {

	char filename[20] = "sentences.txt";
	FILE * file = openFile(filename);

	if (file) {
		cell_t * hashTable[HASH_MAX];
		initHashTable(hashTable);

		createTableFromFile(file, hashTable);

		fclose(file);

		displayTable(hashTable);
		freeHashTable(hashTable);
	}

	return 0;
}
