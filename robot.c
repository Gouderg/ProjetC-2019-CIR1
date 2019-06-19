#include "fonction.h"

void findDepart(Carte carte, Robot *robot) {

	char caracTemp;

	for (int i = 0; i < carte.hauteur; ++i) {
		for (int j = 0; j < carte.largeur; ++j)	{

			caracTemp = carte.tabCarte[i][j];
			if (caracTemp == 'D') {
				robot -> x = j;
				robot -> y = i;
				printf("xDebut: %d, yDebut: %d\n", j,i);
				carte.xInit = j;
				carte.yInit = i;
			}
		}
	}
}


void tourne90(Robot *robot) {

	robot -> direction -= 1;

}

char capteurAvantMur(Robot *robot, Carte carte) {

	char caracTemp;
	int ligne = robot -> x;
	int colonne = robot -> y;

	printf("Colonne: %d, Ligne: %d \n", robot -> x, robot -> y);

	if (robot -> direction == NORD) caracTemp = carte.tabCarte[colonne - 1][ligne];  //Nord +1 case
	if (robot -> direction == EST) caracTemp = carte.tabCarte[colonne][ligne + 1]; //Est +1 case
	if (robot -> direction == SUD) caracTemp = carte.tabCarte[colonne + 1][ligne]; //Sud +1 case
	if (robot -> direction == OUEST) caracTemp = carte.tabCarte[colonne][ligne - 1]; //Ouest +1 case

	return caracTemp;
}

int capteurAvantVisiter(Robot *robot) {

	Robot robotTemp = *robot;

	int visiterPlus1 = 0;

	if (robot -> direction == NORD) { //Nord +1 case
	
		robotTemp.y -= 1;
		visiterPlus1 = (robotTemp.visiter == 0) ? 0 : 1;
	}

	if (robot -> direction == EST) { //Est +1 case
	
		robotTemp.x += 1;
		visiterPlus1 = (robotTemp.visiter == 0) ? 0 : 1;
	}

	if (robot -> direction == SUD) { //Sud +1 case
	
		robotTemp.y += 1;
		visiterPlus1 = (robotTemp.visiter == 0) ? 0 : 1;
	}

	if (robot -> direction == OUEST) { //Ouest +1 case
	
		robotTemp.x-= 1;
		visiterPlus1 = (robotTemp.visiter == 0) ? 0 : 1;
	}

	return visiterPlus1;
}

int verification(char caracTemp, int visiterPlus1, Robot *robot) {

	int retour = 0;

	switch(caracTemp) {

		case 'S':
			robot -> sortie = 1;
			break;

		case 'x':
		case '.':
			retour = 1;
			break;

		case ' ':
			if (visiterPlus1 == 0) retour = 0;
			if (visiterPlus1 == 1) retour = 1;
			break;
	}

	return retour;
}

void check360(Robot *robot, Carte carte) {

	char caracTemp;
	int visiterPlus1 = 0;
	robot -> direction = 0;

	//Nord
	caracTemp = capteurAvantMur(robot, carte);
	visiterPlus1 = capteurAvantVisiter(robot);
	robot -> nord = verification(caracTemp, visiterPlus1, robot);
	printf("visiterPlus1: %d, caracTemp: %c\n", visiterPlus1, caracTemp);
	printf("robot.nord: %d\n\n", robot -> nord);
	tourne90(robot);
	visiterPlus1 = 0;

	//Est
	caracTemp = capteurAvantMur(robot, carte);
	visiterPlus1 = capteurAvantVisiter(robot);
	printf("visiterPlus1: %d, caracTemp: %c\n", visiterPlus1, caracTemp);
	robot -> est = verification(caracTemp, visiterPlus1, robot);
	printf("robot.est: %d\n\n", robot -> est);
	tourne90(robot);
	visiterPlus1 = 0;

	//Sud
	caracTemp = capteurAvantMur(robot, carte);
	visiterPlus1 = capteurAvantVisiter(robot);
	printf("visiterPlus1: %d, caracTemp: %c\n", visiterPlus1, caracTemp);
	robot -> sud = verification(caracTemp, visiterPlus1, robot);
	printf("robot.sud: %d\n\n", robot -> sud);
	tourne90(robot);
	visiterPlus1 = 0;

	//Ouest
	caracTemp = capteurAvantMur(robot, carte);
	visiterPlus1 = capteurAvantVisiter(robot);
	printf("visiterPlus1: %d, caracTemp: %c\n", visiterPlus1, caracTemp);
	robot -> ouest = verification(caracTemp, visiterPlus1, robot);
	printf("robot.ouest: %d\n\n", robot -> ouest);

}

void avancer(Robot *robot, Carte carte) {

	carte.robotX = robot -> x;
	carte.robotY = robot -> y;

	if (robot -> nord == 0) robot -> y -= 1;      //Vers le haut
	else if (robot -> est == 0) robot -> x += 1;  //Vers la droite
	else if (robot -> sud == 0) robot -> y += 1;  //Vers le bas
	else if (robot -> ouest == 0) robot -> x -= 1;//Vers la gauche
	
	
	actualisationCarte(carte, robot);
	robot -> nbPas ++;
}

int depthFirstSearch(Robot *robot, Carte carte) {

	robot -> visiter = 0;
	check360(robot, carte);

	
	if (robot -> nord == 0 && robot -> sortie == 0) {
		
		avancer(robot, carte);
		depthFirstSearch(robot, carte);
	}

	if (robot -> est == 0 && robot -> sortie == 0) {
		
		avancer(robot, carte);
		depthFirstSearch(robot, carte);
	}

	if (robot -> sud == 0 && robot -> sortie == 0) {
		
		avancer(robot, carte);
		depthFirstSearch(robot, carte);
	}

	if (robot -> ouest == 0 && robot -> sortie == 0) {
		
		avancer(robot, carte);
		depthFirstSearch(robot, carte);
	}

	if (robot -> sortie == 1) return 0;

	if (robot -> nord == 1 && robot -> est == 1 && robot -> sud == 1 && robot -> ouest == 1) {
		
		tourne90(robot);
		tourne90(robot);
		while(robot -> nord == 1 && robot -> est == 1 && robot -> sud == 1 && robot -> ouest == 1) {

			avancer(robot, carte);
		}
		return 1;
	}

	//printf("Zut, un cul de sac\n");
	/*if (carte.xInit == robot -> x && carte.yInit == robot -> y) {
		
		printf("Ce labyrinthe n'a pas de sortie.\n");
		return 1;
	}*/

}

int deplacement(Robot *robot, Carte carte) {

	depthFirstSearch(robot,carte);
	
	printf("Vous êtes sortie du labyrinthe\n");
	printf("Nombre de pas: %lld\n", robot -> nbPas);
	return 0;

}
