#include "fonction.h"


int main(int argc, char const *argv[])
{
	//Déclarations des variables
	Carte carte;
	Robot robot;

	char *nomFichier;

	//Initialisation de la carte
	nomFichier = malloc(TAILLE_NOM * sizeof(char));
	nomFichier = recupArg(argc, argv);
	carte = initCarte(nomFichier);

	//Initialisation du Robot
	//printf("\x1b[0;0H");
	initCarteRobotMentale(&robot, carte);
	findDepart(carte, &robot);
	actualisationCarte(carte, &robot);
	robot.sortie = 0;
	robot.nbPas = 0;
	robot.sens = 0;
	robot.lastSens = 0;

	//Mise en marche du programme
	deplacement(&robot, carte);

	
	printf("fin\n");
	
	return 0;
}
