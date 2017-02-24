#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "boucle.h"



/* Fonctions d'initialisation des tableaux 2D � 0 + tirage premier 1 du tableau de jeu + affichage des r�gles */

/*
    @requires : -
    @assigns : -
    @returns : Format qui contient les param�tres du jeu (borne, lignes, colonnes)
    @ensures : 2 <= hauteur et largeur  du tableau <= 20 et 2 <= borne < 10 000
*/


Settings Ini_Regles()
{
    char a[4];
    char b[3];
    char c[3];
    Settings Format;

    printf("\n------------------------------- PROJET IPI 2015 -------------------------------\n\n");

    printf("\n - Jeu de type deux-mille-quarante -\n\n\n ");

    /* On demande le format du jeu � l'aide de boucle do-while pour �viter les cas de troll */

    do
    {
        printf("Entrez le score a atteindre (entre 2 et 10 000): ");

        Demander_Utilisateur(a, 5);               /* Ces deux lignes assurent le fait que la borne soit */
        Format.borne = strtol(a, NULL, 10);       /*  inf�rieure � 10 000                               */

        if (Format.borne < 2)
        {
            printf(" Le score doit etre >= a 2 ! \n\n");
        }

    } while (Format.borne < 2) ; /* Sortie de boucle : la borne est >= � 2 */

    do
    {
        printf("\n Entrez le nombre de colonnes du tableau (entre 2 et 20 compris) : ");
        Demander_Utilisateur(b, 3);
        Format.colonnes = strtol(b, NULL, 10);

        if (Format.colonnes < 2)
        {
            printf(" Le nombre de colonnes doit etre >= a 2 ! \n\n");
        }
        else if (Format.colonnes >20)
        {
            printf(" Le nombre de colonnes doit etre <= 20 ! \n\n");
        }

    } while (Format.colonnes < 2 || Format.colonnes > 20) ; /* Sortie de boucle : 2  <= nombre de colonnes <= 20 */

    do
    {
        printf("\n Entrez le nombre de lignes du tableau (entre 2 et 20 compris) : ");
        Demander_Utilisateur(c, 3);
        Format.lignes = strtol(c, NULL, 10);

        if (Format.lignes < 2 )
        {
            printf(" Le nombre de lignes doit etre >= a 2 ! \n\n");
        }
        else if (Format.lignes >20)
        {
            printf(" Le nombre de lignes doit etre <= 20 ! \n\n");
        }

    } while (Format.lignes < 2 || Format.lignes > 20) ; /* Sortie de boucle : 2  <= nombre de lignes <= 20*/


    return Format;

}

/*
    @requires : tableau de jeu 2D d�j� initialis� + ses dimensions (>= � 2 et <= � 20)
    @assigns : chaque case du tableau de jeu 2D
    @returns : -
    @ensures : chaque case du tableau de jeu 2D a pour valeur 0
*/

void Vide_Tableau (int ** tableau, long lignes, long colonnes)
{
    int i, j;

    for (i=0; i < lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
            tableau[i][j]=0;
        }
    }
}

/*
    @requires : les dimensions du tableau de jeu 2D (>= � 2 et <= � 20)
    @assigns : -
    @returns : renvoie la position du premier 1 qui va appara�tre dans le tableau de jeu 2D
    @ensures : cette position est valide
*/

Position Random_Position (long lignes, long colonnes)
{
    Position Reponse;

    srand(time(NULL));

    Reponse.i = (rand() % lignes);
    Reponse.j = (rand() % colonnes);

    return Reponse;
}

/* Fonctions de saisie de texte s�curis�e */

/*
    @requires : un pointeur sur la cha�ne qui va contenir la r�ponse de l'utilisateur et sa longueur non nulle
    @assigns : la valeur de cha�ne
    @returns : EXIT_SUCESS si la demande s'est d�roul� sans probl�me sinon EXIT_FAILURE
    @ensures : cha�ne contient la r�ponse du joueur tronqu�e si trop longue + pas de stack overflow + pas de '\n'
*/

