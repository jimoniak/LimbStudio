// Element.cpp
/*======================================================
================= Element de Maps ======================
======================================================*/

// --- Zl --- Jimoniak ---
// Création :               31 / 10 / 2011   15H02


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
#include "Element.hpp"

#include <iostream>
#include <fstream>
#include <string.h>
#include "Randomizer.hpp"

using namespace std;
using namespace sf;


Element::Element() {};



void Element::Chargement(int numeroElement , string nomCarte)
{
    string ligneLue;
    m_carte = nomCarte;
    string cheminAcces = "Elements/"+m_carte+".elm";

    ifstream Elm(cheminAcces.c_str(),ios::in);
    if(!Elm)
        cout << "impossible de charger: " << cheminAcces << endl;
    else
    {

        for (int i = 0 ; i < numeroElement + 1; i++)
        {
            while(ligneLue != "$")
                getline(Elm,ligneLue);
            ligneLue = "";
        }

        getline(Elm,ligneLue);
        m_nom = ligneLue;

        getline(Elm,ligneLue);
        if (ligneLue != "")
        {
            m_image.loadFromFile(ligneLue);
            //m_image.setSmooth(0);
            m_image.createMaskFromColor(sf::Color(0, 0, 0));
            if(strstr(ligneLue.c_str(),"Characters"))   AddData(D,"imageMultiple",1);
        }
        else
        {
            m_image.loadFromFile("Ressources/Tiles/0000.png");
            // m_image.setSmooth(0);
            m_image.createMaskFromColor(sf::Color(0, 0, 0));
        }
        getline(Elm,ligneLue);
        if (ligneLue != "")
        {
            m_imageMes.loadFromFile(ligneLue);
            //m_imageMes.setSmooth(0);
            m_imageMes.createMaskFromColor(sf::Color(0, 0, 0));
            //if(strstr(ligneLue.c_str(),"Faceset"))   AddData(D,"AfficheMes",1);
        }
        else
        {
            m_imageMes.loadFromFile("Ressources/Face/FaceVide.png");
            //m_imageMes.setSmooth(0);
            m_imageMes.createMaskFromColor(sf::Color(0, 0, 0));
        }



        getline(Elm,ligneLue);
        m_interrupteur = ConvertionStringInt (ligneLue);

        m_numero = numeroElement;

        getline(Elm,ligneLue);
        m_X = ConvertionStringInt (ligneLue);

        getline(Elm,ligneLue);
        m_Y = ConvertionStringInt (ligneLue);

        m_apparence.setPosition(m_X*LTILE,m_Y*HTILE);
        m_texture.loadFromImage(m_image);
        m_apparence.setTexture(m_texture);
        if(DataExistante(D,"imageMultiple")) m_apparence.setTextureRect(sf::Rect<int> (0,0,m_texture.getSize().x/3,m_texture.getSize().y/4));

        getline(Elm,ligneLue);
        m_collision = ConvertionStringInt (ligneLue);

        int i = 0;
        while(ligneLue != "$" && ligneLue != "EOF")
        {
            getline(Elm,ligneLue);          // Stockage des instructions de l'élément
            m_instructions[i] = ligneLue;
            i++;
            //if(DEBUg) cout<< ligneLue <<endl;
        }
        m_instructions[i] = "µ";
        m_action=false;
        m_instruct=false;

        if (DEBUg) cout << "Element " << m_carte << " " << m_numero <<" Charge" << endl;

    }
}



