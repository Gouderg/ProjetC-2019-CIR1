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
	robot = findDepart(carte);
	actualisationCarte(carte, robot);
	robot.direction = 0;
	robot.visiter = 1;
	robot.sortie = 0;
	robot.nbPas = 0;

	//Mise en marche du programme
	deplacement(robot, carte);

	printf("Vous êtes sorti du labyrinthe\n");
	printf("Nombre de pas: %lld\n", robot.nbPas);
	
	return 0;
}