int Demander_Utilisateur(char * chaine, int longueur)
{
    char * position_entree = NULL;

  /* On lit le texte saisi au clavier */

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        position_entree = strchr(chaine, '\n');

        if (position_entree != NULL)
        {
            *position_entree = '\0';
        }

        Vider_Buffer();

        return EXIT_SUCCESS;
    }
    else
    {
        Vider_Buffer();
        return EXIT_FAILURE;
    }
}

/*
    @requires : -
    @assigns : le contenu du buffer
    @returns : -
    @ensures : le buffer est vid�
*/

void Vider_Buffer()
{

	char c = 0;
	while (c != EOF && c !='\n')
	{
		c = getchar();
	} /* Sortie de boucle : buffer vid� */

}


/* Fonctions d'affichage de tableaux 2D + affichage de la ligne de '-' */

/*
    @requires : le tableau 2D de jeu  d�j� initialis� + ses dimensions (>= � 2 et <= � 20)
    @assigns : -
    @returns : -
    @ensures : toutes les cases pleines du tableau ont �t� affich�es + mise en page qui correspond au sujet
*/


void Affichage_Tableau (int ** tabJeu, long lignes, long colonnes)
{

    int i, j, a;

    /* Am�lioration de la mise en page du tableau de jeu */

    printf("\n");
    Affichage_Separateur(colonnes);
    printf("\n");

    /* On va parcourir le tableau de jeu ligne par ligne */

    for (i=0; i < lignes; i=i+1)
    {

        /* Chaque ligne du tableau faisant trois "|" de hauteur, on affiche la premi�re s�rie de "|" */

        printf("| ");

        for(a=0; a < colonnes; a=a+1)
        {
            printf("    ");
            printf(" | ");
        }

        printf("\n| ");

        /* On affiche ensuite les valeurs des cases pleines du tableau de jeu 2D */

        for (j=0; j < colonnes; j=j+1)
        {

            if(tabJeu[i][j] != 0) /* On teste si la case est remplie, si oui on affichera la valeur de celle-ci */
            {
                if (tabJeu[i][j] > 0) /* Si l'objet est de la famille nombre */
                {
                     printf("%4d", tabJeu[i][j]); /* Utilisation de "%4d" pour aligner les colonnes */
                }
                else /* Si l'objet est de la famille bombe */
                {
                    switch(tabJeu[i][j])
                    {
                    case -1:
                        printf(" +  ");
                    break;
                    case -2:
                        printf(" X  ");
                    break;
                    case -3:
                        printf(" *  ");
                    break;
                    }
                }
            }
            if(tabJeu[i][j] == 0) /* Si la case n'est pas remplie, on affiche un espace vide de m�me dimension */
            {
                printf("    ");
            }

            /* On separe chaque case de la ligne avec un | */

            printf(" | ");

        }

        /* On affiche la troisi�me s�rie de "|" pour chaque ligne */

        printf("\n| ");

        for(a=0; a < colonnes; a=a+1)
        {
            printf("    ");
            printf(" | ");
        }

        printf("\n");

        /* On s�pare la ligne des autres avec une ligne de - de la taille exacte du tableau */

        Affichage_Separateur(colonnes);
        printf("\n");

    }

    printf("\n\n");
    Affichage_Separateur(colonnes);
    printf("\n\n");


}


/*
    @requires : le tableau 2D de jeu  d�j� initialis� + ses dimensions (>= � 2 et <= � 20) + position d'une bombe valide
    @assigns : -
    @returns : -
    @ensures : toutes les cases pleines du tableau ont �t� affich�es + mise en page qui correspond au sujet
               + affichage entre [ ] de la bombe que le joueur veut faire exploser
*/

