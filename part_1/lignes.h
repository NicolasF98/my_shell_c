#ifndef __LIGNES_H__
#define __LIGNES_H__

#define TAILLE_MAX_LIGNE 1024
#define NOMBRE_MAX_LIGNES 1024

void decouper_ligne(char *ligne, char *ligne_decoupee[]);
int lire_ligne_fichier(FILE * fichier, char *ligne);
void init_historique(FILE *f);
int lire_ligne(char *ligne);
void aller_a_la_ligne(int numero);
int obtenir_numero_ligne();

#endif
