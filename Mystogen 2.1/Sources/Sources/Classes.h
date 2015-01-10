// Classes.h
/*======================================================
================= Classes ======================
======================================================*/

// --- Zl ---
// Création :               31 / 10 / 2011   15H02
#ifndef DEFCLASS
#define DEFCLASS



#include "accessoire.hpp"
//#include "Personnage.h"
#include "gameWindow.hpp"
#include <vector>
#include "Element.hpp"

class Personnage;

class Ennemi
{
private :
    std::string                     m_nom;
    int                             m_vie;
    sf::Sprite                     m_skin;
    sf::Texture                    m_Texture;
    int                     m_porteRegard;
    int                     m_vitesseDepl;
    int                         m_defense;
    int                         m_attaque;
    int                          m_portee;


public :
    Ennemi();
    ~Ennemi();

    //getters:
    int      getDefence();
    int      getAttaque();
    int      getVitesse();
    int getPorteeRegard();
    int         getSkin();
    int          getVie();

    sf::Vector2f getPosImg();

    //setters
    void      setVitesse(int newValue);
    void          setVie(int newValue);
    void      setDefense(int newValue);
    void setPorteeRegard(int newValue);
    void       setPortee(int newValue);
    void      setAttaque(int newValue);

    //Methodes
    void     Chargement(std::string nomEnnemi);
    void      Position(int nombreEnnemi,int i);
    void Affichage (gameWindow &fenetre);
    void          Attaquer (Personnage &Cible);
    void                    PerdreVie(int qtt);

};



class Timer : public sf::Clock
{
private:
    sf::Clock    m_horlogeUn;
    sf::Clock  m_horlogeDeux;
    float           m_DifTot;
    char            m_IsStop;

public:
    Timer();
    ~Timer();

    //getter
    float     getElapsedTime();
    //Methodes

    void      ReStart();
    void      Stop();

};


class nuage
{
private:
    sf::Texture m_Texture;
    sf::Sprite m_Nuage;
    int m_sens;
    float m_tempsEcart;



public:

//getter


//setter
    void setTempsEcart(float newValue);


//methodes
    nuage();
    ~nuage();

    void    ChargeTexture(std::string nomTexture);
    void                      ChangerSprite();
    void       bougerNuage(float tempsActuel);
    void   setPosition(sf::Vector2f newValue);
    void Affichage(gameWindow &fenetre);

};

class Cloud
{
private:
    sf::Vector2f m_position;
    sf::Vector2f m_dimension;
    float        m_vitesse;
    float        m_tempsDebut;
    float        m_posDepX;
    float        m_positionOmbreY;

    sf::Sprite   m_apparence;
    sf::Sprite   m_ombre;

    bool m_sens;



public:


    //constructeur
    Cloud();
    Cloud(sf::Texture &Texture,float Vitesse,sf::Vector2f posDepart,bool sens,Timer &temps);

    //setter
    void setPosition(sf::Vector2f NewValue);
    void setX();
    void setDimension(sf::Vector2f NewValue);
    void setVitesse(float NewValue);
    void setTexture(sf::Texture Texture);

    //getter
    float getVitesse();
    sf::Vector2f getDim();
    sf::Vector2f getPosition();


    //methode

    void mouvement(Timer &temps,int DimCarteX);
    void affichageApparence(gameWindow &fenetre);
    void affichageOmbre(gameWindow &fenetre);
    void changerSens(Timer &temps);


};

#endif
