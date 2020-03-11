# Creation d'un mini Shell en C:
Université de Grenoble, Licence Informatique et Maths Appliquées , 1ère année

Contact: Nicolas Fournout <nicolas.fournout@etu.univ-grenoble-alpes.fr>

- [x] 1ère partie:
- [x] 2ème partie: 

## 1ère partie:

#### 1 - Boucle de lecture:

- [x] (A) - Question sur `executer_ligne_commande`.
- [x] (B) - Explication de `ligne.c`et `varibles.c`.

#### 2 - Lecture d'une ligne:

- [x] (C) - Implémentation de `lire_ligne_fichier`.
- [x] (D) - Question sur exécution du script de test `test_1_lecture_ligne.sh`.

#### 3 - Gestion d'un ensemble de variables:

- [x] (E) - Implémentations dans `variable.c`.
- [x] (F) - Implémentation de `trouver_et_appliquer_affectation_variable`.
- [x] (G) - Implémentation de `appliquer_expansion_variables`.

#### 4 - Découpage de la ligne:

- [x] (H) - Implémentations dans `decouper_ligne`.

#### 5 - Variables automatiques:

- [x] (I) - Implémentations d'une fonction qui concatène des chaînes et qui affecte à une chaîne l'écriture décimal d'un nombre.

## 2ème partie

#### 1 - Etat des lieux et objectifs:

- [x] (A) - Création de fichier test en `.sh` avec des instructions conditionnelles ou while.

#### 2 - Quelle sorte de ligne ?:

- [x] (B) - Où est appelé `decode_entree` ? Compléter la fonction.

#### 3 - Automate d'une instruction conditionnelle:
S
- [x] (C) - Compléter les fonctions `init_automate_commades` et `analyse_commande_interne`.

- [x] (D) - Trouver où sont appelées les fonctions définis dans `commandes.c`. 

#### 4 - Boucles while:

- [x] (E) - Modification de `lignes.c` afin de numéroter et stocker un ensemble de ligne pour les réexécuter lors d'itérations, tester la mécanique de retour arrière.
 
- [x] (F) - Dessin de l'automate de structure `while/do/done`.

- [x] (G) - Compléter `commandes.c` en implémentant `while` dans l'automate.
...
