#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAILLE_MAX_LIGNE 200   //Taille maximale d'une ligne d'un fichier
#define TAILLE_NOM 20          //Taille maximale du nom du fichier passé en argument
#define NORD 0
#define EST 1
#define SUD 2
#define OUEST 3

typedef struct Carte {
	char **tabCarte;           //Carte stocké
	int hauteur, largeur;      //Dimension du tableau
	int robotX, robotY;        //Coordonnées du robot sur la carte
	int xInit, yInit;          //Coordonnées initiales du robot
} Carte;

typedef enum Orientation {
	N, E, S, O
} Orientation;

typedef struct Robot {
	int x, y;                  //Coordonées du robot avant implémentaion sur la carte
	Orientation sens;          
	Orientation lastSens;       
	int direction;             //Variable temporaire pour regarder tout autour du robot
	long long nbPas;           //Nombre de pas effectué
	int sortie;                //Variable utilisé pour sortir (1:réussite)
	int **tabVisiter;

} Robot;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte);
void actualisationCarte(Carte carte, Robot *robot);


//Fonction Robot
void initCarteRobotMentale(Robot *robot, Carte carte);
void findDepart(Carte carte, Robot *robot);
int deplacement(Robot *robot, Carte carte);
void avancer(Robot *robot, Carte carte);
void marquerCase(Robot *robot, Carte carte);
char capteurAvantMur(Robot robot, Carte carte);
int capteurAvantVisiter(Robot robot);
int verification(Robot *robot, Carte carte);
int depthFirstSearch(Robot *robot, Carte carte);
void tourner90(Robot *robot);
int searchS(Robot robot, Carte carte);
int goBackSearch(Robot *robot, Carte carte);

