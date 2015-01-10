//jeu.cpp
//---Jimoniak---------------ZL-----------------------


#include "constantes.hpp"

#include "gameWindow.hpp"

#include "gestionAudio.h"
#include "Classes.h"


#include "Carte.hpp"

#include "Prototypes.hpp"
#include "Bouton.hpp"

#include "graphique.hpp"
#include "Inventaire.hpp"

#include "Spherier.hpp"
#include "Personnage.h"

#include "PanneauActif.h"
#include "Messagerie.hpp"

#include "GameData.hpp"

#include "Element.hpp"
#include "settingsMenu.hpp"

#include <SFML/System/Clock.hpp>

using namespace std;
using namespace sf;



int Jeu(gameWindow &FenetrePrincipale ,GameData &g, settingsMenu &sMenu)
{
    sf::Event event;
    Clock ResetAction;
    Clock FPS;

    Bouton BoutonInventaire = Bouton(sf::Vector2f(200,50),false);
    BoutonInventaire.setTexture("Ressources/Interface/Jeu/MenuJeu.png",125);
    BoutonInventaire.setFont(g.font);
    BoutonInventaire.setColorText(Color(0,0,0,255));
    BoutonInventaire.setString("  Inventaire");
    BoutonInventaire.setSizeText(25);
    g.Inv = &BoutonInventaire;

    Bouton BoutonSpherier = Bouton(sf::Vector2f(200,50),false);
    BoutonSpherier.setTexture("Ressources/Interface/Jeu/MenuSphere.png",125);

    BoutonSpherier.setFont(g.font);
    BoutonSpherier.setColorText(Color(0,0,0,255));
    BoutonSpherier.setString("Spherier");
    BoutonSpherier.setSizeText(25);
    // g.Sph = &BoutonSpherier;




    g.Joueur.Chargement(g.nomCarteACharger,g);
    g.Pannel.Chargement(&g.font, g.Joueur);

    sf::Thread AnimationPerso(&AnimationPersonnageThread,&g);
    AnimationPerso.launch();
    //sf::Thread Affichagegeneral(&AffichageThread,&g);


    g.Messager.InitialiserFont(g);
    g.nouveauMessage = false;



    g.HalfSize.x = LFENETRE / 2;
    g.HalfSize.y = HFENETRE / 2;
    g.Inter[0] = 1;                     // Interrupteur num�ro 0 toujours vrai
    LireInterrupteur(g.Inter);          // Charge le fichier interrupteur dans le tableau

    g.pannelOuvert = 0;
    g.Pannel.setSprite(g.Joueur);
    g.Pannel.setVie( g.Joueur);

    g.FPS.setPosition(30,30);
    g.FPS.setString("FPS");
    g.FPS.setFont(g.font);
    g.FPS.setCharacterSize(20);
    g.FPS.setColor(Color(255, 255, 255, 255));




    while (FenetrePrincipale.isOpen())  // Cette boucle recommence quand on change de map (nomCarteACharger change si la fonction t�l�port est appel�e )
    {

        /*== Chargement De La Carte en Cours ==*/
        LireTailleCarte(g.nomCarteACharger,&g.X,&g.Y);
        bool grille[g.X*g.Y];  // grille des collisions de la map ( 1 = collision vraie )
        bool colElm[g.X*g.Y];

        g.Adressegrille = grille;
        g.AdresseColElm = colElm; // Tableau utilisé par les element (type pnj etc..., pour testé les collisions )
        Carte Monde(g.nomCarteACharger,g.X,g.Y,g.general);
        Monde.chargementCouche(&grille[0],g.tablid,g.tablText);
        Monde.initialisePlaces();
        Monde.convertisseurStrSprtCouche(g.tablText);
        Monde.TransformerCoucheTexture(g.tablid);
        g.AdresseCarte = &Monde;

        float curseurX(0.f);
        float curseurY(0.f);


        /*== Cam�ra ==*/

        g.petitX = 1;
        if (LTILE * g.X > LFENETRE) g.petitX = 0;
        g.petitY = 1;
        if (HTILE * g.Y > HFENETRE) g.petitY = 0;
        g.Camera = View(g.Joueur.getPosImg(),sf::Vector2f(LFENETRE,HFENETRE));
        Cameraman(g);
        FenetrePrincipale.setView(g.Camera);



        /*== Chargement Des Elements De La Map ==*/
        LoadElement(g);
        for (int i = 0 ; i < g.n ; i++)
        {
            if(g.Elm[i].getcollision())
                colElm[g.Elm[i].getY() * g.X + g.Elm[i].getX()] = true;
        }

        /*== Changement De La Musique ==*/
        g.MusiqueDeFond.changerMusique(&g.nomCarteACharger);
        g.MusiqueDeFond.chargerMusique();

        /*== Remise des valeurs de d�part de ces variables ==*/

        g.Joueur.resetTempsDeb();
        string nomCarteActuelle = g.nomCarteACharger;
        g.Pannel.setNomCarte(Monde.getNom());




        g.CarteActuel = nomCarteActuelle != g.nomCarteACharger ?  false  : true;


        //Affichagegeneral.Launch();

        while (nomCarteActuelle == g.nomCarteACharger && FenetrePrincipale.isOpen())    // Recommence tant qu'on ne change pas de carte et que la fenetre est ouverte
        {



            //------------------------------------------------------------------------------------------------------------------------------------------

            g.Pannel.setParam( g.Joueur);
            g.Pannel.calculDuree(g.general);
            g.Pannel.AnimationPannel(g.pannelOuvert);

            Monde.bougerCloud(g.general);
            Monde.majgene(g.general);

            //--------------------------------------------FPS--------------------------------------------------------------

            g.Framerate = (int)(1 / (FPS.restart().asMilliseconds()*0.001)); // calcul FPS

            if ( g.FPSTime.getElapsedTime().asSeconds() > 0.5) //Petite condition qui permet de stabiliser l'affichage des fps à l"ecran.
            {
                g.FPS.setString("FPS:"+ ConvertionFltString(g.Framerate));
                g.FPSTime.Clock::restart();
            }


            //--------------------------------------------------------------------------------------------------------------------------------------


            curseurX = g.Camera.getCenter().x - LFENETRE /2 + sf::Mouse::getPosition(FenetrePrincipale).x;
            curseurY = g.Camera.getCenter().y - HFENETRE /2 + sf::Mouse::getPosition(FenetrePrincipale).y;


            /*== gestion Des Animations De D�placement Du Joueur ==*/


            g.Joueur.Animer(g.general);

            /*== Affichage g�n�ral ==*/


            if (Cameraman(g))  FenetrePrincipale.setView(g.Camera);

            g.Messager.setPosition(Vector2f(g.Camera.getCenter().x - LFENETRE/2,g.Camera.getCenter().y -HFENETRE / 2)); //Position Messagerie
            g.Pannel.setPosition(Vector2f(g.Camera.getCenter().x - LFENETRE/2,g.Camera.getCenter().y + HFENETRE / 2));//Position Pannel
            g.FPS.setPosition(g.Camera.getCenter().x - LFENETRE / 2 + 50,g.Camera.getCenter().y - HFENETRE / 2 + 50);// Position FPS
            BoutonInventaire.setPos((Vector2f(g.Camera.getCenter().x + LFENETRE/2  - 100, g.Camera.getCenter().y + HFENETRE / 2 - 25)));
            BoutonSpherier.setPos((Vector2f(g.Camera.getCenter().x - LFENETRE/2 + 100, g.Camera.getCenter().y + HFENETRE / 2 -25 )));
            g.Joueur.setPositionInv(g);



            FenetrePrincipale.clear();


            Monde.afficherCouche(FenetrePrincipale , 1 , g.Joueur.getPosImg());
            Monde.afficherCouche(FenetrePrincipale , 2 , g.Joueur.getPosImg()); // bas de la carte
            Monde.afficherCouche(FenetrePrincipale , 3 , g.Joueur.getPosImg());

            g.Joueur.AfficherBas(FenetrePrincipale);
            for (int i = 0 ; i < g.n ; i++)   g.Elm[i].Affichage(FenetrePrincipale, &g.Inter[0] , g.general);  // personnage et element
            g.Joueur.AfficherHaut(FenetrePrincipale);

            Monde.afficherCouche(FenetrePrincipale , 4 , g.Joueur.getPosImg());
            Monde.afficherCouche(FenetrePrincipale , 5 , g.Joueur.getPosImg()); // haut de la carte


            BoutonInventaire.Affichage(FenetrePrincipale);
            // BoutonSpherier.Affichage(FenetrePrincipale);  // interface gUI



            if(g.Pannel.getPosY() < HFENETRE)
            {
                g.Pannel.pannelOuvert(FenetrePrincipale);
            }
            if(g.Joueur.getEtatInv())
            {
                g.Joueur.OuvrirInv(FenetrePrincipale,g,Monde);
            }
            if(g.Joueur.getEtatSphr())
            {
                g.Joueur.OuvrirSphr(FenetrePrincipale,g.MusiqueDeFond.getMusique());
            }
            g.Affichage.Clock::restart();

            FenetrePrincipale.draw(g.FPS);


            FenetrePrincipale.display();






            if(ResetAction.getElapsedTime().asSeconds() > 0.5)// reset action.
            {
                g.action = 0;
                ResetAction.Clock::restart();
            }


            if( g.Temps.getElapsedTime().asSeconds()> 0.01)
            {
                g.Temps.Clock::restart();



                /*== gestion Des Commandes De L'Utilisateur ==*/

                while (FenetrePrincipale.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        g.m_SonMenu.play();
                        FenetrePrincipale.close();
                    }
                    if (event.type == sf::Event::KeyReleased)
                    {
                        if (event.key.code == sf::Keyboard::T)
                        {
                            g.Pannel.changementEtat(&g.pannelOuvert);
                        }
                        if (event.key.code == sf::Keyboard::P)      {}
                        if (event.key.code == sf::Keyboard::M)
                        {
                            LoadElement(g);
                        }
                        if (event.key.code == sf::Keyboard::O)
                        {
                            g.general.Stop();
                            sMenu.start();
                            g.general.ReStart();
                        }
                        if (event.key.code == sf::Keyboard::R)
                        {
                            g.Joueur.ChangerEtatInv();
                            g.m_SonMenu.play();
                        }
                        if (event.key.code == sf::Keyboard::E)  g.action = 1;
                        if (event.key.code == sf::Keyboard::A)
                        {
                            g.Joueur.ChangerEtatSphr();
                            g.m_SonMenu.play();
                        }


                    }



                }


            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                g.Messager.OuvrirMessageSansInteraction("Quitter?\n O: Oui , N: Non",g);
                while(g.nouveauMessage)
                {


                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    {
                        FenetrePrincipale.close();
                        g.nouveauMessage = false;

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                    {

                        g.nouveauMessage = false;
                        g.general.ReStart();
                    }





                }


            }


            if(BoutonInventaire.ClicInventaire(g.event,curseurX,curseurY))
            {
                g.m_SonMenu.play();
                g.Joueur.ChangerEtatInv();
            }


            if(BoutonSpherier.ClicInventaire(g.event,curseurX,curseurY))
            {
                g.m_SonMenu.play();
                g.Joueur.ChangerEtatSphr();
            }


            if(!g.Joueur.getEtatInv()) //Securite au cas ou l'on essai d'ouvrir l'inventaire lorsque le personnage se deplace.
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))    g.Joueur.deplacer(8 ,&grille[0],g.X,g.Y,&g.Elm[0],g.n,g.general);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    g.Joueur.deplacer(4 ,&grille[0],g.X,g.Y,&g.Elm[0],g.n,g.general);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))   g.Joueur.deplacer(2 ,&grille[0],g.X,g.Y,&g.Elm[0],g.n,g.general);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    g.Joueur.deplacer(6,&grille[0],g.X,g.Y,&g.Elm[0],g.n,g.general);
                }
            }


            /*== Tests d'Interactions des Elements ==*/
            for (int i = 0 ; i < g.n ; i++)   g.Elm[i].Interaction(g);
        }
    }
    return 0;
}






