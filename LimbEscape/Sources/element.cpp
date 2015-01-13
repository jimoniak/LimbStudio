/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "constantes.h"
#include "element.hpp"

bool Element::departPose = false ;
std::vector<Element*> Element::tableauElement;

Element::Element()
{
    Element::tableauElement.push_back(this);

}
Element::~Element()
{

}

bool  Element::estPoussable()
{
    return m_poussable;
}

bool Element::estFranchissable()
{
    return m_franchissable;

}


void Element::Deplacer(sf::Vector2f vecteurDeplacement)
{
     m_position += vecteurDeplacement;
     actualiserPosition(m_position);

}


//getter
sf::Sprite  Element::getApparence()
{
    return m_sprite;
}

sf::Vector2f  Element::getPosition()
{
    return m_position;
}

Type_element  Element::getType()
{
    return m_element;
}




Caisse::Caisse(sf::Vector2f position,RessourceHolder *rholder)
{

   // if(!m_apparence.loadFromFile("Data/Elements/Caisse.png"))   std::cout<<"Impossible d'ouvrir Caisse.png" << std::endl;
    m_apparence = rholder->getTextureElem(CAISSE);
    m_sprite.setTexture(m_apparence);

    m_position = position;
    actualiserPosition(m_position);

    m_poussable = true;
    m_franchissable=false;
    m_element = CAISSE;

    //std::cout<<"Caisse crée en position: (" << m_position.x<<";"<<m_position.y<<")"<<std::endl;


}
Caisse::~Caisse() {}

void Caisse::actualiserPosition(sf::Vector2f position)
{
    m_sprite.setPosition (OFFSET_CARTE+(DEMI_LTILE * position.x - DEMI_LTILE* position.y) + ((LARGEUR_TILE * COTECARTE ) / 2) - DEMI_LTILE  ,DEMI_HTILE * position.x + DEMI_HTILE * position.y - HAUTEUR_TILE);

}

void Caisse::Deplacer(sf::Vector2f vecteurDeplacement)
{

    m_position += vecteurDeplacement;
    actualiserPosition(m_position);


}

Objectif::Objectif(sf::Vector2f position,RessourceHolder *rholder)
{

    // if(!m_apparence.loadFromFile("Data/Elements/TileObjectif.png"))   std::cout<<"Impossible d'ouvrir TileObjectif.png" << std::endl;
    m_apparence = rholder->getTextureElem(OBJECTIF);

    m_sprite.setTexture(m_apparence);
    m_position = position;
    actualiserPosition(m_position);
    m_poussable = false;
    m_franchissable=true;
    m_element = OBJECTIF;

}

void Objectif::testEtat()
{
    m_resolu = false;
    for(unsigned i=0; i< Element::tableauElement.size(); i++) {
        if(Element::tableauElement[i]->getType() == CAISSE) {
            if(Element::tableauElement[i]->getPosition() == m_position) m_resolu = true;

        }

    }

}

void Objectif::changerEtat(bool resolu)
{
    m_resolu = resolu;
}

bool Objectif::estResolu()
{
    return m_resolu;
}

void Objectif::actualiserPosition(sf::Vector2f position)
{
    m_sprite.setPosition (OFFSET_CARTE+(DEMI_LTILE * position.x - DEMI_LTILE* position.y) + ((LARGEUR_TILE * COTECARTE ) / 2) - DEMI_LTILE  ,DEMI_HTILE * position.x + DEMI_HTILE * position.y);
}


Depart::Depart(sf::Vector2f position,RessourceHolder *rholder)
{
    m_apparence = rholder->getTextureElem(DEPART);
    m_sprite.setTexture(m_apparence);
    m_position = position;
    actualiserPosition(m_position);


    Element::departPose = true;
    m_poussable = false;
    m_franchissable=true;

    m_element = DEPART;
}

void Depart::actualiserPosition(sf::Vector2f position)
{
    m_sprite.setPosition (OFFSET_CARTE+(DEMI_LTILE * position.x - DEMI_LTILE* position.y) + ((LARGEUR_TILE * COTECARTE ) / 2) - DEMI_LTILE  ,DEMI_HTILE * position.x + DEMI_HTILE * position.y);
}


Mur::Mur(sf::Vector2f position,RessourceHolder *rholder)
{
    //if(!m_apparence.loadFromFile("Data/Elements/TileCaisse.png"))   std::cout<<"Impossible d'ouvrir TileCaisse.png" << std::endl;
    m_apparence = rholder->getTextureElem(MUR);


    m_sprite.setTexture(m_apparence);
    m_position = position;
    actualiserPosition(m_position);

    m_poussable = false;
    m_franchissable=false;
    m_element = MUR;

}


void Mur::actualiserPosition(sf::Vector2f position)
{
    m_sprite.setPosition (OFFSET_CARTE+(DEMI_LTILE * position.x - DEMI_LTILE* position.y) + ((LARGEUR_TILE * COTECARTE ) / 2) - DEMI_LTILE  ,DEMI_HTILE * position.x + DEMI_HTILE * position.y - HAUTEUR_TILE);

}
