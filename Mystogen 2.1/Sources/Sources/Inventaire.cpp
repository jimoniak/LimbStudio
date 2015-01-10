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


#include <typeinfo>





using namespace std;
using namespace sf;

EmplacementInv::EmplacementInv() :   Bouton(Vector2f(40,40),false)
{
    m_Quantite.setCharacterSize(20);
    m_Quantite.setColor(sf::Color(255,255,255));
    m_IconeEmplacement.loadFromFile("Ressources/Interface/Inventaire/Emplacement.png");
    m_fond.setTexture(m_IconeEmplacement);
}

EmplacementInv::~EmplacementInv()
{

}


void EmplacementInv::afficherIcone(gameWindow &fenetre)
{
    fenetre.draw(m_fond);
    if(m_objetLie != NULL)
    {
        fenetre.draw(m_objetLie->iconeSp);
        if(typeid(*m_objetLie) != typeid(Arme) &&
                typeid(*m_objetLie) != typeid(Casque) &&
                typeid(*m_objetLie) != typeid(Torse) &&
                typeid(*m_objetLie) != typeid(Gant) &&
                typeid(*m_objetLie) != typeid(Jambiere) &&
                typeid(*m_objetLie) != typeid(Chaussure))    fenetre.draw(m_Quantite);
    }

}

void EmplacerEquip::afficherIcone(gameWindow &fenetre)
{
    fenetre.draw(m_fond);
    if(m_objetLie != NULL)
    {
        fenetre.draw(m_objetLie->iconeSp);
    }
}

void EmplacementInv::PositionnerIconeObjet(Inventaire &inventaire,int emplacement)
{
    if (m_objetLie != NULL)
    {
        m_objetLie->setPosition(Vector2f(inventaire.getPosition().x + 40 + 60 *(emplacement%CONSTANTE_EMPLACEMENT_POSITION)
                                         ,inventaire.getPosition().y + 230 + 50*(emplacement/CONSTANTE_EMPLACEMENT_POSITION) ));//positionner l'icone en fonction de sa place dans l'inventaire
    }
    m_position = Vector2f(inventaire.getPosition().x + 38 + 60 *(emplacement%CONSTANTE_EMPLACEMENT_POSITION)
                          ,inventaire.getPosition().y + 228 + 50*(emplacement/CONSTANTE_EMPLACEMENT_POSITION) );
    m_Quantite.setPosition(m_position.x + 30 , m_position.y +20);
    Bouton::setPosition(Vector2f(m_position.x + 10 ,m_position.y+ 10));
    m_fond.setPosition(m_position);
}

void  EmplacementInv::setQuantite()
{
    m_Quantite.setString(string(ConvIntString(m_quantite)));
}

void EmplacementInv::setFont(sf::Font &font)
{
    m_Quantite.setFont(font);

}

Texture EmplacementInv::getIcone()
{
    return m_objetLie->iconeIm;
}

string EmplacementInv::getDescription()
{
    return m_objetLie->m_description;
}

string EmplacementInv::getNom()
{
    return m_objetLie->m_nom;
}

string EmplacementInv::getQuanti()
{
    return ConvIntString(m_quantite);
}


sf::Texture EmplacerEquip::getIcone()
{
    return m_objetLie->iconeIm;
}
std::string EmplacerEquip::getDescription()
{
    return m_objetLie->m_description;
}
std::string EmplacerEquip::getNom()
{
    return m_objetLie->m_nom;
}
EmplacerEquip::EmplacerEquip() : EmplacementInv()
{
}

EmplacerEquip::~EmplacerEquip()
{

}




void EmplacerEquip::setPosition(sf::Vector2f newValues)
{
    m_position = newValues;

    if(m_objetLie != NULL) m_objetLie->setPosition(m_position);


    m_fond.setPosition(m_position.x -2,m_position.y -2);
    Bouton::setPosition(Vector2f(m_position.x + 10 ,m_position.y+ 10));



}

void EmplacerEquip::setPosIcone()
{

    m_objetLie->setPosition(m_position);

}

