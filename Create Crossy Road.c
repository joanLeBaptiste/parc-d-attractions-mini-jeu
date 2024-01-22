#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include "headerBallon.h"

//Constante//
#define LARGEUR 800
#define HAUTEUR 600
#define VITESSE 1
#define NBPLANCHES 20


//sous-programmes//
/// celui-ci nous permettra de déplacer les planches
void deplacerPlanches(Obstacle planches[], int nbPlanches) {
    int i;
    for (i = 0; i < nbPlanches; i++) {
        /// Mettre à jour la position de chaque planche en fonction de sa vitesse
        planches[i].planche.x += planches[i].planche.vit;

        /// Si une planche sort de l'écran vers la gauche, la réinitialiser à une nouvelle position à droite de l'écran (la vitesse peut-être négative)
        if (planches[i].planche.x + planches[i].sprite->w < 0 && planches[i].planche.vit < 0) {
            planches[i].planche.x = LARGEUR;
        }

        /// Si une planche sort de l'écran vers la droite, la réinitialiser à une nouvelle position à gauche de l'écran
        if (planches[i].planche.x > LARGEUR && planches[i].planche.vit > 0) {
            planches[i].planche.x = -planches[i].sprite->w;
        }
    }
}

/// ce sous-programme permet de faire bouger le joueur s'il est sur une planche
void verifier(Position* joueur, Obstacle planches[], int nbPlanches, BITMAP* poulet) {
    int i;
    int joueurSurPlanche = 0;

    for (i = 0; i < nbPlanches; i++) {
        if (joueur->x >= planches[i].planche.x && joueur->x <= (planches[i].planche.x + planches[i].sprite->w) &&
            joueur->y >= planches[i].planche.y && joueur->y <= (planches[i].planche.y + planches[i].sprite->h)) {
            joueurSurPlanche = 1; /// on regarde d'abord si le joueur est sur une planche
            break;
        }
    }

    if (joueurSurPlanche) {
        joueur->x += planches[i].planche.vit; ///si c'est le cas il se déplace à la meme vitesse que la planche
    }
}

///sous-programme qui vérifie si le joueur a perdu ou gagner
int defaite(Position* joueur, Obstacle planches[], int nbPlanches, BITMAP* poulet) {
    int sureau = 0;

    for (int i = 0; i < nbPlanches; i++) {
        if ( joueur->x  >= planches[i].planche.x && joueur->x <= planches[i].planche.x + 100 && joueur->y  >= planches[i].planche.y && joueur->y <= planches[i].planche.y + 50) {
            /// Vérifier si le joueur est sur le cours d'eau
            if (joueur->y >= 50 && joueur->y <= 550) {
                sureau = 1;
                break;
            }
        }
    }

    /// Puis si c'est le cas il vérifie s'il est sur une planche
    if (sureau && joueur->y >= 50 && joueur->y <= 550) {
        return 1; /// Le joueur joue encore si c'est le cas
    } else if (!sureau && joueur->y >= 50 && joueur->y <= 550) {
        return 2; /// Le joueur a perdu si ce n'est pas le cas
    } else if (joueur->y >= 0 && joueur->y <= 50) {
        return 3; /// Le joueur a gagné s'il est de l'autre côté de la rive
    }

}








void crossyroad(joueur_principale tab[2]) {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    srand(time(NULL));


    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    ///on retire un ticket pour la participation
    tab[0].ticket = tab[0].ticket - 1;
    tab[1].ticket = tab[1].ticket - 1;

    printf("oui");

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
    poulet = load_bitmap("crossy/poulet.bmp", NULL);
    planche1 = load_bitmap("crossy/planche1.bmp", NULL);
    fond = load_bitmap("crossy/fond.bmp", NULL);
    /// on verifie qu'elle soit bien chargée
    if (poulet == NULL  || fond == NULL || planche1 == NULL) {
        printf("Erreur lors du chargement de l'image.\n");
        allegro_exit();
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
    while (victoirej2 == 0 && defaitej2 == 0) {
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
                fflush(stdin);
                rest(3000);
            }
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 3) {
                victoirej2 = 1;
                tourj2 = 0;
                fflush(stdin);
                rest(3000);
            }
        }
        if (tourj1==1) {
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 2) {
                defaitej1 = 1;
                tourj2 = 1;
                joueur.x = 400;
                joueur.y = 575;
                tourj1 = 0;
                fflush(stdin);
                rest(3000);
            }
            if (defaite(&joueur, planche, NBPLANCHES, poulet) == 3) {
                victoirej1 = 1;
                tourj2 = 1;
                joueur.x = 400;
                joueur.y = 575;
                tourj1 = 0;
                fflush(stdin);
                rest(3000);
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
        tab[0].ticket = tab[0].ticket + 3;
        tab[0].score_crossy = tab[0].score_crossy + 1;

    } else if (defaitej1 == 1) {
        printf("Le joueur 1 a perdu!\n");

    }
    if (victoirej2 == 1) {
        printf("Le joueur 2 a gagne un ticket!\n");
        tab[1].ticket = tab[1].ticket + 3;
        tab[1].score_crossy = tab[1].score_crossy + 1;


    } else if (defaitej2 == 1) {
        printf("Le joueur 2 a perdu!\n");
    }

    // Libération de la mémoire //
    destroy_bitmap(page);
    destroy_bitmap(decor);
    destroy_bitmap(poulet);
    for(int i = 0 ; i<NBPLANCHES; i++) {
        destroy_bitmap(planche[i].sprite);}
    destroy_bitmap(planche1);
    destroy_bitmap(fond);

}