#include "fonction.h"

Robot findDepart(Carte carte) {

	Robot robotInit;
	char caracTemp;

	for (int i = 0; i < carte.hauteur; ++i) {
		for (int j = 0; j < carte.largeur; ++j)	{

			caracTemp = carte.tabCarte[i][j];
			if (caracTemp == 'D') {
				printf("%c\n", caracTemp);
				robotInit.x = j;
				robotInit.y = i;
				return robotInit;
			}
		}
	}
}

Robot remiseNiveau(Robot robot) {

	if (robot.direction == -4 || robot.direction == 4) robot.direction = 0;
	return robot;
}


Robot avancer(Robot robot) {


	if (robot.direction == -4 || robot.direction == 0) robot.y -= 1;
	if (robot.direction == -1 || robot.direction == 3) robot.x += 1;
	if (robot.direction == -2 || robot.direction == 2) robot.y += 1;
	if (robot.direction == -3 || robot.direction == 1) robot.x -= 1;
		
	return robot;	
}

Robot droite(Robot robot) {

	robot.direction -= 1;

	return robot;
}

Robot gauche(Robot robot) {

	robot.direction += 1;

	return robot;
}

char detectSortie(Robot robot, Carte carte) {

	char caracTemp;

	robot = gauche(robot);

	if ((caracTemp = capteurAvant(robot, carte)) == 'S')
	{
		printf("La sortie est trouvée\n");
		exit(1);
	} else {
		robot = droite(robot);
	}

	return caracTemp;
}

char capteurAvant(Robot robot, Carte carte) {

	char caracTemp;
	int ligne = robot.x;
	int colonne = robot.y;

	if (robot.direction == 0) caracTemp = carte.tabCarte[colonne - 1][ligne];
	if (robot.direction == -1 || robot.direction == 3) caracTemp = carte.tabCarte[colonne][ligne + 1];
	if (robot.direction == -2 || robot.direction == 2) caracTemp = carte.tabCarte[colonne + 1][ligne];
	if (robot.direction == -3 || robot.direction == 1) caracTemp = carte.tabCarte[colonne][ligne - 1];

	return caracTemp;
}

void deplacement(Robot robot, Carte carte) {

	char caractereFinal, caracSortie;

	do{

		robot = avancer(robot);
		caractereFinal = capteurAvant(robot, carte);
		caracSortie = detectSortie(robot, carte);
		if (caractereFinal == 'x')
		{
			robot = droite(robot);
		}

		if (caractereFinal == ' ' && caracSortie == ' ')
		{
			robot = gauche(robot);
		}
		caracSortie = detectSortie(robot, carte);
		actualisationCarte(carte, robot);
		printf("%c\n", caractereFinal);


	}while(caractereFinal != 'S');


}