#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "systeme.h"
#include "debug.h"

int executer_ligne_decoupee(char *ligne_decoupee[]) {
    pid_t pid;
    int stat_loc;
    char *commande;
    int i;

    /* On traite le cas des crochets */
    if (strcmp(ligne_decoupee[0], "[") == 0) {
        debug("Je remplace les crochets par la commande test\n");
        ligne_decoupee[0] = "test";
        i = 1;
        while ((ligne_decoupee[i] != NULL) && (strcmp(ligne_decoupee[i], "]") != 0)) {
            i++;
        }
        if (ligne_decoupee[i] == NULL) {
            fprintf(stderr, "Erreur : crochet fermant manquant\n");
        } else {
            ligne_decoupee[i] = NULL;
            if (ligne_decoupee[i + 1] != NULL)
                fprintf(stderr, "Erreur : arguments supplementaires apres "
                        "le crochet fermant (ignores)\n");
        }
    }

    commande = ligne_decoupee[0];

    switch (pid = fork()) {
    case -1:
        fprintf(stderr, "Erreur dans execute : erreur de fork\n");
        return -1;
    case 0:
        debug("J'execute la commande : %s\n", ligne_decoupee[0]);
        debug("Avec les arguments :");
        i = 1;
        while (ligne_decoupee[i] != NULL) {
            debug(" %s", ligne_decoupee[i]);
            i++;
        }
        debug("\n");
        execvp(commande, ligne_decoupee);
        perror(commande);
        exit(-1);
    default:
        wait(&stat_loc);
        debug("Code de retour de la commande : %d\n", stat_loc);
        if (WIFEXITED(stat_loc)) {
            return WEXITSTATUS(stat_loc);
        } else {
            fprintf(stderr, "Commande terminee par un signal : anormal\n");
            return WTERMSIG(stat_loc);
        }
    }
}
