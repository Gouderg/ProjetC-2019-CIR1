/*!=======================!*/
/*! Auteur: Victor Illien !*/
/*! Nom: robot.c          !*/
/*! Date: 21/06/19        !*/
/*!=======================!*/ 

#include "fonction.h"

/*!================================================!*/
/*! Fonction: findDepart                           !*/
/*! Rôle: Trouve le point de depart en parcourant  !*/
/*!       la carte                                 !*/
/*! Paramètres:                                    !*/
/*!			E: struct Carte                        !*/  
/*!			S: N/A                                 !*/
/*! Retour: struct robot                           !*/
/*!================================================!*/
Robot findDepart(Carte carte) {

	Robot robotInit;
	char caracTemp;

	robotInit.nbPas = 0;

	//On parcours la carte jusqu'à trouver le bon caractère
	for (int i = 0; i < carte.hauteur; ++i) {
		for (int j = 0; j < carte.largeur; ++j)	{
			caracTemp = carte.tabCarte[i][j];
			if (caracTemp == 'D') {
				robotInit.x = j;
				robotInit.y = i;
				return robotInit;
			}
		}
	}
}

/*!================================================!*/
/*! Fonction: detecteDevant                        !*/
/*! Rôle: Regarder la case en face du robot        !*/
/*! Paramètres:                                    !*/
/*!			E: struct Robot, struct Carte          !*/  
/*!			S: N/A                                 !*/
/*! Retour: char                                   !*/
/*!================================================!*/
char detecteDevant(Robot robot, Carte carte) {

	char caracDevant;
	//On ramène la direction à une valeur positive compris entre 0 et 3
	int cap = robot.compteurPledge % 4;

	//On compare le cap et on affecte à la variable le caractère devant le robot
	if(cap == NORD) caracDevant = carte.tabCarte[robot.y - 1][robot.x];
	if(cap == EST) caracDevant = carte.tabCarte[robot.y][robot.x + 1];
	if(cap == SUD) caracDevant = carte.tabCarte[robot.y + 1][robot.x];
	if(cap == OUEST) caracDevant = carte.tabCarte[robot.y][robot.x - 1];

	return caracDevant;
}

/*!================================================!*/
/*! Fonction: detecteCote                          !*/
/*! Rôle: Regarder la case à gauche du robot       !*/
/*! Paramètres:                                    !*/
/*!			E: struct *Robot, struct Carte         !*/  
/*!			S: struct *Robot                       !*/
/*! Retour: char                                   !*/
/*!================================================!*/
char detecteCote(Robot *robot,  Carte carte) {

	char caracCote;

	gauche(robot);                            //On tourne à gauche
	caracCote = detecteDevant(*robot, carte); //On regarde devant 
	droite(robot);                            //On tourne à droite

	return caracCote;
}

/*!=================================================================!*/
/*! Fonction: avancer                                               !*/
/*! Rôle: Avancer de une case en fonction de l'orientation du robot !*/ 
/*! Paramètres:                                                     !*/
/*!			E: struct *Robot, struct Carte, struct Graph, int, char !*/  
/*!			S: struct *Robot                                        !*/
/*! Retour: void                                                    !*/
/*!=================================================================!*/
void avancer(Robot *robot, Carte carte, Graph graph, int choix1, char caracDevant) {

	//On ramène la direction à une valeur positive compris entre 0 et 3
	int cap = robot -> compteurPledge % 4;

	//On conserve les coordonnées précédentes
	carte.robotX = robot -> x;
	carte.robotY = robot -> y;

	//En fonction du cap, on avance d'une case
	if(cap == NORD) robot -> y --;
	if(cap == EST) robot -> x ++;
	if(cap == SUD) robot -> y ++;
	if(cap == OUEST) robot -> x --;

	actualisationCarte(carte, *robot, graph, choix1, caracDevant);
	//On incrémente le compteur de pas
	robot -> nbPas++;
}

/*!================================================!*/
/*! Fonction: droite                               !*/
/*! Rôle: Tourne l'orientaion vers la droite       !*/
/*! Paramètres:                                    !*/
/*!			E: struct *Robot                       !*/  
/*!			S: struct *Robot                       !*/
/*! Retour: void                                   !*/
/*!================================================!*/
void droite(Robot *robot) {

	robot -> compteurPledge ++;
}

/*!================================================!*/
/*! Fonction: gauche                               !*/
/*! Rôle: Tourne l'orientaion vers la gauche       !*/
/*! Paramètres:                                    !*/
/*!			E: struct *Robot                       !*/  
/*!			S: struct *Robot                       !*/
/*! Retour: void                                   !*/
/*!================================================!*/
void gauche(Robot *robot) {

	robot -> compteurPledge --;
}

