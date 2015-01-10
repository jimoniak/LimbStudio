#include "constantes.hpp"

#include "gameWindow.hpp"

#include "gestionAudio.h"
#include "Classes.h"


#include "Carte.hpp"

#include "Prototypes.hpp"
#include "Bouton.hpp"

#include "graphique.hpp"
#include "Inventaire.hpp"

#include "Spherier.hpp"
#include "Personnage.h"

#include "PanneauActif.h"
#include "Messagerie.hpp"

#include "GameData.hpp"
#include <SFML/System/Vector2.hpp>

#include "settingsMenu.hpp"

settingsMenu::settingsMenu(gameWindow* w, GameData* GameDataPtr)
    : m_window(w), m_GameDataPtr(GameDataPtr), m_clock(0), m_backgroundImg(0), m_smoothDeg(0),
      m_running(false), m_quitButtonPtr(0)
{
    m_soundVolume = (sf::Int8)(m_GameDataPtr->Sound.getVolume());
    m_musicVolume = (sf::Int8)m_GameDataPtr->MusiqueDeFond.getVolume();
}

void settingsMenu::start()
{
    m_running = true;
    run();
}

void settingsMenu::stop()
{
    m_running = false;
}

void settingsMenu::run()
{
    m_x = m_window->getView().getViewport().left;
    m_y = m_window->getView().getViewport().top;
    sf::Image img(m_window->capture());

    m_backgroundImg = new sf::Image();
    m_backgroundImg->create(img.getSize().x, img.getSize().y);

    for (unsigned int y = 0; y < img.getSize().y; y++)
    {
        for (unsigned int x = 0; x < img.getSize().x; x++)
            m_backgroundImg->setPixel(x,img.getSize().y - 1 - y, img.getPixel(x, y));
    }

    {
        sf::Vector2f qbsize(50,50);
        m_quitButtonPtr = new Bouton(qbsize,false);
        m_quitButtonPtr->setPosition(sf::Vector2f(m_x+m_window->getSize().x - qbsize.x-5, m_y+5));
        // m_quitButtonPtr->setMask(sf::Color::Green);
        m_quitButtonPtr->setTxt("X", m_GameDataPtr->font, sf::Color::White, 25);
    }

    m_smoothDeg = 100;
    m_clock = new sf::Clock();
    m_clock->restart();
    long lastTime = m_clock->getElapsedTime().asSeconds() * 1000000.0f;
    long timer = m_clock->getElapsedTime().asSeconds() * 1000.0f;
    const double microSec = 1000000.0 / 60.0;
    double delta = 0;
    int frames = 0;
    int updates = 0;
    bool needRendering = false;

    while (m_running)
    {
        float now = m_clock->getElapsedTime().asSeconds() * 1000000.0f;
        delta += (now - lastTime) / microSec;
        lastTime = now;
        while (delta >= 1)
        {
            update();
            updates++;
            delta--;
            needRendering = true;
        }

        if (needRendering)
        {
            render();
            frames++;
            needRendering = false;
        }

        if (m_clock->getElapsedTime().asSeconds() * 1000.0f - timer > 1000)
        {
            timer += 1000;
            std::ostringstream oss;
            oss << updates << " updates, " << frames << " fps";
            std::cout << oss.str() << std::endl;
            updates = 0;
            frames = 0;
        }
    }
    delete m_quitButtonPtr;
    m_quitButtonPtr=0;
}