void Affichage_Tableau_Bombe(int ** tabJeu, long lignes, long colonnes, Position pos_bombe)
{

    int i, j, a;

    /* Am�lioration de la mise en page du tableau de jeu */

    printf("\n");
    Affichage_Separateur(colonnes);
    printf("\n");

    /* On va parcourir le tableau de jeu ligne par ligne */

    for (i=0; i < lignes; i=i+1)
    {

        /* Chaque ligne du tableau faisant trois "|" de hauteur, on affiche la premi�re s�rie de "|" */

        printf("| ");

        for(a=0; a < colonnes; a=a+1)
        {
            printf("    ");
            printf(" | ");
        }

        printf("\n| ");

        /* On affiche ensuite les valeurs des cases pleines du tableau de jeu 2D */

        for (j=0; j < colonnes; j=j+1)
        {

            if(tabJeu[i][j] != 0) /* On teste si la case est remplie, si oui on affichera la valeur de celle-ci */
            {
                if (tabJeu[i][j] > 0) /* Si l'objet est de la famille nombre */
                {
                    printf("%4d", tabJeu[i][j]); /* Utilisation de "%4d" pour aligner les colonnes */
                }
                else /* Si l'objet est de la famille bombe */
                {
                    if( pos_bombe.i == i && pos_bombe.j == j)
                    {
                        switch(tabJeu[i][j])
                        {
                        case -1:
                            printf(" [+]");
                        break;
                        case -2:
                            printf(" [X]");
                        break;
                        case -3:
                            printf(" [*]");
                        break;
                        }
                    }
                    else
                    {
                        switch(tabJeu[i][j])
                        {
                        case -1:
                            printf(" +  ");
                        break;
                        case -2:
                            printf("  X  ");
                        break;
                        case -3:
                            printf(" *  ");
                        break;
                        }
                    }

                }
            }
            if(tabJeu[i][j] == 0) /* Si la case n'est pas remplie, on affiche un espace vide de m�me dimension */
            {
                printf("    ");
            }

            /* On separe chaque case de la ligne avec un | */

            printf(" | ");

        }

        /* On affiche la troisi�me s�rie de "|" pour chaque ligne */

        printf("\n| ");

        for(a=0; a < colonnes; a=a+1)
        {
            printf("    ");
            printf(" | ");
        }

        printf("\n");

        /* On s�pare la ligne des autres avec une ligne de - de la taille exacte du tableau */

        Affichage_Separateur(colonnes);
        printf("\n");

    }

    printf("\n\n");
    Affichage_Separateur(colonnes);
    printf("\n\n");


}


/*
    @requires : le nombre de colonnes du tableau
    @assigns : -
    @returns : -
    @ensures : on affiche une ligne de "-" de la taille exacte du tableau de jeu
*/

void Affichage_Separateur(int colonnes)
{
    int compteur, separateur;

    separateur = (7*colonnes) +1;

    for(compteur=0; compteur < separateur; compteur=compteur+1)
    {
            printf("-");
    }

}


/* Demande du choix de mouvement + de la confirmation avec y */

/*
    @requires : le nombre de colonnes du tableau de jeu (>= � 2 et <= � 20)
                + pointeur sur une cha�ne de taille 2 qui va contenir le choix de mouvement
    @assigns : la cha�ne choix
    @returns : -
    @ensures : le choix de d�placement est valide (i/j/k/l) et confirm� (y) + demandes � l'extr�me droite du tableau de jeu
*/

void Demande_Deplacement (long colonnes, char * choix)
{

    int decalage, compteur;

    decalage = (7*colonnes) - 21;


    do
    {

        printf("\n\nChoix de deplacement : \n\ni = haut / k = bas \nj = gauche / l = droite\n\n");

        /* On effectue un d�calage pour que la demande de choix soit � l'extr�me droite */

        for(compteur=0; compteur < decalage ; compteur=compteur+1)
        {
            printf(" ");
        }

        /* On demande le choix de mouvement de l'utilisateur */

        printf("Entrez votre choix : ");
        Demander_Utilisateur(choix, 2);


    } while (strcmp(choix, "i") != 0 && strcmp(choix, "k") != 0 && strcmp(choix, "j") != 0 && strcmp(choix, "l") != 0);

    /* Sortie de boucle : le choix entr� par l'utilisateur est valide ie �gal � i, j, k ou l */

}

