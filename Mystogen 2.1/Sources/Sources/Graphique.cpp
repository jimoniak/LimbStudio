#include "constantes.hpp"

#include "gameWindow.hpp"
#include "Randomizer.hpp"

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



using namespace std;
using namespace sf;






Barregraphique::Barregraphique()
{}

/*Barregraphique::Barregraphique(std::string ImgUn,std::string ImgDeux,std::string param,int valeur,int valMax,std::string font,int alpha1,int alpha2)//constructeur pour créer des barre a partir d'Texture.
{
     m_BarreFond.setColor(sf::Color(255,255,255,alpha1));
     m_BarreDessus.setColor(sf::Color(255,255,255,alpha2));
    if(!m_TextureDessous.loadFromFile(ImgUn)){cout<< "Ressource impossible à charger:" << ImgUn << endl;}
    if(!m_TextureDessus.loadFromFile(ImgDeux)){cout<< "Ressource impossible à charger:" << ImgDeux << endl;}
    if(!m_Police.loadFromFile(font)) cout << "Police Impossible à ouvrir" << font << endl;
    m_BarreFond.setTexture(m_TextureDessous);
    m_BarreDessus.setTexture(m_TextureDessus);
    m_ValeurParam=valeur;
    m_ValeurMaxParam = valMax;
    m_parametre.setString(param);
    m_decalage.x = m_decalage.y = 0;



    }*/

Barregraphique::Barregraphique(std::string param,int valeur,int valMax,Vector2f dimension,sf::Vector2f position,sf::Color c1,sf::Color c2)
{
    m_ValeurParam=valeur;
    m_ValeurMaxParam = valMax;

    m_prefixe=param;

    m_Dimension = dimension;
    m_dessous.setSize(dimension);
    m_dessus.setSize(sf::Vector2f(dimension.x-10,dimension.y - 10));

    m_dessous.setFillColor(c1);
    m_dessus.setFillColor(c2);

    m_dessous.setPosition(position);
    m_dessus.setPosition(sf::Vector2f(position.x+5,position.y+5));


    setDecalage();

    m_centrage=false;




}


void Barregraphique::ChargementPolice(sf::Font *font,int taille)
{
    m_Police=*font;
    m_parametre.setFont(m_Police);
    m_parametre.setCharacterSize(taille);
}

void Barregraphique::setDecalage()
{

    Vector2f DimBarreFond,DimBarreDes;
    DimBarreFond = m_dessous.getSize();
    DimBarreDes = m_dessus.getSize();



    m_decalage.x=(DimBarreFond.x - DimBarreDes.x) / 2;
    m_decalage.y=(DimBarreFond.y - DimBarreDes.y) / 2;


}


void Barregraphique::setParamText(int taille,Color couleur)
{
    m_parametre.setCharacterSize(taille);
    m_parametre.setColor(couleur);

}

void Barregraphique::setImgUn(std::string ressource)
{
    if(!m_TextureDessous.loadFromFile(ressource)) cout<<"Impossible de charger:"<<ressource<<endl;
}

void Barregraphique::setImgDeux(std::string ressource)
{
    if(!m_TextureDessus.loadFromFile(ressource)) cout<<"Impossible de charger:"<<ressource<<endl;
}

void Barregraphique::setPolice(sf::Font NewValue)
{
    m_Police = NewValue;
}


void Barregraphique::setPosition(sf::Vector2f NewValue)
{
    m_Position=NewValue;
    //setDecalage();
    /*m_BarreFond.setPosition(m_Position);
    m_BarreDessus.setPosition(m_Position.x+m_decalage.x,m_Position.y + m_decalage.y);*/
    setDecalage();
    m_dessous.setPosition(m_Position);
    if(!m_centrage)m_dessus.setPosition(m_Position.x+5/*+m_decalage.x*/,m_Position.y + m_decalage.y);
    else           m_dessus.setPosition(m_Position.x+m_decalage.x,m_Position.y + m_decalage.y);
    m_parametre.setPosition(m_Position.x + m_Dimension.x / 2 , m_Position.y +m_decalage.y);



}


