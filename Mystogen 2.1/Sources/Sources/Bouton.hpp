#ifndef BOUTON
#define BOUTON
/* Class Bouton
 * Sers à créer une zone capable de détecter les clics
 * Peut prendre une forme rectangulaire ou Elliptique
 * Peut prendre une Texture de fond (centrée)
 * Peut prendre un texte par dessus
 * Peut créer son propre masque
 * Peut récupérer les Event pour saisir du texte sans console
 */

#include "gameWindow.hpp"

class Bouton
{
protected :

    sf::Vector2f     m_pos;       // Le centre du bouton (requis)
    sf::Vector2f     m_dim;       // La largeur et hauteur de sa hitbox (requis)
    sf::Text       m_txt;       // Le texte affiché en son centre (optionnel)





    bool             m_ellipse;   // 1 Si le bouton est de forme élliptique
    float            m_rayon;



public :
    sf::RectangleShape       m_dessous;
    sf::RectangleShape       m_surbrillance;
    sf::Texture     m_masqueText;
    sf::Sprite       m_masqueSprite;    // Sprite du masque
    Bouton();
    Bouton(sf::Vector2f dim,bool ell = false) ;
    Bouton(sf::Vector2f pos,sf::Vector2f dim = sf::Vector2f(160,60),bool ell = 0);
    Bouton(float x = 0, float y = 0, float l = 160, float h = 60,bool ell = 0);

    void setPosition(sf::Vector2f newValue);
    void setDimFromTexture();
    void setMaskTransparence(int newTransparence);
    void setSprite(sf::Texture& img);
    void setTxt(std::string txt , sf::Font& font , sf::Color couleur = sf::Color::White, int size = 16);
    void setString(std::string newText);
    void setStringPos(sf::Vector2f pos);
    void setFont(sf::Font &font);
    void setSizeText(int size);
    void setColorText(sf::Color Couleur);
    void setTransparence(int newTransparence);
    void setMask(sf::Color clr = sf::Color::Green ,bool degrade = 1);
    void setTexture(std::string chemin,int alpha = 255);
    void Affichage(gameWindow &App, float angle = 0 , float zoom = 0);
    bool Affichage2(gameWindow &App,float xs , float ys);
    bool Clic(sf::Vector2i positionSouris);
    bool ClicInventaire(sf::Event &Ev,float x,float y);
    bool EstDessus(float x , float y);
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);

    void setEllipse(bool ell = 1);
    std::string EventTxt(gameWindow &App , sf::Font& police ,sf::Color couleur = sf::Color::White, int size = 16);

    ~Bouton();

};


#endif