/*
    @requires : un pointeur sur le choix valide de d�placement du joueur
                + le nombre de colonnes du tableau de jeu (>= � 2 et <= � 20)
    @assigns : -
    @returns : 0 si le choix est confirm� avec y, 1 sinon
    @ensures : un rappel visuel du choix de mouvement est affich� + demande de confirmation � l'extr�me droite du tableau de jeu
*/

int Demande_Confirmation_Depla(long colonnes, char * choix)
{

    int compteur, decalage;
    char confirmation[2];

    decalage =(7*colonnes) - 26;


    /* On met en �vidence le motif correspondant au choix du joueur */

    if (strcmp(choix, "i") == 0)
    {
        printf("/ \\");
        printf("\n |\n");
        printf(" |");
        decalage = decalage - 2;
    }
    if (strcmp(choix, "j") == 0)
    {
        printf("\n<--\n");
    }
    if (strcmp(choix, "k") == 0)
    {
        printf(" |\n");
        printf(" |\n");
        printf("\\ /");
        decalage = decalage - 3;
    }
    if (strcmp(choix, "l") == 0)
    {
        printf("\n-->\n");
    }


    /* On d�cale le texte pour qu'il s'affiche � l'extr�me droite */

    for(compteur=0; compteur < decalage; compteur=compteur+1)
    {
            printf(" ");
    }

    /* On affiche la demande de confirmation + saisie de texte s�curis�e */

    printf("Entrez y pour confirmer : ");
    Demander_Utilisateur(confirmation, 2);
    printf("\n\n");

    /* On compare ce que l'utilisateur a entr� avec y */

    return (strcmp(confirmation, "y"));

}



/*
    @requires : le tableau de jeu 2D d�j� initialis� + ses dimensions (>= � 2)
                + un pointeur sur une position qui contiendra la position d'une bombe entr�e par le joueur
    @assigns : la position de la bombe � exploser
    @returns : -
    @ensures : pos_bombe pointe vers une position valide de bombe dans le tableau de jeu
*/

void Demande_Bombe(long colonnes, long lignes, Position * pos_bombe, int ** tabJeu)
{

    int decalage, compteur;
    char abs[3];
    char ord[3];

    decalage = (7*colonnes) - 39;

    do
    {

        printf("\n\nSelectionner une bombe a exploser \n(origine en bas a gauche)\n\n");

        /* On effectue le d�calage pour que la demande soit � l'extreme droite */

        for(compteur=0; compteur < decalage; compteur=compteur+1)
        {
            printf(" ");
        }

        /* On demande la position de la bombe � l'utilisateur */
        do
        {
            printf("Abscisse de la bombe (entre 1 et %ld) : ", colonnes);
            Demander_Utilisateur(abs, 3);
            pos_bombe->j= strtol(abs, NULL, 10);
            pos_bombe->j= (pos_bombe->j) - 1;

            if (pos_bombe->j < 0 || pos_bombe->j > (colonnes -1))
            {
                printf("Erreur : l'abscisse doit etre comprise entre 1 et %ld !\n\n", colonnes);
            }

        } while (pos_bombe->j < 0 || pos_bombe->j > (colonnes -1)); /* Sortie de boucle : abscisse valide */

        do
        {
            printf("\n");
             for(compteur=0; compteur < decalage + 1; compteur=compteur+1)
            {
                printf(" ");
            }

            printf("Ordonnee de la bombe (entre 1 et %ld) : ", lignes);
            Demander_Utilisateur(ord, 3);
            pos_bombe->i= strtol(ord, NULL, 10);
            pos_bombe->i= lignes - (pos_bombe->i);

            if (pos_bombe->i < 0 || pos_bombe->i > (lignes -1))
            {
                printf("\n\nErreur : l'ordonnee doit etre comprise entre 1 et %ld !\n\n", lignes);
            }

        } while (pos_bombe->i < 0 || pos_bombe->i > (lignes -1)); /* Sortie de boucle : ordonnee valide */

        if (tabJeu[pos_bombe->i][pos_bombe->j] >= 0)
        {
            printf("\n\nErreur : la position selectionnee n'est pas celle d'une bombe !\n\n");
        }

    } while (tabJeu[pos_bombe->i][pos_bombe->j] >= 0);

    /* Sortie de boucle : la position entree est celle d'une bombe */

}


