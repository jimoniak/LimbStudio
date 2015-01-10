
#include "gameWindow.hpp"

#include <iostream>


void gameWindow::ChangerCurseur(std::string cheminImgCurseur)
{
    Souris.setTexture( cheminImgCurseur);

}

 void gameWindow::PositionnerCurseur()
 {
     if(m_horlogeInterne.getElapsedTime().asSeconds() > float(0.015))
     {
         sf::View current = this->getView();
         sf::Vector2f positionVue = sf::Vector2f(current.getCenter().x - current.getSize().x /2,current.getCenter().y - current.getSize().y /2);

     Souris.m_pointeur.setPosition(positionVue.x+sf::Mouse::getPosition().x,positionVue.y+sf::Mouse::getPosition().y);


     m_horlogeInterne.restart();
     }

 }

bool gameWindow::getCurseurEstPerso()
{

    return CurseurPersoActif;

}

 void gameWindow::display()
 {
     //Placement automatique de la souris.
     if(CurseurPersoActif && m_sourisVisible)
     {
         PositionnerCurseur();
         this->draw(Souris.m_pointeur);
          // cout<<  "x:"<< m_input.getMouseX() << " y:" << m_input.getMouseY() << endl ;
     }
    // this->draw(Souris.m_pointeur);
     RenderWindow::display();

 }

      gameWindow::gameWindow(sf::VideoMode mode, const sf::String &title, Uint32 style, const sf::ContextSettings &settings)
    {
            create(mode, title, style,settings);


            if(!Souris.m_Texture.loadFromFile("Ressources/Interface/Jeu/Curseur.png")) std::cerr<<"erreur d'ouverture de la texture du curseur souris!" <<std::endl;
            Souris.m_pointeur.setTexture(Souris.m_Texture);
            Souris.m_visible= false;
            CurseurPersoActif = false;

    }
    void gameWindow::UtiliserCurseurJeu(bool utiliser)
    {
        if (utiliser)
        {
            RenderWindow::setMouseCursorVisible(false);
            CurseurPersoActif = true;
        }
        else
        {
            RenderWindow::setMouseCursorVisible(true);
            CurseurPersoActif = false;
        }

    }

    void gameWindow::setMouseCursorVisible(bool show)
    {
        if(CurseurPersoActif)
        {

            if(show)
            {
                RenderWindow::setMouseCursorVisible(false);
                Souris.m_visible=m_sourisVisible = true;
            }
            else
            {
                RenderWindow::setMouseCursorVisible(false);
                Souris.m_visible=m_sourisVisible = false;
            }
        }
        else
        {

            if(show)
            {
                RenderWindow::setMouseCursorVisible(true);
                Souris.m_visible=m_sourisVisible= false;
            }
            else
            {
                RenderWindow::setMouseCursorVisible(false);
                Souris.m_visible= m_sourisVisible= false;
            }

        }

    }



void CurseurSouris::MontrerCurseur(bool montrer)
{
    m_visible = montrer ? true : false;

}



void CurseurSouris::setTexture(std::string cheminImgCurseur)
{

    m_Texture.loadFromFile(cheminImgCurseur);
    m_pointeur.setTexture(m_Texture);
}



CurseurSouris::CurseurSouris()
{

}

CurseurSouris::~CurseurSouris()
{

}







