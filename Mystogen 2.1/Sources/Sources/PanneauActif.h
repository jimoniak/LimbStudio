#ifndef PANNEAUACTIF
#define PANNEAUACTIF


#include "Bouton.hpp"
#include "graphique.hpp"
#include <SFML/Audio.hpp>
#include "Classes.h"
#include <iostream>
#include <fstream>


class PanneauActif
{
private:

//Stats personnage:
    Barregraphique m_BarreVie;
    Barregraphique m_BarreEnergie;

    sf::Text     m_forcePers; //Stats affichables
    sf::Text     m_endurPers;

    float        tempsEcoule;

    sf::Sprite   m_corps;
    sf::Vector2f m_dimension;
    sf::Vector2f m_Position;

    int m_posY; // Position Relative au bas de la fenetre ( compris entre -size().Y  du pannel (position ouverte)  et 0 (position fermé))
    int m_posY_departAnim; // Sauvegarde de l'etat initial de posY avant le debut de l'animation.
    bool m_enMouvement; // pannel en deplacement...

    sf::Font *m_font;
    sf::Text m_Temps; //temps de jeu
    sf::Texture m_perso; //affichade du personnage à gauche dans le pannel
    sf::Texture m_Pannel;//texture du pannel
    sf::Sprite m_person;
    std::string m_test;

    sf::Text m_lieu;

//------BarreVie-------

    sf::Vector2f m_DimBarreVie;
    sf::Vector2f m_PosBarreVie;
//-----BarreEnergie

    sf::Vector2f m_DimBarreEnergie;
    sf::Vector2f m_PosBarreEnergie;

//----Son------
    sf::SoundBuffer    sonUn;
    sf::SoundBuffer  sonDeux;
    sf::Sound m_sonOuverture;
    sf::Sound m_sonFermeture;

//---Animation

    //float m_tempsTotal;//Variable servant au calcul de la position du pannel en fonction du temps
    float m_tempsAnimation;//Variable servant de diviseur pour le calcul du deplacment du pannel/

    sf::Clock m_horlogeAnimation; //Horloge permettant l'animation du pannel
    float m_tempsDepart;//Instant de l'horloge auquel debute le mouvement du pannel
    float m_TempsActuel;//Variable servant a savoir a quel instant du mouvement l'animation en est



public:

    PanneauActif();
    ~PanneauActif();

    //Methodes
    void calculDuree(Timer &temps);
    void pannelOuvert(gameWindow &fenetre);
    void JouerSon(int Afficher);
    void AnimationPannel(int pannelOuvert);
    void changementEtat(int *pannelOuvert);
    void Chargement(sf::Font *myfont,Personnage &pers);

    int getPosY();

    //setters
    void setVie(Personnage &perso);
    void setEnergie(Personnage &perso);
    void setForce(Personnage   &perso);
    void setEndurance(Personnage   &perso);
    void setParam(Personnage &perso);
    void setDimension(sf::Vector2f newDimension);
    void setPosition(sf::Vector2f newPosition);
    void AnimationPannel();
    void setSprite(Personnage &Joueur);


    void setElapsedTime(float newValue);
    void setNomCarte(std::string newvalue);
    //getters
    float getElapsedTime();


};


class panneauCombat
{
private:

    bool  m_messagerieActive;

    //Stats personnage:
    Barregraphique m_BarreVie;
    Barregraphique m_BarreEnergie;
    Barregraphique m_BarreVieEnm;
    Barregraphique m_BarreEnergieEnm;


    sf::Vector2f m_position;
    sf::Texture    m_Texture;
    sf::Sprite   m_backgroud;//arriere plan


    sf::Sprite   m_facesetJ; //sprite face joueur
    sf::Sprite   m_facesetEnm;

    std::map<std::string, Bouton>::iterator selectionBouton;

    Bouton            Attaque;
    Bouton            Defense;

    sf::String    m_messagerie;


public:

    //methode
    void pannelOuvert(gameWindow &fenetre);
    void AnimationPannel();
    void JouerSon(std::string sonAjouer);


    //setter
    void setPosition(sf::Vector2f newPosition);
    void setFacesetJ(Personnage Joueur);
    void setVie(Personnage perso);
    void setEnergie(Personnage perso);







};

#endif
