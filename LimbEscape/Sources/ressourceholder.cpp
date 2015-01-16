
#include "SFML/Graphics.hpp"
#include "constantes.h"
#include <iostream>

#include "ressourceholder.hpp"


RessourceHolder::RessourceHolder()
{
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[0].loadFromFile("Data/Default/Elements/Caisse.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[1].loadFromFile("Data/Default/Elements/Mur.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[2].loadFromFile("Data/Default/Elements/Objectif.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[3].loadFromFile("Data/Default/Tiles/Depart.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[4].loadFromFile("Data/Default/Tiles/Tile.png");
   // std::cout<<"Ressources holder Ok"<<std::endl;

}


RessourceHolder::RessourceHolder(std::string nomPack)
{
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[0].loadFromFile("Data/"+nomPack+"/Elements/Caisse.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[1].loadFromFile("Data/"+nomPack+"/Elements/Mur.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[2].loadFromFile("Data/"+nomPack+"/Elements/Objectif.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[3].loadFromFile("Data/"+nomPack+"/Tiles/Depart.png");
    m_tableTexture.push_back( sf::Texture());
    m_tableTexture[4].loadFromFile("Data/"+nomPack+"/Tiles/Tile.png");

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
    if(element>5 || element<0)  std::cout<<"Erreur avec le numero envoye a ElementHolder" <<std::endl;
    else
    {
        return m_tableTexture[element];
    }
}





