#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAILLE_MAX_LIGNE 200   //Taille maximale d'une ligne d'un fichier
#define TAILLE_NOM 20          //Taille maximale du nom du fichier passé en argument
#define NORD 0
#define EST -1
#define SUD -2
#define OUEST -3

typedef struct Carte {
	char **tabCarte;           //Carte stocké
	int hauteur, largeur;      //Dimension du tableau
	int robotX, robotY;        //Coordonnées du robot sur la carte
	int xInit, yInit;          //Coordonnées initiales du robot
} Carte;

typedef struct Robot {
	int x, y;                  //Coordonées du robot avant implémentaion sur la carte
	int nord, ouest, sud, est; //Rose des vents indiquant la présence de chemin possible (impossible:1, possible:0)
	int visiter;               //Si la cellule est visité:1 ou non:0
	int direction;             //Variable temporaire pour regarder tout autour du robot
	long long nbPas;           //Nombre de pas effectué
	int sortie;                //Variable utilisé pour sortir (1:réussite)
	int *autrePossibilite;

} Robot;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte);
void actualisationCarte(Carte carte, Robot *robot);


//Fonction Robot
void findDepart(Carte carte, Robot *robot);
int deplacement(Robot *robot, Carte carte);
void avancer(Robot *robot, Carte carte);
void tourne90(Robot *robot);
char capteurAvantMur(Robot *robot, Carte carte);
int capteurAvantVisiter(Robot *robot);
void check360(Robot *robot, Carte carte);
int verification(char caracTemp, int visiterPlus1, Robot *robot);


