
#define DllImport   __declspec(dllimport)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "managerGUI.hpp"
#include "elementGUI.hpp"



namespace lgui
{
    int ElementGUI::compteur = 0;


    void ElementGUI::setFenetrelie(sf::RenderWindow &fenetre)
    {
        m_fenetre = &fenetre;
    }

    void ElementGUI::afficher()
    {
        m_fenetre->draw(m_apparence);
    }

    void ElementGUI::activer()
    {
        std::cout<< "action de ElementGUI"<<std::endl;
    }

    bool  ElementGUI::actif()
    {
        return false;

    }

    bool ElementGUI::estDessus()
    {

        positionSouris.x = sf::Mouse::getPosition(*m_fenetre).x;
        positionSouris.y = sf::Mouse::getPosition(*m_fenetre).y;
        if(positionSouris.x> m_position.x && positionSouris.x< m_position.x + m_taille.x) //test en x
        {
            if(positionSouris.y> m_position.y && positionSouris.y< m_position.y + m_taille.y) //test en y
            {
                if(m_textureOn) m_apparence.setTexture(*m_textureOn);
                return true;
            }
            m_apparence.setTexture(*m_Texture);
            return false;
        }
        else {m_apparence.setTexture(*m_Texture);  return false;}
    }


    bool ElementGUI::estSelectionnable()
    {
        return m_selectionnable;
    }

    void ElementGUI::setPosition(sf::Vector2f position)
    {
        m_position=position;
        m_apparence.setPosition(position);

    }

        ElementGUI::ElementGUI()
        {
            m_actif = false;

             ElementGUI::compteur ++;
//             if(lgui::ManagerGUI::getManager() != NULL) lgui::ManagerGUI::getManager()->ajouterElemnt(this);
 //            else
 //            {
                 /*
                 lgui::ManagerGUI* ptr;
                  ptr = new ManagerGUI() ;
                  lgui::ManagerGUI::setStaticPointeur(ptr);
                  lgui::ManagerGUI::getManager()->ajouterElemnt(this);
                  std::cout<< "Manager Crée! :D"<<std::endl;
                  */

        //     }

             //std::cout<<"ajout effectué"<<std::endl;

        }

    ElementGUI::~ElementGUI()
    {
        ElementGUI::compteur--;

        /*if(compteur==0 && ManagerGUI::getManager() !=NULL)
        {
            delete ManagerGUI::getManager();
        }*/
    }



}
