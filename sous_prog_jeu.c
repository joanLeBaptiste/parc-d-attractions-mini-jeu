#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"
#include "headerBallon.h"
#include "time.h"

void demarrage(joueur_principale Joueur[2]){
    // Déclaration de variables
    BITMAP *ballon_start;
    BITMAP *ballon_start_2;
    BITMAP *ballonpopv2_2;
    BITMAP *press_start;
    BITMAP *main_dart;
    BITMAP *buffer;

// Initialisation Allegro mise dans un sous-programme

// Chargement des images
    ballon_start = load_bitmap("image_tir_ballon/ballon_start_1v2.bmp", NULL);
    ballon_start_2 = load_bitmap("image_tir_ballon/ballon_start_2.bmp", NULL);
    ballonpopv2_2 = load_bitmap("image_tir_ballon/balloonpopv2-2.bmp", NULL);
    press_start = load_bitmap("image_tir_ballon/press_start.bmp", NULL);
    main_dart = load_bitmap("image_tir_ballon/hand_holding_dart.bmp", NULL);

    if (!ballon_start || !ballon_start_2 || !ballonpopv2_2 || !press_start || !main_dart) {
        allegro_message("Erreur lors du chargement des images !");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    // initialisation des position des elements
    int ballon_x = 50; // Position horizontale du ballon
    int ballon_y = (SCREEN_H - ballon_start->h) / 2; // Position verticale initiale du ballon_start
    int ballon_dy = 1; // Vitesse du mouvement du ballon_start

    int ballon_2_x = 850; // Position horizontale du ballon_start_2
    int ballon_2_y = (SCREEN_H - ballon_start_2->h) / 2; // Position verticale initiale du ballon_start_2
    int ballon_2_dy = 1; // Vitesse du mouvement du ballon_start_2

    int press_start_x = 280;
    int press_start_y = SCREEN_H*0.3;
    int press_start_presence = 0; // savoir si il est deja affiché ou pas
    int temps =0;

    int main_dart_y = 580;
    int main_dart_x = 450;

    remove_blanc_fond(ballon_start, 15);
    remove_blanc_fond(ballon_start_2, 15);
    remove_blanc_fond(press_start, 15);
    remove_blanc_fond(main_dart, 15);

// Création du buffer double buffering
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    rest(3000);
    //allegro_message("arrive au jeu");
// Boucle d'événements
    while (!(keypressed() && (readkey() != 's'))) {
        // Dessin sur le buffer
        clear(buffer);
        blit(ballonpopv2_2, buffer, 0, 0, 0, 0, ballonpopv2_2->w, ballonpopv2_2->h);
        draw_sprite(buffer, ballon_start, ballon_x, ballon_y);
        draw_sprite(buffer, ballon_start_2, ballon_2_x, ballon_2_y);
        draw_sprite(buffer, main_dart, main_dart_x, main_dart_y);
        if (press_start_presence == 1) {
            draw_sprite(buffer, press_start, press_start_x, press_start_y);
        }
        // Affichage du buffer sur l'écran
        acquire_screen();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        release_screen();

        // Mouvement du ballon_start
        ballon_y += ballon_dy;
        if (ballon_y <= (SCREEN_H - ballon_start->h) / 2 - 15 || ballon_y >= (SCREEN_H - ballon_start->h) / 2 + 15) {
            ballon_dy *= -1;
        }

        // Mouvement du ballon_start_2
        ballon_2_y += ballon_2_dy;
        if (ballon_2_y <= (SCREEN_H - ballon_start_2->h) / 2 - 15 || ballon_2_y >= (SCREEN_H - ballon_start_2->h) / 2 + 15) {
            ballon_2_dy *= -1;
        }
        temps += 16; // Ajoute le temps écoulé depuis la dernière frame
        if (temps >= 300) {
            // Code pour alterner l'affichage de la bitmap press_start
            if (press_start_presence == 1) {
                press_start_presence = 0;
            } else {
                press_start_presence = 1;
            }

            temps = 0; // Réinitialise le temps écoulé
        }

        rest(16); // Attendre environ 1/60ème de seconde
    }

// Libération de la mémoire des bitmaps
    destroy_bitmap(ballon_start);
    destroy_bitmap(ballon_start_2);
    destroy_bitmap(ballonpopv2_2);
    destroy_bitmap(buffer);
    destroy_bitmap(press_start);
    destroy_bitmap(main_dart);
    rest(200);
    jeu_principal(Joueur); /// appele du jeu principale
}

void chargementBallon(Ballon ballons[]) {
    BITMAP* animation_1 = load_bitmap("image_tir_ballon/ballon_stade_1.bmp", NULL);
    BITMAP* animation_2 = load_bitmap("image_tir_ballon/ballon_stade_2.bmp", NULL);
    BITMAP* animation_3 = load_bitmap("image_tir_ballon/ballon_stade_3.bmp", NULL);
    BITMAP* animation_4 = load_bitmap("image_tir_ballon/ballon_stade_4.bmp", NULL);
    BITMAP* animation_5 = load_bitmap("image_tir_ballon/ballon_stade_5.bmp", NULL);
    if (!animation_1 || !animation_2 || !animation_3 || !animation_4 || !animation_5 ) {
        allegro_message("Erreur lors du chargement des images !");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    remove_blanc_fond(animation_1,15);
    remove_blanc_fond(animation_2, 15);
    remove_blanc_fond(animation_3, 15);
    remove_blanc_fond(animation_4, 15);
    remove_blanc_fond(animation_5, 15);

    // pour la barre de chargement
    int temps = 0;
    float progress;
    int avancementBarre;



    for (int i = 0; i < 12; i++) {
        ballons[i].animations_pop[0] = create_bitmap(animation_1->w, animation_1->h);
        ballons[i].animations_pop[1] = create_bitmap(animation_2->w, animation_2->h);
        ballons[i].animations_pop[2] = create_bitmap(animation_3->w, animation_3->h);
        ballons[i].animations_pop[3] = create_bitmap(animation_4->w, animation_4->h);
        ballons[i].animations_pop[4] = create_bitmap(animation_5->w, animation_5->h);
        ballons[i].touche = 0;

        if (!ballons[i].animations_pop[0] || !ballons[i].animations_pop[1] || !ballons[i].animations_pop[2] || !ballons[i].animations_pop[3] || !ballons[i].animations_pop[4]) {
            allegro_message("Erreur lors de la création des bitmaps dans la structure Ballon !");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        // Copie des animations dans chaque bitmap
        blit(animation_1, ballons[i].animations_pop[0], 0, 0, 0, 0, animation_1->w, animation_1->h);
        blit(animation_2, ballons[i].animations_pop[1], 0, 0, 0, 0, animation_2->w, animation_2->h);
        blit(animation_3, ballons[i].animations_pop[2], 0, 0, 0, 0, animation_3->w, animation_3->h);
        blit(animation_4, ballons[i].animations_pop[3], 0, 0, 0, 0, animation_4->w, animation_4->h);
        blit(animation_5, ballons[i].animations_pop[4], 0, 0, 0, 0, animation_5->w, animation_5->h);
    }
    ///charger les positions des ballons:
    for(int i=0; i<6; i++){
        ballons[i].x = 168+i*128;
        ballons[i].x_image = 150+i*128;
        ballons[i].y =255;
        ballons[i].y_image = 230;
    }
    int j=0;
    for(int i=6; i<12; i++){
        ballons[i].x = 168+j*128;
        ballons[i].x_image = 150+j*128;
        ballons[i].y = 360;
        ballons[i].y_image = 335;
        j++;
    }
    j=0;
    /* test
    for(int i=0; i<12; i++){
        printf("\nx:%d, y:%d", ballons[i].x, ballons[i].y);
    }*/
    //animationBallon(ballons, 5);
    //ANIMATION CHARGEMENT
    clear_to_color(screen, makecol(0, 0, 0)); // Efface l'écran
    while(temps<2000){

        progress = (float)temps / 2000; // Calcul de la progression (entre 0 et 1)
        avancementBarre = (int)(300 * progress); // Calcul de la largeur de la barre en fonction de la progression
        rectfill(screen, 350, 345, 350 + avancementBarre, 375, makecol(255, 200, 100)); // Dessine la barre de chargement
        textout_centre_ex(screen, font, "CHARGEMENT", SCREEN_W / 2, 320, makecol(200, 255, 255), -1);
        rest(20);

        temps += 20;
    }
    //allegro_message("fin anim");
    rest(200);

    //allegro_message("debut destroy");
    //destroy_bitmap_ballon(ballons);
    destroy_bitmap(animation_1);
    destroy_bitmap(animation_2);
    destroy_bitmap(animation_3);
    destroy_bitmap(animation_4);
    destroy_bitmap(animation_5);
    //allegro_message("fin destroy");

}

void destroy_bitmap_ballon(Ballon ballons[]){ /// ne marche absolument pas
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++) {
            destroy_bitmap(ballons[i].animations_pop[j]);
        }
    }
    rest(100);
}


void jeu_principal(joueur_principale Joueurs[2]){
    Ballon ballons[12]; // Tableau de 12 ballons
    Joueur t_joueur[2];
    for(int i=0; i<2; i++){
        t_joueur[i].temps =0;
    }
    strcpy(t_joueur[0].nom, Joueurs[0].nom);
    strcpy(t_joueur[1].nom, Joueurs[1].nom);
    chargementBallon(ballons);
    int mouseX =0;
    int mouseY=0;
    int dx=0;
    int dy=0;
    int ballonnTouche=0;
    double temps=0.0;
    char charTemps[20];
    //allegro_message("debut jeu");
    BITMAP* fond_jeu = load_bitmap("image_tir_ballon/fond_jeu.bmp", NULL);
    //BITMAP *fond_jeu2 = load_bitmap("fond_jeu.bmp", NULL);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    //BITMAP* buffer2 = create_bitmap(SCREEN_W, SCREEN_H);
    clock_t debut = clock(); // Heure de début de la boucle
    clear_to_color(screen, makecol(0, 0, 0));
    rectfill(screen, 350, 300, 650, 400, makecol(255, 255, 255));
    textout_centre_ex(screen, font, "TOUR JOUEUR 1", 450, 350, makecol(240, 22, 145), -1);
    rest(2000);
    while (ballonnTouche<12) {
        clear(buffer);
        // Dessiner le fond
        draw_sprite(buffer, fond_jeu, 0, 0);
        // Dessiner les ballons
        //rectfill(buffer, 150, 360, 160, 360+ 35, makecol(200, 255, 255)); // test hitbox des ballon
       // rectfill(buffer, ballons[6].x, ballons[6].y,ballons[6].x+15, ballons[6].y+50, makecol(200, 255, 255)); // test hitbox des ballon
        //rectfill(buffer, ballons[1].x, ballons[1].y,ballons[1].x+20, ballons[1].y+80, makecol(200, 255, 255));
        //rectfill(buffer, ballons[7].x, ballons[7].y,ballons[7].x+20, ballons[7].y+80, makecol(200, 255, 255));
        dx = rand() % 13 - 6;
        dy = rand() % 13 - 6;
         mouseX = mouse_x+dx;
         mouseY = mouse_y+dy;
        position_mouse(mouseX, mouseY);
        circlefill(buffer, mouseX, mouseY, 3, makecol(255, 0, 0));
        if(mouse_b & 1 || mouse_b & 2) {

            for (int i = 0; i < 12; i++) {

                if (mouseX >= ballons[i].x - 30 && mouseX <= ballons[i].x + 30 &&
                    mouseY >= ballons[i].y - 35 && mouseY <= ballons[i].y + 35 && ballons[i].touche==0) {
                    // La souris touche le ballon, appeler la fonction d'animation
                    ballons[i].touche = 1;
                    animationBallon(ballons, i, fond_jeu);
                    ballonnTouche++;
                    //printf("%d", ballonnTouche);
                }
            }
            for(int i=0; i<12; i++){ // changement de position à chaque clic, que sur x
                ballons[i].x_image += rand() % (130 - 10 + 1) + 10;
                if(ballons[i].x_image <=150){ /// eviter de sortir du cadre
                    ballons[i].x_image = 150;
                }
                if(ballons[i].x_image >=850){
                    ballons[i].x_image = 850;
                }
                for(int j=0; j<12; j++){ /// pour essayer d'eviter que les ballons se superposent
                    if(ballons[i].x_image > ballons[j].x_image-30 &&ballons[i].x_image < ballons[j].x_image+30 ){
                        ballons[i].x_image -=35;
                    }
                }
                ballons[i].x = ballons[i].x_image+18; /// pour avoir une bonne hitbox
                //rest(1);
            }
        }
        drawBallons(buffer, ballons, ballonnTouche);
        rectfill(buffer, 0, SCREEN_H - 30, SCREEN_W, SCREEN_H, makecol(255, 255, 255));
        temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
        sprintf(charTemps, "temps: %.2f", (double)temps);
        textout_centre_ex(buffer, font, charTemps, SCREEN_W / 2, SCREEN_H - 25, makecol(0, 0, 0), -1);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(50);
    }
    t_joueur[0].temps = temps;
    if(temps <Joueurs[0].tempsBallon){ /// modification du meilleur score du joueur pour l'attraction
        Joueurs[0].tempsBallon = temps;
    }
    printf("\n%.2f", temps);
    //allegro_message("tout les ballon sont pete, fin du 1er tour");
    int ballonnTouche2 =0;
    rectfill(buffer, 350, 300, 650, 400, makecol(255, 255, 255));
    textout_centre_ex(buffer, font, "TOUR JOUEUR 2", 450, 350, makecol(240, 22, 145), -1);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(2000);
    Ballon ballons2[12]; /// 2eme tableau de struct de ballon pour eviter les bug avec le 1er
    chargementBallon(ballons2);
        temps=0.0;
        debut = clock();
    allegro_message("2eme tour");
    //exit(EXIT_FAILURE);
    while (ballonnTouche2<12) {
        clear(buffer);
        // Dessiner le fond
        draw_sprite(buffer, fond_jeu, 0, 0);
        // Dessiner les ballons
        //rectfill(buffer, 168+128, 360, 168+128 + 32, 360+ 35, makecol(200, 255, 255)); // test hitbox des ballon
        dx = rand() % 13-6;
        dy = rand() %13-6;
        mouseX = mouse_x+dx;
        mouseY = mouse_y+dy;
        position_mouse(mouseX, mouseY);
        circlefill(buffer, mouseX, mouseY, 3, makecol(255, 0, 0));
        if(mouse_b & 1) {
            for (int i = 0; i < 12; i++) {

                if (mouseX >= ballons2[i].x - 30 && mouseX <= ballons2[i].x + 30 &&
                    mouseY >= ballons2[i].y - 35 && mouseY <= ballons2[i].y + 35 && ballons2[i].touche==0) {
                    // La souris touche le ballon, appeler la fonction d'animation
                    ballons2[i].touche = 1;
                    animationBallon(ballons2, i, fond_jeu);
                    ballonnTouche2++;
                    //printf("%d", ballonnTouche);
                }
            }
            for(int i=0; i<12; i++){ // changement de position à chaque clic, que sur x
                ballons2[i].x_image += rand() % (110 - 10 + 1) + 10;
                if(ballons2[i].x_image <=140){ /// eviter de sortir du cadre
                    ballons2[i].x_image = 140;
                }
                if(ballons2[i].x_image >=850){
                    ballons2[i].x_image = 850;
                }
                for(int j=0; j<12; j++){ /// pour essayer d'eviter que les ballons se superposent
                    if(ballons2[i].x_image > ballons2[j].x_image-30 &&ballons2[i].x_image < ballons2[j].x_image+30 ){
                        ballons2[i].x_image -=35;
                    }
                }
                ballons2[i].x = ballons2[i].x_image+18; /// pour avoir une bonne hitbox
                //rest(1);
            }
        }
        drawBallons(buffer, ballons2, ballonnTouche2);
        rectfill(buffer, 0, SCREEN_H - 30, SCREEN_W, SCREEN_H, makecol(255, 255, 255));
        temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
        sprintf(charTemps, "temps: %.2f", (double)temps);
        textout_centre_ex(buffer, font, charTemps, SCREEN_W / 2, SCREEN_H - 25, makecol(0, 0, 0), -1);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(3);
    }
    t_joueur[1].temps = temps;
    if(temps <Joueurs[1].tempsBallon){ /// modification du meilleur score du joueur pour l'attraction
        Joueurs[1].tempsBallon = temps;
    }
    printf("\n%.2f", temps);
    allegro_message("fin du jeu");
    char gagnant[30];
    if(t_joueur[1].temps<t_joueur[0].temps){
        sprintf(gagnant, "gagnant: %s", t_joueur[1].nom);
        Joueurs[1].ticket ++;
        Joueurs[0].ticket --;
    }
    else{
        sprintf(gagnant, "gagnant: %s", t_joueur[0].nom);
        Joueurs[0].ticket ++;
        Joueurs[1].ticket --;
    }

    clear_to_color(screen, makecol(0, 0, 0)); // Efface l'écran
    rectfill(buffer, 350, 300, 650, 400, makecol(255, 255, 255));
    textout_centre_ex(buffer, font, gagnant, 450, 350, makecol(240, 22, 145), -1);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(4000);

    destroy_bitmap(fond_jeu);
    destroy_bitmap(buffer);
}

/// FONCTION UTILITAIRE ( initialisation, enlever le fond d'une image...)
void initialisationAllegro() {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000 , 720, 0, 0)) != 0) { /// 1000 et 720
        allegro_message("Erreur lors du passage en mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

}

void remove_blanc_fond(BITMAP* bitmap, int tolerance) {
    int x, y;
    int white_color = makecol(255, 255, 255);
    int pixel_color;
    int un;
    int deux;
    int trois;
    for (y = 0; y < bitmap->h; y++) {
        for (x = 0; x < bitmap->w; x++) {
             pixel_color = getpixel(bitmap, x, y);
             un = getr(pixel_color);
             deux = getg(pixel_color);
             trois = getb(pixel_color);

            if (abs(un - 255) <= tolerance && abs(deux - 255) <= tolerance && abs(trois - 255) <= tolerance) {
                putpixel(bitmap, x, y, makecol(255, 0, 255)); // Fond transparent en magenta
            }
        }
    }
}

void animationBallon(Ballon ballons[], int numero, BITMAP* fond_jeu) {
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* animations[5];

    for (int i = 0; i < 5; i++) {
        animations[i] = ballons[numero].animations_pop[i];
    }

    for (int i = 0; i < 5; i++) {
        clear(buffer);
        masked_blit(fond_jeu, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_blit(animations[i], buffer, 0, 0, ballons[numero].x_image, ballons[numero].y_image, animations[i]->w, animations[i]->h);
        drawBallons(buffer, ballons, 0 );
        acquire_screen();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        release_screen();

        rest(65); // Attendre 20 ms entre chaque animation
    }
    rest(10);

    // Destruction des bitmaps du tableau animations
    //allegro_message("fin animations, destroy ");
    for (int i = 0; i < 5; i++) {
        destroy_bitmap(animations[i]);
    }

    destroy_bitmap(buffer);
}

void drawBallons(BITMAP* buffer, Ballon ballons[], int ballonTouche) {
    int x = 150;
    int y1 = 230;
    int y2 = 335;
    int separation = 65;
    //ballons[7].touche = 1; // test
    if(ballonTouche<12) {
        // Afficher les ballons de la première ligne
        for (int i = 0; i < 6; i++) {
            BITMAP *ballon = ballons[i].animations_pop[0];
            if (ballon != NULL && ballons[i].touche != 1) {
                draw_sprite(buffer, ballon, ballons[i].x_image, ballons[i].y_image);
            }
            //x += separation + ballon->w; // Ajouter la largeur de l'animation et la séparation
        }

        // Réinitialiser les valeurs de x et y pour la deuxième ligne
        x = 150;
        // Afficher les ballons de la deuxième ligne
        for (int i = 6; i < 12; i++) {
            BITMAP *ballon2 = ballons[i].animations_pop[0];
            if (ballon2 != NULL && ballons[i].touche != 1) {
                draw_sprite(buffer, ballon2, ballons[i].x_image, ballons[i].y_image);
            }
            //x += separation + ballon2->w; // Ajouter la largeur de l'animation et la séparation
        }
    }
}