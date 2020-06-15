
#ifndef HASH_T_
#define HASH_T_

#define HASH_MAX 29

unsigned int hash_string(const char *str);


typedef struct cell {
	char * word; // mot de la phrase
	int number; // nombre d'appartion du mot
	struct cell * next; // pointeur sur le mot suivant ayant la meme clef
}cell_t;


cell_t * initHashTable();

void freeHashTable(cell_t * hashTable);
void freeChainedList(cell_t * curr);
cell_t * createTableFromFile(FILE * file);

char addWordInTable(cell_t * hashTable, char * word, int size);
char insertWordInTable(cell_t * newCell, char * word, int size);

cell_t ** findWordInChainedList(cell_t * curr, char * word);
cell_t * mallocNewCell();

void displayTable(cell_t * hashTable);


#endif