/*!============================================================!*/
/*! Fonction: deplacement                                      !*/
/*! Rôle: Algorithme permettant de trouver la sortie           !*/
/*! Paramètres:                                                !*/
/*!			E: struct *Robot, struct Carte , struct Graph, int !*/  
/*!			S: struct *Robot                                   !*/
/*! Retour: int                                                !*/
/*!============================================================!*/
int deplacement(Robot *robot, Carte carte, Graph graph, int choix1) {

	char caracDevant, caracCote;
	int fin = 0;

	//Tant qu'on est pas devant un mur, on avance
	while((caracDevant = detecteDevant(*robot, carte)) != 'x') {

		if (caracDevant == 'S') return fin = 1;
		avancer(robot, carte, graph, choix1, caracDevant);
	}
	
	droite(robot); //On tourne à droite

	do {
		//On regarde le caractère à notre gauche et devant nous
		caracDevant = detecteDevant(*robot, carte);
		caracCote = detecteCote(robot, carte);

		//On vérifie si ce n'est pas la sortie
		if(caracCote == 'S') return fin = 1;
		
		//S'il y a un mur à gauche et rien devant, on avance
		else if(caracDevant == ' ' && caracCote == 'x') avancer(robot, carte, graph, choix1, caracDevant);
		
		//S'il n'y a rien devant et rien à gauche, on tourne à gauche et on avance
		else if(caracDevant == ' ' && caracCote == ' ') {
			gauche(robot);
			avancer(robot, carte, graph, choix1, caracDevant);
		}

		//S'il y a un mur devant et un mur à gauche, on tourne à droite et on avance
		else if(caracDevant == 'x' && caracCote == 'x') {
			droite(robot);
			avancer(robot, carte, graph, choix1, caracDevant);
		}

	}while(robot -> compteurPledge != 0);
	//On le fais tant que le compteur n'est pas revenu à 0

	//On effectue un appel récursif tant qu'on ne trouve pas la sortie
	deplacement(robot, carte, graph, choix1);
}




char checkAround(Robot *robot,  Carte carte, int cote) {

	char caracCote;
	// Gauche.
	if (cote == 1) {
		gauche(robot);                            //On tourne à gauche
		caracCote = detecteDevant(*robot, carte); //On regarde devant 
		droite(robot);                            //On tourne à droite
	} 
	// Droite.
	else {
		droite(robot);                            //On tourne à droite
		caracCote = detecteDevant(*robot, carte); //On regarde devant 
		gauche(robot);                            //On tourne à gauche
	}

	return caracCote;
}

void reculer(Robot *robot, Carte carte, Graph graph, int choix1, char caracDevant) {

	//On ramène la direction à une valeur positive compris entre 0 et 3
	int cap = robot -> compteurPledge % 4;

	//On conserve les coordonnées précédentes
	carte.robotX = robot -> x;
	carte.robotY = robot -> y;

	//En fonction du cap, on avance d'une case
	if(cap == NORD) robot -> y ++;
	if(cap == EST) robot -> x --;
	if(cap == SUD) robot -> y --;
	if(cap == OUEST) robot -> x ++;

	actualisationCarte(carte, *robot, graph, choix1, caracDevant);
	//On incrémente le compteur de pas
	robot -> nbPas++;
}




int deplacementRecursif(Robot *robot, Carte carte, Graph graph, int choix1) {
	
	// Si on trouve la sortie on revient.
	if (checkAround(robot, carte, 1) == 'S' || checkAround(robot, carte, 2) == 'S' || detecteDevant(*robot, carte) == 'S') {
		return 1;
	}
	// Si on est bloqué on revient.
	if (checkAround(robot, carte, 1) != ' ' && checkAround(robot, carte, 2) != ' ' && detecteDevant(*robot, carte) && ' ') {
		return 0;
	}
	// On va à droite.
	char c = checkAround(robot, carte, 2);
	if ( c == ' ') {
		droite(robot);
		avancer(robot, carte, graph, choix1, c);
		if (deplacementRecursif(robot, carte, graph, choix1) == 1) return 1;
		reculer(robot, carte, graph, choix1, c);
		gauche(robot);
	}

	// On va en face.
	c = detecteDevant(*robot, carte);
	if ( c == ' ') {
		avancer(robot, carte, graph, choix1, c);
		if (deplacementRecursif(robot, carte, graph, choix1) == 1) return 1;
		reculer(robot, carte, graph, choix1, c);
	}

	// On va à gauche.
	c = checkAround(robot, carte, 1);
	if ( c == ' ') {
		gauche(robot);
		avancer(robot, carte, graph, choix1, c);
		if (deplacementRecursif(robot, carte, graph, choix1) == 1) return 1;
		reculer(robot, carte, graph, choix1, c);
		droite(robot);
	}

	return 0;

}


