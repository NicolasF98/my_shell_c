/* initialisation d'un ensemble de variables a l'ensemble vide */
void init_variables(variables *ens);

/* ajout d'une variable dans un ensemble de variables si elle n'y est pas deja,
 * ecrase sa valeur sinon. Dans tous les cas renvoie l'indice de la variable dans
 * l'ensemble */
int ajouter_variable(variables *ens, char *nom, char *valeur);

/* cardinal d'un ensemble de variables */
int nombre_variables(variables *ens);

/* recherche de l'indice d'une variable dans un ensemble, -1 si la variable n'est
 * pas presente dans l'ensemble */
int trouver_variable(variables *ens, char *nom);

/* variable d'indice i (NULL si cette variable n'existe pas dans l'ensemble) */
char *nom_variable(variables *ens, int i);

/* valeur de la variables a l'indice i ("" si inexistant) */
char *valeur_variable(variables *ens, int i);

/* met a jour la valeur de la variable d'indice i (sans effet si indice invalide) */
void modifier_valeur_variable(variables *ens, int i, char *valeur);
