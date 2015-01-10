

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "constantes.hpp"
#include "ressourceholder.hpp"
#include "element.hpp"
#include "carte.hpp"

using namespace std;

void Carte::creationBase()
{
    sf::Image   m_imageCarte;
    sf::Image   m_imageTile;

    if(!m_imageTile.loadFromFile("Data/Default/Tiles/Tile.png"))    std::cout<<"Impossible d'ouvrir Tile.png"<<std::endl;

    m_imageCarte.create (m_tailleCote * LARGEUR_TILE, m_tailleCote * HAUTEUR_TILE); //creation du support en memoire où blitter les tiles.

    for(unsigned int j=0; j<m_tailleCote; j++)
    {
        for(unsigned int i=0; i<m_tailleCote; i++)
        {
            m_imageCarte.copy(m_imageTile, (DEMI_LTILE * i - DEMI_LTILE* j) + ((LARGEUR_TILE * m_tailleCote ) / 2) - DEMI_LTILE  ,DEMI_HTILE * i + DEMI_HTILE * j,sf::IntRect(0, 0, 0, 0),true); //Copie des tiles sur le support,
        }
    }

    m_textureBase = new sf::Texture();
    m_base = new sf::Sprite();
    m_textureBase->loadFromImage(m_imageCarte); //on envoie le support
    m_base->setTexture(*m_textureBase);//sous forme de texture au sprite representant la carte d'un bloc

    m_base->setPosition(-int(m_tailleCote * LARGEUR_TILE) /2 , 0 ); // position arbitraire de la carte.


    m_textureBase->setSmooth(true);


}

void Carte::creerElement(RessourceHolder &rholder)
{
    m_ElementHolder.clear();
    for(unsigned int i= 0 ; i<m_tailleCote; i++)
    {
        for(unsigned int j  = 0 ; j<m_tailleCote; j++)
        {
            switch(m_tabElement[m_tailleCote*j + i ])
            {
            case CAISSE:

                m_ElementHolder.push_back(new Caisse(sf::Vector2f(i,j),&rholder));
                cout<<"element Caisse cree"<<endl;
                break;
            case MUR:
                m_ElementHolder.push_back(new Mur(sf::Vector2f(i,j),&rholder));
                cout<<"element Mur cree"<<endl;
                break;
            case OBJECTIF:
                m_ElementHolder.push_back(new Objectif(sf::Vector2f(i,j),&rholder));
                cout<<"element Objectif cree"<<endl;
                break;
            case DEPART:
                m_ElementHolder.push_back(new Depart(sf::Vector2f(i,j),&rholder));


                cout<<"element Caisse cree"<<endl;
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


Carte::Carte(std::string nom,int taille)
{
    m_nom = nom;
    m_tailleCote = taille;

    for(unsigned int i = 0; i<m_tailleCote *m_tailleCote; i++)

    {

        m_tabElement.push_back(RIEN);
    }


    m_packRessource = "Default";

    creationBase();

}






Carte::~Carte()
{
    for(unsigned int i; i< m_ElementHolder.size(); i++)
    {
        delete m_ElementHolder[i];
    }

    if(m_textureBase != nullptr) delete m_textureBase;
    if(m_base !=nullptr)           delete m_base;
    std::cout<<"carte detruite"<<std::endl;

}


bool Carte::sauvegarder()
{
    if(m_nom =="")
    {
        cerr<<"Erreur, Nom de carte inexistant";
        return false;
    }
    else if(m_nom.size() >300)
    {
        cerr<<"erreur, nom de carte trop long!";
        return false;
    }
    else
    {
        std::string chemin = "Cartes/" + m_nom + ".map";
        ofstream sauvegarde (chemin.c_str(), ios ::binary);
        if(!sauvegarde)
        {
            cerr<<"Erreur, Impossible de sauvegarder!"<<endl;
            return false;
        }
        else
        {
            sauvegarde.write ((char*)&m_tailleCote, sizeof (m_tailleCote));
            sauvegarde.write ((char*)m_nom.c_str(), sizeof (std::string));
            sauvegarde.write ((char*)m_packRessource.c_str(), sizeof(std::string));
            cout<<m_tabElement.size()<<endl;

            for(unsigned int i =0 ; i< m_tabElement.size(); i++)
            {
                sauvegarde.write((char*)&m_tabElement[i], sizeof (Type_element));
                //  cout<<m_tabElement[i]<<endl;

            }
            sauvegarde.close();
            return true;
        }
    }


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

            chargement.read ((char*)&m_tailleCote, sizeof (m_tailleCote));
            chargement.read ((char*)m_nom.c_str(), sizeof(std::string));
            chargement.read ((char*)m_packRessource.c_str(),sizeof(std::string));




            for(unsigned int i = 0; i<m_tailleCote *m_tailleCote; i++)

            {

                m_tabElement.push_back(RIEN);
            }


            for(unsigned int i =0 ; i< m_tabElement.size(); i++)
            {
                chargement.read((char*)&m_tabElement[i], sizeof (Type_element));
                // cout<<m_tabElement[i]<<endl;



            }

            cout<<"nom de la carte: " <<m_nom<<endl;
            cout<<"nom du pack de ressource: "<<m_packRessource<<endl;
            chargement.close();

        }
    }


    creationBase();
    return true;
}



void Carte::ajouterElement(sf::Vector2f position,Type_element element,RessourceHolder &rholder)
{

    if(m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] == element)
    {

    }
    else if(m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] != RIEN)
    {
        supprimerElement(position);

    }

    if(m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] == RIEN)
    {
        unsigned int i = 0;
        bool continu = true;
        switch(element)
        {
        case CAISSE:
            m_ElementHolder.push_back(new Caisse(position,&rholder));
            m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] = element;
            break;
        case MUR:
            m_ElementHolder.push_back(new Mur(position,&rholder));
            m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] = element;
            break;
        case OBJECTIF:
            m_ElementHolder.push_back(new Objectif(position,&rholder));
            m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] = element;
            break;
        case DEPART:
            do
            {
                if(m_ElementHolder.size()>0)
                {
                    if(m_ElementHolder[i]->getType() == DEPART)
                    {
                        supprimerElement(m_ElementHolder[i]->getPosition());
                        continu =false;
                    }
                }
                i++;
            }
            while(continu && i<m_ElementHolder.size());

            m_ElementHolder.push_back(new Depart(position,&rholder));
            m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] = element;
            break;
        case RIEN:
            if(  m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)]  != RIEN)
            {
                supprimerElement(position);
            }
            break;
        }
    }

    //m_tabElement[(m_tailleCote * int(position.y ))+ int(position.x)] = element->getType();
}


void Carte::supprimerElement(sf::Vector2f position)
{
//    cout<<aSupprimer<<endl;
    // m_tabElement[m_tailleCote * int(m_ElementHolder[aSupprimer]->getPosition().y) + int(m_ElementHolder[aSupprimer]->getPosition().x)] = RIEN;
    bool continuer = true;
    unsigned int i = 0;
    do
    {

        if(m_ElementHolder[i]->getPosition() == position)
        {
            Element* elm =m_ElementHolder[i];
            m_ElementHolder[i] = m_ElementHolder.back(); //on inverse l'element a supprimer avec le dernier du vecteur
            m_ElementHolder[m_ElementHolder.size() - 1 ] = elm;
            delete elm;//on supprime l'element de la memoire.
            m_ElementHolder.pop_back(); // et on le retire proprement
            m_tabElement[m_tailleCote *position.y + position.x] = RIEN;
            continuer = false;
        }
        i++;

    }
    while(continuer && i< m_ElementHolder.size());

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