void settingsMenu::handleInput()
{
    sf::Event& e = m_GameDataPtr->event;
    while (m_GameDataPtr->Fenetre->pollEvent(m_GameDataPtr->event))
    {
        if (m_GameDataPtr->event.type == sf::Event::Closed)
            m_GameDataPtr->Fenetre->close();
    }

    if ((e.type == sf::Event::KeyReleased) && (e.key.code == sf::Keyboard::O))
    {
        stop();
    }

    //  const sf::Input& i = m_window->getInput();

    int curseurX, curseurY;
    curseurX = m_x+sf::Mouse::getPosition(*m_window).x;
    curseurY = m_y+sf::Mouse::getPosition(*m_window).y;

//    int cbutton((int)m_quitButtonPtr->m_dessous.a << 8 & m_quitButtonPtr->m_dessous.r << 8 & m_quitButtonPtr->m_dessous.g << 8 & m_quitButtonPtr->m_dessous.b);
    //  int cGreen((int)sf::Color::Green.a << 8 & sf::Color::Green.r << 8 & sf::Color::Green.g << 8 & sf::Color::Green.b);
    /*  int cred((int)sf::Color::Red.a << 8 & sf::Color::Red.r << 8 & sf::Color::Red.g << 8 & sf::Color::Red.b);

      if (m_quitButtonPtr->EstDessus(curseurX,curseurY))
      {
    !        if(cbutton==cGreen)
          {
              m_quitButtonPtr->setMask(sf::Color::Red);
          }
      }
      else
      {
          if(cbutton==cred)
          {
              m_quitButtonPtr->setMask(sf::Color::Green);
          }
      }

      if (m_quitButtonPtr->ClicInventaire(e, curseurX, curseurY))
      {
          stop();
      }*/



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_GameDataPtr->MusiqueDeFond.setVolume(--m_musicVolume);
        if (m_musicVolume < 0) m_GameDataPtr->MusiqueDeFond.setVolume(++m_musicVolume);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        m_GameDataPtr->MusiqueDeFond.setVolume(++m_musicVolume);
        if (m_musicVolume > 100) m_GameDataPtr->MusiqueDeFond.setVolume(--m_musicVolume);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        m_GameDataPtr->Sound.setVolume((float)--m_soundVolume);
        if (m_soundVolume < 0) m_GameDataPtr->Sound.setVolume((float)++m_soundVolume);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_GameDataPtr->Sound.setVolume((float)++m_soundVolume);
        if (m_soundVolume > 100) m_GameDataPtr->Sound.setVolume((float)--m_soundVolume);
    }
}

void settingsMenu::update()
{
    handleInput();

    if (m_smoothDeg > 0) m_smoothDeg--;
}

void settingsMenu::render()
{
    m_window->clear(sf::Color::Black);
    sf::Image img(*m_backgroundImg);
    /*  sf::Shader postFX;

      postFX.loadFromFile("blur.sfx",sf::Shader::Fragment);

      postFX.setTexture("framebuffer", &img);
      postFX.setParameter("offset",  ((100 - m_smoothDeg)/ -100.0f) * 0.008f);

      float f = 1.0f - (float) m_smoothDeg / 100.0f;
      int alpha = (int)(255. * f);
      if (alpha > 150) alpha = 150;
      sf::Shape alphaMask = sf::Shape::Rectangle(0, 0, m_window->getWidth(), m_window->getHeight(), sf::Color(0, 0, 0, alpha));
      alphaMask.setPosition(m_window->getView().getRect().Left, m_window->getView().getRect().Top);


      m_window->draw(postFX);
      m_window->draw(alphaMask);*/

    sf::Text str;
    str.setString("ECHAP POUR FERMER LE MENU");
    str.setCharacterSize(10);
    str.setPosition(m_x, m_y);
    str.setFont(m_GameDataPtr->font);
    m_window->draw(str);

    std::ostringstream oss;
    oss << "Volume musique : " << (short)m_musicVolume << "/100" << std::endl << "Volume son : " << (short)m_soundVolume << "/100";
    str.setString(oss.str());
    str.move(0, 50);
    m_window->draw(str);

    sf::Text version;
    version.setString("Mystogen v: " + (std::string)VERSION);
    version.setCharacterSize(15);
    version.setPosition(m_x + LFENETRE - 150, m_y + HFENETRE - 50);
    version.setFont(m_GameDataPtr->font);
    version.setColor(sf::Color::Red);
    m_window->draw(version);
    m_quitButtonPtr->Affichage(*m_window);



    m_window->display();
}

bool settingsMenu::isRunning()
{
    return m_running;
}

settingsMenu::~settingsMenu()
{
    if (m_clock)
    {
        delete m_clock;
        m_clock = 0;
    }

}
