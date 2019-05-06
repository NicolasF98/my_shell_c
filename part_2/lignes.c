#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lignes.h"

int lire_ligne_fichier(FILE * fichier, char *ligne) {
    char c;
    int i;

    i = 0;
    fscanf(fichier, "%c", &c);
    while (!feof(fichier) && (c != '\n')) {
        ligne[i] = c;
        i++;
        fscanf(fichier, "%c", &c);
    }
    ligne[i] = '\0';

    if ((i == 0) && feof(fichier))
        return 0;
    else
        return 1;
}

void decouper_ligne(char *ligne, char *ligne_decoupee[]) {
    int i = 0;
    int dans_mot = 0;
    int position = 0;

    while ((ligne[position] != '\0') && (ligne[position] != '#')) {
        if (isspace(ligne[position])) {
            /* Si on etait dans un mot, on le termine */
            if (dans_mot) {
                ligne[position] = '\0';
                dans_mot = 0;
            }
            /* Dans le cas contraire on ne fait rien */
        } else {
            /* Si on commence un mot, on conserve un pointeur sur son debut */
            if (!dans_mot) {
                ligne_decoupee[i] = &ligne[position];
                i++;
                dans_mot = 1;
            }
            /* Dans le cas contraire, rien a faire */
        }
        position++;
    }
    ligne[position] = '\0';
    ligne_decoupee[i] = NULL;
}

