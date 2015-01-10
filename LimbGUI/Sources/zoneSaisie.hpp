
#ifndef ZONE_SAISIE
#define ZONE_SAISIE


#include <iostream>
#include "elementGUI.hpp"


namespace lgui
{

     class DllExport ZoneSaisie : public  ElementGUI
    {
        static ZoneSaisie* selectionner;

        protected:
        sf::Image   m_ImgZoneSaisie;

        std::string m_texteSaisie;
        std::string m_chaineCalcul;
        sf::Text      m_texte;

        std::string m_charset;
        bool m_bloquageClavier;
        int m_nombreCaractere;

        public:
        ZoneSaisie();
        ZoneSaisie(sf::Font &font, sf::Vector2f taille,sf::Vector2f position = sf::Vector2f(0,0), sf::Color couleur1 = sf::Color::Yellow,sf::Color couleur2 =sf::Color::Green);

        std::string getTexte();

        virtual void afficher();
        virtual bool estDessus();

        virtual bool  actif(sf::Event &event);

        void setCharset(std::string &charset);

        virtual ~ZoneSaisie();


    };

}

#endif // ZONE_SAISIE
