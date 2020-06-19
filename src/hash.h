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
cell_t ** initHashTable();



cell_t * mallocNewCell();


cell_t ** createTableFromFile(FILE * file);

char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size);


char createNewWordInTable(cell_t * newCell, char * word, int size);

cell_t ** findWordInChainedList(cell_t ** prev, char * word);

void displayTable(cell_t ** hashTable);

void freeHashTable(cell_t ** hashTable);


void freeChainedList(cell_t * curr);


#endif