/* A COMMENTER
    @requires : le tableau de jeu 2D d�j� initialis� + ses dimensions (>= � 2)
                + la position d'une bombe valide choisie par le joueur
    @assigns : -
    @returns : 0 si l'explosion est confirm�e avec y, 1 sinon
    @ensures : la bombe qui va �tre explos�e a �t� mise en �vidence
                + demande de confirmation � l'extr�me droite du tableau de jeu
*/


int Demande_Confirmation_Bombe(int ** tabJeu, long lignes, long colonnes, Position pos_bombe)
{

    int compteur, decalage;
    char confirmation[2];

    decalage =(7*colonnes) - 26;


    /* On affiche le tableau avec la bombe s�lectionn�e */
    Affichage_Tableau_Bombe(tabJeu, lignes, colonnes, pos_bombe);

    for(compteur=0; compteur < decalage; compteur=compteur+1)
    {
            printf(" ");
    }

    /* On affiche la demande de confirmation + saisie de texte s�curis�e */

    printf("Entrez y pour confirmer : ");
    Demander_Utilisateur(confirmation, 2);
    printf("\n\n");

    /* La fonction retourne 0 si le joueur a entr� y */

    return (strcmp(confirmation, "y"));

}



/* Fonctions pour l'ajout d'objet � la fin de chaque round */

/*
    @requires : la liste des positions vides de taille colonnes * lignes  + le tableau de jeu d�j� initialis�
                + ses dimensions
    @assigns : la liste des positions vides
    @returns : le nombre de positions vides
    @ensures : la liste des positions vides contient toutes les positions des cases vides du tableau de jeu de l'indice 0
                � l'entier qu'elle renvoit -1 + {-1,-1} dans les autres cases
*/

int Actualiser_Pos_Vides (Position * liste, int ** tabJeu, long lignes, long colonnes)
{

    int k, l, compteur, TAILLE_MAX;

    TAILLE_MAX= lignes * colonnes ;
    compteur=0;

    /* On vide la liste en mettant dans toutes les cases {-1;-1} */

    for(k=0; k < TAILLE_MAX; k=k+1)
    {
        (liste[k]).i=-1;
        (liste[k]).j=-1;
    }

    /* On teste maintenant chaque case du tableau de jeu 2D */

    for(k=0; k < lignes; k=k+1)
    {
        for(l=0; l < colonnes; l=l+1)
        {
            if (tabJeu[k][l] == 0) /* Si la case du tableau de jeu est vide ... */
            {
                (liste[compteur]).i=k;    /* ..on ajoute sa position dans la liste des positions vides */
                (liste[compteur]).j=l;
                compteur = compteur + 1;   /* et on incr�mente le compteur de positions vides */
            }

        }
    }

    return compteur;
}

/*
    @requires : le score du joueur
    @assigns : -
    @returns : la valeur du nombre al�atoire qui appara�t � la fin du round dans le tableau de jeu
    @ensures : les r�gles du jeu (score + probabilit�) sont respect�es
*/

int Random_objet (int score)
{

    int reponse; double alea;

    /* On tire un nombre pseudo-al�atoire entre 0 et 100 que l'on stocke dans alea */

    srand(time(NULL));
    alea =(rand() % (101));

    reponse = 1;

    /* On d�termine la valeur de r�ponse en fonction des r�gles du jeu (score + proba) */


    if (score >= 64 && score < 256)
    {
        if (alea > 90)
        {
            reponse = -1;
        }
        else if (alea > 70)
        {
            reponse = 2;
        }
    }
    else if (score >= 256)
    {
        if (alea > 95)
        {
            reponse = - 2;
        }
        else if (alea > 85)
        {
            reponse = -1;
        }
        else if (alea > 60)
        {
            reponse = 2;
        }
    }


    return reponse;

}

