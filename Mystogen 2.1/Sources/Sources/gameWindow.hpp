
#ifndef GAMEWINDOW
#define GAMEWINDOW


#include <SFML/Graphics.hpp>
#include <string>


typedef unsigned int Uint32;

class CurseurSouris
{
private:


    sf::Texture m_Texture;
    sf::Sprite m_pointeur;
    bool m_visible;


public:

    void setTexture(std::string cheminTexture);
    void MontrerCurseur(bool montrer);


    CurseurSouris();
    virtual ~CurseurSouris();

    friend class gameWindow;




};

class gameWindow : public sf::RenderWindow
{

private:
    bool CurseurPersoActif;
    sf::Clock m_horlogeInterne;

    //const sf::Event& m_event;
    CurseurSouris Souris;
    bool m_sourisVisible;


public:
    void UtiliserCurseurJeu(bool utiliser);
    void setMouseCursorVisible(bool show);
    void ChangerCurseur(std::string cheminImgCurseur);
    void PositionnerCurseur();

    bool getCurseurEstPerso();

    void display();

    //gameWindow(sf::VideoMode Mode, const std::string& Title, unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close, const sf::Windowsettings& Params = sf::Windowsettings());
    gameWindow(sf::VideoMode mode, const sf::String &title, Uint32 style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());
};

#endif // GAMEWINDOW
