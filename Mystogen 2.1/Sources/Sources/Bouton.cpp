
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



Bouton::Bouton() :
    m_pos(0,0),
    m_dim(32,32),
    m_dessous(sf::Vector2f(m_dim.x,m_dim.y)),
    m_ellipse(0),
    m_rayon(sqrt(m_dim.x*m_dim.x+m_dim.y*m_dim.y)/2.0)
{}

Bouton::Bouton(sf::Vector2f dim,bool ell) :
    m_dim(dim),
    m_ellipse(ell),
    m_rayon(sqrt(m_dim.x*m_dim.x+m_dim.y*m_dim.y)/2.0)
{}


Bouton::Bouton(sf::Vector2f pos,sf::Vector2f dim,bool ell) :
    m_pos(pos),m_dim(dim),
    m_ellipse(ell), m_rayon(sqrt(m_dim.x*m_dim.x+m_dim.y*m_dim.y)/2.0)
{
    m_dessous.setPosition(pos);
}


Bouton::Bouton(float x , float y , float l , float h ,bool ell) :
    m_pos(x,y),
    m_dim(l,h),
    m_dessous(sf::Vector2f(m_dim.x,m_dim.y)),
    m_ellipse(ell),
    m_rayon(sqrt(m_dim.x*m_dim.x+m_dim.y*m_dim.y)/2.0)
{
}


void Bouton::setPosition(sf::Vector2f newValue)
{
    m_pos =sf::Vector2f(newValue.x ,newValue.y);
    m_txt.setPosition(m_pos ) ;
    m_dessous.setPosition(newValue.x + m_dim.x/4 ,newValue.y+m_dim.y/4);
}

void Bouton::setDimFromTexture()
{
    m_dim.x = m_dessous.getSize().x;
    m_dim.y = m_dessous.getSize().y;

}


void Bouton::setSprite(sf::Texture& img)
{
    m_dessous.setTexture(&img);
    m_surbrillance.setTexture(&img);
    m_surbrillance.setFillColor(sf::Color(255,255,255,100));
    m_dessous.setOrigin(m_dessous.getSize().x/2,m_dessous.getSize().y/2);
    m_surbrillance.setOrigin(m_dessous.getSize().x/2,m_dessous.getSize().y/2);
    m_dessous.setPosition(m_pos);
    m_surbrillance.setPosition(m_pos);
}

void Bouton::setStringPos(sf::Vector2f pos)
{
    m_txt.setPosition(pos);
}


void Bouton::setMaskTransparence(int newTransparence)
{
    m_masqueSprite.setColor(sf::Color(255,255,255,newTransparence));
}


void Bouton::setTxt(std::string txt , sf::Font& font , sf::Color couleur , int size)
{
    m_txt.setString(txt);
    m_txt.setFont(font);
    m_txt.setCharacterSize(size);
    m_txt.setColor(couleur);
    m_txt.setPosition(m_pos);
    m_txt.setOrigin(m_txt.getLocalBounds().width/2.0-2,m_txt.getLocalBounds().height/2.0+2);

    if (m_txt.getLocalBounds().width > m_dim.x)
    {
        float coef = m_txt.getLocalBounds().width*1.25 / m_dim.x ;
        for(float i = 1 ; i < coef ; i++)
            txt.insert(txt.size() *(1/(coef/i)), "\n");
        size++;
        do
        {
            size--;
            m_txt.setCharacterSize(size);
            m_txt.setString(txt);
            m_txt.setOrigin(m_txt.getLocalBounds().width/2.0,m_txt.getLocalBounds().height/2.0);
        }
        while(m_txt.getLocalBounds().height > m_dim.y);
    }

}

void Bouton::setString(std::string newText)
{
    m_txt.setString(newText);
    m_txt.setOrigin(m_txt.getLocalBounds().width/2.0-2,m_txt.getLocalBounds().height/2.0+2);
}


void Bouton::setFont(sf::Font &font)
{
    m_txt.setFont(font);
}
void Bouton::setSizeText(int size)
{
    m_txt.setCharacterSize(size);
}
void Bouton::setColorText(sf::Color Couleur)
{
    m_txt.setColor(Couleur);
}
void Bouton::setTransparence(int newTransparence)
{
//    m_apparence.setColor(sf::Color(255,255,255,newTransparence));
}

