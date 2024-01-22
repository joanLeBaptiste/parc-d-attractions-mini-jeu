#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"
#include "headerBallon.h"
#include "time.h"
#include "stdbool.h"

void plateau(){
    fflush(stdin);
    BITMAP* plateau = load_bitmap("image_menu/fond_menu.bmp", NULL);
    //BITMAP* ballon = load_bitmap("image_menu/dart_game_ballon.bmp", NULL);
    BITMAP* dart_game = load_bitmap("image_menu/dart_game.bmp", NULL);
    BITMAP* pilier = load_bitmap("image_menu/pilier.bmp", NULL);
    BITMAP* chateau = load_bitmap("image_menu/chateau_decors.bmp", NULL);
    BITMAP* herbe = load_bitmap("image_menu/herbe.bmp", NULL);
    BITMAP* dart_batiment = load_bitmap("image_menu/dart_batiment.bmp", NULL);
    BITMAP* tableau_score = load_bitmap("image_menu/tableau_score.bmp", NULL);
    BITMAP* pancarte = load_bitmap("image_menu/pancarte.bmp", NULL);
    BITMAP* crossy = load_bitmap("image_menu/crossy.bmp", NULL);
    BITMAP* snakee = load_bitmap("image_menu/snake.bmp", NULL);
    BITMAP* ladder = load_bitmap("image_menu/ladder.bmp", NULL);
    BITMAP* ranch = load_bitmap("image_menu/ranch.bmp", NULL);
    BITMAP* taupee = load_bitmap("image_menu/taupe.bmp", NULL);
    BITMAP* jackpot = load_bitmap("image_menu/jackpot.bmp", NULL);
    BITMAP* taupe_sol = load_bitmap("image_menu/taupe_sol.bmp", NULL);
    BITMAP* pont_sortie = load_bitmap("image_menu/pont_sortie.bmp", NULL);
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    joueur_principale Joueur[2];
    chargementAnimJoueur(Joueur);
    //test
    //printf("%s", Joueur[0].nom);
    //printf("\n%s", Joueur[1].nom);


    //allegro_message("boucle erreur");
    if(!pont_sortie || !taupe_sol || !plateau || !pancarte || !dart_game || !pilier || !chateau || !herbe || !dart_batiment || !tableau_score || !ranch || !ladder || !jackpot || !crossy || !snakee || !taupee){
        allegro_message("erreur chargement fond_menu");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    //allegro_message("chargement fini");

    remove_blanc_fond(herbe, 50);
    remove_blanc_fond(dart_batiment, 50);
    remove_blanc_fond(pancarte, 50);
    remove_blanc_fond(taupee, 50);
    remove_blanc_fond(ladder, 50);
    remove_blanc_fond(crossy, 100);
    remove_blanc_fond(snakee, 100);
    remove_blanc_fond(pont_sortie, 100);
    //remove_blanc_fond(dart_game, 20);
    //remove_blanc_fond(ballon, 20);
    //allegro_message("remove blanc fini");
    int animation = 0; // Indicateur de l'animation du joueur 0

    int mouvement = 0;
    int joueursActuel = 1;
    int joueurPrecedent =0;
    int quitter =0;
    char scoreJ1[50] = "";
    char scoreJ2[50] = "";
    //strcpy(scoreJ1, Joueur[0].nom);
    //strcpy(scoreJ2, Joueur[1].nom);

    while (quitter == 0 ) {
        clear(buffer);
        /// PARTIE GRAPHIQUE AFFICHAGE BATIMENTS
        blit(plateau, buffer, 0, 0, 0, 0, plateau->w, plateau->h);
        draw_sprite(buffer, herbe, 307, 430);
        draw_sprite(buffer, pilier, 325, 400); // 325/400
        draw_sprite(buffer, dart_game, 280, 360);// 280/360
        draw_sprite(buffer, chateau, 10, 100);
        draw_sprite(buffer, dart_batiment, 350, 420);
        draw_sprite(buffer, pancarte, 150, 200);

        draw_sprite(buffer, taupee, 500, 80);
        draw_sprite(buffer, ladder, 540, 110);
        draw_sprite(buffer, taupe_sol, 490, 135);
        draw_sprite(buffer, herbe, 525, 165);

        draw_sprite(buffer, jackpot, 780, 220);
        draw_sprite(buffer, ranch, 370, 80);
        draw_sprite(buffer, herbe, 375, 165);
        draw_sprite(buffer, herbe, 795, 330);

        draw_sprite(buffer, herbe, 425, 440);
        draw_sprite(buffer, crossy, 410, 360);
        draw_sprite(buffer, herbe, 423, 637);
        draw_sprite(buffer, snakee, 405, 560);
        draw_sprite(buffer, pont_sortie, 700, 680);
        /// FIN PARTIE GRAPHIQUE


        // Déplacement du joueur 0
        if (key[KEY_LEFT]) {
            Joueur[joueursActuel].x -= 10;
            mouvement =1;
        } else if (key[KEY_RIGHT]) {
            Joueur[joueursActuel].x += 10;
            mouvement =1;
        }
        if (key[KEY_UP]) {
            Joueur[joueursActuel].y -= 10;
            mouvement =1;
        } else if (key[KEY_DOWN]) {
            Joueur[joueursActuel].y += 10;
            mouvement =1;
        }

        // Afficher l'animation du joueur 0
        if(mouvement == 0) {
            draw_sprite(buffer, Joueur[0].statique, Joueur[0].x, Joueur[0].y);
            draw_sprite(buffer, Joueur[1].statique, Joueur[1].x, Joueur[1].y);
            if(Joueur[joueursActuel].y<180){
                draw_sprite(buffer, chateau, 10, 100);
            }

        }
        // Changer l'animation toutes les frameDelay millisecondes
        else if (mouvement==1 && animation == 0) {
            draw_sprite(buffer, Joueur[joueursActuel].walk_1, Joueur[joueursActuel].x, Joueur[joueursActuel].y);
            draw_sprite(buffer, Joueur[joueurPrecedent].statique, Joueur[joueurPrecedent].x, Joueur[joueurPrecedent].y);
            if(Joueur[joueursActuel].y<180){
                draw_sprite(buffer, chateau, 10, 100);
            }

        }
        else if (mouvement==1 && animation == 1) {
            draw_sprite(buffer, Joueur[joueursActuel].walk_2, Joueur[joueursActuel].x, Joueur[joueursActuel].y);
            draw_sprite(buffer, Joueur[joueurPrecedent].statique, Joueur[joueurPrecedent].x, Joueur[joueurPrecedent].y);
            if(Joueur[joueursActuel].y<180){
                draw_sprite(buffer, chateau, 10, 100);
            }
        }
        /// VERIFICATION DES POSITION POUR LANCER LES JEU
        //rectfill(buffer, 475, 580, 415, 620, makecol(200, 255, 255)); // test hitbox d'entrée des jeu
        if(Joueur[joueursActuel].x <475 && Joueur[joueursActuel].x >415 && Joueur[joueursActuel].y <620 && Joueur[joueursActuel].y >580){
            printf("\n snake");
            allegro_exit(); /// RE_INITIALISATION DE LA FENETRE POUR CE JEU
            snake(Joueur);
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 520;
            Joueur[joueursActuel].y = 610;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <420 && Joueur[joueursActuel].x >380 && Joueur[joueursActuel].y <150 && Joueur[joueursActuel].y >120){
            printf("\nranch");
            allegro_exit();/// RE_INITIALISATION DE LA FENETRE POUR CE JEU
            ParisHippique(Joueur);
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 320;
            Joueur[joueursActuel].y = 150;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <570 && Joueur[joueursActuel].x >530 && Joueur[joueursActuel].y <150 && Joueur[joueursActuel].y >120){
            printf("\n taupe");
            allegro_exit();/// RE_INITIALISATION DE LA FENETRE POUR CE JEU
            taupe();
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 620;
            Joueur[joueursActuel].y = 150;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <840 && Joueur[joueursActuel].x >800 && Joueur[joueursActuel].y <308 && Joueur[joueursActuel].y >280){
            printf("\n jackpot");
            allegro_exit();/// RE_INITIALISATION DE LA FENETRE POUR CE JEU
            Jackpot(Joueur);
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 700;
            Joueur[joueursActuel].y = 280;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <475 && Joueur[joueursActuel].x >428 && Joueur[joueursActuel].y <425 && Joueur[joueursActuel].y >395){
            printf("\n crossy");
            allegro_exit(); /// RE_INITIALISATION DE LA FENETRE POUR CE JEU
            crossyroad(Joueur);
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 530;
            Joueur[joueursActuel].y = 415;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <355 && Joueur[joueursActuel].x >305 && Joueur[joueursActuel].y <430 && Joueur[joueursActuel].y >410){
            printf("arrivé au jeu ballon");
            allegro_exit(); /// pour quitter allegro et redimenssionner la fenetre après
            initialisationAllegro();
            fflush(stdin);
            demarrage(Joueur);
            allegro_exit();
            initialisationAllegro();
            Joueur[joueursActuel].x = 200;
            Joueur[joueursActuel].y = 400;
            joueurPrecedent =joueursActuel;
            joueursActuel = (joueursActuel + 1) % 2;
        }
        if(Joueur[joueursActuel].x <150 && Joueur[joueursActuel].x >20 && Joueur[joueursActuel].y <170 && Joueur[joueursActuel].y >150){
            //rectfill(buffer, 20, 150, 150, 200, makecol(200, 255, 255)); // test hitbox tableau des scores
            fflush(stdin);
            draw_sprite(buffer, tableau_score, 150, 100);

            sprintf(scoreJ1, ": %f", Joueur[0].tempsBallon);  // Utiliser le format %d pour les entiers
            sprintf(scoreJ2, ": %f", Joueur[1].tempsBallon);
            textout_centre_ex(buffer, font,"score sur tir au ballon:", 300, 150, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, Joueur[0].nom, 220, 170, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, Joueur[1].nom, 220, 190, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ1, 300, 170, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ2, 300, 190, makecol(0, 0, 0), -1);

            textout_centre_ex(buffer, font,"score sur crossy:", 300, 210, makecol(0, 0, 0), -1);

            sprintf(scoreJ1, ": %d", Joueur[0].score_crossy);  // Utiliser le format %d pour les entiers
            sprintf(scoreJ2, ": %d", Joueur[1].score_crossy);
            textout_centre_ex(buffer, font, Joueur[0].nom, 220, 230, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, Joueur[1].nom, 220, 250, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ1, 300, 230, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ2, 300, 250, makecol(0, 0, 0), -1);

            textout_centre_ex(buffer, font,"score sur snake:", 300, 270, makecol(0, 0, 0), -1);

            sprintf(scoreJ1, ": %d", Joueur[0].score_snake);  // Utiliser le format %d pour les entiers
            sprintf(scoreJ2, ": %d", Joueur[1].score_snake);
            textout_centre_ex(buffer, font, Joueur[0].nom, 220, 290, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, Joueur[1].nom, 220, 310, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ1, 300, 290, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ2, 300, 310, makecol(0, 0, 0), -1);


            sprintf(scoreJ1, "nb ticket: %d", Joueur[0].ticket);  // Utiliser le format %d pour les entiers
            sprintf(scoreJ2, "nb ticket: %d", Joueur[1].ticket);
            textout_centre_ex(buffer, font, Joueur[0].nom, 450, 230, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, Joueur[1].nom, 450, 250, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ1, 560, 230, makecol(0, 0, 0), -1);
            textout_centre_ex(buffer, font, scoreJ2, 560, 250, makecol(0, 0, 0), -1);
        }
        if(Joueur[joueursActuel].x <750 && Joueur[joueursActuel].x >680 && Joueur[joueursActuel].y >715){
            quitter = 1;
           // allegro_message("vous quittez le jeu");
        }
        /// FIN POSITION JOUEUR ENVOIE DANS LES JEU

        // Affichage du buffer sur l'écran
        acquire_screen();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        release_screen();

        // Pause pour le délai entre les animations
        rest(80);
        // Incrémenter l'indicateur d'animation
        animation = (animation + 1) % 2;
        mouvement = 0;
    }
    printf("\n%f", Joueur[0].tempsBallon);
    printf("\n%f", Joueur[1].tempsBallon);
    destroy_bitmap(plateau);
    //destroy_bitmap(ballon);
    destroy_bitmap(dart_game);
    destroy_bitmap(buffer);
    destroy_bitmap(pilier);
    destroy_Joueur_bitmap(Joueur);
    destroy_bitmap(herbe);
    destroy_bitmap(tableau_score);
    destroy_bitmap(dart_batiment);
    destroy_bitmap(chateau);
    destroy_bitmap(pancarte);
    destroy_bitmap(taupee);
    destroy_bitmap(snakee);
    destroy_bitmap(jackpot);
    destroy_bitmap(ladder);
    destroy_bitmap(ranch);
    destroy_bitmap(taupe_sol);
    destroy_bitmap(crossy);
    destroy_bitmap(pont_sortie);
    printf("\n FIN PLATEAU");

    //allegro_message("fin");
}

void chargementAnimJoueur(joueur_principale joueur[2])
{
    // Charger les bitmaps du joueur
    joueur[0].statique = load_bitmap("image_menu/shrek_statique.bmp", NULL);
    joueur[0].walk_1 = load_bitmap("image_menu/shrek_walk_1.bmp", NULL);
    joueur[0].walk_2 = load_bitmap("image_menu/shrek_walk_2.bmp", NULL);
    joueur[1].statique = load_bitmap("image_menu/ane_statique.bmp", NULL);
    joueur[1].walk_1 = load_bitmap("image_menu/ane_walk_1.bmp", NULL);
    joueur[1].walk_2 = load_bitmap("image_menu/ane_walk_2.bmp", NULL);
    joueur[0].x = 650;
    joueur[0].y =650;
    joueur[1].x = 750;
    joueur[1].y =650;
    joueur[1].ticket = 5;
    joueur[0].ticket =5;
    joueur[0].score_crossy =0;
    joueur[1].score_crossy =0;
    joueur[0].score_snake =0;
    joueur[1].score_snake =0;
    joueur[0].tempsBallon = 1000;
    joueur[1].tempsBallon = 1000;

    nom(joueur, 0);
    rest(200);
    nom(joueur, 1);

    if(!joueur[0].statique || !joueur[0].walk_1 || !joueur[0].walk_2 || !joueur[1].statique || !joueur[1].walk_1 || !joueur[1].walk_2){
        allegro_message("erreur chargement player 1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void destroy_Joueur_bitmap(joueur_principale joueur[2]){
    destroy_bitmap(joueur[0].walk_2);
    destroy_bitmap(joueur[0].walk_1);
    destroy_bitmap(joueur[0].statique);
    destroy_bitmap(joueur[1].statique);
    destroy_bitmap(joueur[1].walk_1);
    destroy_bitmap(joueur[1].walk_2);
}

void nom(joueur_principale joueur[], int joueurIndex) {
    char buffer[100];
    int Index = 0;
    int keyy;

    clear_keybuf();

    while (!key[KEY_ENTER]) {
        if (keypressed()) {
            keyy = readkey() & 0xFF;

            if (keyy == '\b') {
                if (Index > 0) {
                    Index--;
                    buffer[Index] = '\0';
                }
            } else {
                buffer[Index] = keyy;
                Index++;
                buffer[Index] = '\0';
            }
        }

        if (!key[KEY_ENTER]) {
            clear_to_color(screen, makecol(0, 0, 0));

            textout_ex(screen, font, "Rentrer le nom de", SCREEN_W / 2-150, 310, makecol(200, 50, 140), -1);
            textout_ex(screen, font, joueurIndex == 0 ? "Joueur 1: " : "Joueur 2: ", SCREEN_W / 2, 310, makecol(200, 50, 140), -1);
            textout_ex(screen, font, buffer, SCREEN_W / 2+100, 310, makecol(255, 255, 255), -1);
        }

        rest(100);
    }

    strcpy(joueur[joueurIndex].nom, buffer); // Copier le contenu du tampon dans le nom du joueur
    fflush(stdin);
}
