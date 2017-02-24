#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "mouvement.h"



/* Fonctions pour traiter le d�placement vers le bas : k */


/*
    @requires : le tableau 2D de jeu et celui de l'�ge des bombes d�j� initialis�s
                + le num�ro de colonne valide � descendre + nombre de lignes commun (>= � 2)
    @assigns : la colonne numCol du tableau de jeu et celle du tableau d'�ge des bombes
    @returns : -
    @ensures : toutes les cases de la colonne ont �t� descendues, aucune case vide entre deux cases pleines
                + si une bombe s'est d�plac�e, son �ge aussi
*/

void Descendre_colonne (int ** tabJeu, int ** tabBombe, long lignes, int numCol)
{

    int vide_avant;                 /* vaut 1 s'il y'a une case vide situ�e en dessous de la case consid�r�e */
    int premier_vide;               /* indice de la ligne de la case vide la plus en bas disponible */
    int pos;

    pos = lignes - 1;
    vide_avant= 0;
    premier_vide = pos;


    while (pos > 0)
    {
        if ((tabJeu[pos][numCol] != 0) && vide_avant == 0) /* Si la case est pleine et qu'il n'y a pas de case vide en dessous */
        {
            pos = pos - 1;
        }
        else if (tabJeu[pos][numCol] != 0)                /* Si la case est pleine et qu'il y a des cases vides en dessous */
        {

            tabJeu[premier_vide][numCol]=tabJeu[pos][numCol];
            tabBombe[premier_vide][numCol]=tabBombe[pos][numCol];

            tabJeu[pos][numCol]=0;
            tabBombe[pos][numCol]=0;

            pos = pos - 1;
            premier_vide = premier_vide - 1;

        }
        else if ((tabJeu[pos][numCol] == 0) && (vide_avant == 0) ) /* Case vide + aucune case vide en dessous */
        {
            premier_vide = pos;
            vide_avant = 1;
            pos = pos - 1 ;
        }
        else                                                        /* Case vide comme celle d'en dessous */
        {
            pos = pos - 1 ;
        }

    } /* Sortie de boucle : pos = 0, il ne reste plus qu'� descendre ou non le premier �l�ment de la colonne */

    if (tabJeu[pos][numCol] != 0 && vide_avant == 1)
    {
        tabJeu[premier_vide][numCol]=tabJeu[pos][numCol];
        tabBombe[premier_vide][numCol]=tabBombe[pos][numCol];

        tabJeu[pos][numCol]=0;
        tabBombe[pos][numCol]=0;
    }


}

/*
    @requires : le tableau 2D de jeu et celui de l'�ge des bombes d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : tout le tableau de jeu et celui d'�ge des bombes
    @returns : -
    @ensures : toutes les colonnes du tableau ont �t� descendues, l'�ge des bombes pr�sentes est valide
*/

void Descendre_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{

    int j;

    for(j=0; j < colonnes; j=j+1)
    {
        Descendre_colonne(tabJeu, tabBombe, lignes, j);
    }

}


/*
    @requires : le tableau 2D de jeu d�j� descendu et le tableau d'�ge des bombes initialis�
                + leur nombre de lignes commun (>= � 2) + num�ro de colonne (valide) � traiter pr l'addition
    @assigns : la colonne numCol du tableau de jeu
    @returns : -
    @ensures : s'il y avait deux objets �gaux l'un en dessous de l'autre dans la colonne ceux-ci ont disparu
                   + le double est apparu dans la case la plus en bas (si nombres)
                   ou x est apparu dans la case la plus en bas (si bombes +)
                   ou * est apparu dans la case la plus en bas (si bombes x)
                   ou explosion des deux bombes *
            + �ge valide des bombes dans la colonne
*/


