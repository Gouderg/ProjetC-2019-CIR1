#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 200
#define TAILLE_NOM 20


typedef struct Carte {
	char **tabCarte;
	int hauteur;
	int largeur;
	int robotX;
	int robotY;
} Carte;

typedef struct Robot {
	int x;
	int y;
	int nord;
	int sud;
	int est;
	int ouest;
	int nbPas;
	int direction;

} Robot;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte, Robot robot);
void actualisationCarte(Carte carte, Robot robot);


//Fonction Robot
Robot findDepart(Carte carte);
Robot remiseNiveau(Robot robot);
void deplacement(Robot robot, Carte carte);
Robot avancer(Robot robot);
Robot droite(Robot robot);
Robot gauche(Robot robot);

char detectSortie(Robot robot, Carte carte);
char capteurAvant(Robot robot, Carte carte);