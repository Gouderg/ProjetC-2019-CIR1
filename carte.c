#include "fonction.h"

char *recupArg(int const argc, char const **argv) {

	char *nomFichier;
	nomFichier = malloc(TAILLE_NOM * sizeof(char));

	if (argc != 2) {
		printf("Erreur, nombre d'arguments erronés, vous avez saisis %d au lieu de 2 arguments\n", argc);
	}

	strcpy(nomFichier, argv[1]);

	return nomFichier;
}

Carte initCarte(const char *nomFichier) {

	Carte carteRecup;
	FILE *fichier;
	char ligne[TAILLE_MAX_LIGNE];
	int i = 0;

	if ((fichier = fopen(nomFichier,"r")) == NULL) {
		printf("Erreur à l'ouverture du fichier\n");
	}

	fgets(ligne, TAILLE_MAX_LIGNE, fichier);
	char *ptr = strchr(ligne, ':');
	*ptr = '\0';
	ptr++;
	carteRecup.largeur = atoi(ligne);
	carteRecup.hauteur = atoi(ptr);

	carteRecup.tabCarte = (char**) malloc(carteRecup.hauteur * sizeof(char *));
	for (int i = 0; i < carteRecup.hauteur; ++i) {

		carteRecup.tabCarte[i] = (char *) malloc(carteRecup.largeur * sizeof(int));
	}
	
	while(fgets(ligne, TAILLE_MAX_LIGNE, fichier)) {
	
		strcpy(carteRecup.tabCarte[i], ligne);
		i ++;
	}

	fclose(fichier);
	return carteRecup;
}

void affichCarte(Carte carte, Robot robot) {

	getchar();
	for (int i = 0; i < carte.hauteur; ++i)
	{
		for (int j = 0; j < carte.largeur; ++j)
		{
			printf("%c", carte.tabCarte[i][j]);
		}
		printf("\n");
	}
}

void actualisationCarte(Carte carte, Robot robot) {

	
	int ligne = robot.x;
	int colonne = robot.y;
	
	carte.tabCarte[carte.robotY][carte.robotX] = '.';
	carte.tabCarte[colonne][ligne] = 'R';

	affichCarte(carte, robot);

}
