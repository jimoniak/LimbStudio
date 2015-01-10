//---------------------------Mystogen------------------------------------------------

//main.cpp..............................................................................
//Jimmy peault & Zl.....................................................................

#define GLOBAL
#include <string>
#include "Sources/constantes.hpp"


#include "Sources/gestionAudio.h"
#include "Sources/Classes.h"


#include "Sources/Carte.hpp"

#include "Sources/Prototypes.hpp"
#include "Sources/Bouton.hpp"

#include "Sources/graphique.hpp"
#include "Sources/Inventaire.hpp"

#include "Sources/Spherier.hpp"
#include "Sources/Personnage.h"

#include "Sources/PanneauActif.h"
#include "Sources/Messagerie.hpp"



#include "Sources/settingsMenu.hpp"
#include "Sources/GameData.hpp"

#include <cmath>






using namespace std;
using namespace sf;


int main()
{
    std::cout << "Mystogen " << VERSION << std::endl;
    //int HFENETRE = 700;int LFENETRE = 1024;


#ifdef WINDOW
    HFENETRE= sf::VideoMode::getDesktopMode ().height ;
    LFENETRE= sf::VideoMode::getDesktopMode ().width ;
   // gameWindow FenetrePrincipale(sf::VideoMode(LFENETRE,HFENETRE), "Mystogen",sf::Style::Fullscreen);

    gameWindow FenetrePrincipale(sf::VideoMode(LFENETRE,HFENETRE), "Mystogen",sf::Style::Fullscreen);
#endif
#ifdef LINUX
    HFENETRE= sf::VideoMode::getDesktopMode ().Height;
    LFENETRE= sf::VideoMode::getDesktopMode ().Width;
    //HFENETRE= 600;
    //LFENETRE= 800;
    //gameWindow FenetrePrincipale(sf::VideoMode(LFENETRE,HFENETRE), "Mystogen",sf::Style::Fullscreen);
    gameWindow FenetrePrincipale(sf::VideoMode(LFENETRE,HFENETRE), "Mystogen",sf::Style::Fullscreen);


#endif


    srand(time((0)));
    Timer HorlogeEffet;
    std::vector<sf::VideoMode> modeVideo;

    modeVideo= sf::VideoMode::getFullscreenModes();
    if(HFENETRE < 600 || LFENETRE < 800)
    {
        cout << "Resolution d'ecran trop petite , la stabilite du jeu est incertaine... " << endl
             << "Souhaitez-vous malgres tout continuer ? ( 0 = oui )" << endl;
        int a = 1;
        cin >> a;
        if(a) return EXIT_FAILURE;
    }

    //gameWindow FenetrePrincipale(sf::VideoMode(LFENETRE, HFENETRE), "Mystogen");
   // gameWindow FenetrePrincipale(modeVideo[0], "Mystogen",sf::Style::Fullscreen);
    FenetrePrincipale.setFramerateLimit(60);
    FenetrePrincipale.setVerticalSyncEnabled(true);
    FenetrePrincipale.setPosition(sf::Vector2i(0,0));

    FenetrePrincipale.UtiliserCurseurJeu(1);
    FenetrePrincipale.setMouseCursorVisible(false);

    //Variable necessaire au fondu avant Menu.
    sf::Image  fondu;
    fondu.create (LFENETRE, LFENETRE);
    sf::Sprite FonduNoir;
    FonduNoir.setColor(Color(0,0,0,255));
    sf::Texture texFondu;
    texFondu.loadFromImage(fondu);
    FonduNoir.setTexture(texFondu);
    //-----------------------------------------

    GameData g;

    g.Fenetre = &FenetrePrincipale;
    g.font.loadFromFile("Ressources/Font/SF Comic Script Condensed.ttf");

    if(!g.sonMenu.loadFromFile("Ressources/Sounds/ClicMenu.ogg"))     cout<< "ouverture Son ClicMenu impossible"<<endl;
    g.m_SonMenu .setBuffer(g.sonMenu);

    g.MusiqueDeFond.chargerMusique("A The Lonely Amazon.ogg");
    g.MusiqueDeFond.setVolume(50.0);



    //----------------------------------------------------------
    Texture logo;
    Sprite log;
    logo.loadFromFile("Ressources/LogoMysto.png");
    log.setTexture(logo);
    log.setPosition(LFENETRE/2 -251,50);
    //---------------------------------------------------------
    Bouton BtJeu (LFENETRE/2,HFENETRE/2,200,50);
    BtJeu.setTxt("Jeu",g.font,sf::Color::Red,30);
    BtJeu.setTexture("Ressources/Interface/Jeu/Bouton.png",125);
    BtJeu.setDimFromTexture();
    //BtJeu.setMask(sf::Color::Red);

    Bouton BtOption (LFENETRE/2,HFENETRE/2 + 100,200,50);
    BtOption.setTxt("Options",g.font,sf::Color::Blue,24);
    BtOption.setTexture("Ressources/Interface/Jeu/Bouton.png",125);
    BtOption.setDimFromTexture();

    Bouton BtQuitter (LFENETRE/2,HFENETRE/2 + 200,200,50);
    BtQuitter.setTxt("Quitter",g.font,sf::Color::Green,24);
    BtQuitter.setTexture("Ressources/Interface/Jeu/Bouton.png",125);
    BtQuitter.setDimFromTexture();

    bool horlogeActive(false);
    /*
        sf::Image I(512,2,sf::Color::Black);
        for(int i = 256; i < 512 ; i++)
        {   I.setPixel(i,0,sf::Color(0,i,128,i));
            I.setPixel(i,1,sf::Color(i,i,128,i));
        }
        I.CreateMaskFromColor(sf::Color::Black);

        sf::Sprite S;
        S.setTexture(I);
        S.setCenter(S.getSize().x/2,S.getSize().y/2 + 256);
        S.setPosition(LFENETRE/2,HFENETRE/2);*/

    settingsMenu setMenu(&FenetrePrincipale, &g);


    double delta = 0;
    int updates = 0;





    int curseurX,curseurY;
    curseurX = curseurY = 0;

    Presentation(FenetrePrincipale, g);  //presentation du studio

    Clock HorlogeFondu;  //Horloge utilisé pour la réalisation du fondu.

    sf::RectangleShape sky;
    sky.setSize(sf::Vector2f(LFENETRE,HFENETRE));
    sky.setPosition(0,0);
    sky.setFillColor(sf::Color(160,160,255));


    FenetrePrincipale.setMouseCursorVisible(true);
    sf::Event event;
    while( FenetrePrincipale.isOpen())
    {

        while (FenetrePrincipale.pollEvent(event))
        {

            switch(event.type )
            {
            case  sf::Event::Closed :
                FenetrePrincipale.close();
                break;
            default :
                break;
            }
            curseurX = sf::Mouse::getPosition(FenetrePrincipale).x;
            curseurY = sf::Mouse::getPosition(FenetrePrincipale).y;

            sf::Vector2i CurseurPosition = sf::Mouse::getPosition(FenetrePrincipale);


            if      (BtJeu.Clic(CurseurPosition))
            {
                g.m_SonMenu.play();
                HorlogeEffet.Stop();
                g.general.ReStart();
                Jeu(FenetrePrincipale,g, setMenu);
                g.general.Stop();
            }
            if      (BtOption.Clic(CurseurPosition))
            {
                g.m_SonMenu.play();
                g.general.Stop();
                setMenu.start();
                g.general.ReStart();
            }
            if      (BtQuitter.Clic(CurseurPosition))
            {
                g.m_SonMenu.play();
                while(g.m_SonMenu.getStatus() == Sound::Playing) {} FenetrePrincipale.close();
            }
            //if      (BtJeu.EstDessus( g.Event.MouseMove.X ,g.Event.MouseMove.Y)){cout<<"dessus!" <<endl;}
        }




        if(BtJeu.EstDessus(curseurX,curseurY))
        {

            horlogeActive=true;//on dit que l'horloge est utilisé.

        }

        if(BtOption.EstDessus(curseurX,curseurY))
{


            horlogeActive=true;

        }

        if(BtQuitter.EstDessus(curseurX,curseurY))
        {
            horlogeActive=true;
        }

        FenetrePrincipale.clear();
        float t=0;
        t = HorlogeEffet.getElapsedTime();



        FenetrePrincipale.draw(sky);

        BtJeu.Affichage(FenetrePrincipale);
        BtOption.Affichage(FenetrePrincipale);
        BtQuitter.Affichage(FenetrePrincipale);
        FenetrePrincipale.draw(log);
        FenetrePrincipale.display();
    }

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------



