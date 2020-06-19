
#include <stdio.h>
#include "hash.h"
#include "tools.h"


int main() {

	char filename[20] = "sentences.txt";
	FILE * file = openFile(filename);

	if (file) {
		cell_t * hashTable[HASH_MAX];
		initHashTable(hashTable);

		createTableFromFile(file, hashTable);
		fclose(file);

		// addWordInTable(hashTable, "bonjour", 8);
		// addWordInTable(hashTable, "aurevoir", 9);

		// char word[4] = "les";
		// printf("Deleted \"%s\", it appeared %d times\n", word, deleteWordFromTable(hashTable, "les"));

		displayTable(hashTable);
		displayOneWordFromTable(hashTable, "france");
		displayCountVariousWords(hashTable);

		freeHashTable(hashTable);
	}

	return 0;
}