Inventaire::Inventaire() : m_Utiliser(Vector2f(130,30),false), m_Jeter(Vector2f(130,30),false) , m_Sortir(sf::Vector2f(20,20),false)
{


    m_setfont = false;
    m_actif = false;
    m_FondSP.setColor(Color(255,255,255,210));
    m_FondIM.loadFromFile("Ressources/Interface/Inventaire/FondV2R.png"); //Texture du fond de l'inventaire
    m_FondSP.setTexture(m_FondIM);//sprite de l'Texture

    m_menuUtileIM.loadFromFile("Ressources/Interface/Inventaire/miniMenu.png");
    m_menuUtileSP.setColor(Color(255,255,255,190));
    m_menuUtileSP.setTexture(m_menuUtileIM);

    m_Utiliser.setSizeText(20);
    m_Utiliser.setColorText(Color(0,0,0));
    m_Utiliser.setString("Utiliser");
    m_Jeter.setSizeText(20);
    m_Jeter.setColorText(Color(0,0,0));
    m_Jeter.setString("Jeter");

    m_Sortir.setTexture("Ressources/Interface/Inventaire/Curseur1.png");


    m_forcePers.setCharacterSize(20);
    m_forcePers.setString("Force");

    m_endurPers.setCharacterSize(20);
    m_endurPers.setString("Endurance");


    for(int i = 0 ; i< NOMBRE_EMPLACEMENTEQUIP ; i++)
    {
        m_emplacement[i].m_objetLie = NULL;
    }

    for(int i = 0 ; i< 6 ; i++)
    {
        EmplacementEquipement[i].m_objetLie = NULL;
    }





    m_Curseur1IM.loadFromFile("Ressources/Interface/Inventaire/Curseur1.png"); //curseur de selection des objets.
    m_Curseur1SP.setTexture(m_Curseur1IM);

    m_Curseur2IM.loadFromFile("Ressources/Interface/Inventaire/Curseur2.png"); //curseur de selection des objets.
    m_Curseur2SP.setTexture(m_Curseur2IM);

    m_DimBarreVie.x=310;
    m_DimBarreVie.y=20;

    m_DimBarreEnergie = m_DimBarreVie;

    m_inventaireNom.setCharacterSize(20);
    m_inventaireNom.setColor(Color(0,0,0));
    m_inventaireNom.setString("Inventaire");

    m_nomObj.setPosition(m_position.x + 390, m_position.y + 40);
    m_nomObj.setCharacterSize(20);
    m_nomObj.setColor(Color(0,0,0,255));


    m_desObj.setPosition(m_position.x + 390, m_position.y + 260);
    m_desObj.setCharacterSize(20);
    m_desObj.setColor((Color(0,0,0,255)));

    m_QuantiObj.setCharacterSize(20);
    m_QuantiObj.setColor((Color(0,0,0,255)));

    m_emplacementCible = 0;
}