void Ajouter_colonne_bas (int  ** tabJeu, int ** tabBombe, long lignes, long colonnes, int numCol)
{

    int pos;

    pos = lignes - 1;

    while (pos > 0 && tabJeu[pos-1][numCol] != 0)
    {
        if(tabJeu[pos][numCol] == tabJeu[pos-1][numCol])
        {
            if(tabJeu[pos][numCol] > 0) /* Cas de deux nombres */
            {
                tabJeu[pos][numCol]= tabJeu[pos][numCol] * 2;
                tabJeu[pos-1][numCol]=0;

                Descendre_colonne(tabJeu, tabBombe, lignes, numCol);
            }
            else if (tabJeu[pos][numCol] != -3) /* Cas des bombes + et x */
            {

                tabJeu[pos][numCol]= tabJeu[pos][numCol]- 1;
                tabJeu[pos-1][numCol]=0;

                tabBombe[pos][numCol]=1;
                tabBombe[pos-1][numCol]=0;

                Descendre_colonne(tabJeu, tabBombe, lignes, numCol);
            }
            else /* Cas de deux bombes * */
            {
                Position Bombe1, Bombe2;
                Bombe1.i = pos; Bombe2.i = pos-1;
                Bombe1.j = numCol; Bombe2.j = numCol;

                Explosion_etoile(tabJeu, tabBombe, Bombe1, lignes, colonnes);
                Explosion_etoile(tabJeu, tabBombe, Bombe2, lignes, colonnes);

            }
            pos = pos - 1;
        }
        else
        {
            pos = pos - 1 ;
        }

    } /* Sortie de boucle : il n'y a plus de case � traiter sur la colonne, toutes les additions ont �t� faites */

}



/*
    @requires : le tableau 2D de jeu et celui d'�ge des bombes d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu + tabBombe
    @returns : -
    @ensures : toutes les colonnes du tableau de jeu ont �t� trait�es pour l'addition vers le bas
            + �ge des bombes valide dans le tableau
*/

void Ajouter_tableau_bas (int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < colonnes; j=j+1)
    {
        Ajouter_colonne_bas(tabJeu, tabBombe, lignes, colonnes, j);
    }
}

/*
    @requires : le tableau 2D de jeu  et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : on a effectu� le mouvement bas (descente des colonnes + addition si possible) + �ge des bombes valide
*/

void Mouvement_bas(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    Descendre_tableau(tabJeu, tabBombe, lignes, colonnes);
    Ajouter_tableau_bas(tabJeu, tabBombe, lignes, colonnes);
}



/* Fonctions pour traiter le d�placement vers le haut : i */


/*
    @requires : le tableau 2D de jeu et celui de l'�ge des bombes d�j� initialis�s
                + le num�ro de colonne valide � monter + nombre de lignes commun (>= � 2)
    @assigns : la colonne numCol du tableau de jeu et celle du tableau d'�ge des bombes
    @returns : -
    @ensures : toutes les cases de la colonne ont �t� mont�es, aucune case vide entre deux cases pleines
                + si une bombe s'est d�plac�e, son �ge aussi
*/


void Monter_colonne (int ** tabJeu, int ** tabBombe, long lignes, int numCol)
{

    int vide_avant; int premier_vide;
    int pos;

    pos = 0;
    vide_avant = 0;
    premier_vide = pos;

    while (pos < lignes - 1)
    {
        if ((tabJeu[pos][numCol] != 0) && vide_avant == 0)
        {
            pos = pos + 1;
        }
        else if (tabJeu[pos][numCol] != 0)
        {

            tabJeu[premier_vide][numCol]=tabJeu[pos][numCol];
            tabBombe[premier_vide][numCol]=tabBombe[pos][numCol];

            tabJeu[pos][numCol]=0;
            tabBombe[pos][numCol]=0;

            pos = pos + 1;
            premier_vide = premier_vide + 1;

        }
        else if (tabJeu[pos][numCol] == 0 && vide_avant == 0)
        {
            premier_vide = pos;
            vide_avant = 1;
            pos = pos + 1 ;

        }
        else
        {
            pos = pos + 1 ;
        }

    } /* Sortie de boucle : pos = lignes - 1 ie il ne reste plus qu'� monter ou non le dernier �l�ment de la colonne */

    if (tabJeu[pos][numCol] != 0 && vide_avant > 0)
    {
        tabJeu[premier_vide][numCol]=tabJeu[pos][numCol];
        tabBombe[premier_vide][numCol]=tabBombe[pos][numCol];

        tabJeu[pos][numCol]=0;
        tabBombe[pos][numCol]=0;
    }


}

