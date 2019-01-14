/// Structure

typedef struct Case Case;
struct Case{
    int type; //forme de la cases
    int up; // Porte de la case en direction du haut
    int right; // Porte de la case en direction de la droite
    int down; // Porte de la case en direction du bas
    int left; // Porte de la case en direction de la gauche
    int check; // valeur qui permet de verifier si la case est liee a d'autres si elle sont equivalente
};
