// M'Hirsi Aziz et YOUNSI Tayssir

/**
 * Nous nous sommes basée sur l'idée que l'on crée une valeur, ici appellé 'check' dans la sructrure Case, qui sera
 * differente dans toute les cases.
 * Puis dés que l'on ouvre une porte entre deux cases, on mets check a la valeur la plus basse des deux.
 * Et tant que toutes les cases sont differentes de zero, on continue.
 *
 * Une fois cela fait on va utiliser une tableau de reference appeller 'typeCase' qui va permettre de convertir les
 * portes en une valeur numerique appeller 'type' pour pouvoir le dessier et soius forme de dessin.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "case.h"


/// Variable modifiable

#define tailleLab 30

/// Fonctions


// initialise toute les sorties et entrees pour chaque type de case du tableau typeCase
void typeDeCase(int** typeCase){
    // 0 == up; 1 == right; 2 == down; 3 == left


    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 4; j++){
            if ((i == 1 && (j == 0 || j == 2))
                || (i == 0 && (j == 1 || j == 3))
                || (i == 2 && (j == 1 || j == 2 || j == 3))
                || (i == 3 && (j == 0 || j == 1 || j == 3))
                || (i == 4 && (j == 0 || j == 2 || j == 1))
                || (i == 5 && (j == 0 || j == 2 || j == 3))
                || (i == 6 && (j == 0 || j == 3))
                || (i == 7 && (j == 0 || j == 1))
                || (i == 8 && (j == 2 || j == 3))
                || (i == 9 && (j == 2 || j == 1))
                || (i == 10 && j == 0)
                || (i == 11 && j == 3)
                || (i == 12 && j == 2)
                || (i == 13 && j == 1)
                || (i == 15)
                )
            {
                typeCase[i][j] = 0; //fermer
            } else {
                typeCase[i][j] = 1; //ouvert
            }
        }
    }
}


//initialise le tableau qui gere le labyrinthe.
void init(int t,Case** tabLaby, int** typeCase){
    //creation des murs exterieurs
    for (int k = 0; k < t; k++) {
        tabLaby[0][k].type = 15;
        tabLaby[k][0].type = 15;
        tabLaby[t - 1][k].type = 15;
        tabLaby[k][t - 1].type = 15;

        tabLaby[0][k].check = -1;
        tabLaby[k][0].check = -1;
        tabLaby[t - 1][k].check = -1;
        tabLaby[k][t - 1].check = -1;

        tabLaby[0][k].up = 0;
        tabLaby[k][0].up = 0;
        tabLaby[t - 1][k].up = 0;
        tabLaby[k][t - 1].up = 0;
        tabLaby[0][k].right = 0;
        tabLaby[k][0].right = 0;
        tabLaby[t - 1][k].right = 0;
        tabLaby[k][t - 1].right = 0;
        tabLaby[0][k].down = 0;
        tabLaby[k][0].down = 0;
        tabLaby[t - 1][k].down = 0;
        tabLaby[k][t - 1].down = 0;
        tabLaby[0][k].left = 0;
        tabLaby[k][0].left = 0;
        tabLaby[t - 1][k].left = 0;
        tabLaby[k][t - 1].left = 0;
    }

    //mise a zero des cases
    for (int l = 1; l < t-1; l++) {
        for (int j = 1; j < t-1; j++) {
            tabLaby[l][j].type = 16;
            tabLaby[l][j].check = ((l-1)*(t-2))+(j-1);
            tabLaby[l][j].up = 0;
            tabLaby[l][j].right = 0;
            tabLaby[l][j].down = 0;
            tabLaby[l][j].left = 0;
        }
    }


    //entrer
    unsigned int entrer = (rand() % (t-2)) +1;
    tabLaby[entrer][0].type = 1;
    tabLaby[entrer][0].check = 0;
    //sortie
    unsigned int sortie1 = (rand() % (t-2)) +1;
    tabLaby[sortie1][(t-1)].type = 1;
    tabLaby[sortie1][(t-1)].check = 0;
    //sortie 2
    unsigned int sortie2 = (rand() % (t-2)) +1;
    while (sortie1 == sortie2) sortie2 = (rand() % (t-2)) +1;
    tabLaby[sortie2][(t-1)].type = 1;
    tabLaby[sortie2][(t-1)].check = 0;

    //creation des acces au case d'entrer et de sortie
    tabLaby[entrer][0].right = 1;
    tabLaby[entrer][0].left = 1;
    tabLaby[entrer][1].left = 1;

    tabLaby[sortie1][(t-1)].right = 1;
    tabLaby[sortie1][(t-1)].left = 1;
    tabLaby[sortie2][(t-2)].right = 1;

    tabLaby[sortie2][(t-1)].right = 1;
    tabLaby[sortie2][(t-1)].left = 1;
    tabLaby[sortie2][(t-2)].right = 1;
}

// verifie qu'il existe un lien entre toutes les cases
int checkDoor(int t, Case ** tabLaby){
    for (int i = 1; i < t-1; i++){
        for(int j = 1; j < t-1; j++){
            if (tabLaby[i][j].check != 0) return 0;
        }
    }

    return 1;
}

// fonction qui choisi aleatoirement une case et une direction et ouvre la porte entre les deux cases
void openWall(int t, Case ** tabLaby){
    unsigned int x1, y1, x2, y2, d, c1, c2;
    do {
        // choisie aleatoirement une case qui na pas la valeur de check egale a 0 pour eviter des operation inutile
        do {
            x2 = x1 = (unsigned int) ((rand() % (t - 2)) + 1);
            y2 = y1 = (unsigned int) ((rand() % (t - 2)) + 1);
            d = (unsigned int) (rand() % 4);
        } while (tabLaby[x1][y1].check == 0);

        //Donne lles coordonnee en de la deuxieme case en fonction de la direction choisie
        if(d == 0){
            (x2 = x1-1);
        }else if(d == 1){
            (y2 = y1+1);
        }else if(d == 2){
            (x2 = x1+1);
        } else{
            (y2 = y1-1) ;
        }
        // 0 == up; 1 == right; 2 == down; 3 == left


        if (tabLaby[x2][y2].type != 15
            && tabLaby[x1][y1].type != 15
            && (tabLaby[x1][y1].check != tabLaby[x2][y2].check))
        {

            // ouvre les porte des deux cases
            if(d == 0){
                tabLaby[x1][y1].up = 1;
                tabLaby[x2][y2].down = 1;
            } else if(d == 1){
                tabLaby[x1][y1].right = 1;
                tabLaby[x2][y2].left = 1;
            } else if(d == 2){
                tabLaby[x1][y1].down = 1;
                tabLaby[x2][y2].up = 1;
            } else {
                tabLaby[x1][y1].left = 1;
                tabLaby[x2][y2].right = 1;
            }

            //mets les deux case egale a le plus basse valeur de check
            if (tabLaby[x1][y1].check < tabLaby[x2][y2].check) {
                c1 = tabLaby[x2][y2].check;
                tabLaby[x2][y2].check = tabLaby[x1][y1].check;
                c2 = tabLaby[x1][y1].check;
            } else if (tabLaby[x1][y1].check > tabLaby[x2][y2].check) {
                c1 = tabLaby[x1][y1].check;
                tabLaby[x1][y1].check = tabLaby[x2][y2].check;
                c2 = tabLaby[x1][y1].check;
            }
            //mets toute les case liee au porte egale a la nouvelle valeur de check
            for (int i = 1; i < (t-1); i++) {
                for (int j = 1; j < (t-1); j++) {
                    if (tabLaby[i][j].check == c1) tabLaby[i][j].check = c2;
                }
            }
        }
    } while (!checkDoor(t, tabLaby));
}








// choisie le type de case qui correspond au porte defini dans chaque cases
void tabFiller(int t, Case ** tab, int ** tabC){
    int r, cpt = 0;
    for (int i = 1; i < t-1; i++){
        for(int j = 1; j < t-1; j++){
            r = 0;
            while(tabC[r][0] != tab[i][j].up
            || (tabC[r][1] != tab[i][j].right)
            || (tabC[r][2] != tab[i][j].down)
            || (tabC[r][3] != tab[i][j].left))
            {
                r++;
                if (r == 16) {
                    r = 0;
                    cpt++;
                }
                if (cpt == 10) {
                    printf("%d %d %d %d", tab[i][j].up, tab[i][j].right, tab[i][j].down, tab[i][j].left);
                    exit(1);
                }
            }
            // 0 == up; 1 == right; 2 == down; 3 == left
            tab[i][j].type = r;
            tab[i][j].up = tabC[r][0];
            tab[i][j].right = tabC[r][1];
            tab[i][j].down = tabC[r][2];
            tab[i][j].left = tabC[r][3];
        }
    }
}

// Fonction qui verifie le type de chaque case et quitte le programme si elle trouve une case vide.
void errorCheck(int t, Case ** tab){

    for (int i = 0; i < t; i++){
        for (int j = 0; j < t; j++){
            if (tab[i][j].type == 16){
                printf(" ---- ERROR ---- \n ---- CHECK ---- \n %d %d",i,j);
                exit(0);
            }
        }
    }
}




/// Print

// affiche le type de chaque case en fontion de leur enplacement. ainsi que les portes
void tabPrinter(int t,Case ** tabLaby){
    // imprime les valeurs de type en fonction de leur emplacement
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            if (tabLaby[i][j].type <= 9 && tabLaby[i][j].type >= 0){
                printf("   %d", tabLaby[i][j].type);
            } else if (tabLaby[i][j].type <= 99 || tabLaby[i][j].type <= 0){
                printf("  %d", tabLaby[i][j].type);
            } else {
                printf(" %d", tabLaby[i][j].type);
            }
        }
        printf("\n");
    }
    printf("\n");
    // imprime les valeurs de toute les porte de la case en fonction de leur emplacement
    printf("\n");
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < t; k++) {
                if (j == 0) {
                    printf( "   %d  ", tabLaby[i][k].up);
                } else if (j == 1) {
                    printf( " %d   %d", tabLaby[i][k].left, tabLaby[i][k].right);
                } else if (j == 2) {
                    printf( "   %d  ", tabLaby[i][k].down);
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}


// fonction qui regarder la ligne en fonction du type de case. Ou p est la ligne et n le type de la case
void dessin(int n, int p){
    int c = 0; //a modifier pour ecrire un caractere
    if (((n == 1 || n == 6 || n == 7 || n == 5 || n == 4 || n == 3 || n == 10) && p == 0)
        ||((n == 1 || n == 8 || n == 9 || n == 5 || n == 2 || n == 4 || n == 12) && p == 2)
        || n == 15)
    {
        printf("%d%d%d%d",c,c,c,c);
    } else if (((n == 0 || n == 8 || n == 9 || n == 2 || n == 11 || n == 12 || n == 13 || n == 14) && p == 0)
               ||((n == 0 || n == 2 || n == 3) && p == 1)
               ||((n == 0 || n == 6 || n == 7 || n == 3 || n == 11 || n == 13 || n == 10 || n == 14) && p == 2))
    {
        printf("%d  %d",c,c);
    } else if ((n == 6 || n == 8 || n == 5 || n == 11) && p == 1)
    {
        printf("%d   ",c);
    } else if ((n == 7 || n == 9 || n == 4 || n == 13) && p == 1)
    {
        printf("   %d",c);
    } else if ((n == 1 || n == 10 || n == 12 || n == 14) && p == 1)
    {
        printf("    ");
    }
}


// Fonction qui dessine le labyrinthe ligne par ligne .
void labyPrinter(int t, Case ** tab) {
    for (int i = 0; i < t; i++) {
        for (int k = 0; k < 3; k++){
            for (int j = 0; j < t; j++) {
                dessin(tab[i][j].type, k);
            }
            printf("\n");
        }
    }
}





/// Main

int main() {
    srand(time(NULL));

    //Tableeu contemant le labyrinthe
    Case ** tabLaby = (Case **)malloc(tailleLab * sizeof(Case *));
    for (int i = 0; i < tailleLab; ++i) {
        tabLaby[i] = (Case *)malloc(tailleLab * sizeof(Case));
    }

    //Tableau qui definit les type de case en fonction de leur entrées et sorties
    int ** typeCase = (int **)malloc(16 * sizeof(int *));
    for (int i = 0; i < 16; ++i) {
        typeCase[i] = (int *)malloc(4 * sizeof(int));
    }

    //initialisation
    init(tailleLab, tabLaby, typeCase);
    typeDeCase(typeCase);

    //Remplie les tableaux
    openWall(tailleLab, tabLaby);
    tabFiller(tailleLab, tabLaby, typeCase);
    errorCheck(tailleLab, tabLaby);

    //dessine le layrinthe
    labyPrinter(tailleLab,tabLaby);

    return 0;
}
