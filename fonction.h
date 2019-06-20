#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 200
#define TAILLE_NOM 20
#define NORD 0
#define EST 1
#define SUD 2
#define OUEST 3

typedef struct Carte {
	char **tabCarte;
	int hauteur, largeur;
	int robotX, robotY;
} Carte;

typedef struct Robot {
	int x, y;
	long long nbPas;
	int compteurPledge;

} Robot;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte, Robot robot);
void actualisationCarte(Carte carte, Robot robot);


//Fonction Robot
Robot findDepart(Carte carte);
int deplacement(Robot *robot, Carte carte);
char detecteDevant(Robot robot, Carte carte);
char detecteCote(Robot *robot, Carte carte);
void avancer(Robot *robot, Carte carte);
void droite(Robot *robot);
void gauche(Robot *robot);