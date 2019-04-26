#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "variables.h"

void init_variables(variables * ens) {
    /* 
       Initialisation d'un ensemble vide.
     */
    ens->nb=0;
}

int ajouter_variable(variables * ens, char *nom, char *valeur) {
    /*
       Fonction qui affecte la valeur donnee au nom de variable donne.
       Si la variable existe deja dans les variables definies, il suffit juste
       de changer sa valeur. Dans le cas contraire, il faut l'ajouter aux
       variables definies : ajouter un couple (nom, valeur) a l'ensemble
       de variables. Dans tous les cas, la fonction retourne l'indice de la
       variable ajout�e.
     */
    int i=0;
    int indice=-1;

    while(i!=ens->nb){
        if(strcmp(nom,ens->T[i].nom)==0){  /* Si le nom de la variable existe deja... */
            strcpy(ens->T[i].valeur,valeur);
            indice=i;
            break; /* on break pour return notre indice */
        }
        i++;
    }
        if(indice==-1){
            if(ens->nb<NOMBRE_MAX_VARIABLES){
                strcpy(ens->T[ens->nb].nom,nom);
                strcpy(ens->T[ens->nb].valeur,valeur);
                indice=ens->nb;
                ens->nb++;
            }
        }
    return indice;
}

int nombre_variables(variables * ens) {
    /*
       Fonction qui renvoie le nombre de variables dans l'ensemble.
     */
    return ens->nb;
}

int trouver_variable(variables * ens, char *nom) {
    /*
       Fonction qui recherche le nom de variable dans l'ensemble
       des variables definies. Si le nom est trouve, la fonction retourne
       l'indice correspondant dans le tableau, dans le cas
       contraire elle retourne -1.
     */
    int i = 0;
    for(;i!=nombre_variables(ens);i++){
        if(ens->T[i].nom==nom){
            return i;
        }
    }
    return -1;
}

char *nom_variable(variables * ens, int i) {
    /*
       Fonction qui renvoie le nom de la variable a l'indice i ou
       NULL si elle n'existe pas.
     */
    if(nombre_variables(ens)< i) return NULL;
    return ens->T[i].nom;
}

char *valeur_variable(variables * ens, int i) {
    /*
       Fonction qui renvoie la valeur de la variable a l'indice i ou
       "" si elle n'existe pas.
     */
    if(ens->nb<i) return "rekt";
    return ens->T[i].valeur;
}

void modifier_valeur_variable(variables * ens, int i, char *valeur) {
    /*
       Fonction qui modifie la valeur de la variable a l'indice i.
       Comportement indeterminee si l'indice i n'est pas valide.
     */
    strcpy(ens->T[i].valeur,valeur);
}

void afficher_ensemble_variables(variables * ens) {
    for (int i = 0; i < nombre_variables(ens); i++) {
        printf("%s=%s\n", nom_variable(ens, i), valeur_variable(ens, i));
    }
}

int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
    /*
       Fonction qui cherche a reconnaitre une affectation de variable dans le 
       morceau de ligne de commande transmise et, le cas echeant, l'applique. 
       Pour cela il faut determiner si ce morceau de
       ligne est de la forme :
       nom=valeur
       Cette fonction est destructive : elle modifie ligne lorsqu'elle
       trouve une affectation. Retourne 1 en cas d'affectation trouvee, 0 dans le
       cas contraire.
     */
    /* Dans cette situation, l'utilisation d'un automate est pratiquement obligatoire 
    car nous devons nous memoriser dans quel etat nous somme. */
    enum { ESP_DEB, NOM, EGAL, VAL, ERR } etat=ESP_DEB;
	int affectation=0;
	char *nom=NULL, *val=NULL;
	int i=0;

	while (ligne[i]!='\0' && etat!=ERR) {
		switch (etat) {

		case ESP_DEB:
			switch (ligne[i]) {
			case '=': etat=ERR     ; break;
			case ' ': etat=ESP_DEB ; break;
			default :
				nom=&ligne[i];
				etat=NOM;
				break;
			}
			break;

		case NOM:
			switch (ligne[i]) {
			case '=':
				ligne[i]='\0';
				val=&ligne[i+1];
				etat=EGAL;
				break;
			case ' ': etat=ERR  ; break;
			default: etat=NOM  ; break;
			}
			break;

		case EGAL:
			switch (ligne[i]) {
			case '=': etat=ERR  ; break;
			case ' ': etat=ERR  ; break;
			default: etat=VAL  ; break;
			}
			break;

		case VAL:
			switch (ligne[i]) {
			case '=': etat = ERR  ; break;
			case ' ': etat = ERR  ; break;
			default: etat = VAL  ; break;
			}
			break;

		default: break;
		}
		i++;
	}

	if (etat==VAL) {
		ajouter_variable (ens, nom, val);
		affectation = 1;
	}

	return affectation;
}

void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {
/*
  Fonction qui prend une ligne lue en parametre et la recopie dans le tableau
  resultat(==ligne_expansee) en remplacant toutes les utilisations de variable (de la forme
  '$nom' ou nom est une chaine de caracteres alphanumeriques ou * ou #) par la
  valeur de la variable correspondante.
*/
    // A remplacer : le code ci-dessous n'expanse rien

    strcpy(ligne_expansee, ligne_originale);
}

void affecter_variables_automatiques(variables *ens, int argc, char *argv[]) {
/*************** A COMPLETER ******************/
    /*
       Il faut definir les variables automatiques a partir des arguments
       donnes au programme :
       - placer la valeur de chacun des arguments transmis au programme dans la
       variable correspondante ($0, $1, $2, ...)
       - construire au fur et a mesure une chaine de caractere contenant toutes
       les valeurs et l'affecter a $*
       - affecter le nombre d'arguments a $#
     */
/**********************************************/
}
