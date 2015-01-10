#ifndef DEFCARTECLASS
#define DEFCARTECLASS


#include <string>
#include "gameWindow.hpp"
#include "Classes.h"

#include <vector>
class Cloud;
class generateur;

class Carte
{
private:
    std::string              m_nom;
    int                      m_tailleX;
    int                      m_tailleY;
    int                      m_totalcoord;
    int                      m_totalcaractere;
    std::vector<sf::Texture>  m_textPlace1;
    std::vector<sf::Texture>  m_textPlace2;
    std::vector<sf::Texture>  m_textPlace3;
    std::vector<sf::Texture>  m_textPlace4;
    std::vector<sf::Texture>  m_textPlace5;
    std::vector<sf::Sprite>  m_place1;
    std::vector<sf::Sprite>  m_place2;
    std::vector<sf::Sprite>  m_place3;
    std::vector<sf::Sprite>  m_place4;
    std::vector<sf::Sprite>  m_place5;
    std::vector<std::string> m_typecouche1;
    std::vector<std::string> m_typecouche2;
    std::vector<std::string> m_typecouche3;
    std::vector<std::string> m_typecouche4;
    std::vector<std::string> m_typecouche5;

    sf::Image   imageDeCouche[5];
    sf::Sprite  m_CoucheAffichable[5];
    sf::Texture m_TextureCouche[5];



    sf::Texture m_cloud1,m_cloud2,m_cloud3;
    sf::Vector2f m_posDep;
    std::vector<Cloud> m_Cloud;

    bool m_nuage;
    int m_nombregenerateur;
    std::vector<generateur> m_generateurPart;



public:
    Carte();
    Carte(std::string nomCarte,int Tx,int Ty,Timer &temps);


    void TransformerCoucheTexture(sf::Image tab[]);
    void chargementCouche (bool grille[],sf::Image image[],sf::Texture texture[]);                          // Methode qui charge toutes les couches
    void afficherCouche (gameWindow &fenetre , int couche, sf::Vector2f CCamera);
    void initialisePlaces();                                        // Methode qui fixe les positions des Sprites
    void convertisseurStrSprtCouche (sf::Texture tab[]);              // Transformateur string -> Sprite
    std::string getNom();

    void testnuage();

    void CalculCloud(int tailleY,Timer &temps);
    void bougerCloud(Timer &temps);
    void chargegenerateur();
    void majgene(Timer &temps);


    ~Carte();
};

#endif
