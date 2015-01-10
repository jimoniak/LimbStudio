#ifndef setTINgS_MENU
#define setTINgS_MENU

#include "gameWindow.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "Bouton.hpp"

class GameData;
class gameWindow;

class settingsMenu
{
public:
    settingsMenu(gameWindow* w, GameData *gd);
    void start();
    void stop();
    void run();
    void handleInput();
    void update();
    void render();
    bool isRunning();
    ~settingsMenu();
private:
    int m_x;
    int m_y;
    gameWindow* m_window;
    GameData* m_GameDataPtr;
    sf::Clock* m_clock;
    sf::Image* m_backgroundImg;
    sf::Texture* m_backgroundTex;
    int m_smoothDeg;
    bool m_running;
    sf::Int8 m_soundVolume;
    sf::Int8 m_musicVolume;
    Bouton* m_quitButtonPtr;
};

#endif // setTINgS_MENU
