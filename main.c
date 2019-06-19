#include "fonction.h"


int main(int argc, char const *argv[])
{
	//Déclarations des variables
	Carte carte;
	Robot *robot = NULL;
	char *nomFichier;
	int tailleMaxCarte;


	//Initialisation de la carte
	nomFichier = malloc(TAILLE_NOM * sizeof(char));
	nomFichier = recupArg(argc, argv);
	carte = initCarte(nomFichier);


	//Initialisation du Robot
	tailleMaxCarte = carte.largeur * carte.hauteur;
	robot = malloc(tailleMaxCarte * sizeof(Robot));

	findDepart(carte, robot);


	actualisationCarte(carte, robot);

	robot -> direction = 0;
	robot -> visiter = 1;
	robot -> sortie = 0;
	robot -> nbPas = 0;

	//Mise en marche du programme
	deplacement(robot, carte);

	printf("fin\n");
	free(robot);
	
	return 0;
}