void Barregraphique::setPosition(float X,float Y)
{
    m_Position.x=X;
    m_Position.y=Y;
    setDecalage();
    m_dessous.setPosition(m_Position);
    if(!m_centrage)m_dessus.setPosition(m_Position.x,m_Position.y + m_decalage.y);
    else               m_dessus.setPosition(m_Position.x+m_decalage.x,m_Position.y + m_decalage.y);
    m_parametre.setPosition(m_Position.x + m_Dimension.x / 2 , m_Position.y +m_decalage.y);

}

void Barregraphique::setSize(sf::Vector2f NewValue)
{
    m_Dimension = NewValue;
    m_dessus.scale(m_Dimension);

}
void Barregraphique::setSize(float X,float Y)
{
    m_Dimension.x=X;
    m_Dimension.y=Y;
}
void Barregraphique::setColor(sf::Color Color1,sf::Color Color2)
{
    m_BarreFond.setColor(Color1);
    m_BarreDessus.setColor(Color2);
}


void Barregraphique::MajParametre(int newValuePar)
{
    m_ValeurParam=newValuePar;

    int resultat = ((newValuePar * 100)/m_ValeurMaxParam);
    float pourcentage = (resultat*1.0) / 100;

    m_dessus.setSize(sf::Vector2f((m_Dimension.x-10) * pourcentage ,m_Dimension.y - m_decalage.y*2));
    m_parametre.setString(m_prefixe + ConvIntString(newValuePar) + "/" + ConvIntString(m_ValeurMaxParam));

}

void Barregraphique::AfficherBarre(gameWindow &fenetre)
{
    fenetre.draw(m_dessous);
    if(m_ValeurParam>=0)fenetre.draw(m_dessus);
    fenetre.draw(m_parametre);

}


//-----------------------Particule------------------------------------------------------------------------------

Particule::Particule()
{
    m_active = true;
    m_vie = 255;
    m_perteVie= Randomizer::Random(50,150);
    m_couleur= Color(Randomizer::Random(0,255),Randomizer::Random(0,255),Randomizer::Random(0,255),m_vie);
    m_apparence.setSize(sf::Vector2f(3,3));
    m_apparence.setFillColor(m_couleur);
    m_direction.x=Randomizer::Random(-5.f,5.f);
    m_direction.y=Randomizer::Random(-5.f,5.f);
    m_position.x = m_position.y = 0;
    m_posDep= m_position;

    m_apparence.setPosition(m_posDep);


}

Particule::Particule(int vieDep,sf::Color couleur,sf::Vector2f position,int perteVie,sf::Vector2f EndrDirX,sf::Vector2f EndrDirY,sf::Vector2f dim)
{
    m_active =false;
    m_vie=vieDep;
    m_perteVie= perteVie ;
    m_couleur= couleur;
    m_position = m_posDep = position;


    m_apparence.setSize(dim);

    m_apparence.setFillColor(m_couleur);
    m_apparence.setPosition(m_posDep);

    m_encadrDirX = EndrDirX;
    m_encadrDirY = EndrDirY;

    m_direction.x= Randomizer::Random(m_encadrDirX.x,m_encadrDirX.y);
    m_direction.y= Randomizer::Random(m_encadrDirY.x,m_encadrDirY.y);

    typeParticule=1;

}
Particule::~Particule()
{
}



//methode

void Particule::setDir(sf::Vector2f DirX,sf::Vector2f DirY)
{

    m_encadrDirX= DirX;
    m_encadrDirY=DirY;

}

void Particule::setPosDep(sf::Vector2f newValues)
{

    m_posDep= newValues;

}

