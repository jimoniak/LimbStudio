//accessoire.hpp



//jimoniak
#ifndef DEFACCES
#define DEFACCES

#include "constantes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "gameWindow.hpp"


class Personnage;
class Inventaire;
class GameData;


class Item
{

protected:
    std::string m_cheminAcces;
    std::string m_cheminIcone;
    std::string m_nom;
    std::string m_Icone;
    std::string m_description;
    std::string m_propriete;
    int m_quantiteMax;
    sf::Texture iconeIm;
    sf::Sprite iconeSp;

public:

    Item();
    virtual void utiliser(GameData &g,Inventaire &inv)=0;

    std::string getDescript();

    void afficher(gameWindow &fenetre);
    void chargementObjet();
    void setPosition(sf::Vector2f newValue);

    friend class EmplacementInv;
    friend class  EmplacerEquip;


    virtual ~Item();

};


class Consommable : public Item
{
protected:




public:
    Consommable();
    virtual ~Consommable();

};

class Potion : public Consommable
{

protected:
    int m_Soin;
    int m_Energie;



public:
    void afficher();
    void utiliser(GameData &g,Inventaire &inv);
    void chargementObjet();

    Potion(std::string nom);
    virtual ~Potion();

    friend class EmplacementInv;


};

class Equipable : public Item
{
protected:


public:
    Equipable();
    virtual ~Equipable();




};


class Arme : public Equipable
{
protected:
    int m_Degat;


public:
    Arme();
    Arme(std::string nom);
    virtual ~Arme();

    void chargementObjet();

    void afficher();
    void utiliser(GameData &g,Inventaire &inv);

    //getter
    int getdegat();

    friend class EmplacementInv;
};

class Vetement : public Equipable
{
protected:
    int m_protection;

public:
    void chargementObjet();
    int getProtection();

    Vetement();
    virtual ~Vetement();


};

class Casque : public Vetement
{
public:
    virtual ~Casque();
    Casque();
    Casque(std::string nom);
    void utiliser(GameData &g,Inventaire &inv);
    int getProtection();
};
class Torse : public Vetement
{
public:
    virtual ~Torse();
    Torse();
    Torse(std::string nom);
    void utiliser(GameData &g,Inventaire &inv);
};
class Gant : public Vetement
{
public :
    virtual ~Gant();
    Gant();
    Gant(std::string nom);
    void utiliser(GameData &g,Inventaire &inv);
};
class Jambiere : public Vetement
{
public:
    virtual ~Jambiere();
    Jambiere();
    Jambiere(std::string nom);
    void utiliser(GameData &g,Inventaire &inv);

};
class Chaussure : public Vetement
{
public:
    virtual ~Chaussure();
    Chaussure();
    Chaussure(std::string nom);
    void utiliser(GameData &g,Inventaire &inv);
};







#endif
