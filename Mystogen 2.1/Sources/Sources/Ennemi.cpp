/*

#include "constantes.hpp"
#include "Prototypes.hpp"
#include "Classes.h"

using namespace std;
using namespace sf;

Ennemi::Ennemi(){}

Ennemi::~Ennemi(){}

void Ennemi::Chargement(std::string nomEnnemi)
{
    string ligneLue = "Ennemis/"+nomEnnemi+".enm";

    ifstream enm(ligneLue.c_str(),ios::in);
    if(!enm)
        cout << "impossible de charger: Ennemis/" << nomEnnemi << ".enm" << endl;
    else
    {
    m_nom = nomEnnemi;

    getline(enm,ligneLue);
    m_Texture.loadFromFile(ligneLue);
    m_Texture.setSmooth(0);
    m_Texture.CreateMaskFromColor(sf::Color(0, 0, 0));

    m_skin.setTexture(m_Texture);

    getline(enm,ligneLue);
    m_vie = ConvertionStringInt(ligneLue);
    }

}

Vector2f Ennemi::getPosImg()
{
    return m_skin.getPosition();
}

void Ennemi::Position(int nombreEnnemi,int i)
{
    m_skin.setPosition(100*i + 150,200);
    if(nombreEnnemi > 5 && i > 4)
        m_skin.setPosition(100*i - 400,300);
}

void Ennemi::Affichage (gameWindow &fenetre)
{
    fenetre.draw(m_skin);
}

void Ennemi::Attaquer (Personnage &Cible)
{
    Cible.PerdreVie(10);
}

void Ennemi::PerdreVie(int qtt)
{
    m_vie -= qtt;
}

int Ennemi::getVie()
{
    return (m_vie);
}
*/
