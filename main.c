#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"
#include "headerBallon.h"
#include <time.h>

//Constante//
#define LARGEUR 800
#define HAUTEUR 600
#define VITESSE 1
#define NBPLANCHES 20

int main() {
    srand(time(NULL));
    initialisationAllegro();
    plateau();
    allegro_exit();
    return 0;
    //variable//
    Position joueur;
    Obstacle planche[NBPLANCHES];  /// Tableau de structures pour nos planches
    int victoirej1 = 0;
    int victoirej2 = 0;
    int defaitej1 = 0; /// variables qui definissent si un joueur a gagné ou perdu
    int defaitej2 = 0;
    int tourj1 = 1;
    int tourj2 = 0;

    //bitmap//
    /// Création du double buffer
    BITMAP* page = create_bitmap(LARGEUR, HAUTEUR);
    BITMAP* decor = create_bitmap(LARGEUR, HAUTEUR);

    BITMAP* fond = NULL;
    BITMAP* planche1 = NULL;
    BITMAP* poulet = NULL;

    ///chargement des bitmaps
    poulet = load_bitmap("poulet.bmp", NULL);
    planche1 = load_bitmap("planche1.bmp", NULL);
    fond = load_bitmap("fond.bmp", NULL);
    /// on verifie qu'elle soit bien chargée
    if (poulet == NULL  || fond == NULL || planche1 == NULL) {
        printf("Erreur lors du chargement de l'image.\n");
        allegro_exit();
        return 1;
    }


    /// point de départ du joueur
    joueur.x = 400;
    joueur.y = 575;
    joueur.depx = 0;
    joueur.depy = 0;
    joueur.vit = VITESSE;

    ///on initailise nos planches
    for (int i = 0; i < NBPLANCHES / 2; i++) {
        float vitesse = -0.9f + ((float)rand() / RAND_MAX) * 1.8f; ///on choisit un reel pour pas que la vitesse soit trop élevé

        for (int j = 0; j < 2; j++) { /// 2 boucles car 2 planches par lignes
            if (j == 0) {
                planche[2 * i + j].planche.x = (rand() % (LARGEUR - planche1->w));
            }
            else {
                ///on verifie que les planches d'une meme ligne ne se chevauchent pas
                do {
                    planche[2 * i + j].planche.x = (rand() % (LARGEUR - planche1->w));
                } while (planche[2 * i + j].planche.x  < planche[2 * i].planche.x && planche[2 * i + j].planche.x + 100 > planche[2 * i].planche.x || planche[2 * i + j].planche.x  > planche[2 * i].planche.x && planche[2 * i + j].planche.x < planche[2 * i].planche.x + 100);
            }
            planche[2 * i + j].planche.y = 50 + i * 50;
            planche[2 * i + j].planche.vit = vitesse;
            planche[2 * i + j].sprite = planche1;
        }
    }

    //boucle de jeu//
    ///Elle ne s'arrete que lorsque le joueur 2 a fini son tour
    while (defaitej2 == 0 && victoirej2 == 0) {
        /// On gere les deplacements du joueur en fonction des touches haut,bas,droit et gauche du clavier
        if (key[KEY_UP])
            joueur.depy = -joueur.vit;

        else if (key[KEY_DOWN])
            joueur.depy = joueur.vit;
        else
            joueur.depy = 0;

        if (key[KEY_LEFT])
            joueur.depx = -joueur.vit;
        else if (key[KEY_RIGHT])
            joueur.depx = joueur.vit;
        else
            joueur.depx = 0;

        /// Mise à jour des coordonnées du joueur
        joueur.x += joueur.depx;
        joueur.y += joueur.depy;
        ///on verifie ensuite si le joueur a perdu ou non et qui doit jouer
        if (tourj2==1) {
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 2) {
                defaitej2 = 1;
                tourj2 = 0;
            }
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 3) {
                victoirej2 = 1;
                tourj2 = 0;
            }
        }
        if (tourj1==1) {
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 2) {
                defaitej1 = 1;
                tourj2 = 1;
                joueur.x = 400;
                joueur.y = 575;
                tourj1 = 0;
            }
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 3) {
                victoirej1 = 1;
                tourj2 = 1;
                joueur.x = 400;
                joueur.y = 575;
                tourj1 = 0;
            }
        }
        ///si le joueur est sur une planche se deplacera de la meme facon
        verifier(&joueur, planche, NBPLANCHES, poulet);

        // Affichage à l'écran des éléments du jeu //
        blit(decor,page,0,0,0,0,LARGEUR,HAUTEUR);
        draw_sprite(page, fond, 0, 0);
        for(int i = 0 ; i<NBPLANCHES; i++) {
            draw_sprite(page, planche[i].sprite, planche[i].planche.x, planche[i].planche.y);
        }
        draw_sprite(page, poulet, joueur.x, joueur.y);
        deplacerPlanches( planche, NBPLANCHES);
        blit(page,screen,0,0,0,0,LARGEUR,HAUTEUR);

    }
    ///a la fin on affiche si les joueurs on gagné ou perdu
    if (victoirej1 == 1) {
        printf("Le joueur 1 a gagne un ticket !\n");
    } else if (defaitej1 == 1) {
        printf("Le joueur 1 a perdu!\n");
    }
    if (victoirej2 == 1) {
        printf("Le joueur 2 a gagne un ticket!\n");
    } else if (defaitej2 == 1) {
        printf("Le joueur 2 a perdu!\n");
    }

}END_OF_MAIN();




