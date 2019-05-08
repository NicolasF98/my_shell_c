#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lignes.h"

char lignes_lues[NOMBRE_MAX_LIGNES][TAILLE_MAX_LIGNE];
int nombre_ligne_lue;
int position_courante;
FILE *fichier;

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

void init_historique(FILE *f){
    position_courante=0;
    nombre_ligne_lue=0;
    fichier=f;
}

int lire_ligne(char *ligne){
    int ret=1;
    char buffer[TAILLE_MAX_LIGNE];
    if(position_courante<nombre_ligne_lue){
        strcpy(ligne,lignes_lues[position_courante]);
    }
    else{
        if(nombre_ligne_lue>NOMBRE_MAX_LIGNES-1){
            debug("Max atteint\n");
            ligne[0]='\0';
            return 0;
        }
        ret=lire_ligne_fichier(fichier,buffer);
        strcpy(ligne,buffer);
        strcpy(lignes_lues[nombre_ligne_lue],buffer);
        nombre_ligne_lue++;
    }
    position_courante++;
    return ret;
}

void aller_a_la_ligne(int numero){
    position_courante=numero;
}

int obtenir_numero_ligne(){
    return position_courante-1;
}
