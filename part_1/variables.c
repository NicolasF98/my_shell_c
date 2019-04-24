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
    int n=ens->nb;
    while(i!=ens->nb){
        if(nom==ens->T[i].nom){
            strcpy(ens->T[i].valeur,valeur);
            return i;
        }
        i++;
    }
    strcpy(ens->T[n+1].nom,nom);
    strcpy(ens->T[n+1].valeur,valeur);
    return (n+1);
}

int nombre_variables(variables * ens) {
    /*
       Fonction qui renvoie le nombre de variables dans l'ensemble.
     */
    int n=ens->nb;
    return n;
}

int trouver_variable(variables * ens, char *nom) {
    /*
       Fonction qui recherche le nom de variable dans l'ensemble
       des variables definies. Si le nom est trouve, la fonction retourne
       l'indice correspondant dans le tableau, dans le cas
       contraire elle retourne -1.
     */
    int i = 0;
    for(;i!=ens->nb;i++){
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
    if(ens->nb<i) return NULL;
    return ens->T[i].nom;;
}

char *valeur_variable(variables * ens, int i) {
    /*
       Fonction qui renvoie la valeur de la variable a l'indice i ou
       "" si elle n'existe pas.
     */
    if(ens->nb<i) return "";
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
    int i=0,j=0;  /* on utilise 2 compteur: `i`pour parcourir la ligne; `j` pour parcourir le tableau `n` */
    char *n=NULL; /* création tableau vide */

    while(ligne[i]!='\0'){
        if(strcmp(&ligne[i]," ")!=0){       /* si la valeur de ligne[i] est différente d'un espace... */
            n[j]=ligne[i];
            if(strcmp(&ligne[i],"=")==0 && strcmp(&ligne[i+1]," ")!=0){         /* si la valeur de ligne[i] est identique à "=" ET si ligne[i+1] est différente d'un espace... */
                strcpy(ens->T[0].nom,n);      /* le mot analysé est stocké dans le tableau `T` dans la cas `nom` à l'indice `k` */
                strcpy(n,"");        /* on vide notre variable n */
                j=0;         /* l'indexe de la variable n est remit à 0 */
            }
        }
        i++;         /* on cherche la valeur de `nom` en bouclant temps que ligneet stockant,  */
        j++;
    }
    strcpy(ens->T[0].valeur,n);

    return 0;
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