/*
void Bouton::setMask(sf::Color clr,bool degrade) // DANgER !! MATHEMATIQUES !!!!!
{
    m_masqueDegrade = degrade;
    m_dessous.setFillColor(clr);

    sf::Color Vide(0,0,0,0);

    float dx = m_dim.x/2;
    float dy = m_dim.y/2;

    float xx = m_dim.x*m_dim.x;
    float yy = m_dim.y*m_dim.y;

    float coef = yy / xx;
    float yySur4 = yy/4;

    for(int i = -dx ; i < dx ; i++)
    {
        float ii = i*i;
        float iicoef = ii*coef;
        for(int j = -dy ; j < dy ; j++)
        {
            int d = sqrt(ii+j*j);

            if(m_ellipse)
            {
                if(iicoef+j*j <= yySur4)
                {
                    if(m_masqueDegrade)
                        m_dessous.setFillColor(sf::Color(m_dessous.getFillColor().r,m_dessous.getFillColor().g,m_dessous.getFillColor().b,(128*(1-d/m_rayon))));
//                    m_masqueTexture.setPixel(i + dx,j + dy,m_dessous);
                }
                // else
                //m_masqueTexture.setPixel(i + dx,j + dy,Vide);
            }
            else
            {
                if(m_masqueDegrade)
                    m_dessous.setFillColor(sf::Color(m_dessous.getFillColor().r,m_dessous.getFillColor().g,m_dessous.getFillColor().b,(128*(1-d/m_rayon))));
                // m_masqueTexture.setPixel(i + dx,j + dy,m_dessous);
            }
        }
    }

    m_dessous.setTexture(&m_masqueText);
    m_dessous.setFillColor(clr);
    m_dessous.setOrigin(m_dessous.getSize().x/2 , m_dessous.getSize().y/2);
    m_dessous.setPosition(m_pos);

    m_masqueON = 1;
}
*/


void Bouton::setTexture(std::string chemin,int alpha)
{
    if(!m_masqueText.loadFromFile(chemin))	std::cout<<"impossible de charger l'Texture "<< chemin <<std::endl;

    m_dessous.setTexture(&m_masqueText);
    m_surbrillance.setTexture(&m_masqueText);
    m_surbrillance.setFillColor(sf::Color(255,255,255,100));
    m_dessous.setOrigin(m_dessous.getSize().x/2,m_dessous.getSize().y/2);
    m_surbrillance.setOrigin(m_dessous.getSize().x/2,m_dessous.getSize().y/2);
    m_dessous.setPosition(m_pos);
    m_surbrillance.setPosition(m_pos);

}


void Bouton::Affichage(gameWindow &App , float angle , float zoom)
{
    if(angle) m_dessous.rotate(angle);
    if(zoom)  m_dessous.setScale(zoom,zoom);
   	App.draw(m_dessous);

    if(EstDessus(sf::Mouse::getPosition(App).x,sf::Mouse::getPosition(App).y)) App.draw(m_surbrillance);

    App.draw(m_txt);
}


bool Bouton::Affichage2(gameWindow &App,float xs , float ys)
{
    bool b = 0;

        App.draw(m_dessous);

        if( EstDessus(xs,ys))
        {
            b = 1;
            App.draw(m_surbrillance);
        }
        App.draw(m_txt);

    return b;
}



bool Bouton::ClicInventaire(sf::Event &Ev,float x,float y)
{

    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(EstDessus(x,y)) return 1;
    }
    return 0;
}


bool Bouton::Clic(sf::Vector2i positionSouris)
{

    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(EstDessus(positionSouris.x,positionSouris.y)) return 1;
    }

    return 0;
}


bool Bouton::EstDessus(float x , float y)
{
    x -= m_pos.x;
    y -= m_pos.y;

    if(m_ellipse == 0) // Rectangle
    {
        if(x <= m_dim.x/2)
        {
            if(x >= -m_dim.x/2)
            {
                if(y <= m_dim.y/2)
                {
                    if(y >= -m_dim.y/2)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    else if(m_ellipse)
    {
        if(x * x * m_dim.y*m_dim.y / (m_dim.x*m_dim.x) + y * y <= m_dim.y*m_dim.y/4)
            return 1;
    }

    return 0;
}

sf::Vector2f Bouton::getPos()
{
    return m_pos;
}

void Bouton::setPos(sf::Vector2f v)
{
    m_pos=v;
    m_dessous.setPosition(m_pos);
    m_surbrillance.setPosition(m_pos);
    m_txt.setPosition(m_pos);

}

void Bouton::setEllipse(bool ell)
{
    m_ellipse = ell;
}

/*
std::string Bouton::EventTxt(gameWindow &App , sf::Font& police , sf::Color couleur, int size )
{

    std::string txt;
    sf::Event event;
    sf::Image fond(App.capture());
    sf::Texture textureFond;
    textureFond.loadFromImage(fond);
    sf::Sprite fd(textureFond);

    sf::Color OldColor = m_dessous.getFillColor();
    bool WasDegradeON = m_masqueDegrade;

    setMask(sf::Color::Black,0);

    while (event.key.code != 278)
    {
        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                App.close();
                return txt;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code != 278 && event.key.code != 279 && event.key.code != 277)
                    txt += event.key.code;
                else if(event.key.code == 279 && txt.size()) txt.resize(txt.size()-1);
                else if(event.key.code == 277) txt += " ";

                setTxt(txt,police,couleur);
                App.draw(fd);
                Affichage(App);
                App.display();
            }
        }
    }
    setMask(OldColor,WasDegradeON);

    return txt;

}*/

Bouton::~Bouton() {};

