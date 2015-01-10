


#include <iostream>
#include "bouton.hpp"
#include "managerGUI.hpp"

namespace lgui
{
     Bouton::Bouton()
    {
       // std::cout<<"objet crée"<<std::endl;

            m_titre.setString("Sans Titre");
            m_titre.setCharacterSize(10);
            m_titre.setPosition(0,0);
            m_selectionnable = false;

    }

     Bouton::Bouton(sf::Font &font,sf::Vector2f taille, sf::Color couleurbouton,sf::Color couleurboutonOn,sf::Color couleurTexte)
    {
          m_selectionnable = false;

          m_position.x = 0;m_position.y=0;
          m_apparence.setPosition(m_position);
          m_taille= taille;
          m_fond.create (taille.x, taille.y, couleurbouton);
          m_fondOn.create (taille.x, taille.y, couleurboutonOn);
          m_texture.loadFromImage(m_fond);
          m_texturOn.loadFromImage(m_fondOn);
          m_Texture = &m_texture;
          m_textureOn= &m_texturOn;
          m_apparence.setTexture(*m_Texture);

          m_titre.setFont(font);
          m_titre.setString("Youpi");
          m_titre.setCharacterSize(15);
          m_titre.setPosition(m_position.x + m_taille.x / 2 - m_titre.getGlobalBounds().width / 2 ,m_position.y + m_taille.y /2 - m_titre.getGlobalBounds().height);
          m_titre.setColor(couleurTexte);

    }

    Bouton::Bouton(sf::Font &font,sf::Texture *texture,sf::Texture *textureOn,sf::Vector2f position,std::string titre,int tailleFont,sf::Color couleurTexte)
    {
            m_selectionnable = false;
            m_position = position;
            m_taille = sf::Vector2f(texture->getSize());
            m_Texture = texture;
            m_textureOn = textureOn;
            m_apparence.setTexture(*texture);
            m_apparence.setPosition(m_position);
            m_titre.setFont(font);
            m_titre.setString(titre);
            m_titre.setCharacterSize(tailleFont);
            m_titre.setPosition(m_position.x + m_taille.x / 2 - m_titre.getGlobalBounds().width / 2 ,m_position.y + m_taille.y /2 - m_titre.getGlobalBounds().height / 2);
            m_titre.setColor(couleurTexte);

    }






    void Bouton::afficher()
    {
        ElementGUI::afficher();
        m_fenetre->draw(m_titre);
    }

    bool Bouton::actif()
    {
            return m_actif;
    }

    bool Bouton::actionner()
    {


                    if( ElementGUI::estDessus()  && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                            if(!m_actif)
                            {
                                m_actif = true;
                                return true;
                            }
                            return false;

                    }
                    else {m_actif=false; return false;}



    }

    bool Bouton::estDessus()
    {
    return ElementGUI::estDessus();

    }

     std::string Bouton::getString()
     {
         return m_titre.getString();
     }


        sf::Vector2f Bouton::getTaille()
        {
            return m_taille;
        }
        void Bouton::setTexte(sf::Text const &text){}
        void Bouton::setTexte(sf::Font &font,std::string titre,int tailleFont,sf::Color couleurTexte)
        {

            m_titre.setFont(font);
            m_titre.setString(titre);
            m_titre.setCharacterSize(tailleFont);
            //m_titre.setPosition(m_position.x + m_taille.x / 2 - m_titre.getGlobalBounds().width / 2 ,m_position.y + m_taille.y /2 - m_titre.getGlobalBounds().height / 2);
            m_titre.setColor(couleurTexte);



        }
        void Bouton::setTailleTexte(int taille)
        {
            m_titre.setCharacterSize(taille);
        }
        void Bouton::setFont(sf::Font &font)
        {
             m_titre.setFont(font);

        }
        void Bouton::setCouleurTexte(sf::Color couleur)
        {
            m_titre.setColor(couleur);
        }
        void Bouton::setTitre(std::string titre)
        {
            m_titre.setString(titre);
        }

     void Bouton::setTextures(sf::Texture &texture,sf::Texture &textureOn )
     {
         m_Texture = &texture;
         m_textureOn = &textureOn;
          m_taille = sf::Vector2f(texture.getSize());
          m_apparence.setTexture(*m_Texture);

     }

     void Bouton::setScale(float scale)
     {
         m_apparence.setScale (scale, scale);
         m_taille.x = m_Texture->getSize().x  * scale;
         m_taille.y = m_Texture->getSize().y * scale;

     }

     void Bouton::setPosition(sf::Vector2f position)
     {
         ElementGUI::setPosition(position);
         m_titre.setPosition(m_position.x + m_taille.x / 2 - m_titre.getGlobalBounds().width / 2 ,m_position.y + m_taille.y /2 - m_titre.getGlobalBounds().height);

     }
     void Bouton::setPositionTitre(sf::Vector2f position)
     {


     }


    Bouton::~Bouton()
    {}

}
