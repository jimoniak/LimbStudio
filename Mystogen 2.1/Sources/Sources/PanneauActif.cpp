//--------------PanneauActif.cpp-------------------------------
//----------Jimoniak-----------------------------------
#include "constantes.hpp"

#include "gameWindow.hpp"

#include "gestionAudio.h"
#include "Classes.h"


#include "Carte.hpp"

#include "Prototypes.hpp"
#include "Bouton.hpp"

#include "graphique.hpp"
#include "Inventaire.hpp"

#include "Spherier.hpp"
#include "Personnage.h"

#include "PanneauActif.h"
#include "Messagerie.hpp"

#include "GameData.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

PanneauActif::PanneauActif()
{}

PanneauActif::~PanneauActif()
{


}



int PanneauActif::getPosY()
{
    return m_posY;
}

void PanneauActif::setVie(Personnage &pers)
{
    m_BarreVie.MajParametre(pers.getVie());
}

void PanneauActif::setEnergie(Personnage &perso)
{
    m_BarreEnergie.MajParametre(perso.getEnergie());
}

void PanneauActif::setForce(Personnage   &perso)
{
    m_forcePers.setString("Force:" + ConvIntString(perso.getForce()));
}
void PanneauActif::setEndurance(Personnage   &perso)
{
    m_endurPers.setString("Endurance:" + ConvIntString(perso.getEndurance()));
}

void PanneauActif::setParam(Personnage &perso)
{
    m_BarreVie.MajParametre(perso.getVie());
    m_BarreEnergie.MajParametre(perso.getEnergie());
    m_forcePers.setString("Force:" + ConvIntString(perso.getForce()));
    m_endurPers.setString("Endurance:" + ConvIntString(perso.getEndurance()));
}

void PanneauActif::pannelOuvert( gameWindow &fenetre)
{

    fenetre.draw(m_corps);
    fenetre.draw(m_person);
    m_BarreVie.AfficherBarre(fenetre);
    m_BarreEnergie.AfficherBarre(fenetre);
    fenetre.draw(m_forcePers);
    fenetre.draw(m_endurPers);
    fenetre.draw(m_lieu);
    fenetre.draw(m_Temps);

}

void PanneauActif::setDimension(sf::Vector2f newDimension)
{
    m_dimension.x = newDimension.x;
    m_dimension.y = newDimension.y;
}
void PanneauActif::setPosition(sf::Vector2f newPosition)//Placement du pannel sur l'ecran et calcul des coordonnées de ses composants .
{
    m_Position.x = newPosition.x + (LFENETRE -m_Pannel.getSize().x) / 2 ;
    m_Position.y = newPosition.y  + m_posY;

    m_corps.setPosition(m_Position.x, m_Position.y);
    m_person.setPosition(m_Position.x+ 150,m_Position.y);

    m_lieu.setPosition(m_Position.x+ 750,m_Position.y + 60);
    m_Temps.setPosition(m_Position.x+750,m_Position.y + 30);
    m_BarreVie.setPosition(m_Position.x +300 ,m_Position.y + 30);
    m_BarreEnergie.setPosition(m_Position.x+300,m_Position.y + 70);
    m_forcePers.setPosition(m_Position.x+300,m_Position.y+100);
    m_endurPers.setPosition(m_Position.x+300,m_Position.y+130);

}

void PanneauActif::AnimationPannel(int pannelOuvert)
{
    //---------------------------------------Animation defilement Pannel-----------------------------------------------------------------
    if(pannelOuvert && m_enMouvement) //Condition permettant le "deroulement" du pannel.
    {
        //---OUVERTURE PANNEL-----//

        if(m_posY > -int(m_Pannel.getSize().y)  )
        {

            m_posY = m_posY_departAnim  -  (m_Pannel.getSize().y * m_horlogeAnimation.getElapsedTime().asSeconds()) / m_tempsAnimation;
            //cout<<m_posY<<endl;

        }
        else
        {
            m_posY = -m_Pannel.getSize().y;
            m_enMouvement =false;
        }

        //cout<<m_posY<<endl;
    }
    if(!pannelOuvert && m_enMouvement)
    {
        //---FERMETURE PANNEL---//
        if((m_posY <  0) )
        {

            m_posY = m_posY_departAnim +  m_Pannel.getSize().y * m_horlogeAnimation.getElapsedTime().asSeconds() / m_tempsAnimation;

        }
        else
        {
            m_posY = 0;
            m_enMouvement=false;
        }

    }


}