/*
    @requires : le tableau 2D de jeu et d'�ge des bombes d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : tout le tableau de jeu et tabBombe
    @returns : -
    @ensures : toutes les colonnes du tableau ont �t� mont�es, l'�ge des bombes pr�sentes est valide
*/

void Monter_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < colonnes; j=j+1)
    {
        Monter_colonne(tabJeu, tabBombe, lignes, j);
    }
}


/*
    @requires : le tableau 2D de jeu d�j� mont� + tabBombe initialis�
                + leur nombre de lignes commun (>= � 2) + num�ro de colonne (valide) � traiter pr l'addition
    @assigns : la colonne numCol du tableau de jeu et celle de tabBombe
    @returns : -
    @ensures : s'il y avait deux objets �gaux l'un en dessous de l'autre dans la colonne ceux-ci ont disparu
                   + le double est apparu dans la case la plus en haut (si nombres)
                   ou x est apparu dans la case la plus en haut (si bombes +)
                   ou * est apparu dans la case la plus en haut (si bombes x)
                   ou explosion des deux bombes *
             + �ge valide des bombes dans la colonne
*/


void Ajouter_colonne_haut (int  ** tabJeu, int ** tabBombe, long lignes, long colonnes, int numCol)
{
    int pos;
    pos = 0;

    while (pos < (lignes - 1) && tabJeu[pos + 1][numCol] != 0)
    {
        if(tabJeu[pos][numCol] == tabJeu[pos + 1][numCol])
        {
            if (tabJeu[pos][numCol] > 0) /* Si les deux objets sont des nombres */
            {

                tabJeu[pos][numCol]= tabJeu[pos][numCol]* 2;
                tabJeu[pos + 1][numCol]=0;

                Monter_colonne(tabJeu, tabBombe, lignes, numCol);
            }
            else if (tabJeu[pos][numCol] != -3) /* Cas des bombes + et x */
            {

                tabJeu[pos][numCol]= tabJeu[pos][numCol] - 1;
                tabJeu[pos + 1][numCol]=0;

                tabBombe[pos][numCol]=1;
                tabBombe[pos + 1][numCol]=0;

                Monter_colonne(tabJeu, tabBombe, lignes, numCol);
            }
            else /* Cas de deux bombes * */
            {
                Position Bombe1, Bombe2;
                Bombe1.i = pos; Bombe2.i = pos + 1;
                Bombe1.j = numCol; Bombe2.j = numCol;

                Explosion_etoile(tabJeu, tabBombe, Bombe1, lignes, colonnes);
                Explosion_etoile(tabJeu, tabBombe, Bombe2, lignes, colonnes);

            }

            pos = pos + 1;
        }
        else
        {
            pos = pos + 1 ;
        }
    } /* Sortie de boucle : il n'y a plus de case � traiter sur la colonne, toutes les additions ont �t� faites */



}



/*
    @requires : le tableau 2D de jeu et celui de l'�ge des bombes d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : toutes les colonnes du tableau de jeu ont �t� trait�es pour l'addition vers le haut
                + �ge des bombes valide dans le tableau
*/

void Ajouter_tableau_haut (int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < colonnes; j=j+1)
    {
        Ajouter_colonne_haut(tabJeu, tabBombe, lignes, colonnes, j);
    }
}

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : on a effectu� le mouvement haut (mont�e des colonnes + addition si possible) + �ge des bombes valide
*/

void Mouvement_haut(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    Monter_tableau(tabJeu, tabBombe, lignes, colonnes);
    Ajouter_tableau_haut(tabJeu, tabBombe, lignes, colonnes);
}



