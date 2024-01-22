
#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"
#include "headerBallon.h"
#include "time.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void incrementerScore(t_joueur* joueur) {
    joueur->score++;
}

void decrementerTemps(t_joueur* joueur,long int tstart) {
    joueur->tempsRestant=30- (time(NULL)-tstart);
}

BITMAP *creer( char *chaine){
    BITMAP *bitmap;
    bitmap= load_bitmap(chaine, NULL);
    if(bitmap==NULL){
        printf("Erreur : Impossible de charger l'image.\n");
        exit(EXIT_FAILURE);
    }
    return bitmap;
}


int decompte_timer(int duration ) {
    time_t startTime = time(NULL);
    // Durée en secondes
    int remaining;
    while (1) {
        time_t currentTime = time(NULL);
        int elapsed = difftime(currentTime, startTime);


        remaining = duration - elapsed;


        if (remaining <= 0) {
            break;
        }

        //printf("Temps restant : %d secondes\n", remaining);}
        return remaining;
    }
}


void taupe() {
    srand(time(NULL));
    int timer = 0;
    int dureeApparition = 6 * 60;
    int position;
    t_joueur player1, player2, *playerOn;
    allegro_init();
    install_mouse();
    install_keyboard();
    int mouseX = mouse_x;
    int mouseY = mouse_y;
    set_color_depth(desktop_color_depth());
    set_color_depth(24); // Profondeur des couleurs
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0); // Mode graphique

    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0)) != 0) {
        allegro_message("Probleme de mode graphique\n");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP *buffer1 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP *buffer2 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP *fond = NULL;
    BITMAP *tronc=NULL;
    BITMAP *taupe=NULL;
    fond = load_bitmap("fond4.bmp", NULL);
    taupe= load_bitmap("Taupe.bmp", NULL);
    if (fond == NULL || taupe == NULL) {
        printf("Erreur : Impossible de charger l'image.\n");
        exit(1);
    }


    int dim_taupe_x = taupe->w/2;
    int dim_taupe_y = taupe->h/2;
    BITMAP *resizedTaupe = create_bitmap(dim_taupe_x, dim_taupe_y);
    stretch_blit(taupe, resizedTaupe, 0, 0, taupe->w, taupe->h, 0, 0, dim_taupe_x, dim_taupe_y);

    player1.score=0;
    player1.tempsRestant= decompte_timer(30);
    player2.score=0;
    player2.tempsRestant= decompte_timer(30);


    playerOn=&player1;

    FONT* police = font;
    police->height=6;

    int tour[2];

    long int tstart = time(NULL);
    while (!key[KEY_ESC]) {
        if (player1.tempsRestant >= 0 && player2.tempsRestant >= 0) {
            for (int i = 1; i < 2; i++) {



                clear_bitmap(buffer1);

                // Dessiner l'image de fond sur mon buffer
                blit(fond, buffer1, 0, 0, 0, 0, fond->w, fond->h);

                while (timer >= dureeApparition) {
                    // Générer un nombre aléatoire entre 1 et 3 pour choisir la position de l'image
                    position = rand() % 3 + 1;

                    // Afficher l'image en fonction de la position aléatoire
                    switch (position) {
                        case 1:
                            show_mouse(screen);
                            masked_blit(resizedTaupe, buffer1, 0, 0, 300, 550, resizedTaupe->w, resizedTaupe->h);
                            blit(buffer1, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                            if (mouse_b == 1) {
                                if (mouseX >= 280 && mouseX <= 320 + dim_taupe_x && mouseY >= 520 &&
                                    mouseY <= 580 + dim_taupe_y) {
                                    playerOn->score++;
                                }
                            }
                            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Joueur 1 : %d", player1.score);
                            textprintf_ex(screen, font, 10, 30, makecol(255, 255, 255), -1, "Joueur 2 : %d", player2.score);
                            //textprintf_ex(screen, font, SCREEN_WIDTH - 100, 10, makecol(255, 255, 255), -1, "Temps : %d",
                            // playerOn->tempsRestant );
                            textprintf_ex(screen, font, 10, 50, makecol(255, 255, 255), -1, "Joueur en jeu (%d) : %d",
                                          i, playerOn->score);
                            textprintf_ex(screen, font, 10, 70, makecol(255, 255, 255), -1, "Tour : %d", i);
                            vsync();

                            break;
                        case 2:
                            show_mouse(screen);
                            masked_blit(resizedTaupe, buffer1, 0, 0, 546, 495, resizedTaupe->w, resizedTaupe->h);
                            blit(buffer1, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                            if (mouse_b == 1) {
                                if (mouseX >= 516 && mouseX <= 566 + dim_taupe_x && mouseY >= 475 &&
                                    mouseY <= 515 + dim_taupe_y) {
                                    playerOn->score++;
                                }
                            }
                            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Joueur 1 : %d", player1.score);
                            textprintf_ex(screen, font, 10, 30, makecol(255, 255, 255), -1, "Joueur 2 : %d", player2.score);
                            textprintf_ex(screen, font, 10, 50, makecol(255, 255, 255), -1, "Joueur en jeu (%d) : %d",
                                          i, playerOn->score);
                            textprintf_ex(screen, font, 10, 70, makecol(255, 255, 255), -1, "Tour : %d", i);
                            vsync();
                            break;
                        case 3:
                            show_mouse(screen);
                            masked_blit(resizedTaupe, buffer1, 0, 0, 450, 350, resizedTaupe->w, resizedTaupe->h);
                            blit(buffer1, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                            if (mouse_b == 1) {
                                if (mouseX >= 430 && mouseX <= 470 + dim_taupe_x && mouseY >= 330 &&
                                    mouseY <= 370 + dim_taupe_y) {
                                    playerOn->score++;
                                }
                            }
                            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "Joueur 1 : %d", player1.score);
                            textprintf_ex(screen, font, 10, 30, makecol(255, 255, 255), -1, "Joueur 2 : %d", player2.score);
                            textprintf_ex(screen, font, 10, 50, makecol(255, 255, 255), -1, "Joueur en jeu (%d) : %d",
                                          i,playerOn->score);
                            textprintf_ex(screen, font, 10, 70, makecol(255, 255, 255), -1, "Tour : %d", i);
                            vsync();

                            break;
                    }
                    textprintf_ex(screen, font, SCREEN_WIDTH - 100, 10, makecol(255, 255, 255), -1, "Temps : %d",
                                  playerOn->tempsRestant);
                    timer = 0;

                }

                acquire_screen();
                release_screen();
                timer++;
                decrementerTemps(playerOn, tstart);
            }
        }


        else {
            if (player1.score > player2.score) {
                allegro_message("VICTOIRE JOUEUR 1");
                rest(5000);
                // allegro_exit();
            } else if (player1.score < player2.score) {
                allegro_message("VICTOIRE JOUEUR 2");
                rest(5000);
                //allegro_exit();
            } else if (player1.score == player2.score) {
                textprintf_ex(screen, font, 400, 300, makecol(255, 255, 255), -1, "Match Nul");
                rest(5000);
                //allegro_exit();
            }


        }


    }

    destroy_bitmap(fond);
    destroy_bitmap(buffer1);
    destroy_bitmap(tronc);
    destroy_bitmap(taupe);
}