//accessoire.cpp


//jimoniak

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

#include "accessoire.hpp"


#include <typeinfo>


using namespace std;

Item::Item()
{
    m_cheminAcces = "Items/";
    m_cheminIcone = "Ressources/Icons/";

}
Item::~Item()
{
//std::cout<< "l'objet "<< m_nom << " qui " << m_description<< " pouvant être stocké en pile de " << m_quantiteMax<< " a correctement été supprimé." << std::endl;


}

void Item::afficher(gameWindow &fenetre)
{
    fenetre.draw(iconeSp);
}

void Item::chargementObjet()//fonction completer par les class fille avec le principe de Demasquage.
{
    string analyse="";
    ifstream fichier(m_cheminAcces.c_str(),ios::in);
    if(!fichier)
    {
        cout << "impossible de charger: " << m_cheminAcces << endl;
    }
    else
    {
        while(analyse != "END" && analyse!= m_nom)
        {
            getline(fichier,analyse);

        }

        if(analyse == m_nom)
        {
            getline(fichier,m_Icone);
            getline(fichier,m_description);
            getline(fichier, analyse);
            m_quantiteMax=ConvertionStringInt(analyse);
            getline(fichier,m_propriete);
        }
    }

}


Consommable::Consommable() {}
Consommable::~Consommable() {}

Equipable::Equipable() {}
Equipable::~Equipable() {}


Potion::Potion(std::string nom)
{
    m_nom= nom;


    this->chargementObjet();

}

Potion::~Potion() {}

Arme::Arme() {}
Arme::~Arme() {}


Arme::Arme(std::string nom)
{
    m_nom=nom;

    this->chargementObjet();
}


void Arme::utiliser(GameData &g,Inventaire &inv)  //utiliser dans le sens équiper
{
    g.Joueur.ChangerArme(this);
    g.Joueur.ajouterForce(m_Degat);
    //cout<< "arme Equipe" <<endl;
}

void Item::setPosition(sf::Vector2f newValue)
{
    iconeSp.setPosition(newValue);
}

string Item::getDescript()
{
    return m_description;
}




void Potion::chargementObjet()
{
    string decoupe="";
    int j=0;
    string tableauV[2];

    m_cheminAcces += "Potions.itm";
    m_cheminIcone += "Potions/";


    Item::chargementObjet();              //demasquage fonction Item::chargementObjet()

    if(!iconeIm.loadFromFile(m_cheminIcone + m_Icone))
    {
        cout<< "probleme: " << m_cheminIcone + m_Icone  << " introuvable!!!" << endl;
    }
    iconeSp.setTexture(iconeIm);

    for(unsigned int i= 1 ; i< m_propriete.size(); i++)
    {
        if(m_propriete[i] == ',' ||m_propriete[i] == '}')
        {
            tableauV[j]=decoupe;
            j++;
            decoupe="";
        }
        else   decoupe +=m_propriete[i];

    }

    m_Soin = ConvertionStringInt(tableauV[0]);
    m_Energie = ConvertionStringInt(tableauV[1]);

    //cout<< m_Soin << "   " << m_Energie <<endl;
}

