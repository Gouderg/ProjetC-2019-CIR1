Robot.exe: main.o lib.a
	gcc main.o lib.a -Wall -lSDL -lSDL_image -lm -o Robot.exe

lib.a: robot.o carte.o graphique.o
	ar rv lib.a robot.o carte.o graphique.o

main.o: main.c fonction.h
	gcc -g -c main.c

robot.o: robot.c fonction.h
	gcc -g -c robot.c

carte.o: carte.c fonction.h 
	gcc -g -c carte.c

graphique.o: graphique.c fonction.h
	gcc -g -c graphique.c

clean:
	rm *.o *.a *.exe