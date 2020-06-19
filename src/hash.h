/* -------------------------------------------------------------------------- */
/* Nom du fichier : hash.h                                                    */
/* Date de creation : Juin 2020                                               */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Gerer la table de hachage                                       */
/*                                                                            */
/* Fonctions :                                                                */
/*                                                                            */
/* --------------------- Fonctions de gestion de la table ------------------- */
/*  - hash_string                                                             */
/*  - initHashTable                                                           */
/*  - mallocNewCell                                                           */
/*  - createTableFromFile                                                     */
/*  - addWordInTable                                                          */
/*  - deleteWordFromTable                                                     */
/*  - findWordInChainedList                                                   */
/*  - createNewWordInTable                                                    */
/*                                                                            */
/* --------------------- Fonctions d'affichage de la table ------------------ */
/*  - displayTable                                                            */
/*  - displayOneWordFromTable                                                 */
/*  - displayCountVariousWords                                                */
/*                                                                            */
/* -------------------- Fonctions de liberation de la table ----------------- */
/*  - freeHashTable                                                           */
/*  - freeChainedList                                                         */
/*  - deleteWordFromChainedList                                               */
/* -------------------------------------------------------------------------- */

#ifndef HASH_T_
#define HASH_T_

// Taille de la table de hachage
// Tableau contigue de pointeurs vers des listes chainees de structure cell_t
#define HASH_MAX 29


/* -------------------------------------------------------------------------- */
/* struct cell (typedef cell_t)                                               */
/*       Structure d'un élément des listes chainees de la table de hachage    */
/*                                                                            */
/*       word   (char *)      : Mot du fichier                                */
/*       number (int)         : Nombre d'appartions du mot                    */
/*       next (struct cell *) : Pointeur sur l'element suivant de la liste,   */
/*                              Mots ayant la meme clef de hachage            */
/* -------------------------------------------------------------------------- */
typedef struct cell {
	char * word;
	int    number;
	struct cell * next;
}cell_t;


/*════════════════════════════════════════════════════════════════════════════*/
/* --------------------- Fonctions de gestion de la table ------------------- */
/*════════════════════════════════════════════════════════════════════════════*/


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
/* En entrée: file (FILE *)         : Fichier a lire pour creer la table      */
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
/*            word (char *)         : Mot a ajouter dans la table             */
/*            size (int)            : Taille du mot                           */
/*                                                                            */
/* En sortie: errorCode (char) : code d'erreur, 1 si erreur, 0 sinon          */
/* -------------------------------------------------------------------------- */
char addWordInTable(cell_t * hashTable[HASH_MAX], char * word, int size);


/* -------------------------------------------------------------------------- */
/* deleteWordFromTable                                                        */
/*       Supprime un mot de la table et renvoie son nombre d'apparitions      */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage                        */
/*            word (char *)         : Mot a supprimer de la table             */
/*                                                                            */
/* En sortie: number (int) : Nombre d'apparitions du mot dans le fichier      */
/* -------------------------------------------------------------------------- */
int deleteWordFromTable(cell_t * hashTable[HASH_MAX], char * word);


/* -------------------------------------------------------------------------- */
/* findWordInChainedList                                                      */
/*       Recherche le mot passe en parametre dans la liste chainee            */
/*                                                                            */
/* En entrée: prev (cell_t **) : Pointeur sur le pointeur sur la structure a  */
/*                               rechercher                                   */
/*            word (char *)    : Mot a chercher dans la table                 */
/*                                                                            */
/* En sortie: prev (cell_t **) : Pointeur sur le pointeur de la structure     */
/*            trouvee, peut correspondre au champ 'next' de la structure      */
/*            precedente dans la liste, ou bien du pointeur dans la table     */
/*            contigue de hachage                                             */
/* -------------------------------------------------------------------------- */
cell_t ** findWordInChainedList(cell_t ** prev, char * word);


/* -------------------------------------------------------------------------- */
/* createNewWordInTable                                                       */
/*       Creer un nouveau mot dans la table, remplie les champs de la cellule */
/*       vide passee en parametre. Attention a la memoire lors de la          */
/*       liberation, le champ word (char *) est alloue dynamiquement          */
/*                                                                            */
/* En entrée: newCell (cell_t *) : Structure a remplir                        */
/*            word (char *)      : Mot a remplir dans la cellule              */
/*            size (int)         : Taille du mot                              */
/*                                                                            */
/* En sortie: errorCode (char) : code d'erreur, 1 si erreur, 0 sinon          */
/* -------------------------------------------------------------------------- */
char createNewWordInTable(cell_t * newCell, char * word, int size);


/*════════════════════════════════════════════════════════════════════════════*/
/* --------------------- Fonctions d'affichage de la table ------------------ */
/*════════════════════════════════════════════════════════════════════════════*/


/* -------------------------------------------------------------------------- */
/* displayTable                                                               */
/*       Affiche la table de hachage entierement                              */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage a afficher             */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void displayTable(cell_t ** hashTable);


/* -------------------------------------------------------------------------- */
/* displayOneWordFromTable                                                    */
/*       Affiche un mot de la table si il existe et son nombre d'apparitions  */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage                        */
/*            word (char *)         : Mot a chercher et a afficher            */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void displayOneWordFromTable(cell_t ** hashTable, char * word);


/* -------------------------------------------------------------------------- */
/* displayCountVariousWords                                                   */
/*       Affiche le nombre de mots differents et le nombre de mots totaux     */
/*       contenus dans la table                                               */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage                        */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void displayCountVariousWords(cell_t * hashTable[HASH_MAX]);


/*════════════════════════════════════════════════════════════════════════════*/
/* -------------------- Fonctions de liberation de la table ----------------- */
/*════════════════════════════════════════════════════════════════════════════*/


/* -------------------------------------------------------------------------- */
/* freeHashTable                                                              */
/*       Libere la table de hachage de la memoire                             */
/*                                                                            */
/* En entrée: hashTable (cell_t **) : Table de hachage a liberer              */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void freeHashTable(cell_t ** hashTable);


/* -------------------------------------------------------------------------- */
/* freeChainedList                                                            */
/*       Libere la liste chainee passee en parametre de la memoire            */
/*                                                                            */
/* En entrée: curr (cell_t **) : Pointeur sur le pointeur sur le premier      */
/*                               element de la liste chainee                  */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void freeChainedList(cell_t ** curr);


/* -------------------------------------------------------------------------- */
/* deleteWordFromChainedList                                                  */
/*       Supprime un mot de la liste chainee, libere l'element de la memoire  */
/*                                                                            */
/* En entrée: prev (cell_t **) : Pointeur sur le pointeur sur l'element a     */
/*                               supprimer                                    */
/*                                                                            */
/* En sortie: (void)                                                          */
/* -------------------------------------------------------------------------- */
void deleteWordFromChainedList(cell_t ** prev);


#endif