/*
    @requires : la liste des cases vides du tableau de jeu valide + sa taille non nulle
                + le tableau de jeu 2D et celui de l'�ge des bombes d�j� initialis�s + le score du joueur
    @assigns : une case du tableau de jeu dont la position �tait dans la liste de cases vides
                + la case correspondante dans tabBombe
    @returns : -
    @ensures : la case qui va �tre remplie est choisie au hasard parmis les cases vides
                + l'objet qui appara�t respecte les r�gles du jeu (score et probabilit�s)
                + si c'est une bombe, tabBombe est MAJ
*/

void Ajout_Random(Position * liste, int taille, int ** tabJeu, int ** tabBombe, int score)
{

    int objet, alea;
    Position Ajout;

    /* On d�termine l'objet qui va appara�tre dans le tableau */

    objet = Random_objet(score);

    /* On tire de fa�on al�atoire la position de cet objet parmis les positions vides contenues dans la liste de cases vides */

    alea = (rand() % (taille));
    Ajout = liste[alea];

    /* Si cet objet est une bombe, on actualise tabBombe */

    if (objet < 0)
    {
        tabBombe[Ajout.i][Ajout.j]=1;
    }
    /* Actualisation du tableau de jeu */

    tabJeu[Ajout.i][Ajout.j]= objet;

}


/* Fonctions pour g�rer la fin de partie */

/*
    @requires : tableau de jeu  2D d�j� initialis� + ses dimensions (>= � 2) + pointeur vers le score du joueur
    @assigns : le score du joueur
    @returns : -
    @ensures : celui-ci est �gal au plus grand nombre pr�sent dans le tableau de jeu
*/

void Score_tableau (int ** tabJeu, int * score, long lignes, long colonnes)
{

    int i, j;



    for(i=0; i < lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
                if (tabJeu[i][j] > (*score))
                {
                    (*score)=tabJeu[i][j];
                }

        }
    }

}

/*
    @requires : le tableau 2D de jeu d�j� initialis� + ses dimensions (>= � 2)
    @assigns : -
    @returns : 1 si une bombe est pr�sente dans le tableau, 0 sinon
    @ensures : la fonction s'arr�te d�s qu'une bombe est trouv�e ou que le tableau a �t� trait� en entier
*/


int Bombe_presente(int ** tabJeu, long lignes, long colonnes)
{

    int i, j;

    for (i=0; i < lignes; i=i+1)
    {
        for (j=0; j < colonnes; j=j+1)
        {
            if (tabJeu[i][j] < 0)
            {
                return 1;
            }
        }
    }

    return 0;

}



/* Fonctions utilis�es pour v�rifier la possibilit� de choix de mouvement */

/*
    @requires : le tableau 2D de jeu et un tableau 2D interm�diaire d�j� initialis�s + leurs dimensions communes (>= � 2 et <= � 20)
    @assigns : toutes les cases du tableau int�
    @returns : -
    @ensures : toutes les cases du tableau int� ont la m�me valeur que celles du tableau de jeu
*/

void Memoire_Tableau(int ** tabJeu, int ** tabInte, long lignes, long colonnes)
{

    int i, j;

    for(i=0; i < lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
            tabInte[i][j]=tabJeu[i][j];
        }
    }

}

/*
    @requires : le tableau 2D de jeu et un tableau 2D interm�diaire d�j� initialis�s + leurs dimensions communes (>= � 2 et <= � 20)
    @assigns : -
    @returns : 1 si les tableaux sont diff�rents, 0 s'ils sont �gaux
    @ensures : la fonction s'arrete d�s qu'une diff�rence est trouv�e ou que toutes les cases sont trait�es
*/

int Mouvement_possible(int ** tabJeu, int ** tabInte, long lignes, long colonnes)
{

    int i, j;

    for(i=0; i < lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
            if (tabInte[i][j] != tabJeu[i][j])
            {
                return 1;
            }
        }
    }

    return 0;

}
