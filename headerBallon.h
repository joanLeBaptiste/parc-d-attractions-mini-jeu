//
// Created by jbfer on 18/05/2023.
//

#ifndef PROJET_HEADERBALLON_H
#define PROJET_HEADERBALLON_H
#include "stdbool.h"

typedef struct {
    char nom[20];
    double temps;
} Joueur;

typedef struct{
    char nom[20];
    int ticket;
    int x;
    int y;
    float tempsBallon;
    int score_crossy;
    int score_snake;
    BITMAP* statique;
    BITMAP* walk_1;
    BITMAP* walk_2;
}joueur_principale;

typedef struct {
    BITMAP* animations_pop[5];
    int touche;
    int x; /// x et y de la hitbox
    int y;
    int x_image; /// x et y de l'image
    int y_image;
} Ballon;

//structure qui nous permettra d'avoir la position du joueur et des planches//
typedef struct position {
    float x;
    float y;
    float depx;
    float depy;
    float vit;
} Position;

typedef struct maillon {
    Position serpent;
    BITMAP* sprite;
    struct maillon* next;
} Maillon;

typedef struct pomme {
    Position position;
    BITMAP* sprite;
} Pomme;


///je choisis de creer une autre structure pour les planches car on aura besoin d'avoir directement le sprite des planches comme on aura un tableau de structure
typedef struct {
    Position planche;
    BITMAP* sprite;
} Obstacle;

///fonction jeu crossy road
void deplacerPlanches(Obstacle planches[], int nbPlanches);
void verifier(Position* joueur, Obstacle planches[], int nbPlanches, BITMAP* poulet);
int defaite(Position* joueur, Obstacle planches[], int nbPlanches, BITMAP* poulet);
void crossyroad(joueur_principale tab[2]);

///SNAKE
void snake(joueur_principale tab[2]);
int conditionDefaite(Maillon* serpent);
void genererPositionPomme(Pomme* pomme, Maillon* serpent);
bool collisionPomme(Maillon* serpent, Pomme* pomme);
void deplacerSerpent(bool deplacementActif, Maillon* serpent, float directionX, float directionY, double* lastChangeX, double* lastChangeY);

/// PLATEAU ET TIR AU BALLON
void jeu_principal(joueur_principale Joueur[2]);
void demarrage(joueur_principale Joueur[2]);
void remove_blanc_fond(BITMAP* bitmap, int tolerance);
void initialisationAllegro();
void chargementBallon(Ballon ballons[]);
void animationBallon(Ballon ballons[], int numero, BITMAP* fond_jeu);
void destroy_bitmap_ballon(Ballon ballons[]);
void drawBallons(BITMAP* buffer, Ballon ballons[], int ballonnTouche);
void plateau();
void chargementAnimJoueur(joueur_principale joueur[2]);
void destroy_Joueur_bitmap(joueur_principale joueur[2]);
void nom(joueur_principale joueur[2], int joueurIndex);

/// JACKPOT ET RANCH
void ParisHippique(joueur_principale tab[2]);
void Jackpot (joueur_principale tab[2]);

/// TAUPE
void taupe ();
int decompte_timer(int duree );
BITMAP *creer( char *chaine);
typedef struct Joueur {
    int score;
    int tempsRestant;
}t_joueur;
void decrementerTemps(t_joueur* joueur,long int tstart);


#endif //PROJET_HEADERBALLON_H
