
#include "SFML/Graphics.hpp"
#include "constantes.h"
#include <iostream>

#include "ressourceholder.hpp"


RessourceHolder::RessourceHolder()// Par default
{
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[0].loadFromFile("Data/RessourcesPack/Default/Elements/Caisse.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[1].loadFromFile("Data/RessourcesPack/Default/Elements/Mur.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[2].loadFromFile("Data/RessourcesPack/Default/Elements/Objectif.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[3].loadFromFile("Data/RessourcesPack/Default/Elements/Depart.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[4].loadFromFile("Data/RessourcesPack/Default/Tiles/Tile.png");
   // std::cout<<"Ressources holder Ok"<<std::endl;

}


RessourceHolder::RessourceHolder(std::string nomPack) //Charge un pack particulier.
{
    m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[0].loadFromFile("Data/RessourcesPack/"+nomPack+"/Elements/Caisse.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
    m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[1].loadFromFile("Data/RessourcesPack/"+nomPack+"/Elements/Mur.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
    m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[2].loadFromFile("Data/RessourcesPack/"+nomPack+"/Elements/Objectif.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
    m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[3].loadFromFile("Data/RessourcesPack/"+nomPack+"/Elements/Depart.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
    m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[4].loadFromFile("Data/RessourcesPack/"+nomPack+"/Tiles/Tile.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
     m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[5].loadFromFile("Data/RessourcesPack/"+nomPack+"/Tiles/TileBasG.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;
     m_tableTexture.push_back( sf::Texture());
    if(!m_tableTexture[6].loadFromFile("Data/RessourcesPack/"+nomPack+"/Tiles/TileBasD.png")) std::cerr<<"Erreur chargement ressource" <<std::endl;

    for(unsigned int i =0 ;i< m_tableTexture.size() ;i++)
    {
        m_tableTexture[i].setSmooth(true);

    }

    //std::cout<<"Ressources holder Ok"<<std::endl;
}

RessourceHolder::~RessourceHolder() {}

void RessourceHolder::nettoyer()
{
    m_tableTexture.clear();
}



sf::Texture RessourceHolder::getTextureElem(int element) //envoyer une enum
{

    //std::cout<<element<<std::endl;
    if(element>m_tableTexture.size() || element<0) {std::cout<<"Erreur avec le numero envoye a ElementHolder" <<std::endl;
    return m_tableTexture[0];}
    else
    {
        return m_tableTexture[element];
    }

}





