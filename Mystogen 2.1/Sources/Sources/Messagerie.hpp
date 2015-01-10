#ifndef DEFMESSAgERIE
#define DEFMESSAgERIE



#include "gameWindow.hpp"

class GameData;

class Messagerie
{


private:
    bool m_sansFace;

    sf::Text m_texte;

    sf::Texture m_fondIM;
    sf::Sprite m_fondSP;

    sf::Texture m_interlocuteurIM;
    sf::Sprite m_interlocuteurSP;

    sf::Vector2f m_position;



public:

    void InitialiserFont(GameData &g);
    void setPosition(sf::Vector2f newValue);
    void MiseEnPage(std::string messageAFormater);
    void OuvrirMessage(std::string messageAfficher, sf::Image *Interlocuteur,GameData &g);
    void OuvrirMessage(std::string messageAfficher,GameData &g);
    void OuvrirMessageSansInteraction(std::string messageAfficher,GameData &g);
    void Afficher(gameWindow &fenetre);


    Messagerie();
    ~Messagerie();



};
#endif
