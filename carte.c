/*!=======================!*/
/*! Auteur: Victor Illien !*/
/*! Nom: carte.c          !*/
/*! Date: 21/06/19        !*/
/*!=======================!*/ 

#include "fonction.h"

/*!==============================================!*/
/*! Fonction: recupArg                           !*/
/*! Rôle: Récupère la carte lors de la saisie de !*/
/*!       la commande d'exécution                !*/
/*! Paramètres:                                  !*/
/*!			E: int, char **                      !*/  
/*!			S: N/A                               !*/
/*! Retour: char *                               !*/
/*!==============================================!*/
char *recupArg(int const argc, char const **argv) {

	char *nomFichier;
	nomFichier = malloc(TAILLE_NOM * sizeof(char));

	//On vérifie s'il y a le bon nombre d'arguments sur la ligne de commande
	if (argc != 2) {
		printf("Erreur, nombre d'arguments erronés, vous avez saisis %d au lieu de 2 arguments\n", argc);
	}

	//On copie le deuxième argument de la ligne de commande dans notre variable.
	strcpy(nomFichier, argv[1]);

	return nomFichier;
}

/*!=========================================================!*/
/*! Fonction: initCarte                                     !*/
/*! Rôle: Initialise la carte en la récupérant dans le .txt !*/
/*!       Et lui alloue la place mémoire nécéssaire         !*/
/*! Paramètres:                                             !*/
/*!			E: char *                                       !*/  
/*!			S: N/A                                          !*/
/*! Retour: struct Carte                                    !*/
/*!=========================================================!*/
Carte initCarte(const char *nomFichier) {

	Carte carteRecup;
	FILE *fichier;
	char ligne[TAILLE_MAX_LIGNE];
	int i = 0;

	//On ouvre le .txt en lecture seule et on vérifie si l'ouverture se fait bien
	if ((fichier = fopen(nomFichier,"r")) == NULL) {
		printf("Erreur à l'ouverture du fichier\n");
	}

	//On enlève les ':' de la première ligne pour récuperer la hauteur et la largeur de notre tableau 
	fgets(ligne, TAILLE_MAX_LIGNE, fichier);
	char *ptr = strchr(ligne, ':');
	*ptr = '\0';
	ptr++;
	carteRecup.largeur = atoi(ligne);
	carteRecup.hauteur = atoi(ptr);

	//On alloue la place mémoire nécessaire à notre tableau
	carteRecup.tabCarte = (char**) malloc(carteRecup.hauteur * sizeof(char *));
	for (int i = 0; i < carteRecup.hauteur; ++i) {

		carteRecup.tabCarte[i] = (char *) malloc(carteRecup.largeur * sizeof(int));
	}
	
	//On parcours le fichier et le tableau pour copier chaque ligne
	while(fgets(ligne, TAILLE_MAX_LIGNE, fichier)) {
	
		strcpy(carteRecup.tabCarte[i], ligne);
		i ++;
	}

	//On ferme le fichier
	fclose(fichier);
	return carteRecup;
}

/*!==============================================!*/
/*! Fonction: affichCarte                        !*/
/*! Rôle: Parcours la carte intégralement        !*/
/*!       Laisse un délai de 0.1 seconde         !*/
/*! Paramètres:                                  !*/
/*!			E: struct Carte, struct Robot, char  !*/  
/*!			S: N/A                               !*/
/*! Retour: void                                 !*/
/*!==============================================!*/
void affichCarte(Carte carte, Robot robot, char caracDevant) {

	for (int i = 0; i < carte.hauteur; ++i)
	{
		printf("\t");
		for (int j = 0; j < carte.largeur; ++j)
		{
			printf("%c", carte.tabCarte[i][j]);
		}
		printf("\n");
	}

	printf("\t*********************************\n");
	printf("\t* Caractère devant le robot: %c *\n", caracDevant);
	printf("\t* Nombre de pas effectué: %lld  *\n", robot.nbPas);
	printf("\t* Compteur de Pledge: %d        *\n", robot.compteurPledge);
	printf("\t*********************************\n");
	//Délai de 0.1 seconde
	usleep(30000);
}

/*!================================================================!*/
/*! Fonction: actualisationCarte                                   !*/
/*! Rôle: Remplace la dernière position de R par un .              !*/
/*!       Choix entre le mode graphique et le mode terminal        !*/
/*! Paramètres:                                                    !*/
/*!			E: struct Carte, struct Robot, struct Graph, int, char !*/  
/*!			S: N/A                                                 !*/
/*! Retour: void                                                   !*/
/*!================================================================!*/
void actualisationCarte(Carte carte, Robot robot, Graph graph, int choix1, char caracDevant) {
	
	//On remplace l'ancien R par un . et affecte le nouveau R
	carte.tabCarte[carte.robotY][carte.robotX] = '.';
	carte.tabCarte[robot.y][robot.x] = 'R';

	system("clear");

	if(choix1 == 1) affichCarte(carte, robot, caracDevant);
	else if(choix1 == 2) affichageGraph(robot, carte, graph);
	

}
