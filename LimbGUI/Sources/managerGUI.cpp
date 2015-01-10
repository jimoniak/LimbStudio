

#include "managerGUI.hpp"
#include <iostream>



namespace lgui
{
  /*  ManagerGUI* ManagerGUI::m_pointeurthis = NULL;

    ManagerGUI::ManagerGUI()
    {
        if(ManagerGUI::m_pointeurthis==NULL) ManagerGUI::m_pointeurthis = this;
    }

     ManagerGUI::ManagerGUI(sf::RenderWindow *fenetre)
    {
        if(ManagerGUI::m_pointeurthis==NULL) ManagerGUI::m_pointeurthis = this;
        m_fenetre = fenetre;
    }

    void ManagerGUI::afficher()
    {

    }


    void ManagerGUI::ajouterElemnt(lgui::ElementGUI* element)
    {
        m_gestionnaireElement.push_back(element);
    }

    void ManagerGUI::manage()
    {
        if(m_pointeurEventFenetre != NULL)
        {
            m_survole = false;

             for(std::vector<ElementGUI*>::iterator iterateur = m_gestionnaireElement.begin() ; iterateur != m_gestionnaireElement.end() ; iterateur++)
            {
                    if((*iterateur)->estDessus(sf::Vector2f(sf::Mouse::getPosition(*m_fenetre))))
                    {
                            m_elementSurvole = *iterateur;
                            m_survole = true;
                    }

            }
            if(m_survole && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_elementSurvole->estSelectionnable())
                m_elementcible = m_elementSurvole;
                else
                m_elementcible = NULL;
            }

            if(!m_survole)
            {
                m_elementSurvole =  NULL;


                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    m_elementcible = NULL;

                }


            }


        }



    }

    void ManagerGUI::setElementCible(ElementGUI* element)
    {
        m_elementcible = element;

    }

    void ManagerGUI::setEvent(sf::Event *event)
    {
        m_pointeurEventFenetre = event;
    }

     void  ManagerGUI::setStaticPointeur(ManagerGUI* ptr)
     {
         ManagerGUI::m_pointeurthis = ptr;
     }

     ElementGUI*  ManagerGUI::getElementcible()
     {
         return m_elementcible;
     }

      ElementGUI*  ManagerGUI::getElementSurvole()
      {
          return m_elementSurvole;
      }

     sf::Event* ManagerGUI::getEvent()
     {
         return m_pointeurEventFenetre;

     }

    ManagerGUI* ManagerGUI::getManager()
    {
        return m_pointeurthis;

    }

     ManagerGUI::~ManagerGUI()
    {
        //std::cout<<"Manager detruit ;( " <<std::endl;
    }
*/
}
