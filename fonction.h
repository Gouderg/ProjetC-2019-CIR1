#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 200   //Taille maximale d'une ligne d'un fichier
#define TAILLE_NOM 20          //Taille maximale du nom du fichier passé en argument


typedef struct Carte {
	char **tabCarte;           //Tableau stocké
	int hauteur, largeur;      //Dimension du tableau
	int robotX, robotY;        //Coordonées du robot sur la carte
} Carte;

typedef struct Robot {
	int x, y;                  //Coordonées du robot avant implémentaion sur la carte
	int nord, ouest, sud, est; //Rose des vents indiquant la présence de chemin possible (impossible:1, possible:0)
	int visiter;               //Si la cellule est visité:0 ou non:1
	int direction;             //Variable temporaire pour regarder tout autour du robot
	long long nbPas;           //Nombre de pas effectué
	int sortie;                //Variable utilisé pour sortir (1:réussite)

} Robot;

//Fonction Carte
char *recupArg(int const argc, char const **argv);
Carte initCarte(const char *nomFichier);
void affichCarte(Carte carte, Robot robot);
void actualisationCarte(Carte carte, Robot robot);


//Fonction Robot
Robot findDepart(Carte carte);
int deplacement(Robot robot, Carte carte);
Robot avancer(Robot robot, Carte carte);
Robot tourne90(Robot robot);
char capteurAvantMur(Robot robot, Carte carte);
int capteurAvantVisiter(Robot robot);
Robot check360(Robot robot, Carte carte);