Inventaire::~Inventaire()
{
    for(int i = 0 ; i< NOMBRE_EMPLACEMENTEQUIP ; i++)
    {
        if(m_emplacement[i].m_objetLie!=NULL)
            delete m_emplacement[i].m_objetLie;
    }



    // cout << "destructeur inventaire appelé " <<endl;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void Inventaire::chargementInv(GameData &GameData)
{

    if(!m_setfont)
    {
        m_nomObj.setFont(GameData.font);
        m_desObj.setFont(GameData.font);
        m_QuantiObj.setFont(GameData.font);
        m_inventaireNom.setFont(GameData.font);
        m_Utiliser.setFont(GameData.font);
        m_Jeter.setFont(GameData.font);

        m_endurPers.setFont(GameData.font);
        m_forcePers.setFont(GameData.font);

        m_BarreVie=(Barregraphique("Vie:",1,GameData.Joueur.getMaxVie(),m_DimBarreVie, m_PosBarreVie,Color(0,0,0,150),Color(0,0,255,150)));
        m_BarreVie.ChargementPolice(&GameData.font,20);
        m_BarreEnergie=(Barregraphique("Energie:",1,GameData.Joueur.getMaxEnergie(),m_DimBarreEnergie,m_PosBarreEnergie,Color(0,0,0,150),Color(0,255,0,150)));
        m_BarreEnergie.ChargementPolice(&GameData.font,20);

        for(int i=0; i <NOMBRE_EMPLACEMENTEQUIP; i++)
        {
            m_emplacement[i].setFont(GameData.font);
        }
        m_setfont = true;

        m_Utiliser.setFont(GameData.font);
        m_Jeter.setFont(GameData.font);

    }
}

void Inventaire::ouvrirInventaire(gameWindow &fenetre,GameData &GameData,Carte &Monde)
{
    //initialisation de differentes variable:
    m_clock.restart();
    m_BarreVie.MajParametre(GameData.Joueur.getVie());
    m_BarreEnergie.MajParametre(GameData.Joueur.getEnergie());
    setForce(GameData.Joueur);
    setEndurance(GameData.Joueur);

    m_emplacementCible = 0;
    m_emplacementEquipCible = 0;
    m_zoneMenu = SACADOS;
    DeplacerCurseur1();
    DeplacerCurseur2();
    setInfo();
    m_zoneActif = CHOIXZONE;
    m_choixZone = 1;
    m_nomObj.setPosition(m_position.x + 370, m_position.y + 310);
    m_desObj.setPosition(m_position.x + 370, m_position.y + 380);
    m_QuantiObj.setPosition(m_position.x + 380 , m_position.y + 450);
    m_inventaireNom.setPosition(m_position.x + 310 , m_position.y + 20);



    //-------------------------Esthetique (creation du background)
    /*sf::Texture img(fenetre.Capture());
    sf::Sprite backgR;
    backgR.setTexture(img);
    backgR.setPosition(GameData.Camera.getCenter().x -LFENETRE/2 , GameData.Camera.getCenter().y -HFENETRE / 2);
    */


    PositionnerIcone();

    int curseurX,curseurY;
    curseurX = curseurY = 0;
    bool boutonClique = false;


    //-------------------------------------------------------------

    while(m_actif)
    {

        //fenetre.draw(backgR); //on affiche l'impression écran du jeu



        GameData.Framerate = (int)(1 / GameData.Affichage.getElapsedTime().asSeconds()); // calcul FPS
        if (GameData.FPSTime.getElapsedTime().asSeconds() > 0.5) //Petite condition qui permet de stabiliser l'affichage des fps à l"ecran.
        {
            GameData.FPS.setString("FPS:"+ ConvertionFltString(GameData.Framerate));
            GameData.FPSTime.Clock::restart();
        }


        this->affichage(fenetre,GameData,Monde); //on affiche l'inventaire.






        sf::Event event;
        while (fenetre.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))    return;

            switch(event.type )
            {
            case  sf::Event::Closed :
                GameData.Joueur.ChangerEtatInv();
                fenetre.close();
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::R)
                {
                    GameData.Joueur.ChangerEtatInv();   //si on appuie R n'importe quand on referme l'inventaire
                }

                break;

            default :
                break;
            }




            curseurX = GameData.Camera.getCenter().x - LFENETRE /2 +sf::Mouse::getPosition(fenetre).x;
            curseurY = GameData.Camera.getCenter().y - HFENETRE /2 + sf::Mouse::getPosition(fenetre).y;

            // cout<<curseurX<<endl;




            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                GameData.Messager.OuvrirMessageSansInteraction("Quitter?\n O: Oui , N: Non",GameData);
                while(GameData.nouveauMessage)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    {
                        fenetre.close();
                        GameData.nouveauMessage = false;

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                    {

                        GameData.nouveauMessage = false;
                        GameData.general.ReStart();
                    }


                }


            }


        }




        if(m_Sortir.ClicInventaire(GameData.event,curseurX,curseurY)) //si on clic sur la petite croix jaune haut droite
        {
            GameData.m_SonMenu.play();
            GameData.Joueur.ChangerEtatInv();

        }



        //NAVIgATION DANS L'INVENTAIRE ------------------------------------------------------------------SOURIS





        if(m_zoneActif != OBJETCHOISI) //si on est sur l'inventaire
        {
            for(unsigned int i=0; i<NOMBRE_EMPLACEMENTEQUIP; i++) //on verifie si on survole un des emplacement
            {
                if(m_emplacement[i].EstDessus(curseurX,curseurY))
                {
                    m_zoneMenu = SACADOS;
                    m_emplacementCible = i;
                    DeplacerCurseur2(); //direction aleatoire car on ne s'en sert pas
                    setInfo(); //On actualise la description de lobjet de l'inventaire
                    setStringMenu(); // on actualise le texte du mini Menu.
                    m_Curseur1SP.setPosition(m_menuUtileSP.getPosition().x +8 , m_menuUtileSP.getPosition().y + 8); // on repositionne le curseur dessus
                }

            }

            for(unsigned int i=0 ; i< 6 ; i++)
            {

                if(EmplacementEquipement[i].EstDessus(curseurX,curseurY)) // meme principe qu'au dessus, smais si  on survole les emplacmenet deja équipé
                {
                    m_zoneMenu = PERSONAEQUIP;
                    m_emplacementEquipCible = i;
                    DeplacerCurseur2();
                    setStringMenu();
                    m_Curseur1SP.setPosition(m_menuUtileSP.getPosition().x +8 , m_menuUtileSP.getPosition().y + 8);


                }


            }
        }






        if(m_zoneActif == OBJETCHOISI)  // Si on a deja selectionné un objet
        {
            if(m_Utiliser.EstDessus(curseurX,curseurY))
            {
                m_choixMenu = 1;
                DeplacerCurseur1();
                //En fonction de l'option choisi
            }

            if(m_Jeter.EstDessus(curseurX,curseurY))
            {
                m_choixMenu = 2;
                DeplacerCurseur1();
            }

            if(m_Utiliser.ClicInventaire(GameData.event,curseurX,curseurY))
            {
                GameData.m_SonMenu.play();
                UtiliserObjet(GameData,*this);
                m_zoneActif = SACADOS;
                m_choixMenu = 1;
                DeplacerCurseur1();                //Si on clic sur un des choix
            }
            if(m_Jeter.ClicInventaire(GameData.event,curseurX,curseurY))
            {
                GameData.m_SonMenu.play();
                JeterObjet(GameData);
                m_zoneActif = SACADOS;
                m_choixMenu = 1;
                DeplacerCurseur1();
            }

        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))//Condition de verifie si on a cliqué en dehors d'un des 2 bouton utiliser ou jeter
        {
            if(m_zoneActif == OBJETCHOISI)
            {
                if(!boutonClique)
                {
                    m_zoneActif = SACADOS; //si c'est le cas, on ferme le menu
                }


            }

        }



        if(m_emplacement[m_emplacementCible].ClicInventaire(GameData.event,curseurX,curseurY))
        {
            if(m_emplacement[m_emplacementCible].m_objetLie != NULL)       m_zoneActif = OBJETCHOISI; //si on a cliqué sur un emplacement , on ouvre le mini menu
            GameData.m_SonMenu.play();
        }
        if(EmplacementEquipement[m_emplacementEquipCible].ClicInventaire(GameData.event,curseurX,curseurY))
        {
            if(EmplacementEquipement[m_emplacementEquipCible].m_objetLie != NULL)  m_zoneActif = OBJETCHOISI;//si on a cliqué sur un emplacement , on ouvre le mini menu
            GameData.m_SonMenu.play();
        }





        setInfo();//actualisation des info descriptive
        setStringMenu();//actualisation du text du mini menu

        fenetre.draw(GameData.FPS);

        fenetre.display();



    }



}