void Arme::chargementObjet()
{

    string decoupe="";
    int j=0;
    string tableauV[1];

    m_cheminAcces += "Armes.itm";
    m_cheminIcone += "Armes/";


    Item::chargementObjet();              //demasquage fonction Item::chargementObjet()

    if(!iconeIm.loadFromFile(m_cheminIcone + m_Icone))
    {
        cout<< "probleme: " << m_cheminIcone + m_Icone  << " introuvable!!!" << endl;
    }
    iconeSp.setTexture(iconeIm);

    for(unsigned int i= 1 ; i< m_propriete.size(); i++)
    {
        if(m_propriete[i] == ',' || m_propriete[i] == '}')
        {
            tableauV[j]=decoupe;
            j++;
            decoupe="";
        }
        else   decoupe +=m_propriete[i];

    }

    m_Degat = ConvertionStringInt(tableauV[0]);



}
void Potion::utiliser(GameData &g,Inventaire &inv)
{
    string regain = ConvIntString(m_Soin) + " Points de vie et " + ConvIntString(m_Energie) +" points d'energie";
    if( m_Soin != 0  && m_Energie == 0)
    {

        if(g.Joueur.getVie() != g.Joueur. getMaxVie())
        {
            g.Joueur.Soigner(m_Soin);
            inv.RetireQuantite(1);
            g.Messager.OuvrirMessage(string("Potion Utilise! Regain de : " + regain),g);
        }

    }
    else if( m_Energie != 0 && m_Soin == 0)
    {

        if(g.Joueur.getEnergie() != g.Joueur.getMaxEnergie())
        {
            g.Joueur.Energie(m_Energie);
            inv.RetireQuantite(1);
            g.Messager.OuvrirMessage(string("Potion Utilise! Regain de : " + regain),g);

        }

    }
    else if( m_Soin != 0  && m_Energie != 0)
    {
        bool potionUtilise = false;

        if(g.Joueur.getVie() != g.Joueur. getMaxVie())
        {
            g.Joueur.Soigner(m_Soin);
            potionUtilise = true;
        }

        if(g.Joueur.getEnergie() != g.Joueur.getMaxEnergie())
        {
            g.Joueur.Energie(m_Energie);
            potionUtilise = true;
        }

        if(  potionUtilise)
        {

            inv.RetireQuantite(1);

            g.Messager.OuvrirMessage(string("Potion Utilise! Regain de : " + regain),g);
        }

    }



}

Vetement::Vetement() {}
Vetement::~Vetement() {}
void Vetement::chargementObjet()
{
    m_cheminAcces += "Vetements.itm";
    m_cheminIcone += "Vetements/";
    string tableauV[1];
    string decoupe="";
    int j=0;
    Item::chargementObjet();

    if(!iconeIm.loadFromFile(m_cheminIcone + m_Icone))
    {
        cout<< "probleme: " << m_cheminIcone + m_Icone  << " introuvable!!!" << endl;
    }
    iconeSp.setTexture(iconeIm);


    for(unsigned int i= 1 ; i< m_propriete.size(); i++)
    {
        if(m_propriete[i] == ',' ||m_propriete[i] == '}')
        {
            tableauV[j]=decoupe;
            j++;
            decoupe="";

        }
        else   decoupe +=m_propriete[i];

    }

    m_protection = ConvertionStringInt(tableauV[0]);






}

int Vetement::getProtection()
{
    return m_protection;

}

int Casque::getProtection()
{
    return m_protection;

}

Casque::~Casque() {}
Casque::Casque() {}
Casque::Casque(string nom)
{
    m_nom= nom;
    this->chargementObjet(); //appel de la version VEtement::chargementObjet();
}
void Casque::utiliser(GameData &g,Inventaire &inv)
{
    g.Joueur.ChangerCasque(this);
    g.Joueur.ajouterEndurance(m_protection);
}

Torse::~Torse() {}
Torse::Torse() {}
Torse::Torse(string nom)
{
    m_nom= nom;
    this->chargementObjet();
}
void Torse::utiliser(GameData &g,Inventaire &inv)
{
    g.Joueur.ChangerTorse(this);
    g.Joueur.ajouterEndurance(m_protection);
}

Gant::~Gant() {}
Gant::Gant() {}
Gant::Gant(string nom)
{
    m_nom= nom;
    this->chargementObjet();
}
void Gant::utiliser(GameData &g,Inventaire &inv)
{
    g.Joueur.ChangerGant(this);
    g.Joueur.ajouterEndurance(m_protection);
}

Jambiere::~Jambiere() {}
Jambiere::Jambiere() {}
Jambiere::Jambiere(string nom)
{
    m_nom= nom;
    this->chargementObjet();
}
void Jambiere::utiliser(GameData &g,Inventaire &inv)
{
    g.Joueur.ChangerJambiere(this);
    g.Joueur.ajouterEndurance(m_protection);
}

Chaussure::~Chaussure() {}
Chaussure::Chaussure() {}
Chaussure::Chaussure(string nom)
{
    m_nom= nom;
    this->chargementObjet();
}
void Chaussure::utiliser(GameData &g,Inventaire &inv)
{
    g.Joueur.ChangerChaussure(this);
    g.Joueur.ajouterEndurance(m_protection);

}

