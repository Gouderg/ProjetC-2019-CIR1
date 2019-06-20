#include "fonction.h"

Robot findDepart(Carte carte) {

	Robot robotInit;
	char caracTemp;

	for (int i = 0; i < carte.hauteur; ++i) {
		for (int j = 0; j < carte.largeur; ++j)	{

			caracTemp = carte.tabCarte[i][j];
			if (caracTemp == 'D') {
				robotInit.x = j;
				robotInit.y = i;
				return robotInit;
			}
		}
	}
}

char detecteDevant(Robot robot, Carte carte) {

	char caracDevant;
	int cap = robot.compteurPledge % 4;
	int ligne = robot.x;
	int colonne = robot.y;

	if(cap == NORD) caracDevant = carte.tabCarte[colonne - 1][ligne];
	if(cap == EST) caracDevant = carte.tabCarte[colonne][ligne + 1];
	if(cap == SUD) caracDevant = carte.tabCarte[colonne + 1][ligne];
	if(cap == OUEST) caracDevant = carte.tabCarte[colonne][ligne - 1];

	printf("Caractere devant: %c\n", caracDevant);
	return caracDevant;
}

void avancer(Robot *robot, Carte carte) {

	int cap = robot -> compteurPledge % 4;

	carte.robotX = robot -> x;
	carte.robotY = robot -> y;

	if(cap == NORD) robot -> y --;
	if(cap == EST) robot -> x ++;
	if(cap == SUD) robot -> y ++;
	if(cap == OUEST) robot -> x --;

	actualisationCarte(carte, *robot);
	robot -> nbPas++;
}

void droite(Robot *robot) {

	robot -> compteurPledge ++;
}

void gauche(Robot *robot) {

	robot -> compteurPledge --;
}

char detecteCote(Robot *robot,  Carte carte) {

	char caracCote;

	gauche(robot);
	caracCote = detecteDevant(*robot, carte);
	droite(robot);

	return caracCote;
}

int deplacement(Robot *robot, Carte carte) {

	char caracDevant, caracCote;
	int fin = 0;

	while((caracDevant = detecteDevant(*robot, carte)) != 'x') {

		if (caracDevant == 'S') return fin = 1;
		avancer(robot, carte);
	}
	
	droite(robot);

	do {
		caracDevant = detecteDevant(*robot, carte);
		caracCote = detecteCote(robot, carte);

		if(caracCote == 'S') return fin = 1;
		
		if(caracDevant == ' ' && caracCote == 'x') avancer(robot, carte);
		
		if(caracDevant == ' ' && caracCote == ' ') {
			gauche(robot);
			avancer(robot, carte);
		}

		if(caracDevant == 'x' && caracCote == 'x') {
			droite(robot);
			avancer(robot, carte);
		}

		if (caracDevant == '.') return fin = 0;



	}while(robot -> compteurPledge != 0);

	deplacement(robot, carte);

}


