#include <stdio.h>               //Directive du préprocesseur
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


#define TAILLE_MAX_LIGNE 200     //Taille maximale d'une ligne de notre .txt
#define TAILLE_NOM 20            //Taille maximale du nom du .txt
#define TAILLE_PIXEL 15
#define NORD 0					 
#define EST 1
#define SUD 2
#define OUEST 3

//Structure conservant les infos de la carte
typedef struct Carte {           
	char **tabCarte;             //Tableau à double dimension qui conserve la carte
	int hauteur, largeur;        //Hauteur et largeur de la carte
	int robotX, robotY;          //Position précèdante du robot
} Carte;

//Structure conservant les infos du robot
typedef struct Robot {
	int x, y;                    //Coordonnées du robot sur la carte
	long long nbPas;             //Nombre de pas depuis le départ
	int compteurPledge;          //Compteur de Pledge comptant les changements de direction
} Robot;

typedef struct Graph {
	SDL_Surface *ecran;
	SDL_Surface *sortie;
	SDL_Surface *mur;
	SDL_Surface *robot;
	SDL_Surface *trace;

} Graph;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte, Robot robot);
void actualisationCarte(Carte carte, Robot robot, Graph graph, int choix1);


//Fonction Robot Pledge
Robot findDepart(Carte carte);
int deplacement(Robot *robot, Carte carte, Graph graph, int choix1);
char detecteDevant(Robot robot, Carte carte);
char detecteCote(Robot *robot, Carte carte);
void avancer(Robot *robot, Carte carte, Graph graph, int choix1);
void droite(Robot *robot);
void gauche(Robot *robot);

//Fonction graphique
void menu(Robot robot, Carte carte, Graph graph);
void sousMenu(Robot robot, Carte carte, Graph graph, int choix1, int choix2);
Graph initGraph(Carte carteGraphique);
void affichageGraph(Robot robot, Carte carte, Graph graph);
void murGraph(int x, int y, Graph graph);
void sortieGraph(int x, int y, Graph graph);
void traceGraph(int x, int y, Graph graph);
void murGraph(int x, int y, Graph graph);