//--------------------------------------------------------------------
//--------------------------------------------------------------------

void Inventaire::PositionnerIcone()
{
    for(int i=0; i<NOMBRE_EMPLACEMENTEQUIP; i++)
    {
        m_emplacement[i].PositionnerIconeObjet(*this,i);
    }

}

void Inventaire::affichage(gameWindow &fenetre,GameData &g,Carte &Monde)
{


    //Le monde continue de tourner...

    g.Affichage.Clock::restart();
    fenetre.clear();
    Monde.bougerCloud(g.general);
    Monde.majgene(g.general);
    g.Pannel.calculDuree(g.general);



    g.Affichage.Clock::restart();
    fenetre.clear();
    Monde.afficherCouche(fenetre , 1 , g.Joueur.getPosImg());
    Monde.afficherCouche(fenetre , 2 , g.Joueur.getPosImg());
    Monde.afficherCouche(fenetre , 3 , g.Joueur.getPosImg());
    for (int i = 0 ; i < g.n ; i++)   g.Elm[i].Affichage(fenetre, &g.Inter[0] , g.general);
    g.Joueur.Affichage(fenetre);
    Monde.afficherCouche(fenetre , 4 , g.Joueur.getPosImg());
    Monde.afficherCouche(fenetre , 5 , g.Joueur.getPosImg());
    g.Pannel.pannelOuvert(fenetre);

    for (int i = 0 ; i < g.n ; i++)   g.Elm[i].Interaction(g);


//-------------------------------------------------------------------------
    m_Curseur1SP.setColor(sf::Color(255,255,255,128*(1+cos(3*m_clock.getElapsedTime().asSeconds()))));
    m_Curseur2SP.setColor(sf::Color(255,255,255,128*(1+sin(3*m_clock.getElapsedTime().asSeconds()))));
    fenetre.draw(m_FondSP);
    fenetre.draw(m_inventaireNom);
    m_BarreVie.AfficherBarre(fenetre);
    m_BarreEnergie.AfficherBarre(fenetre);
    fenetre.draw(m_forcePers);
    fenetre.draw(m_endurPers);


    for(int i=0; i <NOMBRE_EMPLACEMENTEQUIP; i++)
    {
        m_emplacement[i].afficherIcone(fenetre);

    }

    for(int i=0 ; i<6; i++)
    {
        EmplacementEquipement[i].afficherIcone(fenetre);
    }
    /*if(m_zoneActif == SACADOS || m_zoneActif == PERSONAEQUIP)
    {*/

    fenetre.draw(m_desObj);
    fenetre.draw(m_nomObj);
    fenetre.draw(m_objSelSP);
    if(m_zoneMenu == SACADOS)
    {
        if(m_emplacement[m_emplacementCible].m_objetLie != NULL)
        {
            if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Arme) &&
                    typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Casque) &&
                    typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Torse) &&
                    typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Gant) &&
                    typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Jambiere) &&
                    typeid(*m_emplacement[m_emplacementCible].m_objetLie) != typeid(Chaussure))       fenetre.draw(m_QuantiObj);//Si l'objet selectionner est une Arme , on cache la quantité.
        }
    }
    // }
    if(m_zoneActif == OBJETCHOISI)
    {
        fenetre.draw(m_desObj);
        fenetre.draw(m_nomObj);
        fenetre.draw(m_objSelSP);


        fenetre.draw(m_menuUtileSP);
        fenetre.draw(m_Curseur2SP);
        fenetre.draw(m_Curseur1SP);
        m_Utiliser.Affichage(fenetre,false,false);
        m_Jeter.Affichage(fenetre,false,false);



    }
    m_Sortir.Affichage(fenetre,false,false);

    //fenetre.draw(m_Curseur1SP);
    fenetre.draw(m_Curseur2SP);




}
void Inventaire::setPosition(sf::Vector2f newposition) //repositionnement de l'inventaire et de ces attributs.
{
    m_position.x = newposition.x + (LFENETRE - m_FondIM.getSize().x) / 2;
    m_position.y = newposition.y + (HFENETRE - m_FondIM.getSize().y) / 2;

    m_FondSP.setPosition(m_position);
    m_Curseur1SP.setPosition(m_position.x + 318 , m_position.y + 188);

    m_PosBarreVie.x= m_position.x + 30;
    m_PosBarreVie.y= m_position.y + 75;

    m_PosBarreEnergie.x=m_position.x + 30;
    m_PosBarreEnergie.y=m_position.y + 125;

    m_BarreVie.setPosition(m_PosBarreVie);
    m_BarreEnergie.setPosition(m_PosBarreEnergie);

    m_forcePers.setPosition(m_position.x+30,m_position.y+160);
    m_endurPers.setPosition(m_position.x+30,m_position.y+180);

    m_Sortir.setPosition(Vector2f(m_position.x+675,m_position.y + 15));



    EmplacementEquipement[0].setPosition(Vector2f(m_position.x+430,m_position.y+130));
    EmplacementEquipement[1].setPosition(Vector2f(m_position.x+540,m_position.y+20));
    EmplacementEquipement[2].setPosition(Vector2f(m_position.x+600,m_position.y+70));
    EmplacementEquipement[3].setPosition(Vector2f(m_position.x+650,m_position.y+130));
    EmplacementEquipement[4].setPosition(Vector2f(m_position.x+600,m_position.y+190));
    EmplacementEquipement[5].setPosition(Vector2f(m_position.x+540,m_position.y+240));

}


