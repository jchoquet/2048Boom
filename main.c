#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mouvement.h"


/* ******************** QUESTION 2 : JEU AVEC BOMBES **************************** */


int main()
{

    /* ******************** INITIALISATION DU JEU **************************** */

    /* **** Création des différentes variables nécessaires **** */


    int **tabJeu; int **tabInte;   /* Tableau de jeu 2D + un autre tableau 2D intermediaire */
    int **tabBombe; int **tabTmp;  /* Tableau 2D qui contiendra l'âge des bombes présentes dans le tableau de jeu + tableau temporaire*/
    Position Debut;                /* Position du premier 1 qui apparaîtra dans le tableau de jeu */

    Settings Format;               /* Contiendra les paramètres du jeu (borne, lignes, colonnes) */
    long borne, lignes, colonnes;

    int score = 1;
    int perdu = 0;                 /* perdu = 1 -> fin du jeu */
    int round = 0;                 /* vaut 1 si un round a été effectué */


    /*  On affiche les règles et on récupère le format du jeu */

    Format = Ini_Regles();

    borne = Format.borne;
    lignes = Format.lignes;
    colonnes = Format.colonnes;

    /* Création de la liste de positions vides du tableau de jeu */

    int TAILLE_MAX;
    TAILLE_MAX = lignes * colonnes;
    Position ListeVide[TAILLE_MAX];

    /* Variables de gestion de choix de déplacement et de bombe */

    char choix[2];                       /* contiendra le choix de déplacement */
    int possible[4]={0,0,0,0};           /* les cases correspondent dans l'ordre aux mouvements i/j/k/l
                                                et valent 1 si le mouvement est possible */

    Position Pos_Bombe;                  /* contiendra la position de la bombe qui va exploser */

    int bombe_ou_depla;                 /* vaut 2 si le joueur veut faire exploser une bombe, 1 pour un déplacement */
    int bombe_dans_tab;                 /* vaut 1 s'il y a une bombe dans le tableau de jeu */
    int encore_mouvement;               /* vaut 1 si un mouvement est possible */

    char uti[2];
    int i, taille;
    long compteur;


    /* **** Allocation dynamique de la mémoire pour les tableaux 2D **** */

    /* Première allocation dynamique */

    tabJeu =(int ** )malloc(lignes * sizeof(*tabJeu));
    tabInte =(int **)malloc(lignes * sizeof(*tabInte));

    tabBombe=(int **)malloc(lignes * sizeof(*tabBombe));
    tabTmp=(int **)malloc(lignes * sizeof(*tabTmp));

    /* On vérifie que la première allocation s'est bien déroulée, sinon on quitte */

    if(tabJeu == NULL || tabInte == NULL || tabBombe == NULL || tabTmp == NULL) {exit(EXIT_FAILURE);};

    /* Deuxième allocation dynamique */

    for(i=0 ; i < lignes ; i=i+1)
    {

        tabJeu[i] =(int *)malloc(colonnes * sizeof(**tabJeu));
        tabInte[i] =(int *)malloc(colonnes * sizeof(**tabInte));
        tabBombe[i] =(int *)malloc(colonnes * sizeof(**tabBombe));
        tabTmp[i] =(int *)malloc(colonnes * sizeof(**tabTmp));

        /* On vérifie que la seconde allocation s'est bien déroulée, sinon on libère la mémoire allouée les 2 fois */

        if(tabJeu[i] == NULL || tabInte[i] == NULL || tabBombe[i] == NULL || tabTmp[i] == NULL)
        {
            for(i = i-1 ; i >= 0 ; i=i-1)
            {
                free(tabJeu[i]);
                free(tabInte[i]);

                free(tabBombe[i]);
                free(tabTmp[i]);
            }

         free(tabJeu); free(tabInte); free(tabBombe); free(tabTmp);
         exit(EXIT_FAILURE);
         }
    }

    /* **** Initialisation du tableau de jeu (et l'inte) + celui de l'âge des bombes (et le temp) **** */

    Vide_Tableau(tabJeu, lignes, colonnes);
    Vide_Tableau(tabInte, lignes, colonnes);

    Vide_Tableau(tabBombe, lignes, colonnes);
    Vide_Tableau(tabTmp, lignes, colonnes);

    /* On ajoute le 1er "1" au hasard dans le tableau de jeu */

    Debut = Random_Position(lignes, colonnes);
    tabJeu[Debut.i][Debut.j]=1;


    /* ******************** BOUCLE DU JEU **************************** */


    while (perdu != 1 && score < borne )
    {

        round = 0; /* On commence un nouveau round */

        /* On fait exploser les bombes non explosées depuis 7 round */

        Explosion_Bombe(tabJeu, tabBombe, lignes, colonnes);

         /* Pour chaque mouvement, on met en mémoire le tableau de jeu dans tabInte pour tester sa possibilité*/

        Memoire_Tableau(tabJeu, tabInte, lignes, colonnes);
        Mouvement_haut(tabInte, tabTmp, lignes, colonnes);
        possible[0]=Mouvement_possible(tabJeu, tabInte, lignes, colonnes);

        Memoire_Tableau(tabJeu, tabInte, lignes, colonnes);
        Mouvement_gauche(tabInte, tabTmp, lignes, colonnes);
        possible[1]=Mouvement_possible(tabJeu, tabInte, lignes, colonnes);

        Memoire_Tableau(tabJeu, tabInte, lignes, colonnes);
        Mouvement_bas(tabInte, tabTmp, lignes, colonnes);
        possible[2]=Mouvement_possible(tabJeu, tabInte, lignes, colonnes);

        Memoire_Tableau(tabJeu, tabInte, lignes, colonnes);
        Mouvement_droite(tabInte, tabTmp, lignes, colonnes);
        possible[3]=Mouvement_possible(tabJeu, tabInte, lignes, colonnes);

        /* On vérifie qu'il existe une possibilité de mouvement ou une bombe à selectionner*/

        perdu = 1;

        bombe_dans_tab=Bombe_presente(tabJeu, lignes, colonnes);

        for(i=0; i < 4; i=i+1)
        {
            if ( possible[i] == 1)
            {
                encore_mouvement = 1;
            }
        }

        if (encore_mouvement || bombe_dans_tab)
        {
            perdu = 0;
        }

        /* Si le joueur peut jouer, on effectue un round de jeu */

        if (perdu == 0)
        {

            while (round != 1)
            {

                /* Affichage du tableau et rappel du score*/

                Affichage_Tableau(tabJeu, lignes, colonnes);
                printf("Borne : %ld \nVotre score : %d\n\n", borne, score);
                Affichage_Separateur(colonnes);
                printf("\n\n");

                if (bombe_dans_tab == 0 ) /* S'il n'y a pas de bombe */
                {

                    Demande_Deplacement(colonnes, choix);    /* On demande uniquement le déplacement à effectuer au joueur */

                    if (Demande_Confirmation_Depla(colonnes, choix) == 0)
                    {
                        /* Deplacement en fonction du choix s'il est possible, sinon message d'erreur */

                        if ((strcmp(choix, "i") == 0)  && (possible[0] == 1))
                        {
                            Mouvement_haut(tabJeu, tabBombe, lignes, colonnes);
                            round = 1;
                        }
                        else if ((strcmp(choix, "l") == 0) &&(possible[3] == 1))
                        {
                            Mouvement_droite(tabJeu, tabBombe, lignes, colonnes);
                            round = 1;
                        }
                        else if ((strcmp(choix, "k") == 0) &&(possible[2] == 1))
                        {
                            Mouvement_bas(tabJeu, tabBombe, lignes, colonnes);
                            round = 1;
                        }
                        else if (((strcmp(choix, "j") == 0) &&(possible[1] == 1)))
                        {
                            Mouvement_gauche(tabJeu, tabBombe, lignes, colonnes);
                            round = 1;
                        }
                        else
                        {
                            printf("Erreur : ce choix n'est pas possible ! \n\n");
                        }
                    }
                }
                else if (encore_mouvement == 0) /* S'il n'y a pas de mouvement possible */
                {

                    Demande_Bombe(colonnes, lignes, &Pos_Bombe, tabJeu);       /* On demande au joueur la bombe à exploser */

                    if (Demande_Confirmation_Bombe(tabJeu, lignes, colonnes, Pos_Bombe) == 0)
                    {
                        switch (tabJeu[Pos_Bombe.i][Pos_Bombe.j])
                        {
                        case -1:
                            Explosion_plus(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                            round = 1;
                        break;
                        case -2:
                            Explosion_fois(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                            round = 1;
                        break;
                        case -3:
                            Explosion_etoile(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                            round=1;
                        break;
                        }
                    }

                }
                else        /* Si les deux sont possible, on demande au joueur de choisir entre les deux */
                {

                    printf("Vous pouvez choisir entre: \neffectuer un deplacement (1) \nou faire exploser une bombe (2) !\n");
                    for(compteur=0; compteur < ((7*colonnes) - 21); compteur=compteur+1)
                    {
                        printf(" ");
                    }
                    printf("Entrez votre choix : ");
                    Demander_Utilisateur(uti, 2);
                    bombe_ou_depla=strtol(uti, NULL, 10);

                    printf("\n");
                    Affichage_Separateur(colonnes);

                    if(bombe_ou_depla == 2)
                    {
                        Demande_Bombe(colonnes, lignes, &Pos_Bombe, tabJeu);

                        if (Demande_Confirmation_Bombe(tabJeu, lignes, colonnes, Pos_Bombe) == 0)
                        {
                            /* On effectue les explosions en fonction du type de bombe sélectionnée */

                            switch (tabJeu[Pos_Bombe.i][Pos_Bombe.j])
                            {
                            case -1:
                                Explosion_plus(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                                round = 1;
                            break;
                            case -2:
                                Explosion_fois(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                                round = 1;
                            break;
                            case -3:
                                Explosion_etoile(tabJeu, tabBombe, Pos_Bombe, lignes, colonnes);
                                round=1;
                            break;
                            }
                        }
                    }
                    else if(bombe_ou_depla == 1)
                    {
                        Demande_Deplacement(colonnes, choix);

                        if (Demande_Confirmation_Depla(colonnes, choix) == 0)
                        {
                            /* Deplacement en fonction du choix s'il est possible */

                            if ((strcmp(choix, "i") == 0)  && (possible[0] == 1))
                            {
                                Mouvement_haut(tabJeu, tabBombe, lignes, colonnes);
                                round = 1;
                            }
                            else if ((strcmp(choix, "l") == 0) &&(possible[3] == 1))
                            {
                                Mouvement_droite(tabJeu, tabBombe, lignes, colonnes);
                                round = 1;
                            }
                            else if ((strcmp(choix, "k") == 0) &&(possible[2] == 1))
                            {
                                Mouvement_bas(tabJeu, tabBombe, lignes, colonnes);
                                round = 1;
                            }
                            else if (((strcmp(choix, "j") == 0) &&(possible[1] == 1)))
                            {
                                Mouvement_gauche(tabJeu, tabBombe, lignes, colonnes);
                                round = 1;
                            }
                            else
                            {
                                printf("Ce choix n'est pas possible ! \n\n");
                            }
                        }
                    }
                    else
                    {
                        printf("\nErreur : entrez 0 ou 1 pour jouer \n");
                    }


                }

            } /* Sortie de boucle : round = 1 ie un round a été fait ie un mouvement possible effectué */


            /* ROUND EFFECTUE */

            /* MAJ du score du joueur */

            Score_tableau(tabJeu, &score, lignes, colonnes);

            /* MAJ de l'âge des bombes présentes */

            Actualiser_tabBombe(tabBombe, lignes, colonnes);

            /* Ajout d'un nouvel élèment de façon aleatoire dans une position vide */

            taille=Actualiser_Pos_Vides(ListeVide, tabJeu, lignes,colonnes);
            Ajout_Random(ListeVide, taille, tabJeu, tabBombe, score);

        }

    }  /* Sortie de boucle : perdu = 1 (aucun mouvement possible ou bombe présente) ou score du joueur >= borne de jeu*/

    /* Affichage spécial de fin de partie */

    Affichage_Tableau(tabJeu, lignes, colonnes);

    if (score < borne)
    {
        printf("\n");
        Affichage_Separateur(colonnes);
        printf("\n\nGAME OVER : TRY AGAIN !\n\n");
        Affichage_Separateur(colonnes);
    }
    else
    {
        printf("\n");
        Affichage_Separateur(colonnes);
        printf("\n\n YOU WIN !!! \n\n");
        Affichage_Separateur(colonnes);

    }

    /* ******************** FIN DU PROGRAMME **************************** */

    /* On libère la mémoire allouée aux tableaux 2D */

    for(i=0 ; i < lignes ; i=i+1)
    {
        free(tabJeu[i]); free(tabInte[i]) ; free(tabBombe[i]); free(tabTmp[i]);
    }

    free(tabJeu); free(tabInte); free(tabBombe); free(tabTmp);

    return EXIT_SUCCESS;

}
