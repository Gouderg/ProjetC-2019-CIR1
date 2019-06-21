#include "fonction.h"

void initCarteRobotMentale(Robot *robot, Carte carte) {

	//Allocation dynamique de la mémoire
	robot -> tabVisiter = (int**) malloc(carte.hauteur * sizeof(int *));
	for (int i = 0; i < carte.hauteur; ++i) {

		robot -> tabVisiter[i] = (int *) malloc((carte.largeur + 2) * sizeof(int));
	}

	//Initialisation de toute les cases à 0
	for (int i = 0; i < carte.hauteur; ++i)
	{
		for (int j = 0; j < carte.largeur; ++j)
		{
			robot -> tabVisiter[i][j] = 0;
		}
	}

}

void findDepart(Carte carte, Robot *robot) {

	char caracTemp;

	for (int i = 0; i < carte.hauteur; ++i) {
		for (int j = 0; j < carte.largeur; ++j)	{

			caracTemp = carte.tabCarte[i][j];
			if (caracTemp == 'D') {
				robot -> x = j;
				robot -> y = i;
				carte.xInit = j;
				carte.yInit = i;
			}
		}
	}
	
}

char capteurAvantMur(Robot robot, Carte carte) {

	char caracTemp;
	int ligne = robot.x;
	int colonne = robot.y;

	if (robot.sens == NORD) caracTemp = carte.tabCarte[colonne - 1][ligne];  //Nord +1 case
	if (robot.sens == EST) caracTemp = carte.tabCarte[colonne][ligne + 1]; //Est +1 case
	if (robot.sens == SUD) caracTemp = carte.tabCarte[colonne + 1][ligne]; //Sud +1 case
	if (robot.sens == OUEST) caracTemp = carte.tabCarte[colonne][ligne - 1]; //Ouest +1 case

	return caracTemp;
}

int capteurAvantVisiter(Robot robot) {

	int visiterPlus1 = 0;
	int ligne = robot.x;
	int colonne = robot.y;

	if (robot.sens == NORD) visiterPlus1 = robot.tabVisiter[colonne - 1][ligne];
	if (robot.sens == EST) visiterPlus1 = robot.tabVisiter[colonne][ligne + 1];
	if (robot.sens == SUD) visiterPlus1 = robot.tabVisiter[colonne + 1][ligne];
	if (robot.sens == OUEST) visiterPlus1 = robot.tabVisiter[colonne][ligne - 1];

	printf("robot sens: %d\n", robot.sens);
	return visiterPlus1;
}

int verification(Robot *robot, Carte carte) {

	int retour = 0, visiterPlus1 = 0;
	char caracTemp;

	visiterPlus1 = capteurAvantVisiter(*robot);
	caracTemp = capteurAvantMur(*robot, carte);
	//printf("Caractere: %c, visiter devant: %d\n\n", caracTemp, visiterPlus1);

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


void avancer(Robot *robot, Carte carte) {

	carte.robotX = robot -> x;
	carte.robotY = robot -> y;


	if (robot -> sens == NORD) robot -> y -= 1;      //Vers le haut
	if (robot -> sens == EST) robot -> x += 1;  	//Vers la droite
	if (robot -> sens == SUD) robot -> y += 1;  	//Vers le bas
	if (robot -> sens == OUEST) robot -> x -= 1;	//Vers la gauche
	
	
	actualisationCarte(carte, robot);
	printf("x: %d, y: %d\n", robot -> x, robot -> y);
	robot -> nbPas ++;
}

void marquerCase(Robot *robot, Carte carte) {

	robot -> tabVisiter[robot -> y][robot -> x] = 1;
	/*for (int i = 0; i < carte.hauteur; ++i)
	{
		for (int j = 0; j < carte.largeur; ++j)
		{
			printf("%d", robot -> tabVisiter[i][j]);
		}
		printf("\n");
	}*/
}

void tourner90(Robot *robot) {

	robot -> sens = (robot -> sens + 1) % 4;
}

int searchS(Robot robot, Carte carte) {

	Robot robotTemp = robot;

	char retourTemp = 0;
	int sortie = 0;
	robotTemp.sens = 0;

	for (int i = 0; i < 4; ++i)	{

		robotTemp.sens = i;
		retourTemp = capteurAvantMur(robotTemp, carte);
		//printf("retourTemp n°%d: %c\n", i, retourTemp);
		if (retourTemp == 'S') {
			
			sortie = 1;
			break;
		}

	}
	return sortie;
}

int goBackSearch(Robot *robot, Carte carte) {

	Robot robotTemp = *robot;

	char retourTemp = 0;
	int sortie = 1;
	robotTemp.sens = 0;

	for (int i = 0; i < 4; ++i)	{

		robotTemp.sens = i;
		retourTemp = capteurAvantMur(robotTemp, carte);
		printf("retourTemp n°%d: %c\n", i, retourTemp);
		if (retourTemp == ' ') {
			
			sortie = 0;
			robot -> sens = robotTemp.sens;
			break;
		}

	}
	return sortie;
}

int depthFirstSearch(Robot *robot, Carte carte) {

	int retour = 0, impossible = 0;
	robot -> sens = 0; //Remise au Nord
	marquerCase(robot, carte);

	for (int i = 0; i < 4; ++i) {

		robot -> sortie = searchS(*robot, carte);
		retour = verification(robot, carte);
		if (robot -> sortie == 1) return 0;
		if(retour == 0 && robot -> sortie == 0) {

			robot -> lastSens = robot -> sens;
			avancer(robot, carte);
			depthFirstSearch(robot, carte);
		} else {
			tourner90(robot);
			impossible ++;
			printf("impossible: %d\n", impossible);
		}
		if (impossible == 4){
			while (retour != 0) {
				printf("GO backkkkkkk\n");
				robot -> sens =  robot -> lastSens;
				
				tourner90(robot);
				tourner90(robot);
				
				printf("robot.lastSens: %d\n", robot -> lastSens);
				printf("robot.Sens: %d\n", robot -> sens);
				avancer(robot, carte);
				tourner90(robot);
				tourner90(robot);
				retour = goBackSearch(robot, carte);
				impossible = 0;
				printf("retour: %d\n", retour);

			}
			avancer(robot, carte);
		}

	

	}

	
}

int deplacement2(Robot *robot, Carte carte) {
	
	depthFirstSearch(robot,carte);
	
	printf("Vous êtes sortie du labyrinthe\n");
	printf("Nombre de pas: %lld\n", robot -> nbPas);
	return 0;

}