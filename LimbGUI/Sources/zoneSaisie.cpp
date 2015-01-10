
#include "zoneSaisie.hpp"
#include "managerGUI.hpp"

namespace lgui
{

    ZoneSaisie* ZoneSaisie::selectionner=nullptr;



    ZoneSaisie::ZoneSaisie(sf::Font &font, sf::Vector2f taille,sf::Vector2f position , sf::Color couleur1 ,sf::Color couleur2)
    {
          m_selectionnable = true;
          m_bloquageClavier = false;
          m_charset =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890.";
          m_taille=taille;
          m_position=position;
          m_apparence.setPosition(m_position);

          m_fond.create (taille.x, taille.y, couleur1);
          m_fondOn.create (taille.x, taille.y, couleur2);
          m_texture.loadFromImage(m_fond);
          m_texturOn.loadFromImage(m_fondOn);
          m_Texture = &m_texture;
          m_textureOn= &m_texturOn;
          m_apparence.setTexture(*m_Texture);

          m_texte.setFont(font);
          m_texte.setString("_");
          m_texte.setCharacterSize(18);
          m_texte.setPosition(m_position.x  ,m_position.y );
          m_texte.setColor(sf::Color::Black);



    }

    std::string ZoneSaisie::getTexte()
    {
        return m_texteSaisie;
    }

    void ZoneSaisie::afficher()
    {
        ElementGUI::afficher();
        m_fenetre->draw(m_texte);

    }

    bool ZoneSaisie::estDessus()
    {
       return  ElementGUI::estDessus();
    }


    bool  ZoneSaisie::actif(sf::Event &event)
    {

        if(m_selectionnable)
        {

            if(!m_actif)
            {

                if(estDessus()  && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    m_actif =true;
                    if(selectionner!=nullptr)selectionner->m_actif = false;
                    selectionner=this;
                    //std::cout<<"Select"<<std::endl;
                    return true;
                }
            }

            if(m_actif)//si on est en mode saisie
            {


                    if (event.type == sf::Event::TextEntered)
                    {

                        if (event.text.unicode == '\b' )
                        {
                            if(m_texteSaisie.size()>0)
                            m_texteSaisie.erase(m_texteSaisie.size() - 1, 1);
                            m_texte.setString(m_texteSaisie);

                            if(m_texte.getLocalBounds().width>m_taille.x)
                            {
                                m_chaineCalcul = m_texteSaisie;
                                while(m_texte.getLocalBounds().width>m_taille.x)
                                {
                                            if(m_chaineCalcul.size()>0)    m_chaineCalcul.erase(0,1);
                                            m_texte.setString(m_chaineCalcul);
                                }

                            }
                            return true;

                        }
                        for(unsigned int i=0;i<m_charset.size();i++)
                        {
                             if ((event.text.unicode == m_charset[i]))
                             {
                                  m_bloquageClavier = true;
                                  m_texteSaisie += static_cast<char>(event.text.unicode) ;
                                  m_texte.setString(m_texteSaisie);

                                    if(m_texte.getLocalBounds().width>m_taille.x)
                                    {
                                        m_chaineCalcul = m_texteSaisie;
                                        while(m_texte.getLocalBounds().width>m_taille.x)
                                        {
                                            if(m_chaineCalcul.size()>0)    m_chaineCalcul.erase(0,1);
                                            m_texte.setString(m_chaineCalcul);
                                        }

                                    }
                                    return true;

                             }

                        }

                    }

            }
            else return false;

        }
        return false;

        }


    void ZoneSaisie::setCharset(std::string &charset)
    {
        m_charset=charset;
    }



     ZoneSaisie::~ZoneSaisie()
     {}



}
