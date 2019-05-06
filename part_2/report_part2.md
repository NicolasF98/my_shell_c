FOURNOUT Nicolas
# *Compte rendu partie 2 - Interpreteur*
 


## 1 - Etat des lieux et objectifs:

#### *[a]:*

done.

## 2 - Quelle sorte de ligne ?

#### *[b]:*

La fonction `decode_entree` est appelé dans le fichier `commandes.c`.

```java
int decode_entree(char *mot) {
    /*
       Comparer la chaine mot passee en parametre aux mnemoniques, retourner la
       valeur du mnemonique si le mot est un mnemonique, retourner INSTRUCTION sinon
     */
    int i=0;
    while(i!=nombre_mnemoniques){
        if(strcmp(mot,mnemonique[i])==0){
            return valeur_mnemonique[i]; 
        }
        i++;
    }
    return INSTRUCTION;
}
```

#### *[d]:*

Toutes les commandes sans arguments sont exécutés.

## 3 - Gestion d'un ensemble des variables:

#### *[e]:*

```java
void init_variables(variables * ens) {
    ens->nb=0;
}
```
```java
int ajouter_variable(variables * ens, char *nom, char *valeur) {
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
```
```java
int nombre_variables(variables * ens) {
    return ens->nb;
}
```
```java
int trouver_variable(variables * ens, char *nom) {
    int indice=-1;
    for(int i=0;i!=nombre_variables(ens);i++){
        if(strcmp(ens->T[i].nom,nom)==0){ 
            indice=i;
            break;
        }
    }
    return indice;
}
```
```java
char *nom_variable(variables * ens, int i) {
    char *nom=NULL;
    if(nombre_variables(ens)>i && i>=0) nom=ens->T[i].nom;
    return nom;
}
```
```java
char *valeur_variable(variables * ens, int i) {
    char *valeur="";
    if(nombre_variables(ens)>i && i>=0) valeur=ens->T[i].valeur;
    return valeur;
}
```
```java
void modifier_valeur_variable(variables * ens, int i, char *valeur) {
    strcpy(ens->T[i].valeur,valeur);
}
```

#### *[f]:*

```java
int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
  enum {ESP_DEB, NOM, EGAL, VAL, ERR} etat=ESP_DEB;
	int affectation=0;
	char *nom=NULL, *val=NULL;
	int i=0;

	while (ligne[i]!='\0' && etat!=ERR){
		switch (etat){
            case ESP_DEB:
                switch (ligne[i]){
                    case '=': etat=ERR; break;
                    case ' ': etat=ESP_DEB; break;
                    default:
                        nom=&ligne[i];
                        etat=NOM;
                        break;
                }
                break;

            case NOM:
                switch (ligne[i]){
                    case '=':
                        ligne[i]='\0';
                        val=&ligne[i+1];
                        etat=EGAL;
                        break;
                    case ' ': etat=ERR; break;
                    default: etat=NOM; break;
                }
                break;

            case EGAL:
                switch (ligne[i]){
                    case '=': etat=ERR; break;
                    case ' ': etat=ERR; break;
                    default: etat=VAL; break;
                }
                break;

            case VAL:
                switch (ligne[i]){
                    case '=': etat=ERR; break;
                    case ' ': etat=ERR; break;
                    default: etat=VAL; break;
                }
                break;
		    default: break;
		}
		i++;
	}
	if (etat==VAL){
		ajouter_variable(ens, nom, val);
		affectation=1;
	}
	return affectation;
}
```
![alt text](https://image.noelshack.com/fichiers/2018/32/6/1534018137-1502418912-verre3.png) (p'tit shot d'eau bien merité)


#### *[g]:*

```java
void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {
    enum {COPY,DOLLAR, EXPAN} etat=COPY;
    char nom[TAILLE_MAX_NOM]="";
    int i_o=0, i_e=0, i_n=0;  /* 3 compteurs: i_o pour ligne_originale; i_e pour ligne_expansee; i_n pour parcourir nom. */
    
    while(ligne_originale[i_o]!='\0' && etat==EXPAN){
    switch(etat){

        case COPY:
            switch(ligne_originale[i_o]){

                case '$':
                    etat=DOLLAR;
                    break;
                default:
                    ligne_expansee[i_e]=ligne_originale[i_o];
                    i_e++;
                    etat=COPY;
                    break;
            }
            break;
        
        case DOLLAR:
            if(isalnum(ligne_originale[i_o]) || (ligne_originale[i_o]!='*') || (ligne_originale[i_o]!='#')){
                nom[i_n]=ligne_originale[i_o];
                i_n++;
                etat=EXPAN;
            }
            else{
                ligne_expansee[i_e]='$';
                ligne_expansee[i_e+1]=ligne_originale[i_o];
                i_e=i_e+2;
                etat=COPY;
            }
            break;
        
        case EXPAN:
            if(isalnum(ligne_originale[i_o])){
                nom[i_n]=ligne_originale[i_o];
                i_n++;
                etat=EXPAN;
            }
            else{
                nom[i_n]='\0';
                int var_id=trouver_variable(ens,nom);
                if(var_id!=-1){
                    char *val=valeur_variable(ens,var_id);
                    int i_v=0; 
                    while(val[i_v]!='\0'){
                        ligne_expansee[i_e]=val[i_v];
                        i_e++;
                        i_v++;
                    }
                }
                if(ligne_originale[i_o]!='\0'){
                    ligne_expansee[i_e]=ligne_originale[i_o];
                    i_e++;
                }
                else{
                    i_o--;
                }
                etat=COPY;
            }
            break;
        }
        i_o++;
    }
    ligne_expansee[i_e]='\0';
}
```