void Particule::deplacerParticule()
{

    m_vie-=m_perteVie;
    m_couleur.a=m_vie;
    m_position.x += m_direction.x * 0.08;
    m_position.y += m_direction.y * 0.08;

    m_apparence.setFillColor(m_couleur);
    m_apparence.setPosition(m_position);




    if(m_vie<=0)
    {

        m_active=true;
        m_vie = Randomizer::Random(50,255);
        m_couleur.a= m_vie;
        m_apparence.setPosition(m_posDep);
        m_position=m_posDep;

    }



}

void Particule::afficher(gameWindow &fenetre)
{
    if(m_active)
    {
        fenetre.draw(m_apparence);
    }
}

//-------------------------------------generateur

generateur::generateur(int nombrePart,sf::Vector2f pos,sf::Vector2f encadrDirX,sf::Vector2f encadrDirY, sf::Vector2f encadrPerte, sf::Vector2f encadreVie,sf::Color couleur,sf::Vector2f dim)
{
    m_nombreParticule=nombrePart; //le generateur possede un nombre de particule
    m_position=pos; // il a une position
    m_endrDirX=encadrDirX;
    m_endrDirY=encadrDirY;
    m_tempsDisp= 0;

    for(int i=0; i<m_nombreParticule; i++)
    {


        m_vie=Randomizer::Random(encadreVie.x,encadreVie.y);//une vie de depart (comprise entre 0 et 255)
        m_perteVie=Randomizer::Random(encadrPerte.x,encadrPerte.y);//Une perte de vie par deplacement.

        m_direction.x = Randomizer::Random(encadrDirX.x,encadrDirX.y);//une direction suivant x
        m_direction.y = Randomizer::Random(encadrDirY.x,encadrDirY.y);//puis une direction suivant y

        /* m_particle.push_back(particule());
         m_particle[i].active=false;
         m_particle[i].apparence.Resize(dim);
         m_particle[i].apparence.setPosition(m_position);
         m_particle[i].couleur=couleur;
         m_particle[i].apparence.setColor(couleur);
         m_particle[i].vie=m_vie;
         m_particle[i].perteVie=m_perteVie;
         m_particle[i].direction= m_direction;
          */

        m_particule.push_back(Particule(m_vie,couleur, m_position, m_perteVie, m_endrDirX, m_endrDirY,dim)); //on ajoute une particule au tableau par tour de boucle.


    }

}


generateur::~generateur()
{
}




void generateur::deplacerParticule(Timer &temps)
{

    if(temps.getElapsedTime() - m_tempsDisp > 0.05)//on regule la vitesse des particules
    {
        m_tempsDisp=temps.getElapsedTime();//on actualise tempsDisp pour la condtition ci dessus
        for(int i=0; i<m_nombreParticule; i++)
        {
            m_particule[i].deplacerParticule();//appel de la methode permettant de faire evoluer la particule



            /* m_particle[i].vie-=m_particle[i].perteVie;
             m_particle[i].couleur.a=m_particle[i].vie;
             m_particle[i].position.x += m_particle[i].direction.x * 0.08;
             m_particle[i].position.y += m_particle[i].direction.y * 0.08;

             m_particle[i].apparence.setColor(m_particle[i].couleur);
             m_particle[i].apparence.setPosition(m_particle[i].position);
             cout<<m_particle[1].vie<<endl;




             if(m_particle[i].vie<=0)
             {

             m_particle[i].active=true;
             m_particle[i].vie = Randomizer::Random(50,255);
             m_particle[i].couleur.a= m_particle[i].vie;
             m_particle[i].apparence.setPosition(m_position);
             m_particle[i].position=m_position;

             }*/


        }
    }

}


void generateur::deplacergenerateur(sf::Vector2f newValue)
{
    m_position = newValue;

}
void generateur::afficherParticule(gameWindow &fenetre)
{
    for(int i=0; i<m_nombreParticule; i++)
    {
        m_particule[i].afficher(fenetre);
    }

}

void generateur::reset()
{
    m_actif=false;
}