/* Fonctions pour traiter le d�placement vers la droite : l */

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s +
                le num�ro de ligne valide � d�caler vers la droite + leur nombre de colonnes commun (>= � 2)
    @assigns : la ligne numLig du tableau de jeu et celle de tabBombe
    @returns : -
    @ensures : toutes les cases de la ligne ont �t� d�cal�es, aucune case vide entre deux cases pleines
            + + si une bombe s'est d�plac�e, son �ge aussi

*/

void Droite_ligne (int ** tabJeu, int ** tabBombe, int numLig, long colonnes)
{

    int vide_avant; int premier_vide;
    int pos;

    pos = colonnes - 1;
    vide_avant = 0;
    premier_vide = pos;

    while (pos > 0)
    {
        if ((tabJeu[numLig][pos] != 0) && vide_avant==0)
        {
            pos = pos - 1;
        }
        else if (tabJeu[numLig][pos] != 0 )
        {

            tabJeu[numLig][premier_vide]=tabJeu[numLig][pos];
            tabBombe[numLig][premier_vide]=tabBombe[numLig][pos];

            tabJeu[numLig][pos]=0;
            tabBombe[numLig][pos]=0;

            pos = pos - 1;
            premier_vide = premier_vide - 1;

        }
        else if (tabJeu[numLig][pos] == 0 && vide_avant == 0)
        {
            premier_vide = pos;
            vide_avant = 1;
            pos = pos - 1 ;
        }
        else
        {
            pos = pos - 1 ;
        }
    } /* Sortie de boucle : pos = 0 ie il ne reste plus qu'� d�caler vers la droite ou non le premier �l�ment de la ligne */

    if (tabJeu[numLig][pos] != 0 && vide_avant > 0)
    {
        tabJeu[numLig][premier_vide]=tabJeu[numLig][pos];
        tabBombe[numLig][premier_vide]=tabBombe[numLig][pos];

        tabJeu[numLig][pos]=0;
        tabBombe[numLig][pos]=0;
    }


}

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : tout le tableau de jeu et tabBombe
    @returns : -
    @ensures : toutes les lignes du tableau ont �t� d�cal�es vers la droite,  l'�ge des bombes pr�sentes est valide
*/

void Droite_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < lignes; j=j+1)
    {
        Droite_ligne(tabJeu, tabBombe, j, colonnes);
    }
}

/*
    @requires : le tableau 2D de jeu d�j� d�cal� vers la droite + et le tableau d'�ge des bombes initialis�
                + son nombre de colonnes (>= � 2) + num�ro de ligne (valide) � traiter pr l'addition
    @assigns : la ligne numLig du tableau de jeu et celle de tabBombe
    @returns : -
    @ensures : s'il y avait deux objets �gaux l'un � c�t� de l'autre dans la ligne ceux-ci ont disparu
                   + le double est apparu dans la case la plus � droite (si nombres)
                   ou x est apparu dans la case la plus � droite (si bombes +)
                   ou * est apparu dans la case la plus � droite (si bombes x)
                   ou explosion des deux bombes *
                + �ge des bombes valide dans la ligne
*/


void Ajouter_ligne_droite (int  ** tabJeu, int ** tabBombe, long colonnes, long lignes, int numLig)
{
    int pos;
    pos = colonnes - 1;

    while (pos > 0 && tabJeu[numLig][pos - 1] != 0 )
    {
        if(tabJeu[numLig][pos] == tabJeu[numLig][pos -1 ])
        {
            if (tabJeu[numLig][pos] > 0) /* Si les deux objets sont des nombres */
            {

                tabJeu[numLig][pos]= tabJeu[numLig][pos]* 2;
                tabJeu[numLig][pos - 1]=0;

                Droite_ligne(tabJeu, tabBombe, numLig, colonnes);
            }
            else if (tabJeu[numLig][pos] != -3) /* Cas des bombes + et x */
            {

                tabJeu[numLig][pos]= tabJeu[numLig][pos] - 1;
                tabJeu[numLig][pos -1]=0;

                tabBombe[numLig][pos]=1;
                tabBombe[numLig][pos -1]=0;

                Droite_ligne(tabJeu, tabBombe, numLig, colonnes);
            }
            else /* Cas de deux bombes * */
            {
                Position Bombe1, Bombe2;
                Bombe1.i = numLig; Bombe2.i = numLig;
                Bombe1.j = pos; Bombe2.j = pos-1;

                Explosion_etoile(tabJeu, tabBombe, Bombe1, lignes, colonnes);
                Explosion_etoile(tabJeu, tabBombe, Bombe2, lignes, colonnes);

            }


            pos = pos - 1;
        }
        else
        {
            pos = pos - 1 ;
        }
    } /* Sortie de boucle : il n'y a plus de case � traiter sur la ligne, toutes les additions ont �t� faites */



}


