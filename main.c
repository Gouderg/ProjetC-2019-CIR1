#include "fonction.h"


int main(int argc, char const *argv[])
{
	//Déclarations des variables
	Carte carte;
	Robot robot;
	char *nomFichier;
	int fin = 0;

	//Initialisation de la carte
	nomFichier = malloc(TAILLE_NOM * sizeof(char));
	nomFichier = recupArg(argc, argv);
	carte = initCarte(nomFichier);
	carte.robotX = 0;
	carte.robotY = 0;
	
	//Initialisation du Robot
	robot = findDepart(carte);
	actualisationCarte(carte, robot);
	robot.compteurPledge = 0;

	//Mise en marche du programme
	fin = deplacement(&robot, carte);

	if(fin == 1) printf("Vous êtes sortie du labyrinthe en %lld pas\n", robot.nbPas);
	if(fin == 0) printf("Ce labyrinthe n'a pas de sortie sur mon chemin\n");


	
	return 0;
}
