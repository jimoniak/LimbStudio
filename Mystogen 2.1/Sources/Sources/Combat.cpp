/*#include "constantes.hpp"
#include "Carte.hpp"
#include "Classes.h"
#include "Personnage.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;

int Combat (gameWindow &fenetre,Personnage &Joueur,std::string infos[])
{
    fenetre.Clear();
        fenetre.setView(fenetre.getDefaultView()); // Reset de la caméra

    Event Event;
    Clock Temps;

    // Chargement de la zone de combat

    sf::Texture Battleback;
    Battleback.loadFromFile(infos[0]);
    sf::Sprite Bb;
    Bb.setTexture(Battleback);


    // Création des Ennemis

    int const nombreEnnemi = ConvertionStringInt(infos[1]);
	Ennemi* Enm = new Ennemi[nombreEnnemi];
    for (int i = 0; i < nombreEnnemi ; i++)
    {   Enm[i].Chargement(infos[i+2]);
        Enm[i].Position(nombreEnnemi,i);
    }


    // Musique
    sf::Music musique;
    if(!musique.OpenFromFile("Ressources/Musics/Battle.ogg"))   cout << "Erreur d 'ouverture de la musique" << endl;
    musique.play();


    // Bruitage ( temporaire )
    sf::SoundBuffer sonAttaque;
    if (!sonAttaque.loadFromFile("Ressources/Sounds/mediumpunch.wav")) cout << "Erreur d'ouverture du son"  << endl;

    sf::Sound Sound;
    Sound.setBuffer(sonAttaque);


    // Ciblage graphique
    Texture Fleche;
    Fleche.loadFromFile("Ressources/Icons/Fleche.png");
    Fleche.setSmooth(0);
    Fleche.CreateMaskFromColor(sf::Color(0, 0, 0));

    Sprite Ciblage;
    Ciblage.setTexture(Fleche);


    // Variables
    int cible = 0;
    bool TourDuJoueur = 1;
    bool Victoire = 0;
    Vector2f posCible;





    // Boucle du Combat
    while (!Victoire && Joueur.getVie() > 0)
    {   if (Temps.getElapsedTime() > 0.02)
        {   Temps.Clock::Reset();
            if (TourDuJoueur)
            {
                while (fenetre.getEvent(Event))
                {
                    if (Event.Type == sf::Event::Closed)
                    {   fenetre.Close();
                        exit(EXIT_SUCCESS);
                    }

                    if (Event.Type == sf::Event::KeyPressed)
                    {
                        if(Event.Key.Code == 'a')       // Attaque simple sur la cible
                        {
                            Joueur.Attaquer(Enm[cible]);
                            cout << "Il lui reste " << Enm[cible].getVie() << " points de vie" << endl ;
                            Sound.play();
                            TourDuJoueur = 0;
                        }

                        else if(Event.Key.Code == 'd')  // Décale la cible à gauche
                        {
                            if (cible < nombreEnnemi - 1) cible++;
                            else cible = 0;
                            while((Enm[cible].getVie() < 0))
                            {
                                if (cible == nombreEnnemi - 1) cible = 0;
                                else cible++;
                            }
                        }

                        else if(Event.Key.Code == 'q')  // Décale la cible à droite
                        {
                            if (cible > 0) cible--;
                            else cible = nombreEnnemi - 1;
                            while((Enm[cible].getVie() < 0))
                            {
                                if (cible == 0) cible = nombreEnnemi - 1;
                                else cible--;
                            }
                        }
                    }
                }
                // Test de Victoire
                Victoire = 1;
                for (int i = 0; i < nombreEnnemi ; i++)
                {
                    if (Enm[i].getVie() > 0)   Victoire = 0;
                }

                // Décalage de la cible si achevée ce tour-ci
                while((Enm[cible].getVie() < 0) && !Victoire)
                {
                    if (cible == nombreEnnemi - 1) cible = 0;
                    else cible++;
                }
                posCible = Enm[cible].getPosImg();
                Ciblage.setPosition(posCible);

            }

            else    // Tour Adverse
            {
                for (int i = 0; i < nombreEnnemi ; i++)
                {   if (Enm[i].getVie() > 0)
                        Enm[i].Attaquer(Joueur);
                }
                TourDuJoueur = 1;
                cout << " Le Joueur a encore " << Joueur.getVie() << endl;
            }



            fenetre.Clear();
            fenetre.draw(Bb);
            for (int i = 0; i < nombreEnnemi ; i++)
            {   if (Enm[i].getVie() > 0)
                    Enm[i].Affichage(fenetre);
            }
            fenetre.draw(Ciblage);
            Joueur.AffichageCombat(fenetre);
            fenetre.Display();



        }
    }

	delete[] Enm;
    return 0;
}

*/
