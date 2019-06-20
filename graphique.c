#include "fonction.h"

void menu(Robot robot, Carte carte, Graph graph) {

	int choix1 = 0, choix2 = 0;

	printf("\t*--------------------Bienvenue sur notre solveur de labyrinthe--------------------*\n");
	printf("\t*                                                                                 *\n");
	printf("\t* Comment voulez-vous voir votre labyrinthe se résoudre ?                         *\n");
	printf("\t*                                                                                 *\n");
	printf("\t* 1- En mode terminal\n");
	printf("\t* 2- En mode graphique\n");
	printf("\t* Votre choix: ");
	scanf("%d", &choix1);
	getchar();
	printf("\t*                                                                                 *\n");
	printf("\t*                                                                                 *\n");
	printf("\t* Quel algorithme voulez-vous utiliser ?                                          *\n");
	printf("\t* 1- L'algorithme de Pledge                                                       *\n");
	printf("\t* 2- L'algorithme de Trémaux                                                      *\n");
	printf("\t* Votre choix: "); 
	scanf("%d", &choix2);
	getchar();
	printf("\t*                                                                                 *\n");
	printf("\t*---------------------------------------------------------------------------------*\n");

	switch(choix1) {

		case 1:
			sousMenu(robot, carte, graph, choix1, choix2);
			break;

		case 2:
			graph = initGraph(carte);
			sousMenu(robot, carte, graph, choix1, choix2);
			break;

		default:
			printf("Vous avez effectué une mauvaise saisie dans votre premier choix\n");
			break;


	}
}

void sousMenu(Robot robot, Carte carte, Graph graph, int choix1, int choix2) {

	int fin = 0;

	switch(choix2) {

		case 1:
			fin = deplacement(&robot, carte, graph, choix1);
			break;

		case 2:
			printf("Programme en cours de codage\n");
			break;

		default:
			printf("Vous avez effectué une mauvaise saisie dans votre deuxième choix\n");
			break;
	}

	if(fin == 1) printf("Bien jouer vous êtes sortis du labyrinthe en %lld pas\n", robot.nbPas);
}

Graph initGraph(Carte carteGraphique) {

	Graph graph;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {

		fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	graph.ecran = SDL_SetVideoMode(carteGraphique.largeur * TAILLE_PIXEL, carteGraphique.hauteur * TAILLE_PIXEL, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	graph.mur = IMG_Load("image/mur.png");
	graph.robot = IMG_Load("image/robot.png");
	graph.trace = IMG_Load("image/trace.png");
	graph.sortie = IMG_Load("image/sortie.png"); 

	if(graph.ecran == NULL || graph.mur == NULL || graph.robot == NULL || graph.trace == NULL || graph.sortie == NULL) {

		fprintf(stderr, "Impossible de charger le mode vidéo ou vos images: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("LABYRINTHE", NULL);
	SDL_FillRect(graph.ecran, NULL, 0x04b7f5);

	SDL_Flip(graph.ecran);
	return graph;
}

void murGraph(int x, int y, Graph graph) {

	SDL_Rect mur;

	mur.x = x * TAILLE_PIXEL;
	mur.y = y * TAILLE_PIXEL;

	SDL_BlitSurface(graph.mur, NULL, graph.ecran, &mur);
}

void traceGraph(int x, int y, Graph graph) {

	SDL_Rect trace;

	trace.x = x * TAILLE_PIXEL;
	trace.y = y * TAILLE_PIXEL;

	SDL_BlitSurface(graph.trace, NULL, graph.ecran, &trace);
}

void sortieGraph(int x, int y, Graph graph) {

	SDL_Rect sortie;

	sortie.x = x * TAILLE_PIXEL;
	sortie.y = y * TAILLE_PIXEL;

	SDL_BlitSurface(graph.sortie, NULL, graph.ecran, &sortie);
}

void robotGraph(int x, int y, Graph graph) {

	SDL_Rect robot;

	robot.x = x * TAILLE_PIXEL;
	robot.y = y * TAILLE_PIXEL;

	SDL_BlitSurface(graph.robot, NULL, graph.ecran, &robot);
}

void affichageGraph(Robot robot, Carte carte, Graph graph) {

	for(int y = 0; y < carte.hauteur; ++y)	{

		for(int x = 0; x < carte.largeur; ++x)	{

			if(carte.tabCarte[y][x] == 'x')  murGraph(x,y,graph);
			else if(carte.tabCarte[y][x] == '.') traceGraph(x,y,graph);
			else if(carte.tabCarte[y][x] == 'S') sortieGraph(x,y,graph);
			else if(carte.tabCarte[y][x] == 'R') robotGraph(x,y,graph);
				
		}
	}

	SDL_Flip(graph.ecran);
	usleep(10000);

}