/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : toutes les colonnes du tableau de jeu ont �t� trait�es pour l'addition vers la droite
                + �ge des bombes valides
*/

void Ajouter_tableau_droite (int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < lignes; j=j+1)
    {
        Ajouter_ligne_droite(tabJeu, tabBombe, colonnes, lignes, j);
    }
}

/*
    @requires : le tableau 2D de jeu  et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : on a effectu� le mouvement droite (d�calage vers la droite + addition si possible) + �ge des bombes valide
*/


void Mouvement_droite(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    Droite_tableau(tabJeu, tabBombe, lignes, colonnes);
    Ajouter_tableau_droite(tabJeu, tabBombe, lignes, colonnes);
}


/* Fonctions pour traiter le d�placement vers la gauche : j */

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s
            + le num�ro de ligne valide � d�caler vers la gauche + leur nombre de colonnes commun (>= � 2)
    @assigns : la ligne numLig du tableau de jeu et celle de tabBombe
    @returns : -
    @ensures : toutes les cases de la ligne ont �t� d�cal�es, aucune case vide entre deux cases pleines
            + + si une bombe s'est d�plac�e, son �ge aussi
*/

void Gauche_ligne (int ** tabJeu, int ** tabBombe, int numLig, long colonnes)
{

    int vide_avant; int premier_vide;
    int pos;

    pos = 0;
    vide_avant = 0;
    premier_vide = pos;

    while (pos < colonnes - 1)
    {
        if ((tabJeu[numLig][pos] != 0) && vide_avant==0)
        {
            pos = pos + 1;
        }
        else if (tabJeu[numLig][pos] != 0)
        {
            tabJeu[numLig][premier_vide]=tabJeu[numLig][pos];
            tabBombe[numLig][premier_vide]=tabBombe[numLig][pos];

            tabJeu[numLig][pos]=0;
            tabBombe[numLig][pos]=0;

            pos = pos + 1;
            premier_vide= premier_vide + 1;
        }
        else if (tabJeu[numLig][pos] == 0 && vide_avant == 0)
        {
            premier_vide=pos;
            vide_avant = 1;
            pos = pos + 1 ;
        }
        else
        {
            pos = pos + 1 ;
        }

    } /* Sortie de boucle : pos = colonnes - 1 ie il ne reste plus qu'� d�caler ou non vers la gauche le dernier �l�ment de la ligne */

    if (tabJeu[numLig][pos] != 0 && vide_avant > 0)
    {
        tabJeu[numLig][premier_vide]=tabJeu[numLig][pos];
        tabBombe[numLig][premier_vide]=tabBombe[numLig][pos];

        tabJeu[numLig][pos]=0;
        tabBombe[numLig][pos]=0;
    }


}

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis� + leurs dimensions communes (>= � 2)
    @assigns : tout le tableau de jeu et tabbombe
    @returns : -
    @ensures : toutes les lignes du tableau ont �t� d�cal�es vers la gauche, �ge des bombes pr�sentes valide
*/

void Gauche_tableau(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < lignes; j=j+1)
    {
        Gauche_ligne(tabJeu, tabBombe, j, colonnes);
    }
}