void Inventaire::ChangerEtat()
{

//m_actif = m_actif ? m_actif = false : m_actif = true;

    m_actif = !m_actif;


}

bool Inventaire::getEtat()
{
    return m_actif;
}

sf::Vector2f Inventaire::getPosition()
{
    return m_FondSP.getPosition();
    cout<<getPosition().x <<endl;
}
//--------------------------------------Methode lié au curseur


void Inventaire::DeplacerCurseur1()
{

    if(m_zoneActif == OBJETCHOISI)
    {
        if(m_choixMenu == 1)
            m_Curseur1SP.setPosition(m_menuUtileSP.getPosition().x + 8 , m_menuUtileSP.getPosition().y + 8);


        if(m_choixMenu == 2)
            m_Curseur1SP.setPosition(m_menuUtileSP.getPosition().x +8 , m_menuUtileSP.getPosition().y + 58);


    }

}



void Inventaire::DeplacerCurseur2()
{


    if(m_zoneMenu == SACADOS)              //Si on est dans le sac a dos
    {

        m_Curseur2SP.setPosition(Vector2f(m_position.x + 37 + 60 *(m_emplacementCible%CONSTANTE_EMPLACEMENT_POSITION)
                                          ,m_position.y + 227 + 50*(m_emplacementCible/CONSTANTE_EMPLACEMENT_POSITION) )); // on actualise ici la position du curseur en fonction de l'emplacement où il se trouve.
        m_menuUtileSP.setPosition(Vector2f(m_Curseur2SP.getPosition().x ,m_Curseur2SP.getPosition().y -110));
        PositionnerTextMenu();

        setStringMenu();
    }
    // cout<< m_emplacementCible <<endl; //Cout de maintenance
    else if(m_zoneMenu == PERSONAEQUIP) //si on est entré sur la zone d'equipement de l'inventaire
    {
        //ici pu de calcule de "collision avec la brodure, n'ayant que 6 emplacement , on calcule la position du curseur en fonction de la ou il se trouve
        //ainsi que ces deplacmeents possible.


        if(m_emplacementEquipCible==0) //on actualise le curseur (graphiquement) en fonction de l'emplacement d'equipement ciblé.
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+427,m_position.y+127));
        }
        else if(m_emplacementEquipCible==1)
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+537,m_position.y+17));
        }
        else if(m_emplacementEquipCible==2)
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+597,m_position.y+67));
        }
        else if(m_emplacementEquipCible==3)
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+647,m_position.y+127));
        }
        else if(m_emplacementEquipCible==4)
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+597,m_position.y+187));
        }
        else if(m_emplacementEquipCible==5)
        {
            m_Curseur2SP.setPosition(Vector2f(m_position.x+537,m_position.y+237));
        }

        m_menuUtileSP.setPosition(Vector2f(m_position.x + 360 ,m_position.y + 190));
        PositionnerTextMenu();

    }
    //cout<<m_emplacementEquipCible <<endl;
}