void Element::Interaction(GameData &g)
{
    if (!g.Inter[m_interrupteur])
    {}
    else
    {
        if(1)                                           // Interaction 00 : Toujours vraie
        {
            Instruction(0,g);
        }

        int X = g.Joueur.getX();
        int Y = g.Joueur.getY();
        if( X == m_X  && Y == m_Y && !g.Joueur.getMouvement())                     // Interaction 01 : Pos Joueur = Pos Elm
        {
            Instruction(1,g);
        }

        int sens = g.Joueur.getSens();
        if (g.action)
        {
            if   ((sens == 4 && X - 1 == m_X && Y == m_Y )
                    ||(sens == 2 && X == m_X && m_Y == Y + 1 )
                    ||(sens == 6 && X + 1 == m_X && m_Y == Y )
                    ||(sens == 8 && X == m_X && m_Y == Y - 1 )
                    ||( X == m_X  && Y == m_Y ))
            {

                if(!m_instruct)//securité
                {

                    int direction(0);//dans le cas ou l'element est un PNJ (ou un element qui doit être réorienter)
                    switch(g.Joueur.getSens())//on réoriente le pnj a qui on parle
                    {

                    case 4:// Si on regarde a gauche,
                        direction=6;// on donne l'ordre au pnj de regarder à droite
                        break;
                    case 2:
                        direction=8;//etc...
                        break;
                    case 6:
                        direction=4;
                        break;
                    case 8:
                        direction=2;
                        break;

                    }



                    AddData(D,"Direction",direction);
                    StaticSubRectSelector(D,"Direction");//On change la zone de l'image a afficher
                    m_action = true;// Si on interagie avec l'element, on envoie a la fonction afficher le booleen
                    //  g.Fenetre->draw(m_apparence);
                    //cout<<direction<<endl;


                }
                if(m_instruct==true) //Voir passage a true dans la fonction Afficher.
                {
                    // Une fois afficher le pnj  on donne l'ordre de lancer les instructions concernant l'interaction avec l'element en question.
                    Instruction(2,g); // Interaction 02 : Le joueur a appuyer sur E devant l'élément
                    m_instruct=false;//Un fois l'interaction fini , on REset m_instruct
                }





            }


        }


    }
}





void Element::Instruction(int I,GameData &g) // I est le type d'interaction
{
    // Etape 1 : Trouver la ligne a laquelle correspond le début des instructions de valeur I

    int ligne = 0;
    int i = 0;

    for(ligne = 0; ligne < MAX_INSTRUCTION - 2 && i == 0; ligne++)
    {
        if(m_instructions[ligne] == "INT")
        {
            if(ConvertionStringInt(m_instructions[ligne+1]) == I)
                i = ligne + 1;
        }
        if(m_instructions[ligne] == "µ") return;
    }
    if (!i) return;

    int boucleDeCondition = 0;

    do
    {
        i++;
        if (m_instructions[i] == "DO")        boucleDeCondition++;       // Si on tombe sur DO , les instructions appartiennent à une condition , on les ignore ici
        else if (m_instructions[i] == "END")  boucleDeCondition--;       // On recommence à lire dès END qui termine les instructions a conditions
        else if (m_instructions[i] == "---" && !boucleDeCondition)
            MultiFonction (&m_instructions[i+1],g);
    }
    while(m_instructions[i] != "###");
}





void Element::Affichage(gameWindow &fenetre, int Inter[] , Timer &general)
{
    if (!Inter[m_interrupteur]) {}
    else
    {
        if(VData(D,"SeDeplace") > 0)
        {
            float TpsMove = VData(D,"TpsMove");
            int Direction = VData(D,"Direction");
            float TpsLastMove = VData(D,"TpsLastMove");

            if (TpsLastMove + TpsMove > general.getElapsedTime())
            {
                float t = (general.getElapsedTime() - TpsLastMove)/TpsMove;

                if(DataExistante(D,"imageMultiple"))
                {
                    int DecalageY = HTILE - m_texture.getSize().y/4;
                    int DecalageX = LTILE - m_image.getSize().x/3;

                    if (Direction == 2)         m_apparence.setPosition((m_X) * LTILE + DecalageX,((m_Y-1) + t) * HTILE  + DecalageY);//m_Y - 1 pour compenser le changement de position fait dans Multifonction => RandomMove
                    else if (Direction == 4)    m_apparence.setPosition(((m_X+1) - t) * LTILE + DecalageX, (m_Y ) * HTILE + DecalageY);//on effectue le même principe sur chaque direction
                    else if (Direction == 6)    m_apparence.setPosition(((m_X -1) + t) * LTILE + DecalageX, (m_Y ) * HTILE + DecalageY);
                    else if (Direction == 8)    m_apparence.setPosition((m_X) * LTILE + DecalageX,((m_Y+1) - t) * HTILE  + DecalageY);

                    m_apparence.setTextureRect(SubRectSelector(m_texture,Direction,t));
                }
            }
            else
            {
                AddData(D,"SeDeplace",0);//Changement de position directement dans la Mutlifonction "RandomMove" pour "reserver  la tile de la futur position de l'element( annule le bug de traverser du pnj)
                /*if (Direction == 2) m_Y++;
                else if (Direction == 4) m_X--;  // Directement dans RandomMove
                else if (Direction == 6) m_X++;
                else if (Direction == 8) m_Y--;*/
            }
        }
        else
        {

            if(m_action ==true)//Si on  a interagie , apres avoir afficher la réorientation du pnj
            {
                m_action =false;
                m_instruct=true;// on set une nouvelle variable que l'on renvoie a la fonction instruction de l'element.
            }
        }

        fenetre.draw(m_apparence);



    }
}


