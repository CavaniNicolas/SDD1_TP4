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
/* initHashTable                                                              */
/*       Initialise la table de hachage de taille HASH_MAX                    */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage, tableau de pointeurs  */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void initHashTable(cell_t * hashTable[HASH_MAX]);


/* -------------------------------------------------------------------------- */
/* mallocNewCell                                                              */
/*       Alloue la memoire pour une cellule et initialise ses champs          */
/*                                                                            */
/* En entrée: (void)                                                          */
/*                                                                            */
/* En sortie: cell (cell_t *) : Cellule allouee                               */
/* -------------------------------------------------------------------------- */
cell_t * mallocNewCell();


/* -------------------------------------------------------------------------- */
/* createTableFromFile                                                        */
/*       Creer la table de hachage depuis le fichier ouvert passe en parametre*/
/*                                                                            */
/* En entrée: file (FILE *) : Fichier a lire pour creer la table              */
/*            hashTable (cell_t **) : Table de hachage                        */
/*                                                                            */
/* En sortie: errorCode (char) : code d'erreur, 1 si erreur, 0 sinon          */
/* -------------------------------------------------------------------------- */
char createTableFromFile(FILE * file, cell_t ** hashTable);


/* -------------------------------------------------------------------------- */
/* addWordInTable                                                             */
/*       Ajoute un mot dans la table de hachage, il peut etre necessaire que  */
/*       de la memoire soit allouee si le mot a ajouter n'est pas deja present*/
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage                        */
/*            word (char *) : Mot a ajouter dans la table                     */
/*            size (int) : Taille du mot                                      */
/*                                                                            */
/* En sortie: errorCode (char) : code d'erreur, 1 si erreur, 0 sinon          */
/* -------------------------------------------------------------------------- */
char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size);


/* -------------------------------------------------------------------------- */
/* deleteWordFromTable                                                        */
/*       Supprime un mot de la table et renvoie son nombre d'apparitions      */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage                        */
/*            word (char *) : Mot a supprimer de la table                     */
/*                                                                            */
/* En sortie: number (int) : Nombre d'apparitions du mot dans le fichier      */
/* -------------------------------------------------------------------------- */
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
