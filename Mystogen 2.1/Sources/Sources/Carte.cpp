
//Carte.cpp---------------------------------------------
#include <stdlib.h>
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
#include <iostream>
#include <fstream>

#include "Randomizer.hpp"
#include <ctime>


using namespace std;
using namespace sf;

Carte::Carte() {}; //constructeur par defaut (que l'on n'utilisera jamais ...)


Carte::Carte(std::string nomCarte,int Tx,int Ty,Timer &temps) :
    m_nom(nomCarte),
    m_tailleX(Tx),
    m_tailleY(Ty),

    m_totalcoord(Tx * Ty),
    m_totalcaractere(Tx*4),
    m_place1(Tx * Ty,Sprite()),
    m_place2(Tx * Ty,Sprite()),
    m_place3(Tx * Ty,Sprite()),
    m_place4(Tx * Ty,Sprite()),
    m_place5(Tx * Ty,Sprite()),
    m_typecouche1(Tx * Ty,"0000"),
    m_typecouche2(Tx * Ty,"0000"),
    m_typecouche3(Tx * Ty,"0000"),
    m_typecouche4(Tx * Ty,"0000"),
    m_typecouche5(Tx * Ty,"0000")

{

    m_nombregenerateur=0;

    if((Ty*LTILE)<100)
        m_nuage=false;

    else
    {
        m_nuage= true;
        m_posDep.x=0;
        m_posDep.y=0;


        m_cloud1.loadFromFile("Ressources/obj/cloud2.png");
        m_cloud2.loadFromFile("Ressources/obj/cloud.png");
        m_cloud3.loadFromFile("Ressources/obj/Cloud3.png");

        CalculCloud(Ty,temps);


    }
    testnuage();
    chargegenerateur();



}//constructeur à appeler systematiquement dès la création d'un objet Carte.


void Carte::TransformerCoucheTexture(sf::Image tab[]) //permet de crée un SF::Texture à de la carte
{

    int X,Y;
    for(int i = 0 ; i< 5 ; i++)
    {
        imageDeCouche[i].create (m_tailleX * LTILE, m_tailleY * HTILE,Color(255, 0, 0, 255)); // on crée les Textures des couches au dimension de la carte
        // imageDeCouche[i].setSmooth(0);//on veux un decor net.
    }


    for(int i=0; i<m_tailleY; i++)
    {
        Y=HTILE * i;

        for(int j=0; j<m_tailleX; j++)
        {
            X=LTILE * j;
            //[m_tailleX * i + j]
            string troncon = "0000" ;
            troncon = m_typecouche1[m_tailleX * i + j].c_str();
            imageDeCouche[0].copy(tab[ConvertionStringInt(troncon)],X,Y); //on copie l'Texture de telle tile au bon endroit sur l'Texture de la carte

            troncon = m_typecouche2[m_tailleX * i + j].c_str();
            imageDeCouche[1].copy(tab[ConvertionStringInt(troncon)],X,Y);

            troncon = m_typecouche3[m_tailleX * i + j].c_str();
            imageDeCouche[2].copy(tab[ConvertionStringInt(troncon)],X,Y);

            troncon = m_typecouche4[m_tailleX * i + j].c_str();
            imageDeCouche[3].copy(tab[ConvertionStringInt(troncon)],X,Y);

            troncon = m_typecouche5[m_tailleX * i + j].c_str();
            imageDeCouche[4].copy(tab[ConvertionStringInt(troncon)],X,Y);

        }

    }


    for(int i= 0; i< 5 ; i++)
    {
        m_TextureCouche[i].loadFromImage(imageDeCouche[i]);

        m_CoucheAffichable[i].setTexture(m_TextureCouche[i]);

    }



}



