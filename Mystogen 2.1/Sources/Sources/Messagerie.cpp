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
using namespace sf;
using namespace std;

Messagerie::Messagerie()
{

    m_texte.setCharacterSize(20);
    m_texte.setColor(Color(0,0,0,255));
    m_fondSP.setColor(Color(255,255,255,150));
    m_texte.setString("Pas De Message");
    m_fondIM.loadFromFile("Ressources/Pannel/Pannel.png");
    m_fondSP.setTexture(m_fondIM);

}


void Messagerie::InitialiserFont(GameData &g)
{
    m_texte.setFont(g.font);
}
void Messagerie::setPosition(sf::Vector2f newValue)
{
    m_position = Vector2f(newValue.x,newValue.y + 400);
    m_position.x = newValue.x + (LFENETRE -m_fondIM.getSize().x) / 2 ;
    m_position.y = newValue.y + (HFENETRE  - m_fondIM.getSize().y);

    m_texte.setPosition(Vector2f(m_position.x +350 , m_position.y +40));
    m_fondSP.setPosition(m_position);
    m_interlocuteurSP.setPosition(m_position.x +175,m_position.y +25);
}

void Messagerie::MiseEnPage(string messageAFormater)
{
    string transformation = messageAFormater;
    string messageDecoupe="";
    int j = 0 ;
    int k = 0;

    for(unsigned int i=0 ; i< transformation.size() ; i++)
    {
        if(transformation[i] == '\n')
        {
            j=0;
        }
        if(j==65) // hachage du message en ligne de 65 caractères.
        {
            if((transformation[i] != ' ' && transformation[i-1] != ' ' )|| transformation[i] != ' ' )//puis hachage au mot prés.
            {
                j=0;
                for(k = messageDecoupe.size() ; messageDecoupe[k] != ' ' ; k--)  //Si a l'endroit du hachage , il y a un caractere autre q'un espace et que le caractere precedent est également différent d'un espace.
                {
                    messageDecoupe[k]='\0'; //on revient en arriere sur la chaine jusqu'a trouver un espace
                    j++;
                }
                messageDecoupe[k] = '\n'; //on insere le saut de ligne dans la chaine
                i -= (j- 1);
                j=0;
            }
            else
            {
                messageDecoupe += '\n';
                j=0;
            }
        }
        messageDecoupe +=transformation[i];//puis on ecrit le caractere suivant.
        j++;
    }
    m_texte.setString(messageDecoupe);

}

void Messagerie::OuvrirMessage(std::string messageAfficher,sf::Image*Interlocuteur,GameData &g)
{
    g.general.Stop();
    m_sansFace = false;
    if (!Interlocuteur) cout <<"Texture NULL" <<endl;
    m_interlocuteurIM.loadFromImage(*Interlocuteur);
    m_interlocuteurSP.setTexture(m_interlocuteurIM);
    MiseEnPage(messageAfficher);


    g.nouveauMessage = true;

    Image Capture;
    Texture capture;
    Capture = g.Fenetre->capture();
    capture.loadFromImage(Capture);
    capture.setSmooth(0);

    Sprite BackgR;
    BackgR.setTexture(capture);
    BackgR.setPosition(g.Camera.getCenter().x-LFENETRE /2 , g.Camera.getCenter().y -HFENETRE/2);
    Event event;
    while(g.nouveauMessage)  // Attend l'appui sur E avant de fermer le message
    {

        g.Fenetre->clear();
        g.Fenetre->draw(BackgR);
        g.Messager.Afficher(*g.Fenetre);


        while (g.Fenetre->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                g.Fenetre->close();
                exit(EXIT_SUCCESS);
            }

            if(event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::E)
                {
                    if(g.nouveauMessage)
                    {
                        g.nouveauMessage = false;
                        g.general.ReStart();
                    }
                }

            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(g.nouveauMessage)
            {
                g.nouveauMessage = false;
                g.general.ReStart();
            }
        }
        g.Fenetre->display();
    }


}



void Messagerie::OuvrirMessage(std::string messageAfficher,GameData &g)
{

    g.general.Stop();
    m_sansFace = true;
    MiseEnPage(messageAfficher);
    g.nouveauMessage = true;

    Image Capture;
    Texture capture;
    Capture = g.Fenetre->capture();
    capture.loadFromImage(Capture);

    cout<<"Texture enregistre"<<endl;
    capture.setSmooth(1);

    Sprite BackgR;
    BackgR.setTexture(capture);
    BackgR.setPosition(g.Camera.getCenter().x-LFENETRE /2  , g.Camera.getCenter().y -HFENETRE/2);

    while(g.nouveauMessage)  // Attend l'appui sur E avant de fermer le message
    {

        g.Fenetre->clear();
        g.Fenetre->draw(BackgR);
        g.Messager.Afficher(*g.Fenetre);


        while (g.Fenetre->pollEvent(g.event))
        {
            if (g.event.type == sf::Event::Closed)
            {
                g.Fenetre->close();
                exit(EXIT_SUCCESS);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if(g.nouveauMessage)
            {
                g.nouveauMessage = false;
                g.general.ReStart();
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(g.nouveauMessage)
            {
                g.nouveauMessage = false;
                g.general.ReStart();
            }
        }
        g.Fenetre->display();

    }

}


void Messagerie::OuvrirMessageSansInteraction(std::string messageAfficher,GameData &g)
{

    g.general.Stop();
    m_sansFace = true;
    MiseEnPage(messageAfficher);

    g.nouveauMessage = true;

    Image Capture;
    Texture capture;
    Capture = g.Fenetre->capture();
    capture.loadFromImage(Capture);
    cout<<"Texture enregistre"<<endl;
    capture.setSmooth(1);

    Sprite BackgR;
    BackgR.setTexture(capture);
    BackgR.setPosition(g.Camera.getCenter().x-LFENETRE /2  , g.Camera.getCenter().y -HFENETRE/2);


    g.Fenetre->clear();
    g.Fenetre->draw(BackgR);
    g.Messager.Afficher(*g.Fenetre);
    g.Fenetre->display();
}

void Messagerie::Afficher(gameWindow &fenetre)
{

    fenetre.draw(m_fondSP);
    if(!m_sansFace)fenetre.draw(m_interlocuteurSP);
    fenetre.draw(m_texte);
}


Messagerie::~Messagerie()
{}