void Inventaire::setIconeObj() //actualisation de l'icone de description de l'inventaire
{
    if(m_zoneMenu == SACADOS)
    {
        if(m_emplacement[m_emplacementCible].m_objetLie!=NULL)
        {
            m_objSelIM=m_emplacement[m_emplacementCible].getIcone();

        }
        else
        {
            m_objSelIM .loadFromFile("Ressources/Interface/Inventaire/EmplacementVide.png");
        }
    }
    else if(m_zoneMenu == PERSONAEQUIP)
    {
        if( EmplacementEquipement[m_emplacementEquipCible].m_objetLie!=NULL)
        {
            m_objSelIM= EmplacementEquipement[m_emplacementEquipCible].getIcone();
        }
        else
        {
            m_objSelIM .loadFromFile("Ressources/Interface/Inventaire/EmplacementVide.png");
        }
    }
    else

        m_objSelIM .loadFromFile("Ressources/Interface/Inventaire/EmplacementVide.png");

    m_objSelSP.setTexture(m_objSelIM);
    m_objSelSP.setPosition(m_position.x + 640 , m_position.y + 300);
}

void Inventaire::setDesobjtsel()//actualise la description de l'objet selectioné en fonction de l'affichage
{
    if(m_zoneMenu == SACADOS)
    {
        if(m_emplacement[m_emplacementCible].m_objetLie!=NULL)
        {
            m_desObj.setString("Description: " +m_emplacement[m_emplacementCible].getDescription());
            MiseEnPage(m_desObj.getString());
        }
        else
            m_desObj.setString("...");
    }
    else if(m_zoneMenu == PERSONAEQUIP)
    {
        if( EmplacementEquipement[m_emplacementEquipCible].m_objetLie!=NULL)
        {
            m_desObj.setString("Description: " + EmplacementEquipement[m_emplacementEquipCible].getDescription());
            MiseEnPage(m_desObj.getString());
        }

        else
            m_desObj.setString("...");



    }

}




void Inventaire::setnomObj() // actualise le nom de l'objet selectionner pour laffichage
{
    if(m_zoneMenu == SACADOS)
    {

        if(m_emplacement[m_emplacementCible].m_objetLie!=NULL)
            m_nomObj.setString("Objet: " +m_emplacement[m_emplacementCible].getNom());
        else
            m_nomObj.setString("...");
    }
    else if (m_zoneMenu == PERSONAEQUIP)
    {
        if( EmplacementEquipement[m_emplacementEquipCible].m_objetLie!=NULL)
            m_nomObj.setString("Objet: " + EmplacementEquipement[m_emplacementEquipCible].getNom());
        else
            m_nomObj.setString("...");

    }

}

