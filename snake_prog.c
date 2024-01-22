#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "headerBallon.h"

#define LARGEUR 800
#define HAUTEUR 600
#define LAR_CADRE 900
#define HAU_CADRE 700
#define TAILLE_CASE 50

// sous-progremme //
///pour le déplacement du serpent
void deplacerSerpent(bool deplacementActif, Maillon* serpent, float directionX, float directionY, double* lastChangeX, double* lastChangeY) {
    if (deplacementActif) { /// si une touche du clavier a été préssée
        Maillon* maillonCourant = serpent;
        ///on utilise round pour convertir en entier et TAILLE_CASE pour qu'il n'y ait pas d'erreur
        maillonCourant->serpent.x = TAILLE_CASE * round((maillonCourant->serpent.x) / TAILLE_CASE);
        maillonCourant->serpent.y = TAILLE_CASE * round((maillonCourant->serpent.y) / TAILLE_CASE);


        int ancienX = maillonCourant->serpent.x;
        int ancienY = maillonCourant->serpent.y;
        /// le corps du serpent suit la tete
        maillonCourant->serpent.x += TAILLE_CASE * directionX;
        maillonCourant->serpent.y += TAILLE_CASE * directionY;

        int tempX, tempY;
        while (maillonCourant->next != NULL) {
            maillonCourant = maillonCourant->next;
            tempX = maillonCourant->serpent.x;
            tempY = maillonCourant->serpent.y;
            maillonCourant->serpent.x = ancienX;
            maillonCourant->serpent.y = ancienY;
            ancienX = tempX;
            ancienY = tempY;
        }

        /// Vérification si le dernier maillon atteint une position multiple de TAILLE_CASE (utilisation de fmod)  car
        /// le changement de direction doit se faire quand le serpent est pile dans une case
        if (fmod(serpent->serpent.x, TAILLE_CASE) == 0 && fmod(serpent->serpent.y, TAILLE_CASE) == 0) {
            *lastChangeX = serpent->serpent.x;
            *lastChangeY = serpent->serpent.y;
        }
    }
}




///on détecte si le serpent et la pomme ont les memes coordonnées
bool collisionPomme(Maillon* serpent, Pomme* pomme) {
    if (serpent->serpent.x == pomme->position.x && serpent->serpent.y == pomme->position.y){
        return true;}
    else{return false;}
}

///on génère une nouvelle position pour la pomme en cas de contact
void genererPositionPomme(Pomme* pomme, Maillon* serpent) {
    int posX, posY;
    bool positionValide = false;

    ///si les positions sont les memes
    while (!positionValide) {
        ///on genere une nouvelle position aleatoire pour la pomme
        int alea1 = rand()% 16;
        int alea2 = rand()% 12;

        posX = 50 + alea1 * TAILLE_CASE;
        posY = 50 + alea2 * TAILLE_CASE;
        pomme->position.x = posX ;
        pomme->position.y = posY ;

        /// Vérifier si la position de la pomme n'est pas la meme que celle du serpent
        if (!collisionPomme(serpent, pomme)) {
            positionValide = true;
        }
    }
}

///fonction qui vérifie si un joueur a perdu
int conditionDefaite(Maillon* serpent) {
    /// On vérifie les collisions entre la tete et le corps du serpent
    Maillon* maillonCourant = serpent->next;
    while (maillonCourant != NULL) {
        if (serpent->serpent.x == maillonCourant->serpent.x && serpent->serpent.y == maillonCourant->serpent.y) {
            return 2;
        }
        maillonCourant = maillonCourant->next;
    }

    /// On vérifie les collisions entre la tete et les bordures de l'écran
    if (serpent->serpent.x <= 0 || serpent->serpent.x >= LAR_CADRE-TAILLE_CASE || serpent->serpent.y < 50 || serpent->serpent.y >= HAU_CADRE-TAILLE_CASE) {
        return 2;
    }
    ///retourne 2 si le joueur a perdu

    return 1;
}


