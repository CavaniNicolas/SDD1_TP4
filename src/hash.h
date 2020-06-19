/* -------------------------------------------------------------------------- */
/* Nom du fichier : hash.h                                                    */
/* Date de creation : Juin 2020                                               */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Gerer la table de hachage                                       */
/*                                                                            */
/* Fonctions :                                                                */
/*                                                                            */
/* --------------------- Fonctions de gestion de la table ------------------- */
/*  - initHashTable                                                           */
/* -------------------------------------------------------------------------- */

#ifndef HASH_T_
#define HASH_T_

#define HASH_MAX 29


typedef struct cell {
	char * word;        // mot de la phrase
	int    number;      // nombre d'appartion du mot
	struct cell * next; // pointeur sur le mot suivant ayant la meme clef
}cell_t;


/* -------------------------------------------------------------------------- */
/* hash_string                                                                */
/*       Fonction de hachage de D.J. Bernstein                                */
/* -------------------------------------------------------------------------- */
unsigned int hash_string(const char *str);


/* -------------------------------------------------------------------------- */
/* initH                                                                      */
/*       Initialise la table de hachage de taille HASH_MAX                    */
/*                                                                            */
/* En entrée: (void)                                                          */
/*                                                                            */
/* En sortie: hashTable (cell_t **) : Table de hachage (tableau contenant les */
/*            pointeurs vers les structures) (initialises a NULL)             */
/* -------------------------------------------------------------------------- */
void initHashTable(cell_t * hashTable[HASH_MAX]);

cell_t * mallocNewCell();

char createTableFromFile(FILE * file, cell_t ** hashTable);

char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size);

int deleteWordFromTable(cell_t * hashTable[HASH_MAX], char * word);

cell_t ** findWordInChainedList(cell_t ** prev, char * word);

char createNewWordInTable(cell_t * newCell, char * word, int size);


void displayTable(cell_t ** hashTable);

void displayOneWordFromTable(cell_t ** hashTable, char * word);

void displayCountVariousWords(cell_t * hashTable[HASH_MAX]);


void freeHashTable(cell_t ** hashTable);

void freeChainedList(cell_t ** curr);

void deleteWordFromChainedList(cell_t ** prev);

#endif