void AnimationPersonnageThread(void* gdata)
{

    GameData*  g = static_cast<GameData*>(gdata);
    while(g->Fenetre->isOpen())
    {
        while(g->Joueur.getMouvement())
        {

            g->Joueur.Animer(g->general);
            sf::sleep(sf::milliseconds(10));


        }

        sf::sleep(sf::milliseconds(5));

    }
}


void AffichageThread(void* Gdata)
{


    GameData* g = static_cast<GameData*>(Gdata);

    while(g->Fenetre->isOpen())
    {


        if(g->Joueur.getEtatInv() != true && g->Joueur.getEtatSphr() != true)
        {



            g->Fenetre->clear();


            g->AdresseCarte->afficherCouche(*g->Fenetre , 1 , g->Joueur.getPosImg());
            g->AdresseCarte->afficherCouche(*g->Fenetre , 2 , g->Joueur.getPosImg()); // bas de la carte
            g->AdresseCarte->afficherCouche(*g->Fenetre , 3 , g->Joueur.getPosImg());

            g->Joueur.AfficherBas(*g->Fenetre);
            for (int i = 0 ; i < g->n ; i++)   g->Elm[i].Affichage(*g->Fenetre, &g->Inter[0] , g->general);  // personnage et element
            g->Joueur.AfficherHaut(*g->Fenetre);

            g->AdresseCarte->afficherCouche(*g->Fenetre , 4 , g->Joueur.getPosImg());
            g->AdresseCarte->afficherCouche(*g->Fenetre , 5 , g->Joueur.getPosImg()); // haut de la carte


            g->Inv->Affichage(*g->Fenetre);
            g->Sph->Affichage(*g->Fenetre);  // interface gUI


            g->Fenetre->draw(g->FPS);


            g->Fenetre->display();

        }

        sf::sleep(sf::milliseconds(50));
    }
}
