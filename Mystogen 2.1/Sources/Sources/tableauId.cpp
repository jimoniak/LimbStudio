//-------------------------------tableauId.cpp
//-----------Tableau de conversion pour changer les chaine de caractere en Id tile.


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
#include <ios>

using namespace std;
using namespace sf;




/*============================================
=========Chargement de Tous les Tiles=========
============================================*/

void ChargeTexture(sf::Image image[],sf::Texture texture[])
{
    string nomDeLaTexture;                               // Création d'un tableau de char
    for(int i=0; i<TAILLETABID; i++) // Pour tous les Tiles/Textures
    {
        string numero = ConvertionIntString (i);
        nomDeLaTexture = "Ressources/Tiles/" + numero + ".png";
        image[i].loadFromFile(nomDeLaTexture);

        image[i].createMaskFromColor(sf::Color(0, 0, 0));

        texture[i].loadFromImage(image[i]);
        texture[i].setSmooth(0);

    }
}

/*==========================================
==========Chargement d'un seul Tile=========
===========================================*/
void ChargeMonoTexture(sf::Image image[],sf::Texture texture[],string n)
{
    int a = ConvertionStringInt(n);
    if (image[a].getSize().x == 0)
    {
        string nomDeLaTexture;
        nomDeLaTexture = "Ressources/Tiles/" + n + ".png";
        image[a].loadFromFile(nomDeLaTexture);
        texture[a].setSmooth(0);
        image[a].createMaskFromColor(sf::Color(0, 0, 0));
        texture[a].loadFromImage(image[a]);
        if (DEBUg) cout << "Image " << a << " chargee." << endl;
    }
}




/*==========================================
======="Renvoi" le X et Y d'une carte=======
==========================================*/

void  LireTailleCarte(string Nom,int *x,int *y)
{
    string NomComplet="Cartes/"+Nom+".wld";         // Recompose le chemin relatif de la carte

    ifstream lecture(NomComplet.c_str(),ios::in);
    if(!lecture)    cout<<"Erreur dans la fonction void LireTailleCarte()"<<endl;
    else
    {
        int n=0;
        getline(lecture,NomComplet);
        n = (NomComplet[2] - 48) * 1000 + (NomComplet[3] - 48) * 100 + (NomComplet[4] - 48) * 10 + NomComplet[5] - 48;
        *x = n;
        getline(lecture,NomComplet);
        n = (NomComplet[2] - 48) * 1000 + (NomComplet[3] - 48) * 100 + (NomComplet[4] - 48) * 10 + NomComplet[5] - 48;
        *y = n;
    }
}

/*==========================================
======= Transforme un string en Int ========
==========================================*/

int  ConvertionStringInt ( std::string chaine )
{
    int t = chaine.size();
    int n = 0;
    for(int i = 0; i < t ; i++) n+= ( chaine[i] - 48 ) * pow(10.f,t-i-1) ;
    return n;

}

/*========================================================
======= Transforme un int en string de 4 chiffres ========
========================================================*/

string ConvertionIntString(int nb)
{
    string chaine="0000";

    if(nb<10) chaine= "000" + ConvIntString(nb);
    else if(nb<100) chaine= "00" + ConvIntString(nb);
    else if(nb<1000) chaine= "0" + ConvIntString(nb);
    else if(nb<10000) chaine=  ConvIntString(nb);

    return chaine.c_str();
}


string ConvertionFltString(float nombre )
{
    ostringstream os;
    os << nombre;
    return os.str();

}

string ConvIntString(int nombre)
{
    ostringstream os;
    os << nombre;
    return os.str();

}

int ConvStringInt(string chaine)
{
    int I;
    istringstream ss;
    ss.str(chaine);
    ss >> I;
    return I;

}

float ConvertionStringFlt(string m)
{
    float f ;
    istringstream ss;
    ss.str(m);
    ss >> f;
    return f;
}



