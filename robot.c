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


Robot avancer(Robot robot, Carte carte) {

	robot.visiter = 1;
	robot = check360(robot, carte);

	if (robot.nord == 0) robot.y -= 1; //Vers le haut
	else if (robot.est == 0) robot.x += 1;  //Vers la droite
	else if (robot.sud == 0) robot.y += 1;  //Vers le bas
	else if (robot.ouest == 0) robot.x -= 1;//Vers la gauche
	

	robot.direction = 0;
	robot.nbPas ++;
		
	return robot;	
}

Robot tourne90(Robot robot) {

	robot.direction -= 1;

	return robot;
}

char capteurAvantMur(Robot robot, Carte carte) {

	char caracTemp;
	int ligne = robot.x;
	int colonne = robot.y;
	if (robot.direction == 0) caracTemp = carte.tabCarte[colonne - 1][ligne];  //Nord +1 case
	if (robot.direction == -1) caracTemp = carte.tabCarte[colonne][ligne + 1]; //Est +1 case
	if (robot.direction == -2) caracTemp = carte.tabCarte[colonne + 1][ligne]; //Sud +1 case
	if (robot.direction == -3) caracTemp = carte.tabCarte[colonne][ligne - 1]; //Ouest +1 case

	printf("%c", caracTemp);
	return caracTemp;
}

int capteurAvantVisiter(Robot robot) {

	Robot robotTemp = robot;
	int etat = 0;

	if (robot.direction == 0)//Nord +1 case
	{
		robotTemp.y -= 1;
		etat = (robotTemp.visiter == 1) ? 1 : 0;
	}

	if (robot.direction == -1)//Est +1 case
	{
		robotTemp.x += 1;
		etat = (robotTemp.visiter == 1) ? 1 : 0;
	}

	if (robot.direction == -2)//Sud +1 case
	{
		robotTemp.y += 1;
		etat = (robotTemp.visiter == 1) ? 1 : 0;
	}

	if (robot.direction == -3)//Ouest +1 case
	{
		robotTemp.x -= 1;
		etat = (robotTemp.visiter == 1) ? 1 : 0;
	}

	printf(",etat %d\n", etat);
	return etat;
}

Robot check360(Robot robot, Carte carte) {

	char caracTemp;
	int etatTemp = 0;


	caracTemp = capteurAvantMur(robot, carte);
	etatTemp = capteurAvantVisiter(robot);
	if (caracTemp == 'S') robot.sortie = 1;
	else if (caracTemp == ' ' || etatTemp == 1) robot.nord = 0;
	else if (caracTemp == 'x' || etatTemp == 0) robot.nord = 1;
	printf("robot.nord: %d\n\n", robot.nord);
	robot = tourne90(robot);
	etatTemp = 0;

	caracTemp = capteurAvantMur(robot, carte);
	etatTemp = capteurAvantVisiter(robot);
	if (caracTemp == 'S') robot.sortie = 1;
	else if (caracTemp == ' ' || etatTemp == 1) robot.est = 0;
	else if (caracTemp == 'x' || etatTemp == 0) robot.est = 1;
	printf("robot.est: %d\n\n", robot.est);
	robot = tourne90(robot);
	etatTemp = 0;

	caracTemp = capteurAvantMur(robot, carte);
	etatTemp = capteurAvantVisiter(robot);
	if (caracTemp == 'S') robot.sortie = 1;
	else if (caracTemp == ' ' || etatTemp == 1) robot.sud = 0;
	else if (caracTemp == 'x' || etatTemp == 0) robot.sud = 1;
	printf("robot.sud: %d\n\n", robot.sud);
	robot = tourne90(robot);
	etatTemp = 0;

	caracTemp = capteurAvantMur(robot, carte);
	etatTemp = capteurAvantVisiter(robot);
	if (caracTemp == 'S') robot.sortie = 1;
	else if (caracTemp == ' ' || etatTemp == 1) robot.ouest = 0;
	else if (caracTemp == 'x' || etatTemp == 0) robot.ouest = 1;
	printf("robot.ouest: %d\n\n", robot.ouest);

	return robot;
}

int deplacement(Robot robot, Carte carte) {

	
		
	robot = avancer(robot, carte);

	carte.robotX = robot.x;
	carte.robotY = robot.y;
	actualisationCarte(carte, robot);
	if (robot.sortie == 0) deplacement(robot, carte);

	return 0;

	//else if go back



}