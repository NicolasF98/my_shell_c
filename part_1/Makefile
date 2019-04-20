all: interpreteur main_test_vars

interpreteur: systeme.o variables.o lignes.o interpreteur.o
	clang -o interpreteur systeme.o variables.o lignes.o interpreteur.o

main_test_vars: variables.o main_test_vars.o
	clang -o main_test_vars variables.o main_test_vars.o

lignes.o: lignes.c lignes.h
	clang -Wall -Werror -g -DDEBUG -c lignes.c

interpreteur.o: interpreteur.c systeme.h lignes.h debug.h variables.h \
 variables_base.h
	clang -Wall -Werror -g -DDEBUG -c interpreteur.c

systeme.o: systeme.c systeme.h debug.h
	clang -Wall -Werror -g -DDEBUG -c systeme.c

variables.o: variables.c debug.h variables.h variables_base.h
	clang -Wall -Werror -g -DDEBUG -c variables.c

main_test_vars.o: main_test_vars.c variables.h variables_base.h
	clang -Wall -Werror -g -DDEBUG -c main_test_vars.c

clean:
	rm *.o interpreteur main_test_vars
