/*!=======================!*/
/*! Auteur: Victor Illien !*/
/*! Nom: main.c           !*/
/*! Date: 21/06/19        !*/
/*!=======================!*/ 

#include "fonction.h"

int main(int argc, char const *argv[])
{
	//Déclarations des variables
	Carte carte;
	Robot robot;
	Graph graph;
	char *nomFichier;

	//Initialisation de la carte
	nomFichier = malloc(TAILLE_NOM * sizeof(char));
	nomFichier = recupArg(argc, argv);
	carte = initCarte(nomFichier);
	carte.robotX = 0;
	carte.robotY = 0;
	
	//Initialisation du Robot
	robot = findDepart(carte);
	robot.compteurPledge = 0;
	

	//Mise en marche du programme
	menu(robot, carte, graph);

	
	return 0;
}