int Element::getX()
{
    return m_X;
}
int Element::getY()
{
    return m_Y;
}
int Element::getcollision()
{
    return m_collision;
}


Element::~Element()
{}





/*=========================================================================================================================================*/
/*============================================================= MultiFonction =============================================================*/
/*=========================================================================================================================================*/
/*========== Reconnait les Fonctions à appelées dans inst[0] , puis execute la Fonction avec les parametres des lignes suivantes ==========*/


void Element::MultiFonction (string inst[],GameData &g)
{
    // Conversion automatique des 4 premiers paramêtres en int
    int p1 = ConvertionStringInt (inst[1]);
    int p2 = ConvertionStringInt (inst[2]);
    int p3 = ConvertionStringInt (inst[3]);
    int p4 = ConvertionStringInt (inst[4]);

    // Reconnaissance des Fonctions , puis execution des fonctions

    if      (inst[0] == "Taille")   // TROIS paramêtres : grossissement X , grossissement Y , Durée avant Inversion
    {
        if (!DataExistante(D,"TailleFrame"))  AddData(D,"TailleFrame",0);
        int Frame = VData(D,"TailleFrame");
        if (Frame < 10*p3 && Frame >= 0)
        {
            m_apparence.setScale(1 + float(p1)/ 1000.0,1 + float(p2)/1000.0);
            Frame++;
        }
        if (Frame == 10*p3)
            Frame = -10*p3;
        if (Frame >= -10*p3 && Frame < 0)
        {
            m_apparence.setScale(1 - float(p1)/ 1000.0,1 - float(p2)/1000.0);
            Frame++;
        }
        AddData(D,"TailleFrame",Frame);
    }
    else if (inst[0] == "Tourne")   // UN param. : La vitesse de rotation
    {
        m_apparence.rotate(p1);
    }

    else if (inst[0] == "Message")  // QUATRE param. MAXIMUM : Ligne 1 , 2 , 3 et 4
    {
        string messageRecompose="";

        int ligne = 1;
        while(inst[ligne] != "###" && inst[ligne] != "---")
            ligne++;

//        sf::String message[ligne];

        for (int i=1; i < ligne ; i++)
        {
            messageRecompose+=inst[i];
            messageRecompose+= '\n';
        }

        //------------------------------------------------Code permettant d'actualiser le regard des pnj.
        g.Fenetre->clear();
        g.AdresseCarte->afficherCouche(*g.Fenetre , 1 , g.Joueur.getPosImg());
        g.AdresseCarte->afficherCouche(*g.Fenetre , 2 , g.Joueur.getPosImg());
        g.AdresseCarte->afficherCouche(*g.Fenetre , 3 , g.Joueur.getPosImg());
        g.Joueur.AfficherBas(*g.Fenetre);
        for (int i = 0 ; i < g.n ; i++)   g.Elm[i].Affichage(*g.Fenetre, &g.Inter[0] , g.general);
        g.Joueur.AfficherHaut(*g.Fenetre);
        g.AdresseCarte->afficherCouche(*g.Fenetre , 4 , g.Joueur.getPosImg());
        g.AdresseCarte->afficherCouche(*g.Fenetre , 5 , g.Joueur.getPosImg());

        //-----------------------------------------------------------------------------------------
        g.Messager.OuvrirMessage(messageRecompose,&m_imageMes,g);

        g.action= 0;
    }

    else if(inst[0] == "Teleport")  // QUATRE param : Sens Joueur , NomCarte , X , Y
    {
        if (g.Joueur.getSens() == p1 || !p1)
        {
            g.nomCarteACharger = inst[2];
            g.Fenetre->clear();
            g.Joueur.Teleport(p3,p4);
        }
    }


    else if(inst[0] == "IF" || inst[0] == "If" || inst[0] == "Si" || inst[0] == "SI")
    {
        bool condition = 0;
        if (inst[1] == "INTER") // Condition de type interrupteur - numéro inter - Valeur Requise
        {
            if (inst[3] == "VRAI" || inst[3] == "TRUE" || p3 == 1)
            {
                if (g.Inter[p2] == 1) condition = 1;
            }
            else if (inst[3] == "FAUX" || inst[3] == "FALSE" || p3 == 0)
            {
                if (g.Inter[p2] == 0) condition = 1;
            }
        }

        int boucleDeCondition = 0;
        if (condition)
        {
            int i = 1;
            while (inst[i] != "DO") i++;

            do
            {
                i++;
                if (inst[i] == "DO")        boucleDeCondition++;
                else if (inst[i] == "END")  boucleDeCondition--;
                if (inst[i] == "---" && !boucleDeCondition) MultiFonction (&inst[i+1],g);
            }
            while(inst[i] != "END");
        }
    }

    /*
    else if (inst[0] == "Combat")
    {
        Combat(Fenetre,Joueur,&inst[1]);
    }
    */


    else if(inst[0] == "RandomMove") // TpsMove TpsEntre2Move Rayon
    {
        if (VData(D,"SeDeplace") == 1) return;
        if (!DataExistante(D,"TpsLastMove"))  AddData(D,"TpsLastMove",g.general.getElapsedTime());

        if (VData(D,"TpsLastMove") + ConvertionStringFlt(inst[2]) > g.general.getElapsedTime()) return;
        AddData(D,"TpsLastMove",g.general.getElapsedTime());
        AddData(D,"TpsMove",ConvertionStringFlt(inst[1]));

        int direction;
        direction = 2 * Randomizer::Random(1,4); // 2 4 6 ou 8 -> voir pavé numérique
        int Nx = m_X;
        int Ny = m_Y;
        if (direction == 2)
        {
            Ny = m_Y+1;
            if (Ny < g.Y )
            {
                if (*(g.Adressegrille + sizeof(bool)*(Nx+Ny*g.X)) != 1 && (g.Joueur.getX() != Nx || g.Joueur.getY() != Ny))
                {
                    if(*(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X)) != 1)
                    {
                        *(g.AdresseColElm +sizeof(bool)*(m_X+m_Y*g.X)) = false;
                        AddData(D,"SeDeplace",1);
                        m_Y++;
                        *(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X))= true;
                    }

                }
            }
        }
        else if (direction == 4)
        {
            Nx = m_X-1;
            if (Nx >= 0)
            {
                if (*(g.Adressegrille + sizeof(bool)*(Nx+Ny*g.X)) != 1 && (g.Joueur.getX() != Nx || g.Joueur.getY() != Ny))
                {
                    if(*(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X)) != 1)
                    {
                        *(g.AdresseColElm +sizeof(bool)*(m_X+m_Y*g.X)) = false;
                        AddData(D,"SeDeplace",1);
                        m_X--;
                        *(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X))= true;
                    }
                }
            }
        }
        else if (direction == 6)
        {
            Nx = m_X+1;
            if (Nx < g.X)
            {
                if (*(g.Adressegrille + sizeof(bool)*(Nx+Ny*g.X)) != 1 && (g.Joueur.getX() != Nx || g.Joueur.getY() != Ny))
                {
                    if(*(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X)) != 1)
                    {
                        *(g.AdresseColElm +sizeof(bool)*(m_X+m_Y*g.X)) = false;
                        AddData(D,"SeDeplace",1);
                        m_X++;
                        *(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X))= true;
                    }
                }
            }
        }
        else if (direction == 8)
        {
            Ny = m_Y-1;
            if (Ny >= 0)
            {
                if (*(g.Adressegrille + sizeof(bool)*(Nx+Ny*g.X)) != 1 && (g.Joueur.getX() != Nx || g.Joueur.getY() != Ny))
                {
                    if(*(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X)) != 1)
                    {
                        *(g.AdresseColElm +sizeof(bool)*(m_X+m_Y*g.X)) = false;
                        AddData(D,"SeDeplace",1);
                        m_Y--;
                        *(g.AdresseColElm +sizeof(bool)*(Nx+Ny*g.X))= true;
                    }
                }
            }
        }
        AddData(D,"Direction",direction);
    }

    else if(inst[0] == "Sound") // NomDuSon
    {
        g.sonElem.loadFromFile("Ressources/Sounds/" + inst[1]);
        g.Sound.setBuffer(g.sonElem);
        g.Sound.play();
    }

    else if(inst[0] == "Stop")
    {
        g.general.Stop();
    }
    else if(inst[0] == "ReStart")
    {
        g.general.ReStart();
    }
    else if(inst[0] == "Musique" || inst[0] == "Music")
    {
        g.MusiqueDeFond.chargerMusique(inst[1]);
    }
    else if(inst[0] == "Inter")     g.Inter[p1] = p2;
    /*else if(inst[0] == "Particule")
    {
        AppData(D,"NombreParticule",inst[1]);
        AppData(D,"vieX",inst[2]);
        AppData(D,"vieY",inst[3]);
        AppData(D,"dirXX",inst[4]);
        AppData(D,"dirXY",inst[5]);
        AppData(D,"dirYX",inst[6]);
        AppData(D,"dirYY",inst[7]);
        AppData(D,"perteX",inst[8]);
        AppData(D,"perteY",inst[9]);
        AppData(D,"red",inst[10]);
        AppData(D,"green",inst[11]);
        AppData(D,"blue",inst[12]);
        AppData(D,"dimX",inst[13]);
        AppData(D,"dimY",inst[14]);







    }*/

}