void LireNombreElement(std::string nomCarte , int *n)
{
    string ligneLue;
    string cheminAcces = "Elements/"+nomCarte+".elm";
    int nombreElement = 0;

    ifstream Elm(cheminAcces.c_str(),ios::in);
    if(!Elm && DEBUg)    cout << "impossible de charger: " << cheminAcces << endl;
    else
    {
        while(ligneLue != "EOF")
        {
            getline(Elm,ligneLue);
            if(ligneLue == "$") nombreElement++;
        }
    }
    *n = nombreElement;
}




void LireInterrupteur(int tabInter[])
{
    string ligneLue = "";
    int i;
    ifstream file ("Interrupteur.itr");
    if(!file)   cout << "Fichier Interrupteur.itr introuvable !" << endl;

    else
    {
        for (i = 1 ; i < NOMBRE_INTERRUPTEUR ; i++)
        {
            getline ( file , ligneLue);
            tabInter[i] = ConvertionStringInt(ligneLue);
        }
    }
}


int Cameraman (GameData &g)
{
    sf::Vector2f CCamera = g.Joueur.getPosImg();

    if (!g.petitX)
    {
        if (CCamera.x - g.HalfSize.x < 0) CCamera.x = g.HalfSize.x ;
        if (CCamera.x + g.HalfSize.x > LTILE * g.X) CCamera.x = LTILE * g.X - g.HalfSize.x ;
    }
    else
        CCamera.x = g.X * LTILE / 2;

    if (!g.petitY)
    {
        if (CCamera.y - g.HalfSize.y < 0) CCamera.y = g.HalfSize.y ;
        if (CCamera.y + g.HalfSize.y > HTILE * g.Y) CCamera.y = HTILE * g.Y - g.HalfSize.y ;
    }
    else
        CCamera.y = g.Y * HTILE / 2;

    g.Camera.setCenter(CCamera);
    return 1;

}


void LoadElement(GameData &g)
{
    g.n = 0;
    LireNombreElement(g.nomCarteACharger,&g.n);
    g.Elm.resize(g.n);
    for (int i = 0 ; i < g.n ; i++)
        g.Elm[i].Chargement(i,g.nomCarteACharger);

    g.MusiqueDeFond.changerMusique(&g.nomCarteACharger);
    g.MusiqueDeFond.chargerMusique();

}

// Récupère le i-eme morceau de string de la string s entre deux séparateurs
std::string StringNum(std::string s,unsigned int i , char separateur)
{
    unsigned int pos = 0;
    for (unsigned int j = 0 ; j < i ; j++)  pos = s.find(separateur,pos) + 1;
    return s.substr(pos,s.find(separateur,pos)-pos);
}

