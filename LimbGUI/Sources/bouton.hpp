
#ifndef BOUTON
#define BOUTON


#include "elementGUI.hpp"

//#define DllExport   __declspec(dllexport)

namespace lgui
{


class DllExport Bouton :public ElementGUI
    {
        friend class ManagerGUI;

        protected:

        sf::Text           m_titre;

        public:

        Bouton();
        Bouton(sf::Font &font,sf::Vector2f taille = sf::Vector2f(0,0), sf::Color couleurbouton = sf::Color::Green,sf::Color couleurboutonOn = sf::Color::Blue,sf::Color couleurTexte = sf::Color::Black); //crée un bouton de toute piece! :D
        Bouton(sf::Font &font,sf::Texture *texture,sf::Texture *textureOn,sf::Vector2f position = sf::Vector2f(float(0),float(0)), std::string titre = "sans Titre",int tailleFont = 10,sf::Color couleurTexte = sf::Color::Black);//crée un bouton à partir d'images demandées
       // bool estDessus(sf::Vector2f positionSouris);

        virtual void afficher();
        virtual bool actif();
        virtual bool estDessus();

        bool actionner();


        //getter
        std::string getString();

        //sf::Sprite     getApparence();
        sf::Vector2f getTaille();

        //setter
        void setTexte(sf::Text const &text);
        void setTexte(sf::Font &font,std::string titre = "sans Titre",int tailleFont = 10,sf::Color couleurTexte = sf::Color::Black);
        void setTailleTexte(int taille);
        void setFont(sf::Font &font);
        void setCouleurTexte(sf::Color couleur);
        void setTitre(std::string titre);


        void setTextures(sf::Texture &texture,sf::Texture &textureOn);
        void setTextureOn(sf::Texture *textureOn);
        void setScale(float scale);
        void setPosition(sf::Vector2f position);
        void setPositionTitre(sf::Vector2f position);

        virtual ~Bouton();

    };
}
#endif // BOUTON