void Carte::chargementCouche(bool grille[],sf::Image image[],sf::Texture texture[])  // Méthode du cas général qui prendrai en paramêtres le numéro de la couche à chargé !
{
    string ligneLue;                            // Tableau permettant de charger la carte ligne par ligne
    string cheminAcces = "Cartes/"+m_nom+".wld";// Recompose le chemin d'accès à la carte
    string troncon = "0000";                     // Petit tableau récupérant les morceaux de cartes tile par tile

    ifstream carte(cheminAcces.c_str(),ios::in);//ouverture du fichier contenant les infos des tiles de la couche basse de la carte
    if(!carte)  cout << "impossible de charger: " << cheminAcces << endl;

    getline(carte,ligneLue);
    getline(carte,ligneLue);

    int numeroCouche , i , j;
    for(numeroCouche = 1 ; numeroCouche < 7 ; numeroCouche++ )
    {
        for(i=0 ; i < m_tailleY ; i++)
        {
            getline(carte,ligneLue);    // On saute une ligne pour que le contenu du fichier soit lisible
            getline(carte,ligneLue);    // On récupère toute la ligne dans ligneLue

            for(j=0 ; j < m_totalcaractere ; j+=4) // On avance j par coup de 4 car codage de forme : 012|
            {
                troncon[0] = ligneLue[j];              // On prend les 4 premiers caractères du bloc
                troncon[1] = ligneLue[j+1];
                troncon[2] = ligneLue[j+2];
                troncon[3] = ligneLue[j+3];

                ChargeMonoTexture(image,texture,troncon);

                if      (numeroCouche == 1)     m_typecouche1[m_tailleX * i + j / 4] = troncon;
                else if (numeroCouche == 2)     m_typecouche2[m_tailleX * i + j / 4] = troncon;
                else if (numeroCouche == 3)     m_typecouche3[m_tailleX * i + j / 4] = troncon;
                else if (numeroCouche == 4)     m_typecouche4[m_tailleX * i + j / 4] = troncon;
                else if (numeroCouche == 5)     m_typecouche5[m_tailleX * i + j / 4] = troncon;
                else if (numeroCouche == 6)     grille [m_tailleX * i + j / 4] = ConvertionStringInt(troncon);
            }
        }
        getline(carte,ligneLue);






    }
    if(DEBUg) cout << "La carte "  << cheminAcces << " a correctement ete chargee" << endl;
}



void Carte::afficherCouche(gameWindow &fenetre , int couche , sf::Vector2f CCamera)
{
    int jini = (int)((CCamera.y - HFENETRE/2)/32);
    int iini = (int)((CCamera.x - LFENETRE/2)/32);
    if (jini >= m_tailleY - HFENETRE/32)    jini = m_tailleY - HFENETRE/32 - 1;
    if (jini < 0)                           jini = 0;
    if (iini >= m_tailleX - LFENETRE/32)    iini = m_tailleX - LFENETRE/32;
    if (iini < 0)                           iini = 0;
    //if (DEBUg) cout << jini << " " << iini << endl;

    /* for(int j=jini ; j <= jini + HFENETRE/32 + 1 && j < m_tailleY ;j++)
     {   for(int i=iini ; i <= iini + LFENETRE/32 && i < m_tailleX ;i++)
         {
           int p = m_tailleX * j + i;*/


    //m_CoucheAffichable[couche-1].setSubRect(sf::IntRect(fenetre.getView().getRect().Left, fenetre.getView().getRect().Top,fenetre.getView().getRect().Left+LFENETRE, fenetre.getView().getRect().Top+HFENETRE));
    //m_CoucheAffichable[couche-1].setPosition(fenetre.getView().getRect().Left, fenetre.getView().getRect().Top);

    fenetre.draw(m_CoucheAffichable[couche-1]);
    // }
    // }

    if(m_nuage)
    {
        if(couche ==3)
        {
            for(unsigned int i = 0 ; i < (m_Cloud.size()); i++)
                m_Cloud[i].affichageOmbre(fenetre);

        }
        else if(couche == 5)
        {
            for(unsigned int i = 0 ; i < (m_Cloud.size()); i++)
                m_Cloud[i].affichageApparence(fenetre);
        }
    }

    if(couche==5)
    {
        for(int i =0 ; i< m_nombregenerateur; i++)
            m_generateurPart[i].afficherParticule(fenetre);
    }
}


void Carte::initialisePlaces()
{
    int X,Y;
    for(int i=0; i<m_tailleY; i++)
    {
        Y=HTILE * i;
        for(int j=0; j<m_tailleX; j++)
        {
            X=LTILE * j;
            m_place1[m_tailleX * i + j].setPosition(X,Y);
            m_place2[m_tailleX * i + j].setPosition(X,Y);
            m_place3[m_tailleX * i + j].setPosition(X,Y);
            m_place4[m_tailleX * i + j].setPosition(X,Y);
            m_place5[m_tailleX * i + j].setPosition(X,Y);
        }
    }
}


void Carte::convertisseurStrSprtCouche(Texture tab[])
{
    for(int i=0; i<m_totalcoord; i++)
    {

        string troncon = "0000" ;
        troncon = m_typecouche1[i].c_str();

        m_place1[i].setTexture(tab[ConvertionStringInt(troncon)]);

        troncon = m_typecouche2[i].c_str();
        m_place2[i].setTexture(tab[ConvertionStringInt(troncon)]);

        troncon = m_typecouche3[i].c_str();
        m_place3[i].setTexture(tab[ConvertionStringInt(troncon)]);

        troncon = m_typecouche4[i].c_str();
        m_place4[i].setTexture(tab[ConvertionStringInt(troncon)]);

        troncon = m_typecouche5[i].c_str();
        m_place5[i].setTexture(tab[ConvertionStringInt(troncon)]);
    }
}


string Carte::getNom()
{
    return m_nom;
}