sf::Rect<int> SubRectSelector(sf::Texture &texture,int Direction,float t)
{
    int h = texture.getSize().y;
    int l = texture.getSize().x;
    int x = 0, y = 0;

    if(0.2 < t && t < 0.46) x = l/NBFRAMEANIM;
    else if ( 0.54 < t && t < 0.92) x = 2*l/NBFRAMEANIM;

    y = (Direction - 2)/2 * h/4;

    return sf::Rect<int> (x,y,l/NBFRAMEANIM,h/4);
}




void Element::StaticSubRectSelector(std::vector<Data> &D,string nom)
{
    int h = m_image.getSize().x/4;
    int l = m_image.getSize().y/3;
    int y = 0;

    int direction=VData(D,"Direction");

    y = (direction - 2)/2 * h;
    m_apparence.setTextureRect(IntRect(0,y,l,y+h));


}














bool AddData(vector<Data> &D,string nom,float v)
{
    Data C;
    for (unsigned int i = 0 ; i < D.size() ; i++)
    {
        C = D[i];
        if (C.nom == nom)
        {
            C.v = v;
            D[i] = C;
            return 1;
        }
    }
    D.resize(D.size() + 1);
    C.nom = nom;
    C.v = v;
    D[D.size()-1] = C;
    return 0;
}

float VData(vector<Data> &D,string nom)
{
    Data C;
    for (unsigned int i = 0 ; i < D.size() ; i++)
    {
        C = D[i];
        if (C.nom == nom)
            return C.v;
    }
    return -1;
}

bool DataExistante(vector<Data> &D,string nom)
{
    Data C;
    for (unsigned int i = 0 ; i < D.size() ; i++)
    {
        C = D[i];
        if (C.nom == nom)
            return 1;
    }
    return 0;
}