void PanneauActif::setSprite(Personnage &Joueur)
{
    m_person.setTexture(*Joueur.getSprite());
    //m_person.setSubRect(IntRect(10, 10, 20, 20));
}


float PanneauActif::getElapsedTime()
{
    return tempsEcoule;
}

void PanneauActif::setElapsedTime(float newValue)
{
    tempsEcoule = newValue;
}

void PanneauActif::JouerSon(int Afficher)
{
    if(Afficher) m_sonOuverture.play();
    else         m_sonFermeture.play();
}

void PanneauActif::setNomCarte(string newvalue)
{
    m_lieu.setString("Lieu: " + newvalue + ".");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PanneauActif::changementEtat(int *pannelOuvert)
{

    *pannelOuvert = ! *pannelOuvert;
    this->JouerSon(*pannelOuvert);
    m_horlogeAnimation.restart().asSeconds();
    m_posY_departAnim = m_posY;
    m_enMouvement = true;

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void PanneauActif::Chargement(sf::Font *myfont,Personnage &pers)
{
    m_DimBarreVie.x=150;
    m_DimBarreVie.y=20;

    m_DimBarreEnergie = m_DimBarreVie;

    m_Position.x=0;
    m_Position.y= HFENETRE - 300;
    m_dimension.x= LFENETRE;
    m_dimension.y=200;

    m_posY = m_posY_departAnim = 0;
    m_enMouvement = false;

    m_PosBarreVie.x= m_Position.x + 255;
    m_PosBarreVie.y= m_Position.y + 150;

    m_PosBarreEnergie.x=m_Position.x + 255;
    m_PosBarreEnergie.x=m_Position.y + 305;



    m_BarreVie=(Barregraphique("Vie:",1,pers.getMaxVie(),m_DimBarreVie, m_PosBarreVie,Color(0,0,0,150),Color(0,0,255,150)));
    m_BarreVie.ChargementPolice(*&myfont,20);
    m_BarreEnergie=(Barregraphique("Energie:",1,pers.getMaxEnergie(),m_DimBarreEnergie,m_PosBarreEnergie,Color(0,0,0,150),Color(0,255,0,150)));
    m_BarreEnergie.ChargementPolice(*&myfont,20);

    m_corps.setColor(sf::Color(0, 255, 255, 128));

    if(!m_Pannel.loadFromFile("Ressources/Pannel/Pannel.png"))  cout << "Fichier Ressources/Pannel/Pannel.png Introuvable !!" << endl;

    m_corps.setTexture(m_Pannel);
    m_corps.setPosition(m_Position.x, m_Position.y);

    if (!sonUn.loadFromFile("Ressources/Sounds/sonUn.ogg"))     cout<< "ouverture impossible"<<endl;
    if (!sonDeux.loadFromFile("Ressources/Sounds/sonDeux.ogg")) cout<< "ouverture impossible"<<endl;

    m_sonOuverture.setBuffer(sonUn);
    m_sonFermeture.setBuffer(sonDeux);

    m_lieu.setFont(*myfont);
    m_lieu.setCharacterSize(20);
    m_lieu.setString("Lieu");
    m_lieu.setColor(sf::Color::Black);

    m_Temps.setFont(*myfont);
    m_Temps.setCharacterSize(20);
    m_Temps.setString("Temps: Heures:Minutes:Secondes");
    m_Temps.setColor(sf::Color::Black);

    m_forcePers.setFont(*myfont);
    m_forcePers.setCharacterSize(20);
    m_forcePers.setString("Force");
    m_endurPers.setFont(*myfont);
    m_endurPers.setCharacterSize(20);
    m_endurPers.setString("Endurance");


    m_tempsAnimation = 0.5;
}

void PanneauActif::calculDuree(Timer &temps)
{
    m_Temps.setString("Temps:" + ConvIntString(temps.getElapsedTime() / 3600) + "h:" + ConvIntString((int)(temps.getElapsedTime() / 60) % 60) + "m:" + ConvIntString((int)temps.getElapsedTime() % 60)+"sec");
}
