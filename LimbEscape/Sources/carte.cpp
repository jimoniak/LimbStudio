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
#include <fstream>
#include <vector>
#include <memory>

#include "constantes.h"

#include "element.hpp"

#include "carte.hpp"



using namespace std;

void Carte::creationBase(RessourceHolder *rholder)
{
    sf::Image   m_imageCarte;
    sf::Image   m_imageTile;
    sf::Image  m_TileBasD;
    sf::Image m_TileBasG;

   // if(!m_imageTile.loadFromFile("Data/RessourcesPack/"+ m_packRessource + "/Tile.png"))    std::cout<<"Impossible d'ouvrir Tile.png"<<std::endl;
    m_imageTile = rholder->getTextureElem(RIEN).copyToImage();
    m_TileBasG = rholder->getTextureElem(5).copyToImage();
    m_TileBasD = rholder->getTextureElem(6).copyToImage();
    m_imageCarte.create ((m_tailleCote+1) * LARGEUR_TILE, (m_tailleCote+1) * HAUTEUR_TILE); //creation du support en memoire où blitter les tiles.
    m_imageCarte.createMaskFromColor(sf::Color::Black);

  /*  for(unsigned int i = 0 ; i< m_tailleCote;i++)
    {
        unsigned int j = m_tailleCote - 1 ;
        m_imageCarte.copy(m_TileBasG, (DEMI_LTILE * i - DEMI_LTILE* (j+1)) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * i + DEMI_HTILE * (j+1),sf::IntRect(0, 0, 0, 0),true);

    }

     for(unsigned int j = 0 ; j< m_tailleCote;j++)
    {
        unsigned int i = m_tailleCote - 1 ;
        m_imageCarte.copy(m_TileBasD, (DEMI_LTILE * (i+1) - DEMI_LTILE* j) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * (i+1) + DEMI_HTILE * j,sf::IntRect(0, 0, 0, 0),true);
    }*/

    for(unsigned int j=0; j<m_tailleCote; j++)
    {
        for(unsigned int i=0; i<m_tailleCote; i++)
        {
            m_imageCarte.copy(m_imageTile, (DEMI_LTILE * i - DEMI_LTILE* j) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * i + DEMI_HTILE * j,sf::IntRect(0, 0, 0, 0),true); //Copie des tiles sur le support,
            if(j == m_tailleCote - 1 ) m_imageCarte.copy(m_TileBasG, (DEMI_LTILE * i - DEMI_LTILE* (j+1)) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * i + DEMI_HTILE * (j+1),sf::IntRect(0, 0, 0, 0),true);
             if(i == m_tailleCote - 1 ) m_imageCarte.copy(m_TileBasD, (DEMI_LTILE * (i+1) - DEMI_LTILE* j) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * (i+1) + DEMI_HTILE * j,sf::IntRect(0, 0, 0, 0),true);
        }



    }

    m_textureBase = new sf::Texture();
    m_base = new sf::Sprite();
    m_textureBase->loadFromImage(m_imageCarte); //on envoie le support
    m_base->setTexture(*m_textureBase);//sous forme de texture au sprite representant la carte d'un bloc

    m_base->setPosition(-int(m_tailleCote * LARGEUR_TILE) /2 , 0 ); // position arbitraire de la carte.


    m_textureBase->setSmooth(true);


}

void Carte::assembler(RessourceHolder *rholder)
{
    creationBase(rholder);
    m_ElementHolder.clear();
    for(unsigned int i= 0 ; i<m_tailleCote; i++)
    {
        for(unsigned int j  = 0 ; j<m_tailleCote; j++)
        {
            switch(m_tabElement[m_tailleCote*j + i ])
            {
            case CAISSE:
                m_ElementHolder.push_back(new Caisse(sf::Vector2f(i,j),rholder));
                break;
            case MUR:
                m_ElementHolder.push_back(new Mur(sf::Vector2f(i,j),rholder));
                break;
            case OBJECTIF:
                m_ElementHolder.push_back(new Objectif(sf::Vector2f(i,j),rholder));
                break;
            case DEPART:
                m_ElementHolder.push_back(new Depart(sf::Vector2f(i,j),rholder));
                break;
            case RIEN:
                break;
            default:
                break;
            }

        }

    }

}



Carte::Carte()
{
    m_nom = "default";
    m_packRessource="Default";
     m_textureBase=nullptr;
     m_base=nullptr;


}





Carte::~Carte()
{
    for(unsigned int i=0; i< m_ElementHolder.size(); i++)
    {
      m_ElementHolder[i] = nullptr;
    }

    m_ElementHolder.clear();
   // rholder =nullptr;

    if(m_textureBase != nullptr) delete m_textureBase;
    if(m_base !=nullptr)           delete m_base;

    m_tabElement.clear();
    std::cout<<"carte detruite"<<std::endl;

}



bool Carte::charger(std::string const &nom)
{

    if(nom =="")
    {
        cerr<<"Erreur, Nom de carte inexistant";
        return false;
    }
    else if(nom.size() >300)
    {
        cerr<<"erreur, nom de carte trop long!";
        return false;
    }
    else
    {
        std::string chemin = "Cartes/" + nom  + ".map";
        ifstream chargement(chemin.c_str(), ios ::binary);

        if(!chargement)
        {
            cerr<<"Erreur, Impossible de charger "<<nom<<"!"<<endl;
            return false;
        }
        else
        {

            int taillestring;
            int taille2;
            chargement.read ((char*)&m_tailleCote, sizeof (m_tailleCote));
            chargement.read((char*)&taillestring,sizeof(int));
            m_nom.resize(taillestring);
            chargement.read ((char*)m_nom.c_str(), taillestring);

            chargement.read((char*)&taille2,sizeof(int));
            m_packRessource.resize(taille2);
            chargement.read ((char*)m_packRessource.c_str(),taille2);
            for(unsigned int i = 0; i<m_tailleCote *m_tailleCote; i++)
            {
                m_tabElement.push_back(RIEN);
            }
            for(unsigned int i =0 ; i< m_tabElement.size(); i++)
            {
                chargement.read((char*)&m_tabElement[i], sizeof (Type_element));
            }
            cout<<"nom de la carte: " <<m_nom<<endl;
            cout<<"nom du pack de ressource: "<<m_packRessource<<endl;


           // rholder = new RessourceHolder(m_packRessource);
            chargement.close();
          //  return true;

        }
    }

    return true;
}



sf::Sprite Carte::getSprElem(int element)
{

    return m_ElementHolder[element]->getApparence();

}



sf::Sprite Carte::getSprCarte()
{
    return *m_base;
}



std::string Carte::getNom()
{
    return m_nom;

}

int Carte::getTaille()
{
    return m_tailleCote;
}


std::string Carte::getPackRessource()
{
    return m_packRessource;
}


std::vector<Element*> Carte::getElementHolder()
{
    return m_ElementHolder;
}


