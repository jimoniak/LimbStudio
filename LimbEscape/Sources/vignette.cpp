

#include <SFML/Graphics.hpp>
#include <GUI.hpp>
#include "vignette.hpp"


      Vignette::Vignette(sf::Font &font)
      {

          m_fond.create (50, 50, sf::Color::Blue);
          m_fondOn.create (50, 50, sf::Color::Yellow);
          m_texture.loadFromImage(m_fond);
          m_texturOn.loadFromImage(m_fondOn);
          m_Texture = &m_texture;
          m_textureOn= &m_texturOn;
          m_apparence.setTexture(*m_Texture);

          m_titre.setFont(font);
          m_titre.setString("Youpi");
          m_titre.setCharacterSize(18);
          m_titre.setColor(sf::Color::Green);
      }
      Vignette::~Vignette(){}

    void Vignette::setPosition(sf::Vector2f position)
     {
        Bouton::setPosition(position);
        m_titre.setPosition(position.x,position.y + m_Texture->getSize().y +5);
        //setPositionTitre(position.x,position.y + m_Texture->getSize().y +5);

     }




