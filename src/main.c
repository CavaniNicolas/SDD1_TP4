
#include <stdio.h>
#include "hash.h"
#include "tools.h"


int main() {

	char filename[20] = "sentences.txt";
	FILE * file = openFile(filename);

	if (file) {
		cell_t ** hashTable = createTableFromFile(file);
		fclose(file);

		if (hashTable) {
			displayTable(hashTable);
			freeHashTable(hashTable);
		}
	}

	return 0;
}