void Inventaire::setQuantObj() // actualisation du SF::String concernant la quantité de l'objet selectionné
{
    if(m_emplacement[m_emplacementCible].m_objetLie!=NULL)
        m_QuantiObj.setString("Quantite :" + m_emplacement[m_emplacementCible].getQuanti());
    else
        m_QuantiObj.setString("Quantite :?");

}

void Inventaire::PositionnerTextMenu() //repositionnement des texte du menu objet en fonction de celui-ci
{
    m_Utiliser.setPosition(Vector2f(m_menuUtileSP.getPosition().x + 40 , m_menuUtileSP.getPosition().y + 15 ));
    m_Jeter.setPosition(Vector2f(m_menuUtileSP.getPosition().x + 40 , m_menuUtileSP.getPosition().y + 65 ));

}

void  Inventaire::setStringMenu()
{
    if(m_zoneMenu == SACADOS)
    {
        if(m_emplacement[m_emplacementCible].m_objetLie != NULL) //on actualise le texte de la zone "utiliser" en fonction de l'objet selectionné.
        {
            if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Potion))   m_Utiliser.setString("Boire");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Arme))     m_Utiliser.setString("Equiper");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Casque))     m_Utiliser.setString("Porter");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Torse))     m_Utiliser.setString("Porter");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Gant))     m_Utiliser.setString("Porter");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Jambiere))     m_Utiliser.setString("Porter");
            else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Chaussure))     m_Utiliser.setString("Porter");

        }

    }
    else if(m_zoneMenu == PERSONAEQUIP)
    {

        m_Utiliser.setString("Retirer");

    }
}



