
/* Déclaration des deux structures utilisées : format du tableau + borne et position */

struct Settings {long borne; long colonnes; long lignes;} ;
struct Position {long i; long j;} ;
typedef struct Settings Settings;
typedef struct Position Position;

/* Fonctions d'initialisation des tableaux 2D à 0 + tirage premier 1 du tableau de jeu + affichage des règles */

Settings Ini_Regles();
void Vide_Tableau (int ** tableau, long lignes, long colonnes);
Position Random_Position (long lignes, long colonnes);

/* Fonctions de saisie de texte sécurisée */

int Demander_Utilisateur(char * chaine, int longueur);
void Vider_Buffer();

/* Fonctions d'affichage de tableaux 2D + affichage de la ligne de '-' + mise en évidence de la bombe sélectionnée */

void Affichage_Tableau (int ** tabJeu, long lignes, long colonnes);
void Affichage_Separateur(int colonnes);
void Affichage_Tableau_Bombe(int ** tabJeu, long lignes, long colonnes, Position pos_bombe);

/* Demande du choix de mouvement ou d'explostion de bombe + de la confirmation avec y */

void Demande_Deplacement (long colonnes, char * choix);
int Demande_Confirmation_Depla(long colonnes, char * choix);

void Demande_Bombe(long colonnes, long lignes, Position * pos_bombe, int ** tabJeu);
int Demande_Confirmation_Bombe(int ** tabJeu, long lignes, long colonnes, Position pos_bombe);

/* Fonctions pour l'ajout d'objet à la fin de chaque round */

int Actualiser_Pos_Vides (Position * liste, int ** tabJeu, long lignes, long colonnes);
int Random_objet (int score);
void Ajout_Random(Position * liste, int taille, int ** tabJeu, int ** tabBombe, int score);

/* Fonctions pour gérer la fin de partie */

void Score_tableau (int ** tabJeu, int * score, long lignes, long colonnes);
int Bombe_presente(int ** tabJeu, long lignes, long colonnes);

/* Fonctions utilisées pour vérifier la possibilité de choix de mouvement */

void Memoire_Tableau(int ** tabJeu, int ** tabInte, long lignes, long colonnes);
int Mouvement_possible(int ** tabJeu, int ** tabInte, long lignes, long colonnes);

