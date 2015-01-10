#ifndef GAMEDATA
#define GAMEDATA

#include "constantes.hpp"


struct GameData
{
public:

    sf::Image tablid[TAILLETABID];
    sf::Texture tablText[TAILLETABID];
    sf::Font font;
    sf::Event event;
    sf::Sound Sound;
    sf::SoundBuffer sonElem;

    sf::SoundBuffer sonMenu;
    sf::Sound m_SonMenu;

    sf::Clock Temps,Affichage,FPSTime;

    float Framerate;
    std::string nomCarteACharger;
    bool CarteActuel;

    Personnage Joueur;
    PanneauActif Pannel;
    Messagerie Messager;
    int pannelOuvert;
    sf::Vector2f HalfSize;
    sf::View Camera;
    int Inter[NOMBRE_INTERRUPTEUR];
    sf::Text FPS;
    MusiqueAmbiance MusiqueDeFond;
    std::vector <Element> Elm;
    Carte *AdresseCarte;
    gameWindow* Fenetre;
   // gameWindow* Fenetre;
    bool *Adressegrille;
    int X,Y;
    int petitX;
    int petitY;
    int n;
    int action;
    std::string nomCarteActuelle;
    bool  *AdresseColElm;
    bool nouveauMessage;
    Timer general;

    Bouton* Inv;
    Bouton* Sph;

    GameData();
    ~GameData();

};

#endif
