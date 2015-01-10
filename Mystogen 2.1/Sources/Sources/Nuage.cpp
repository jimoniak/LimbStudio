//---Jimoniak----------------

#ifndef DEFNUAgE
#define DEFNUAgE

#include "Classes.h"



using namespace sf;
using namespace std;




//------------------------------------------Class Cloud-----------------------------------------------------------------------



//constructeur
Cloud::Cloud()
{
    /*m_apparence.Resize(100,75);
    m_apparence.setColor(sf::Color(255,255,255,55));
    m_position.y=400;
    m_apparence.setPosition(200,400);
    m_vitesse= 1.0;
    m_tempsDebut = 0;

    m_sens=false;*/



}
Cloud::Cloud(sf::Texture &texture,float Vitesse,sf::Vector2f posDepart,bool sens,Timer &temps)
{
    m_apparence.setColor(sf::Color(255,255,255,128));

    m_apparence.setTexture(texture);
    m_apparence.setTextureRect(IntRect(0,0,texture.getSize().x,texture.getSize().y/2));
    m_ombre.setTexture(texture);
    m_ombre.setTextureRect(IntRect(0,texture.getSize().y/2,texture.getSize().x,texture.getSize().y));
    m_position=posDepart;
    m_positionOmbreY= posDepart.y + texture.getSize().y/2;

    m_apparence.setPosition(posDepart);
    m_ombre.setPosition(posDepart.x,m_positionOmbreY);
    m_vitesse= Vitesse;
    m_tempsDebut = temps.getElapsedTime();
    m_dimension = sf::Vector2f(texture.getSize());
    m_sens= sens;


    // if(m_sens) cout << "de gauche à droite" <<endl;
    //else       cout<<"de droite a gauche" << endl;

}

//setter
void  Cloud::setPosition(sf::Vector2f NewValue)
{
    m_apparence.setPosition(m_position);


}
void  Cloud::setX()
{

    m_apparence.setPosition(m_position.x,m_position.y);


}
void  Cloud::setDimension(sf::Vector2f NewValue) {}
void  Cloud::setVitesse(float NewValue) {}
void  Cloud::setTexture(sf::Texture Texture) {}

//getter
float  Cloud::getVitesse()
{
    return 0;
}
sf::Vector2f  Cloud::getDim()
{
    Vector2f v(0,0);
    return v;
}

sf::Vector2f  Cloud::getPosition()
{
    return m_position;
}


//methode

void  Cloud::mouvement(Timer &temps,int DimCarteX)

{
    if(m_sens)
    {
        if(m_position.x + m_dimension.x < (DimCarteX * LTILE) )
        {
            m_position.x=m_position.x + (m_vitesse * LTILE) * ( temps.getElapsedTime() - m_tempsDebut ) ;
            m_apparence.setPosition(m_position);
            m_ombre.setPosition(m_position.x,m_positionOmbreY);
            m_tempsDebut=temps.getElapsedTime();
        }
        else
        {

            changerSens(temps);

        }

    }
    else
    {
        if(m_position.x > 0)
        {
            if(m_position.x + m_dimension.x > (DimCarteX * LTILE))
            {
                m_position.x= DimCarteX * LTILE - m_dimension.x;
            }
            m_position.x = m_position.x - (m_vitesse * LTILE) * (temps.getElapsedTime() - m_tempsDebut);
            m_apparence.setPosition(m_position);
            m_ombre.setPosition(m_position.x,m_positionOmbreY);
            m_tempsDebut= temps.getElapsedTime();
        }
        else
        {
            changerSens(temps);
        }

    }





}



void  Cloud::affichageApparence(gameWindow &fenetre)
{
    fenetre.draw(m_apparence);
}
void  Cloud::affichageOmbre(gameWindow &fenetre)
{
    fenetre.draw(m_ombre);
}

void Cloud::changerSens(Timer &temps)
{
    if(m_sens) m_sens=false;
    else       m_sens=true;

    //m_tempsDebut= temps.getElapsedTime();

}






#endif
