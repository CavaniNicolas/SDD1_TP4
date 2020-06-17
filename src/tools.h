/* -------------------------------------------------------------------------- */
/* Nom du fichier : tools.h                                                   */
/* Date de creation : Juin 2020                                               */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Outils divers                                                   */
/*                                                                            */
/* Fonctions :                                                                */
/*                                                                            */
/* ----------------------------- Fonctions outils --------------------------- */
/*  - openFile                                                                */
/*  - editWord                                                                */
/* -------------------------------------------------------------------------- */

#ifndef TOOLS_H_
#define TOOLS_H_


/* -------------------------------------------------------------------------- */
/* openFile                                                                   */
/*       Ouvre le fichier dont le nom est passé en parametre                  */
/*                                                                            */
/* En entrée: filename (char const *) : Nom du fichier                        */
/*                                                                            */
/* En sortie: file (FILE *) : Fichier ouvert, NULL si erreur. Pensez a        */
/*            fclose(file) dans votre code                                    */
/* -------------------------------------------------------------------------- */
FILE * openFile(char const * filename);


/* -------------------------------------------------------------------------- */
/* editWord                                                                   */
/*       Supprime le '.' a la fin du mot si il existe, Lower tous les         */
/*       caracteres et Renvoie la longueur du mot                             */
/*                                                                            */
/* En entrée: word (char *) : Mot a modifier si necessaire                    */
/*                                                                            */
/* En sortie: size (int) : Taille de la chaine de caractere word              */
/* -------------------------------------------------------------------------- */
int editWord(char * word);


#endif