void Inventaire::UtiliserObjet(GameData &g,Inventaire &inv) //fonction qui permet de se servir de l'objet
{
    if(m_zoneMenu== SACADOS) //si on se trouve dans le SACADOS
    {

        if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Arme))                //si l'objet selectionné est une arme
        {
            if(EmplacementEquipement[0].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[0].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[0].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Arme *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getArme();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[0].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[0].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }

        }
        else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Casque))
        {
            if(EmplacementEquipement[1].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[1].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[1].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Casque *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getCasque();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[1].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[1].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }
        }
        else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Torse))
        {
            if(EmplacementEquipement[2].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[2].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[2].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Torse *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getTorse();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[2].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[2].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }
        }
        else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Gant))
        {
            if(EmplacementEquipement[3].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[3].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[3].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Gant *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getGant();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[3].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[3].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }
        }
        else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Jambiere))
        {
            if(EmplacementEquipement[4].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[4].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[4].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Jambiere *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getJambiere();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[4].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[4].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }
        }
        else if(typeid(*m_emplacement[m_emplacementCible].m_objetLie) == typeid (Chaussure))
        {
            if(EmplacementEquipement[5].m_objetLie == NULL)                                         // si l'emplacement arme du personnage est libre
            {
                EmplacementEquipement[5].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie; //on envoie l'objet selectionné sur le pointeur de l'emplacement Arme du personnage
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                     // on appel la methode utiliser de l'objet arme copié (qui permet de le lié au personnage)
                EmplacementEquipement[5].setPosIcone();                                             //on initialise l'icone de l'emplacement
                m_emplacement[m_emplacementCible].m_objetLie =NULL;                                 //on reinitialise le pointeur de l'emplacement de l'inventaire
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                  //on position le curseur 1 sur le choix 1



            }
            else                                                                                    //sinon si l'emplacement arme du personnage n'est pas libre
            {
                Chaussure *intermediaire;                                                                    //creation d'un pointeur intermediaire
                intermediaire = g.Joueur.getChaussure();                                                     //on affecte l'objet lié au personage  au pointeur intermediaire
                EmplacementEquipement[5].m_objetLie = m_emplacement[m_emplacementCible].m_objetLie;      //on envoie la nouvelle arme à l'emplacement Arme du perso.
                EmplacementEquipement[5].setPosIcone();                                                   //reactualisation de l'icone
                m_emplacement[m_emplacementCible].m_objetLie ->utiliser(g,inv);                         //liaison du nouvelle objet au personnage
                m_emplacement[m_emplacementCible].m_objetLie = intermediaire;                           // on affecte l'ancien objet à la place de nouvel objet dans l'inventaire
                m_emplacement[m_emplacementCible].PositionnerIconeObjet(*this,m_emplacementCible);      //on repositionne l'icone de l'ancien objet  sur l'inventaire et au bon endroit
                m_Curseur1SP.setPosition(m_position.x +318 , m_position.y + 188);                       // on repositionne le curseur.

            }

        }
        else m_emplacement[m_emplacementCible].m_objetLie->utiliser(g,inv);// si n'est pas d'un des type ci dessus:(securité)





        // on se resitue dans le SACADOS

    }
    else if(m_zoneMenu ==PERSONAEQUIP)//si on est dans le grpuhique d'equipement (est que l'on "utilise" donc ,que l'on retire l'objet
    {
        bool objetplace = false;//booleen permettant de savoir si on a deja remi lobjet dans linventaire (faux des le depart)


        for(int i= 0 ; i< NOMBRE_EMPLACEMENTEQUIP; i++) //on parcours l'inventaire
        {
            if(!objetplace) //tant que l'objet n'est pas placé
            {

                if(m_emplacement[i].m_objetLie == NULL) //si l'emplacmeent sur lequel on est est libre
                {
                    objetplace = true; //on dit que l'on a posé l'objet
                    m_emplacement[i].m_objetLie = EmplacementEquipement[m_emplacementEquipCible].m_objetLie;// on copie sur le pointeur de l'emplacement de l'inventaire , celui de l'objet équipé que l'on retire
                    m_emplacement[i].PositionnerIconeObjet(*this,i); //on repositionne l'icone de l'objet dans l'inventaire
                    EmplacementEquipement[m_emplacementEquipCible].m_objetLie = NULL; // on Reset le pointeur de l'emplacement de l'equipement.




                    if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Arme))        g.Joueur.RetirerArme();//on "delie l'objet au personnage.
                    else if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Casque))      g.Joueur.RetirerCasque();
                    else if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Torse))       g.Joueur.RetirerTorse();
                    else if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Gant))        g.Joueur.RetirerGant();
                    else if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Jambiere))    g.Joueur.RetirerJambiere();
                    else if(typeid(*m_emplacement[i].m_objetLie ) == typeid (Chaussure))   g.Joueur.RetirerChaussure();



                }

            }


        }



        m_Curseur1SP.setPosition(m_position.x +398 , m_position.y + 138);

    }



    m_BarreVie.MajParametre(g.Joueur.getVie());
    m_BarreEnergie.MajParametre(g.Joueur.getEnergie());
    setForce(g.Joueur);
    setEndurance(g.Joueur);
}
void Inventaire::JeterObjet(GameData &g)
{
    if(m_zoneMenu == SACADOS)
    {
        Item * poubelle;
        poubelle = m_emplacement[m_emplacementCible].m_objetLie;
        m_emplacement[m_emplacementCible].m_objetLie = NULL;
        delete poubelle;
        m_zoneActif = m_zoneMenu;
    }
    else

    {
        g.Messager.OuvrirMessage("Impossible de jeter, Retirer l'objet d'abord.", g);
    }
}


void Inventaire::RetireQuantite(int quantite)
{
    m_emplacement[m_emplacementCible].m_quantite -= quantite; //on retire la quantité corespondante à l'emplacement de l'objet ciblé
    m_emplacement[m_emplacementCible].setQuantite();//on actualise le sf::String  pour l'affichage.



    if(m_emplacement[m_emplacementCible].m_quantite == 0) //si la quantité tombe à 0
    {
        Item* poubelle;
        poubelle= m_emplacement[m_emplacementCible].m_objetLie; // on donne l'objet a un pointeur poubell
        m_emplacement[m_emplacementCible].m_objetLie= NULL; //on reset le pointeur de l'emplacement
        delete poubelle; //puis on supprime l'objet.

        m_zoneActif = SACADOS; //enfin en referme le menu
        //suppresion de l'objet.
    }

}

void Inventaire::setForce(Personnage   &perso)
{
    m_forcePers.setString("Force:" + ConvIntString(perso.getForce()));
}
void Inventaire::setEndurance(Personnage   &perso)
{
    m_endurPers.setString("Endurance:" + ConvIntString(perso.getEndurance()));
}

void Inventaire::setInfo() //fonction regroupant d'autre fonction permettant d'alleger le code
{

    setIconeObj();
    setDesobjtsel();
    setnomObj();
    setQuantObj();


}

void Inventaire::MiseEnPage(string messageAFormater)
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
        if(j==40) // hachage du message en ligne de 40 caractères.
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
    m_desObj.setString(messageDecoupe);

}

int Inventaire::getEmplacementCible()
{
    return m_emplacementCible;
}