/*
    @requires : le tableau 2D de jeu d�j� d�cal� vers la gauche + tabBombe d�j� initialis�
        + leur nombre de colonnes commun (>= � 2) + num�ro de ligne (valide) � traiter pr l'addition
    @assigns : la ligne numLig du tableau de jeu et celle de tabBombe
    @returns : -
    @ensures : s'il y avait deux objets �gaux l'un � c�t� de l'autre dans la ligne ceux-ci ont disparu
                   + le double est apparu dans la case la plus � gauche (si nombres)
                   ou x est apparu dans la case la plus � gauche (si bombes +)
                   ou * est apparu dans la case la plus � gauche (si bombes x)
                   ou explosion des deux bombes *
            + �ge des bombes valide dans la ligne
*/

void Ajouter_ligne_gauche (int  ** tabJeu, int ** tabBombe, long colonnes, long lignes, int numLig)
{
    int pos;
    pos = 0 ;

    while (pos < (colonnes-1) && tabJeu[numLig][pos + 1] != 0)
    {
        if(tabJeu[numLig][pos] == tabJeu[numLig][pos + 1 ])
        {
            if (tabJeu[numLig][pos] > 0) /* Si les deux objets sont des nombres */
            {

                tabJeu[numLig][pos]= tabJeu[numLig][pos]* 2;
                tabJeu[numLig][pos + 1]=0;

                Gauche_ligne(tabJeu, tabBombe, numLig, colonnes);
            }
            else if (tabJeu[numLig][pos] != -3) /* Cas des bombes + et x */
            {

                tabJeu[numLig][pos]= tabJeu[numLig][pos] - 1;
                tabJeu[numLig][pos + 1]=0;

                tabBombe[numLig][pos]=1;
                tabBombe[numLig][pos + 1]=0;

                Gauche_ligne(tabJeu, tabBombe, numLig, colonnes);
            }
            else /* Cas de deux bombes * */
            {
                Position Bombe1, Bombe2;
                Bombe1.i = numLig; Bombe2.i = numLig;
                Bombe1.j = pos; Bombe2.j = pos + 1;

                Explosion_etoile(tabJeu, tabBombe, Bombe1, lignes, colonnes);
                Explosion_etoile(tabJeu, tabBombe, Bombe2, lignes, colonnes);

            }

            pos=pos + 1;
        }
        else
        {
            pos = pos + 1 ;
        }
    } /* Sortie de boucle : il n'y a plus de case � traiter sur la ligne, toutes les additions ont �t� faites */


}


/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : toutes les lignes du tableau de jeu ont �t� trait�es pour l'addition vers la gauche, �ge des bombes valide
*/

void Ajouter_tableau_gauche (int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    int j;

    for(j=0; j < lignes; j=j+1)
    {
        Ajouter_ligne_gauche(tabJeu, tabBombe, colonnes, lignes, j);
    }
}

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
    @assigns : le tableau 2D de jeu et tabBombe
    @returns : -
    @ensures : on a effectu� le mouvement gauche (d�calage vers la gauche + addition si possible)
                + �ge des bombes valide dans le tableau
*/