void snake(joueur_principale tab[2]) {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    srand(time(NULL));

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, LAR_CADRE, HAU_CADRE, 0, 0) != 0) {
        allegro_message("Problème lors du passage en mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    ///on retire un ticket pour la participation
    tab[0].ticket = tab[0].ticket - 1;
    tab[1].ticket = tab[1].ticket - 1;

    // Bitmap //
    BITMAP* fond = NULL;
    BITMAP* teteb = NULL;
    BITMAP* teteh = NULL;
    BITMAP* teteg = NULL;
    BITMAP* teted = NULL;

    fond = load_bitmap("snake/fondv3.bmp",NULL);
    teteb = load_bitmap("snake/Tete_bas.bmp",NULL);
    teteh = load_bitmap("snake/Tete_haut.bmp",NULL);
    teteg = load_bitmap("snake/Tete_gauche.bmp",NULL);
    teted = load_bitmap("snake/Tete.bmp",NULL);
    BITMAP* page = create_bitmap(LAR_CADRE, HAU_CADRE);
    BITMAP* decor = create_bitmap(LAR_CADRE, HAU_CADRE);

    // variable et initialisation //
    Maillon* serpent = malloc(sizeof(Maillon));
    serpent->serpent.x = LAR_CADRE/2;
    serpent->serpent.y = HAU_CADRE / 2;
    serpent->serpent.depx = LAR_CADRE / 2;
    serpent->serpent.depy = HAU_CADRE / 2;
    serpent->serpent.vit = 20.0;
    serpent->sprite = teted;
    serpent->next = NULL;

    Maillon* corps_serpent = malloc(sizeof(Maillon));
    corps_serpent->serpent.x = serpent->serpent.x - TAILLE_CASE;
    corps_serpent->serpent.y = serpent->serpent.y;
    corps_serpent->serpent.depx = serpent->serpent.x - TAILLE_CASE;
    corps_serpent->serpent.depy = serpent->serpent.y;
    corps_serpent->serpent.vit = serpent->serpent.vit;
    corps_serpent->sprite = load_bitmap("snake/corps.bmp", NULL);
    corps_serpent->next = NULL;

    serpent->next = corps_serpent;

    float directionX = 1.0;
    float directionY = 0.0;
    float derniereDirectionX = 0;
    float derniereDirectionY = 0;
    int pommesMangeesj1 = 0;
    int pommesMangeesj2 = 0;
    int tourj1 = 1;
    int tourj2 = 0;
    int victoirej1;
    int victoirej2;

    int deplacement = 0;
    double lastChangeX = serpent->serpent.x;
    double lastChangeY = serpent->serpent.y;

    Pomme* pomme = malloc(sizeof(Pomme));
    pomme->sprite = load_bitmap("snake/pomme.bmp", NULL);

    ///on génère une position pour la pomme
    genererPositionPomme(pomme, serpent);



    while ( tourj1 == 1 || tourj2 == 1) {
        deplacerSerpent(true, serpent, directionX, directionY, &lastChangeX, &lastChangeY);

/// Variable pour vérifier si un changement de direction a été effectué
        bool changementDirection = false;

        ///on regarde quelle touche a été préssée
        if (keypressed()) {
            if (key[KEY_LEFT] && derniereDirectionX != 1 && !changementDirection) {
                directionX = -1;
                directionY = 0;
                /// on génère le sprite qui convient à la direction empruntée
                serpent->sprite = teteg;
                changementDirection = true;
            } else if (key[KEY_RIGHT] && derniereDirectionX != -1 && !changementDirection) {
                directionX = 1;
                directionY = 0;
                serpent->sprite = teted;
                changementDirection = true;
            } else if (key[KEY_UP] && derniereDirectionY != 1 && !changementDirection) {
                directionX = 0;
                directionY = -1;
                serpent->sprite = teteh;
                changementDirection = true;
            } else if (key[KEY_DOWN] && derniereDirectionY != -1 && !changementDirection) {
                directionX = 0;
                directionY = 1;
                serpent->sprite = teteb;
                changementDirection = true;
            }
        }

/// On enregistre la dernière direction en cas de changement
        if (!changementDirection) {
            derniereDirectionX = directionX;
            derniereDirectionY = directionY;
        }

        changementDirection = false;



        deplacerSerpent(deplacement, serpent, directionX, directionY, &lastChangeX, &lastChangeY);

        if (conditionDefaite(serpent)==2 && tourj2==1){ ///on vérifie si le joueur n'a pas perdu
            printf("vous avez perdu joueur 2 \n");
            printf("vous avez mange %d pommes\n", pommesMangeesj2);
            tourj2=0; }

        if (conditionDefaite(serpent) == 2 && tourj1 == 1) {
            printf("Vous avez perdu joueur 1\n");
            printf("Vous avez mange %d pommes\n", pommesMangeesj1);

            /// On Réinitialise la position du serpent pour le deuxième joueur
            serpent->serpent.x = LAR_CADRE / 2;
            serpent->serpent.y = HAU_CADRE / 2;
            serpent->serpent.depx = LAR_CADRE / 2;
            serpent->serpent.depy = HAU_CADRE / 2;
            directionX = 1.0;
            directionY = 0.0;
            derniereDirectionX = 0;
            derniereDirectionY = 0;
            deplacement = 0;
            lastChangeX = serpent->serpent.x;
            lastChangeY = serpent->serpent.y;
            deplacerSerpent(true, serpent, directionX, directionY, &lastChangeX, &lastChangeY);
            changementDirection = false;

            /// On réinitialise également  la taille du serpent
            Maillon* maillonCourant = serpent->next;
            while (maillonCourant != NULL) {
                Maillon* maillonSuivant = maillonCourant->next;
                free(maillonCourant);
                maillonCourant = maillonSuivant;
            }
            serpent->next = NULL;

            /// Ajout d'un nouveau maillon pour le corps du serpent
            Maillon* corps_serpent = malloc(sizeof(Maillon));
            corps_serpent->serpent.x = serpent->serpent.x - TAILLE_CASE;
            corps_serpent->serpent.y = serpent->serpent.y;
            corps_serpent->serpent.depx = serpent->serpent.x - TAILLE_CASE;
            corps_serpent->serpent.depy = serpent->serpent.y;
            corps_serpent->serpent.vit = serpent->serpent.vit;
            corps_serpent->sprite = load_bitmap("snake/corps.bmp", NULL);
            corps_serpent->next = NULL;
            serpent->next = corps_serpent;

            /// On génère une nouvelle position pour la pomme
            genererPositionPomme(pomme, serpent);
            tourj2 = 1;
            tourj1 = 0;
            draw_sprite(page, serpent->sprite, serpent->serpent.x, serpent->serpent.y);
        }



        // Affichage à l'écran //
        clear_bitmap(page);
        blit(decor, page, 0, 0, 0, 0, LAR_CADRE, HAU_CADRE);
        draw_sprite(page, fond, 0,0);


        Maillon* maillonCourant = serpent;
        while (maillonCourant != NULL) {
            draw_sprite(page, maillonCourant->sprite, maillonCourant->serpent.x, maillonCourant->serpent.y);
            maillonCourant = maillonCourant->next;
        }

        draw_sprite(page, pomme->sprite, pomme->position.x, pomme->position.y);

        blit(page, screen, 0, 0, 0, 0, LAR_CADRE, HAU_CADRE);
        rest(100);

        /// On vérifie s'il y a contact entre le serpent et la pomme
        if (collisionPomme(serpent, pomme)) {
            /// si c'est le cas on génère une nouvelle pomme
            genererPositionPomme(pomme, serpent);
            if (tourj1==1){
                pommesMangeesj1 = pommesMangeesj1 + 1;}

            if (tourj2==1){
                pommesMangeesj2 = pommesMangeesj2 + 1;}

            /// On Ajoute un nouveau maillon au serpent pour son corps
            Maillon* nouveauMaillon = malloc(sizeof(Maillon));
            Maillon* dernierMaillon = serpent;
            while (dernierMaillon->next != NULL) {
                dernierMaillon = dernierMaillon->next;
            }
            dernierMaillon->next = nouveauMaillon;
            nouveauMaillon->serpent.x = dernierMaillon->serpent.depx;
            nouveauMaillon->serpent.y = dernierMaillon->serpent.depy;
            nouveauMaillon->serpent.depx = dernierMaillon->serpent.depx - TAILLE_CASE;
            nouveauMaillon->serpent.depy = dernierMaillon->serpent.depy;
            nouveauMaillon->serpent.vit = serpent->serpent.vit;
            nouveauMaillon->sprite = load_bitmap("snake/corps.bmp", NULL);
            nouveauMaillon->next = NULL;
        }
    }
    tab[0].score_snake = pommesMangeesj1;
    tab[1].score_snake = pommesMangeesj2;

    ///on regarde ensuite qui a gagné
    if (pommesMangeesj1 > pommesMangeesj2){
        printf("le joueur 1 l'emporte et gagne un ticket");
        victoirej1 = 1;
        tab[0].ticket = tab[0].ticket + 3;

    }
    else if (pommesMangeesj1 < pommesMangeesj2){
        printf("le joueur 2 l'emporte et gagne un ticket");
        victoirej2 = 1;
        tab[1].ticket = tab[1].ticket + 3;

    }
    else if (pommesMangeesj1 == pommesMangeesj2){
        printf("egalite il n'y a pas de vainqueur");
        tab[0].ticket = tab[0].ticket + 1;
        tab[1].ticket = tab[1].ticket + 1;

    }

    // Libération de la mémoire //
    destroy_bitmap(page);
    destroy_bitmap(decor);
    destroy_bitmap(serpent->sprite);
    destroy_bitmap(corps_serpent->sprite);
    destroy_bitmap(pomme->sprite);
    free(serpent);
    free(corps_serpent);
    free(pomme);

}