void Carte::testnuage()
{

    //--------------------------------------------Si nuage ou non------------------------------------------------------------------------



    string ligneLue2;
    string Chemin2 = "Elements/"+m_nom+".elm";
    ifstream TestNuage(Chemin2.c_str(),ios::in);
    if(!TestNuage)  cout << "impossible de charger: " << m_nom <<".elm" << endl;
    getline(TestNuage, ligneLue2);
    while(ligneLue2 != "@" && ligneLue2 != "$" && ligneLue2 != "EOF")
        getline(TestNuage, ligneLue2);

    if(ligneLue2== "@")
    {
        getline(TestNuage, ligneLue2);
        getline(TestNuage, ligneLue2);

        if(ligneLue2 == "Nuage")  m_nuage = true;
        else if(ligneLue2 == "NoNuage") m_nuage = false;
        else    m_nuage= false;
    }
    else   m_nuage = false;


    //---------------------------------------------------------------------------------------------------------------------------------


}





void Carte::CalculCloud(int tailleY,Timer &temps)
{
    if(m_nuage)
    {

        for(int i=0; i< ((tailleY * LTILE)/100); i++)
        {
            m_Cloud.push_back(Cloud());

            m_posDep.y = i * 100;//on place un nuage tout les 100 pixel de hauteur
            m_posDep.x = ((rand() % (m_tailleX * 32))); //on positionne aleatoirement le nuage en x en étant sur qu'on ne sort pas de la carte

            int choixSprite = sf::Randomizer::Random(1,3);
            if(choixSprite ==1)
                m_Cloud[i]=Cloud(m_cloud1,sf::Randomizer::Random(0.25,1.f),m_posDep,sf::Randomizer::Random(0,1),temps); // on choisi une vitesse aleatoire ainsi qu'un sens aleatoire
            else if(choixSprite == 2)
                m_Cloud[i]=Cloud(m_cloud2,sf::Randomizer::Random(0.25, 1.f),m_posDep,sf::Randomizer::Random(0, 1),temps);
            else if(choixSprite == 3)
                m_Cloud[i]=Cloud(m_cloud3,sf::Randomizer::Random(0.25, 1.f),m_posDep,sf::Randomizer::Random(0, 1),temps);



        }
        //cout<< "size "<<m_Cloud.size()<<endl;
    }

}


void Carte::bougerCloud(Timer &temps)
{
    if(m_nuage)
    {
        for(unsigned int i = 0 ; i<m_Cloud.size() ; i++)
            m_Cloud[i].mouvement(temps,m_tailleX);  //on appel la fonction des objets Cloud
    }
}


void Carte::chargegenerateur() //methode contenant  l'algo d'analyse pour la création d'un generateur a partir du fichier elm.
{
    string ligneLue;
    string analyse;
    int comptDonnee=0;
    bool neg=false;
    int don[16];
    string Chemin = "Elements/"+m_nom+".elm";
    ifstream gene(Chemin.c_str(),ios::in);
    if(!gene)  cout << "impossible de charger: " << m_nom <<".elm" << endl;
    getline(gene, ligneLue);
    while(ligneLue != "~" && ligneLue != "$" && ligneLue != "EOF")  getline(gene, ligneLue);
    if(ligneLue == "~")
    {
        getline(gene, ligneLue);
        while(ligneLue!="%")
        {
            m_nombregenerateur++;
            for(unsigned int i=1; i< ligneLue.size(); i++)
            {
                if(ligneLue[i] != ',' && ligneLue[i] != '}')
                {
                    if(ligneLue[i]=='-')
                        neg=true;
                    else
                        analyse +=ligneLue[i];
                }
                else
                {
                    if(neg)
                    {
                        don[comptDonnee] = ConvertionStringInt(analyse.c_str());
                        don[comptDonnee] -= 2* don[comptDonnee];
                        comptDonnee++;
                        analyse="";
                        neg=false;
                    }
                    else
                    {
                        don[comptDonnee]=ConvertionStringInt(analyse.c_str());
                        comptDonnee++;
                        analyse="";
                    }
                }
            }
            m_generateurPart.push_back(generateur(don[0],Vector2f(don[1]* LTILE + LTILE/2,don[2]*HTILE +HTILE/2),
                                                  Vector2f((float)don[5],(float)don[6]),
                                                  Vector2f((float)don[7],(float)don[8]),
                                                  Vector2f((float)don[9],(float)don[10]),
                                                  Vector2f((float)don[3],(float)don[4]),
                                                  Color(don[11],don[12],don[13]),
                                                  Vector2f((float)don[14],(float)don[15])));
            getline(gene, ligneLue);
            comptDonnee=0;

        }
    }
}


void Carte::majgene(Timer &temps)
{
    for(int i=0; i< m_nombregenerateur; i++)
    {
        m_generateurPart[i].deplacerParticule(temps);
    }

}


Carte::~Carte()
{

    //std::cout<< "carte " << m_nom << " supprimée " <<std::endl;
}