void Presentation(gameWindow &fenetre, GameData &g)//Fonction qui presente la SFML ainsi que le Studio.
{

    sf::Text TextPasse;

    TextPasse.setFont(g.font);
    TextPasse.setCharacterSize(15);                      //texte qui indique la commande à utiliser pour passer
    TextPasse.setColor(Color::White);
    TextPasse.setPosition(20,HFENETRE -50);
    TextPasse.setString("Appuyer sur E pour passer...");

    sf::Text Presente;
    Presente.setFont(g.font);
    Presente.setCharacterSize(30);                      //texte qui indique la commande à utiliser pour passer
    Presente.setColor(Color::Blue);
    Presente.setString("Présente...");
    Presente.setPosition(LFENETRE /2 - (Presente.getLocalBounds().width / 2 ) ,HFENETRE /  2 - Presente.getLocalBounds().height/2);




    sf::Texture JinnIm;               //Logo  Studio
    sf::Texture sfmlIm;
    if(!JinnIm.loadFromFile("Jinn.png")) cout<< "Logo non chargé!" <<endl;
    if(!sfmlIm.loadFromFile("sfml.png")) cout<< "Logo non chargé!" <<endl;
    sf::Sprite JinnSp;
    sf::Sprite sfmlSp;      //Logo SFML
    // JinnSp.setColor(sf::Color(255,255,255,0));
    JinnSp.setTexture(JinnIm);
    JinnSp.setPosition((LFENETRE - JinnIm.getSize().x) / 2 ,(HFENETRE - JinnIm.getSize().y) / 2 );

    sfmlSp.setColor(sf::Color(255,255,255,0));
    sfmlSp.setTexture(sfmlIm);
    sfmlSp.setPosition((LFENETRE - sfmlIm.getSize().x) / 2 ,(HFENETRE - sfmlIm.getSize().y) / 2 );


    sf::Clock temps;
    float tempsDep = temps.getElapsedTime().asSeconds();
    float tempsatt= 0;

    while(temps.getElapsedTime().asSeconds() - tempsDep < 5 && fenetre.isOpen())  //Boucle pour la SFML
    {
        if(temps.getElapsedTime().asSeconds() - tempsDep < 1)
        {
            sfmlSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep) * 255)));//On fait apparaitre le Logo
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 1  && temps.getElapsedTime().asSeconds() - tempsDep < 3)
        {
            sfmlSp.setColor(sf::Color(255,255,255,255)); //on garde le logo afficher un certain temps
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 3  && temps.getElapsedTime().asSeconds() - tempsDep < 4)
        {
            sfmlSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep + 3)) * 255)))); //on fait disparaitre le logo
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds())))); //on change la transparence du texte de commande selon un sinus
        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01)
        {
            fenetre.clear();
            fenetre.draw(sfmlSp);
            fenetre.draw(TextPasse);   //affichage...
            fenetre.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }


        while (fenetre.pollEvent(g.event))
        {
            if (g.event.type == sf::Event::Closed)
            {
                g.m_SonMenu.play();
                fenetre.close();
            }
            else
            {
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))   return;
    }

    temps.restart();  //on reset le temps
    tempsDep = temps.getElapsedTime().asSeconds();//on reactualise la pos de depart du temsp
    tempsatt= 0; //temps pour l'affichage.


    while(temps.getElapsedTime().asSeconds() - tempsDep < 5 && fenetre.isOpen())  //Même procéder pour le Logo
    {
        if(temps.getElapsedTime().asSeconds() - tempsDep < 1)
        {
            JinnSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep) * 255)));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 1  && temps.getElapsedTime().asSeconds() - tempsDep < 4)
        {
            JinnSp.setColor(sf::Color(255,255,255,255));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 4  && temps.getElapsedTime().asSeconds() - tempsDep < 5)
        {
            JinnSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep + 4)) * 255))));
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));
        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01)
        {
            fenetre.clear();
            fenetre.draw(JinnSp);
            fenetre.draw(TextPasse);
            //fenetre.draw(Presente);
            fenetre.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }

        while (fenetre.pollEvent(g.event))
        {
            if (g.event.type == sf::Event::Closed)
            {
                g.m_SonMenu.play();
                fenetre.close();
            }
            else
            {
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))   return;

    }


    temps.restart();  //on reset le temps
    tempsDep = temps.getElapsedTime().asSeconds();//on reactualise la pos de depart du temsp
    tempsatt= 0; //temps pour l'affichage.


    while(temps.getElapsedTime().asSeconds() - tempsDep < 5 && fenetre.isOpen())  //Même procéder pour le Logo
    {
        if(temps.getElapsedTime().asSeconds() - tempsDep < 1)
        {
            Presente.setColor(sf::Color(0,0,255, ((temps.getElapsedTime().asSeconds() - tempsDep) * 255)));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 1  && temps.getElapsedTime().asSeconds() - tempsDep < 4)
        {
            Presente.setColor(sf::Color(0,0,255,255));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep > 4  && temps.getElapsedTime().asSeconds() - tempsDep < 5)
        {
            Presente.setColor(sf::Color(0,0,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep + 4)) * 255))));
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));
        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01)
        {
            fenetre.clear();
            fenetre.draw(Presente);
            fenetre.draw(TextPasse);
            fenetre.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }

        while (fenetre.pollEvent(g.event))
        {
            if (g.event.type == sf::Event::Closed)
            {
                g.m_SonMenu.play();
                fenetre.close();
            }
            else
            {
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))   return;

    }




}
