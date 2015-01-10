#ifndef ELEMENT
#define ELEMENT

#include <SFML/Audio.hpp>
#include "gameWindow.hpp"
#include <vector>


#define MAX_INSTRUCTION 200
class Personnage;
class Timer;




class Element
{
private :

    std::string     m_nom;          // On peut lui donner un nom
    std::string     m_carte;
    std::string     m_instructions[MAX_INSTRUCTION];
    sf::Sprite      m_apparence;    // On peut lui donner une apparence
    sf::Image      m_image;
    sf::Texture       m_texture;
    sf::Image       m_imageMes;// On peut avoir une Texture pour les messages
    sf::Sprite      m_Faceset;// Sprite de m_Textureset.
    std::vector<struct Data>    D;
    int             m_interrupteur; // On doit lui donner son interrupteur d'activation
    int             m_numero;
    int             m_X;
    int             m_Y;            // On doit lui donner une position sur la carte
    bool            m_collision;
    bool            m_action;
    bool            m_instruct;

    void Instruction(int I,GameData &g);        // I est la valeur du type d 'interaction vraie
    void MultiFonction (std::string*,GameData &g);

public :

    Element();
    Element(std::string nomCarte);

    void Chargement(int numeroElement , std::string nomCarte);
    void Interaction(GameData &g);
    void Affichage(gameWindow &fenetre, int Inter[], Timer &general);
    void StaticSubRectSelector(std::vector<Data> &D,std::string nom);

    int getX();
    int getY();
    int getcollision();



    ~Element();

};

#endif
