/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "constantes.h"
#include "ressourceholder.hpp"
#include "element.hpp"
#include "carte.hpp"
#include "gestionSouris.hpp"




GestionSouris::GestionSouris(sf::RenderWindow *fenetre)
{
    pfenetrePrincipale = fenetre;
    //pcarte = carte;

    if(!m_overlaySouris.loadFromFile("Data/Tiles/MouseOverlay.png")) {
        std::cout<< "Erreur avec MouseOverlay.png"<<std::endl;
    }

}


sf::Vector2f GestionSouris::CalcCoordCarte()
{

    PositionSourisFenetre = sf::Vector2f(sf::Mouse::getPosition(*pfenetrePrincipale));
    Position2D = pfenetrePrincipale->mapPixelToCoords(sf::Vector2i(PositionSourisFenetre));

    sf::Vector2f VariableCalc (floor((Position2D.x + DEMI_LTILE) / (LARGEUR_TILE))  , floor(Position2D.y / (HAUTEUR_TILE )) );
    PositionSourisGrille = VariableCalc;

    coorPointeurIso.x= int(PositionSourisGrille.x+PositionSourisGrille.y);
    coorPointeurIso.y=int(PositionSourisGrille.y - PositionSourisGrille.x);

    couleurPixelOverlay=m_overlaySouris.getPixel(int(floor(Position2D.x + DEMI_LTILE)) % (LARGEUR_TILE), int(floor(Position2D.y)) % (HAUTEUR_TILE ));

    if(couleurPixelOverlay==sf::Color::Blue) {
        coorPointeurIso.x+=1;
        //cout<<"bleu!"<<endl;
    } else if (couleurPixelOverlay==sf::Color::Red) {
        coorPointeurIso.y-=1;
        // cout<<"rouge!"<<endl;
    } else if (couleurPixelOverlay==sf::Color::Yellow) {
        coorPointeurIso.x-=1;
        // cout<<"jaune!"<<endl;
    } else if (couleurPixelOverlay==sf::Color::Green) {
        coorPointeurIso.y+=1;
        // cout<<"vert!"<<endl;
    } else {}

    return coorPointeurIso;


}


sf::Vector2f GestionSouris::getCoordSouris()
{

    return coorPointeurIso;

}


Selecteur::Selecteur()
{

    if(!Selection.loadFromFile("Data/Tiles/TileSelection.png")) {
        std::cout<<"Impossible d'ouvrir TileSelection.png" <<std::endl;
    }

    Selection.setSmooth(true);
    spriteSelection.setTexture(Selection);
}

void Selecteur::positionnerSelecteur(GestionSouris &gestionSouris)
{
    spriteSelection.setPosition(DEMI_LTILE * gestionSouris.getCoordSouris().x - DEMI_LTILE* gestionSouris.getCoordSouris().y - DEMI_LTILE ,   DEMI_HTILE * gestionSouris.getCoordSouris().x + DEMI_HTILE * gestionSouris.getCoordSouris().y);
}

sf::Sprite Selecteur::getSprite()
{
    return spriteSelection;
}
