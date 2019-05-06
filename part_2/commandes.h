#ifndef __COMMANDES_H__
#define __COMMANDES_H__

#define NB_MAX_ETATS 128
#define NB_MAX_ENTREES 128

typedef struct {
	int etat;
        int nb_etats;
        int etat_initial;
        int transitions[NB_MAX_ETATS][NB_MAX_ENTREES];
        int sortie[NB_MAX_ETATS][NB_MAX_ENTREES];
	int ligne_boucle;
        } automate;

void init_automate_commandes(automate *A)  ;
int analyse_commande_interne(automate *A, char *ligne_courante);

#endif
