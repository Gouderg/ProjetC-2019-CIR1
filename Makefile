Robot.exe: main.o lib.a
	gcc main.o lib.a -Wall -o Robot.exe

lib.a: robot.o carte.o
	ar rv lib.a robot.o carte.o

main.o: main.c fonction.h
	gcc -g -c main.c

robot.o: robot.c fonction.h
	gcc -c robot.c

carte.o: carte.c fonction.h
	gcc -c carte.c

clean:
	rm *.o *.a *.exe