
#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"
#include "headerBallon.h"
#include "time.h"

void ParisHippique(joueur_principale tab[2]){
    // prix de l'attraction
    tab[0].ticket=tab[0].ticket-1;
    tab[1].ticket=tab[1].ticket-1;
    printf("passer");
    srand(time(NULL));

    int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
    int dx1,dy,dx2,dx3,dx4,dx5;
    int tx,ty;
    // nuemro du cheval gagnant {1,2,3,4,5}
    int gagnant=0;


    int cptdx=0, tmpdx=1;

    int imgcourante=0;
    int cptimg=0, tmpimg=4;

    // sequence d'animation
    BITMAP *img1[12];
    BITMAP *img2[12];
    BITMAP *img3[12];
    BITMAP *img4[12];
    BITMAP *img5[12];
    BITMAP *decompte[5];
    BITMAP *chiffre[5];
    BITMAP *defaite;
    BITMAP *Victoire1;
    BITMAP *Victoire2;
    BITMAP *Victoire12;




    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // La tempo g�n�rale (fonction rest) sera r�glable
    int tempoglobale=10;

    // Pour charger la s�quence
    int i=0;
    char nomfichier1[256];
    char nomfichier2[256];
    char nomfichier3[256];
    char nomfichier4[256];
    char nomfichier5[256];


    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,470,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // charger image de fond
    decor=load_bitmap("ranch_jackpot/BITMAP1/fondVrai.bmp",NULL);
    Victoire1= load_bitmap("ranch_jackpot/BITMAP1/VV1.bmp", NULL);
    Victoire2= load_bitmap("ranch_jackpot/BITMAP1/VV2.bmp", NULL);
    Victoire12= load_bitmap("ranch_jackpot/BITMAP1/V12.bmp", NULL);
    defaite= load_bitmap("ranch_jackpot/BITMAP1/D.bmp",NULL);
    if (!defaite)
    {
        allegro_message("MerdeOuEstMonDecorBordelAQueu.bmp");
        exit(EXIT_FAILURE);
    }
    // chargement des chiffres gagnant et des cheveaux
    // chargement du compte à rebour
    // charger premier cheval
    for (i=0;i<12;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/DADA%d.bmp",i+1);

        img1[i] = load_bitmap(nomfichier1,NULL);
        if (!img1[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    // charger deuxième cheval
    for (i=0;i<12;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/DADA%d.bmp",i+1);

        img2[i] = load_bitmap(nomfichier1,NULL);
        if (!img2[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    // charger troisième cheval
    for (i=0;i<12;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/DADA%d.bmp",i+1);

        img3[i] = load_bitmap(nomfichier1,NULL);
        if (!img3[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    // charger quatrième cheval
    for (i=0;i<12;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/DADA%d.bmp",i+1);

        img4[i] = load_bitmap(nomfichier1,NULL);
        if (!img4[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    // charger quatrième cheval
    for (i=0;i<12;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/DADA%d.bmp",i+1);

        img5[i] = load_bitmap(nomfichier1,NULL);
        if (!img5[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<5;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier3,"ranch_jackpot/BITMAP1/chiffre%d.bmp",i+1);

        chiffre[i] = load_bitmap(nomfichier3,NULL);
        if (!img1[i]){
            printf("Ca marche pas");
            allegro_message("pas pu trouver %s",nomfichier3);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<5;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier2,"ranch_jackpot/BITMAP1/%d.bmp",i+1);

        decompte[i] = load_bitmap(nomfichier2,NULL);
        if (!img1[i]){
            allegro_message("pas pu trouver %s",nomfichier2);
            exit(EXIT_FAILURE);
        }
    }


    // initialisation des donn�es du chat

    tx = img1[0]->w; // pour la taille on se base sur la 1�re image de la s�quence
    ty = img1[0]->h;

    x1=0;
    x2=0;
    x3=0;
    x4=0;
    x5=0;

    y1=290;
    y2=260;
    y3=240;
    y4=210;
    y5=190;

    // initialisation aléatoire des vitesses des cheveaux
    dx1 =rand()%10;
    dx2 =rand()%10;
    dx3 =rand()%10;
    dx4 =rand()%10;
    dx5 =rand()%10;
    //system()
    cptdx=0;
    tmpdx=1;

    imgcourante=0;
    cptimg=0;
    tmpimg=5;
    int paris1,paris2;
    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
    draw_sprite(page,img5[imgcourante],x1,y1);
    draw_sprite(page,img5[imgcourante],x2,y2);
    draw_sprite(page,img5[imgcourante],x3,y3);
    draw_sprite(page,img5[imgcourante],x4,y4);
    draw_sprite(page,img5[imgcourante],x5,y5);
    //draw_sprite(page, chiffre[1], 100,200);
    textprintf_ex(page,font,16,20,makecol(255,255,255),0,"Joeur 1 sélectionner le cheval sur lequel vous miser",tempoglobale);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    while(!key[KEY_1] ||!key[KEY_2] ||!key[KEY_3] ||!key[KEY_4]||!key[KEY_5]){
        if(key[KEY_1]){
            paris1=1;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[0], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_2]){
            paris1=2;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[1], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_3]){
            paris1=3;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[2], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);

            break;
        }
        if(key[KEY_4]){
            paris1=4;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[3], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_5]){
            paris1=5;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[4], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
    }
    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
    draw_sprite(page,img5[imgcourante],x1,y1);
    draw_sprite(page,img5[imgcourante],x2,y2);
    draw_sprite(page,img5[imgcourante],x3,y3);
    draw_sprite(page,img5[imgcourante],x4,y4);
    draw_sprite(page,img5[imgcourante],x5,y5);
    textprintf_ex(page,font,16,20,makecol(255,255,255),0,"Joeur 2 sélectionner le cheval sur lequel vous miser",tempoglobale);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    while(!key[KEY_1] ||!key[KEY_2] ||!key[KEY_3] ||!key[KEY_4]||!key[KEY_5]){
        if(key[KEY_1]){
            paris2=1;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[0], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_2]){
            paris2=2;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[1], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_3]){
            paris2=3;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[2], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_4]){
            paris2=4;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[3], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
        if(key[KEY_5]){
            paris2=5;
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, chiffre[4], 400,100);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(700);
            break;
        }
    }

    for (int j = 0; j < 5; ++j) {
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, decompte[j],100,100);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(1000);
    }







    while (!key[KEY_ESC]){

        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        if ( (x1<0 && dx1<0))
            dx1 = -dx1;
        if ( (x2<0 && dx2<0))
            dx2 = -dx2;
        if ( (x3<0 && dx3<0))
            dx3 = -dx3;
        if ( (x4<0 && dx4<0))
            dx4 = -dx4;
        if ( (x5<0 && dx5<0))
            dx5 = -dx5;


        if ((x1+tx>SCREEN_W && dx1>0) )
            gagnant=1;
        if ((x2+tx>SCREEN_W && dx2>0) )
            gagnant=2;
        if ((x3+tx>SCREEN_W && dx3>0) )
            gagnant=3;
        if ((x4+tx>SCREEN_W && dx4>0) )
            gagnant=4;
        if ((x5+tx>SCREEN_W && dx5>0) )
            gagnant=5;
        if(gagnant!=0){
            break;
        }

        cptdx++;
        if (cptdx>=tmpdx){
            cptdx=0;
            x1+=dx1;
            x2+=dx2;
            x3+=dx3;
            x4+=dx4;
            x5+=dx5;
        }

        cptimg++;
        if (cptimg>=tmpimg){
            cptimg=0;

            imgcourante++;

            if (imgcourante>=12)
                imgcourante=0;
        }

        if (dx1>=0){
            draw_sprite(page,img1[imgcourante],x1,y1);
        }
        else{
            draw_sprite(page,img1[imgcourante],x1,y1);

        }
        if(dx2>=0){
            draw_sprite(page,img2[imgcourante],x2,y2);
        }
        else{
            draw_sprite(page,img2[imgcourante],x2,y2);
        }
        if(dx3>=0){
            draw_sprite(page,img3[imgcourante],x3,y3);
        }
        else{
            draw_sprite(page,img3[imgcourante],x3,y3);
        }
        if(dx4>=0){
            draw_sprite(page,img4[imgcourante],x4,y4);
        }
        else{
            draw_sprite(page,img4[imgcourante],x4,y4);
        }
        if(dx5>=0){
            draw_sprite(page,img5[imgcourante],x5,y5);
        }
        else{
            draw_sprite(page,img5[imgcourante],x5,y5);
        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        rest(tempoglobale);
    }
    if(paris1==gagnant && paris2!=gagnant){
        tab[0].ticket=tab[0].ticket+2;
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, Victoire1, 200, 0);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(1000);

    }
    else if(paris2==gagnant && paris1!=gagnant){
        tab[1].ticket=tab[1].ticket+2;
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, Victoire2, 200, 0);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(1000);
    }
    else if(paris1==paris2==gagnant){
        tab[0].ticket=tab[0].ticket+2;
        tab[1].ticket=tab[1].ticket+2;
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, Victoire12, 200, 0);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(1000);
    }
    else{
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        draw_sprite(page, defaite, 200, 0);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(1000);
    }
}
void Jackpot (joueur_principale tab[2]){
    BITMAP *Poigne[5];
    BITMAP *Tourne[8];
    BITMAP *Fin[6];
    int Un1,Deux2,Trois3;
    srand(time(NULL));
    char nomfichier1[256];
    char nomfichier2[256];
    char nomfichier3[256];

    BITMAP *page;

    // Image de fond
    BITMAP *decor;
    BITMAP *victoire;
    BITMAP *defaite;

    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,800,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // charger image de fond
    decor=load_bitmap("ranch_jackpot/BITMAP1/jackpot.bmp",NULL);
    victoire= load_bitmap("ranch_jackpot/BITMAP1/bravo.bmp",NULL);
    defaite= load_bitmap("ranch_jackpot/BITMAP1/perdre.bmp",NULL);
    if (!victoire)
    {
        allegro_message("ouinnn ouinnn trouve pas mon décore");
        exit(EXIT_FAILURE);
    }
// on charge la séquence de la poignée
    for (int i=0;i<5;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier1,"ranch_jackpot/BITMAP1/P%d.bmp",i+1);

        Poigne[i] = load_bitmap(nomfichier1,NULL);
        if (!Poigne[i]){
            allegro_message("pas pu trouver %s",nomfichier1);
            exit(EXIT_FAILURE);
        }
    }
    // on charge la séquence de la roue
    for (int i=0;i<8;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier2,"ranch_jackpot/BITMAP1/I%d.bmp",i+1);

        Tourne[i] = load_bitmap(nomfichier2,NULL);
        if (!Tourne[i]){
            allegro_message("pas pu trouver %s",nomfichier2);
            exit(EXIT_FAILURE);
        }
    }
    // on charge les images de la victoire
    for (int i=0;i<6;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier3,"ranch_jackpot/BITMAP1/V%d.bmp",i+1);

        Fin[i] = load_bitmap(nomfichier3,NULL);
        if (!Fin[i]){
            allegro_message("pas pu trouver %s",nomfichier3);
            exit(EXIT_FAILURE);
        }
    }
    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
    draw_sprite(page,Poigne[0], 725, 135);
    draw_sprite(page,Fin[0], 110, 430);
    draw_sprite(page, Fin[0],330,430);
    draw_sprite(page, Fin[0],530,430);
    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    allegro_message("Joueur 1 appuyé sur 1 pour jouer, Joueur 2 appuyé sur 2 pour jouer, appuyé sur 3 pour sortir. Si vous avez trois sept vous gagnez 3 tickets si vous avez trois autres symboles identiques vous perdez 1 tickets");

    while (!key[KEY_ESC]){
// joueur 1
        if(key[KEY_1]){
            Un1=rand()%(7 - 1) + 1;
            Deux2=rand()%(7 - 1) + 1;
            Trois3=rand()%(7 - 1) + 1;

            printf("%d%d%d",Un1, Deux2,Trois3);
            // descente de la poigné
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[1], 710,140);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[2],710, 250);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[3],710, 310);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[4],710,370);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            // montee de la poignee
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[3],710, 310);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[1], 710,140);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 8; ++j) {
                    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(page,Poigne[0], 725, 135);
                    draw_sprite(page,Tourne[j], 110, 430);
                    draw_sprite(page, Tourne[j],330,430);
                    draw_sprite(page, Tourne[j],530,430);
                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                    rest(5+5*i);
                }

            }

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[Un1-1], 110, 430);
            draw_sprite(page, Fin[Deux2-1],330,430);
            draw_sprite(page, Fin[Trois3-1],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(500);
            if(Un1==Deux2 && Deux2==Trois3 && Trois3==2){
                printf("je rentre");
                tab[0].ticket=tab[0].ticket+3;
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page,Poigne[0], 725, 135);
                draw_sprite(page,Fin[Un1-1], 110, 430);
                draw_sprite(page, Fin[Deux2-1],330,430);
                draw_sprite(page, Fin[Trois3-1],530,430);
                draw_sprite(page, victoire,200,200);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            else if (Un1==Deux2 && Deux2==Trois3 && Trois3!=2){
                tab[0].ticket=tab[0].ticket-1;
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page,Poigne[0], 725, 135);
                draw_sprite(page,Fin[Un1-1], 110, 430);
                draw_sprite(page, Fin[Deux2-1],330,430);
                draw_sprite(page, Fin[Trois3-1],530,430);
                draw_sprite(page, defaite,200,200);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }


        }
        // joeur 2
        if(key[KEY_2]){
            Un1=rand()%(7 - 1) + 1;
            Deux2=rand()%(7 - 1) + 1;
            Trois3=rand()%(7 - 1) + 1;
            printf("%d%d%d",Un1, Deux2,Trois3);
            // descente de la poigné
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[1], 710,140);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[2],710, 250);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[3],710, 310);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[4],710,370);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            // montee de la poignee
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[3],710, 310);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page, Poigne[1], 710,140);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[0], 110, 430);
            draw_sprite(page, Fin[0],330,430);
            draw_sprite(page, Fin[0],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(10);
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 8; ++j) {
                    rest(5+10*i);
                    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                    draw_sprite(page,Poigne[0], 725, 135);
                    draw_sprite(page,Tourne[j], 110, 430);
                    draw_sprite(page, Tourne[j],330,430);
                    draw_sprite(page, Tourne[j],530,430);
                    blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                }

            }

            blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(page,Poigne[0], 725, 135);
            draw_sprite(page,Fin[Un1-1], 110, 430);
            draw_sprite(page, Fin[Deux2-1],330,430);
            draw_sprite(page, Fin[Trois3-1],530,430);
            blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(500);
            if(Un1==Deux2 && Deux2==Trois3 && Trois3==2){
                tab[1].ticket=tab[1].ticket+3;
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page,Poigne[0], 725, 135);
                draw_sprite(page,Fin[Un1-1], 110, 430);
                draw_sprite(page, Fin[Deux2-1],330,430);
                draw_sprite(page, Fin[Trois3-1],530,430);
                draw_sprite(page, victoire,200,200);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            else if (Un1==Deux2 && Deux2==Trois3 && Trois3!=2){
                tab[1].ticket=tab[1].ticket-1;
                blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(page,Poigne[0], 725, 135);
                draw_sprite(page,Fin[Un1-1], 110, 430);
                draw_sprite(page, Fin[Deux2-1],330,430);
                draw_sprite(page, Fin[Trois3-1],530,430);
                draw_sprite(page, defaite,200,200);
                blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }


        }
        if(key[KEY_3]){
            break;
        }

    }
}