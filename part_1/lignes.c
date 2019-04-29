#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lignes.h"

int lire_ligne_fichier(FILE * fichier, char *ligne) {
    /*
       Lecture d'une ligne depuis un fichier avec stockage de la ligne lue
       dans la variable ligne. Le '\n' final de chaque ligne n'est pas inclu dans la variable
       ligne et est remplace par '\0'.
       La valeur de retour est 0 s'il n'y a plus rien a lire (fin de
       fichier sans avoir lu aucun caractere) et 1 sinon.
     */

    int i=0;
    char c;
    fscanf(fichier,"%c",&c);
    while(!feof(fichier)){
        while(c!='\n'){
            ligne[i]=c;
            i++;
            fscanf(fichier,"%c",&c);
        }
        ligne[i]='\0';
        return 1;
    }
    ligne[i]='\0';
    return 0;
}

void decouper_ligne(char *ligne, char *ligne_decoupee[]) {
    /* 
       Decoupage de la ligne : chaque mot devient une chaine, c'est-a-dire
       est termine par '\0'. ligne_decoupee contient les adresses de ces mots,
       et se termine par NULL (s'il y a N mots, ligne_decoupee[0] pointe sur
       le premier mot et ligne_decoupee[i] vaut NULL.
       L'algorithme consiste a parcourir la variable ligne en reperant
       les debuts et les fins de mots (les mots sont separes par des espaces).
       Au debut d'un mot, on garde son adresse dans ligne_decoupee.
       A la fin d'un mot, on remplace le 1er espace qui le suit par '\0'
     */
   int char_suiv=1, i=0, num=0;

	while(ligne[i]!='\0'){
		if(ligne[i]==' '&& !char_suiv){
			ligne[i]='\0';
		}

		if(ligne[i]!=' ' && char_suiv){
			ligne_decoupee[num] = &ligne[i];
			num++;
		}

		char_suiv=(ligne[i]==' ' || ligne[i]=='\0');
		i++;
	}
ligne_decoupee[num]=NULL;
}
