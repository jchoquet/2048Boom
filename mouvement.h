#include "boucle.h"

/* Fonctions pour traiter le déplacement vers le bas : k */

void Descendre_colonne (int ** tabJeu, int ** tabBombe, long lignes, int numCol);
void Descendre_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);
void Ajouter_colonne_bas (int  ** tabJeu, int ** tabBombe, long lignes, long colonnes, int numCol);
void Ajouter_tableau_bas (int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

void Mouvement_bas(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

/* Fonctions pour traiter le déplacement vers le haut : i */

void Monter_colonne (int ** tabJeu, int ** tabBombe, long lignes, int numCol);
void Monter_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);
void Ajouter_colonne_haut (int  ** tabJeu, int ** tabBombe, long lignes, long colonnes, int numCol);
void Ajouter_tableau_haut (int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

void Mouvement_haut(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

/* Fonctions pour traiter le déplacement vers la droite : l */

void Droite_ligne (int ** tabJeu, int ** tabBombe, int numLig, long colonnes);
void Droite_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);
void Ajouter_ligne_droite (int  ** tabJeu, int ** tabBombe, long colonnes, long lignes,  int numLig);
void Ajouter_tableau_droite (int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

void Mouvement_droite(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

/* Fonctions pour traiter le déplacement vers la gauche : j */

void Gauche_ligne (int ** tabJeu, int ** tabBombe, int numLig, long colonnes);
void Gauche_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);
void Ajouter_ligne_gauche (int  ** tabJeu, int ** tabBombe, long colonnes, long lignes, int numLig);
void Ajouter_tableau_gauche (int ** tabJeu, int ** tabBombe, long lignes, long colonnes);

void Mouvement_gauche(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);


/* Fonctions pour traiter l'explosion des différentes bombes */

void Explosion_plus(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes);
void Explosion_fois(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes);
void Explosion_etoile(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes);

/* Fonction pour gérer l'âge des bombes */

void Explosion_Bombe(int ** tabJeu, int ** tabBombe, long lignes, long colonnes);
void Actualiser_tabBombe(int ** tabBombe, long lignes, long colonnes);
