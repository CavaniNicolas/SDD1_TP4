
#include <stdio.h>
#include "hash.h"
#include "tools.h"


int main() {
	// printf("%d\n", hash_string("hellofldlfmdlfoe"));
	// printf("%d\n", hash_string("heLlO"));
	// printf("%d\n", hash_string("1"));
	// printf("%d\n", hash_string("a"));
	// printf("%d\n", hash_string("A"));
	// printf("%d\n", 10<<2);

	// printf("%c\n", tolower('B'));
	// printf("%d\n", tolower('é'));

	char filename[20] = "sentences.txt";
	FILE * file = openFile(filename);
	if (file) {
		cell_t * hashTable = createTableFromFile(file);
		fclose(file);

		printf("\n");
		displayTable(hashTable);

		freeHashTable(hashTable);
	}

	return 0;
}