void Mouvement_gauche(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{
    Gauche_tableau(tabJeu, tabBombe, lignes, colonnes);
    Ajouter_tableau_gauche(tabJeu, tabBombe, lignes, colonnes);
}



/* Fonctions pour traiter l'explosion des diff�rentes bombes */

/*
    @requires : le tableau 2D de jeu et de bombe d�j� initialis�s + leurs dimensions communes (>= � 2)
                + la position d'une bombe '+'
    @assigns : les 4 cases du tableau de jeu entourant la bombe '+' et celle-ci
                + tabBombe
    @returns : -
    @ensures : les 5 cases ont disparu si celles-ci sont accessibles, tabBombe a �t� mis � jour
*/

void Explosion_plus(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes)
{

    long i, j;
    i=Pos_bombe.i;
    j=Pos_bombe.j;

    tabJeu[i][j]=0;
    tabBombe[i][j]=0;

    if (i > 0)
    {
         tabJeu[i-1][j]=0;
         tabBombe[i-1][j]=0;
    }
    if( i < lignes - 1)
    {
        tabJeu[i+1][j]=0;
        tabBombe[i+1][j]=0;
    }
    if ( j > 0)
    {
        tabJeu[i][j-1]=0;
        tabBombe[i][j-1]=0;
    }
    if (j < colonnes - 1)
    {
        tabJeu[i][j+1]=0;
        tabBombe[i][j+1]=0;
    }

}

/*
    @requires : le tableau 2D de jeu et de bombe d�j� initialis�s + leurs dimensions communes(>= � 2)
                + la position d'une bombe 'x'
    @assigns : les 4 cases du tableau de jeu aux diagonales de la bombe 'x' et celle-ci
                + tabBombe
    @returns : -
    @ensures : les 5 cases ont disparu si celles-ci sont accessibles et tabBombe a �t� mis � jour
*/

void Explosion_fois(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes)
{

    long i, j;
    i=Pos_bombe.i;
    j=Pos_bombe.j;

    tabJeu[i][j]=0;
    tabBombe[i][j]=0;

    if (i > 0)
    {
        if (j > 0)
        {
            tabJeu[i-1][j-1]=0;
            tabBombe[i-1][j-1]=0;
        }
        if( j < colonnes - 1)
        {
            tabJeu[i-1][j+1]=0;
            tabBombe[i-1][j+1]=0;
        }
    }
    if ( i < lignes - 1)
    {
        if (j > 0)
        {
            tabJeu[i+1][j-1]=0;
            tabBombe[i+1][j-1]=0;
        }
        if (j < colonnes - 1)
        {
            tabJeu[i+1][j+1]=0;
            tabBombe[i+1][j+1]=0;
        }
    }

}

/*
    @requires : le tableau 2D de jeu et de bombe d�j� initialis�s + leurs dimensions communes(>= � 2)
                + la position d'une bombe '*'
    @assigns : les 8 cases du tableau de jeu entourant la bombe '*' et celle-ci
                + tabBombe
    @returns : -
    @ensures : les 9 cases ont disparu si celles-ci sont accessibles et tabBombe � �t� mis � jour
*/

void Explosion_etoile(int ** tabJeu, int ** tabBombe, Position Pos_bombe, long lignes, long colonnes)
{
    Explosion_plus(tabJeu, tabBombe, Pos_bombe, lignes, colonnes);
    Explosion_fois(tabJeu, tabBombe, Pos_bombe, lignes, colonnes);
}


/* Fonctions pour g�rer l'�ge des bombes */

/*
    @requires : le tableau 2D de jeu et tabBombe d�j� initialis�s + leurs dimensions communes (>= � 2)
                + la position d'une bombe '*'
    @assigns : le tableau de jeu 2D et celui de l'�ge des bombes
    @returns : -
    @ensures : si l'utilisateur a choisi de ne pas faire exploser une bombe pendant 7 tours cons�cutifs, celle-ci explose d'elle-m�me
*/
void Explosion_Bombe(int ** tabJeu, int ** tabBombe, long lignes, long colonnes)
{

    int i, j;
    Position pos_bombe;

    for(i=0; i < lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
            if(tabBombe[i][j] == 9)
            {
                pos_bombe.i = i;
                pos_bombe.j = j;

                switch(tabJeu[i][j])
                {
                case -1:
                    Explosion_plus(tabJeu, tabBombe, pos_bombe, lignes, colonnes);
                break;
                case -2:
                    Explosion_fois(tabJeu, tabBombe, pos_bombe, lignes, colonnes);
                break;
                case -3:
                    Explosion_etoile(tabJeu, tabBombe, pos_bombe, lignes, colonnes);
                break;
                }
            }
        }
    }

}


/*
    @requires : le tableau 2D tabBombe d�j� initialis�s + ses dimensions (>= � 2)
    @assigns : tabBombe
    @returns : -
    @ensures : si une bombe est pr�sente dans le tableau, son �ge augmente de 1 � la fin du round
*/


void Actualiser_tabBombe(int ** tabBombe, long lignes, long colonnes)
{
    int i, j;

    for (i=0; i< lignes; i=i+1)
    {
        for(j=0; j < colonnes; j=j+1)
        {
            if(tabBombe[i][j] > 0)
            {
                tabBombe[i][j]=tabBombe[i][j] + 1;
            }
        }
    }
}


