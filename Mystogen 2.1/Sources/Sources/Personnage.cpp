
//Personnage.cpp
// Zl..............Jimoniak...........
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

using namespace std;
using namespace sf;



Personnage::Personnage(gameWindow *fen,sf::Font &polic , sf::Clock &Tp) :
    ArmeEquipe(NULL),
    CasqueEquipe(NULL),
    TorseEquipe(NULL),
    GantEquipe(NULL),
    JambiereEquipe(NULL),
    ChaussureEquipe(NULL)

//    m_spherier("goku",polic,Tp)
{}

Personnage::~Personnage() {}

void Personnage::Chargement(string &nomCarteACharger,GameData &g)
{
    string ligneLue;
    m_vitesseDep = 4;
    m_mouvementEnCour = false;

    ifstream sav("Joueur.sav",ios::in);
    if(!sav)//si on ne trouve pas de sauvegarde
        cout << "impossible de charger: Joueur.sav" << endl;
    else//si on le trouve,on explore le fichier de sauvegarde pour reprendre l'etat du joueur.
    {
        getline(sav,ligneLue);
        m_nom = ligneLue;

        getline(sav,ligneLue);
        nomCarteACharger = ligneLue;

        getline(sav,ligneLue);
        m_X = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_Y = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_image.loadFromFile(ligneLue);

        m_image.createMaskFromColor(sf::Color(0, 0, 0));
        m_Texture.loadFromImage(m_image);
        m_Texture.setSmooth(0);


        h = m_Texture.getSize().y;
        l = m_Texture.getSize().x;

        m_apparence.setPosition(m_X*LTILE - (l/NBFRAMEANIM - LTILE),m_Y*HTILE - ((h/4) - HTILE));
        m_apparence.setTexture(m_Texture);
        m_apparenceHaut = m_apparenceBas = m_apparence;
        m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h /8 );


        sf::Rect<int> Bas0(0,0,l/NBFRAMEANIM,h/4);
        sf::Rect<int> BasHaut0(0,0,l/NBFRAMEANIM,h/8);
        sf::Rect<int> BasBas0(0,h/8,l/NBFRAMEANIM,h/8);
        m_apparence.setTextureRect(Bas0);
        m_apparenceHaut.setTextureRect(BasHaut0);
        m_apparenceBas.setTextureRect(BasBas0);



        getline(sav,ligneLue);
        m_imageBattler.loadFromFile(ligneLue);
        m_battler.loadFromImage(m_imageBattler);
        m_battler.setSmooth(0);
        m_imageBattler.createMaskFromColor(sf::Color(0, 0, 0));

        m_skin.setPosition(LFENETRE/2 - m_battler.getSize().x / 2,HFENETRE - m_battler.getSize().y);
        m_skin.setTexture(m_battler);

        getline(sav,ligneLue);
        m_vie = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_MAXvie = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_energie = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_MAXenergie = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_force = ConvertionStringInt(ligneLue);

        getline(sav,ligneLue);
        m_endurance = ConvertionStringInt(ligneLue);

        ChargementInventaire();
        chargementInv(g);



        m_sens = 2;

        m_move = 1;

        m_tempsDepart=0.0;
    }
}


void Personnage::ChargementInventaire()
{

    ifstream sav("Joueur.sav",ios::in);
    string analyse;
    string parametre[4];
    string chaineDecoup;
    int j=0;

    while(analyse != "#Inventory")
    {
        getline(sav,analyse);

    }

    while(analyse!= "#EndInventory")
    {
        getline(sav,analyse);

        for(unsigned int i=1; i< analyse.size(); i++)
        {
            if(analyse[i]==',' || analyse[i] == '}')
            {
                parametre[j] = chaineDecoup;
                j++;
                chaineDecoup="";
            }
            else
            {
                chaineDecoup += analyse[i];

            }




        }
        j=0;
        chaineDecoup ="";


        switch(ConvertionStringInt (parametre[1]))
        {
        case 1:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Arme(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 2:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Potion(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 3:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Casque(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 4:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Torse(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 5:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Gant(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 6:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Jambiere(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;
        case 7:
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_objetLie = new Chaussure(parametre[2]);
            m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_quantite = ConvertionStringInt(parametre[3]);
            break;

        }


        m_Inventaire.m_emplacement[ConvertionStringInt(parametre[0])].m_Quantite.setString(parametre[3]);

    }


}

void Personnage::ChangerEtatInv()
{
    m_Inventaire.ChangerEtat();

}

void Personnage::ChangerEtatSphr()
{
//        m_spherier.ChangerEtat();
}

void Personnage::ChangerArme(Arme *newArme)
{
    ArmeEquipe = newArme;


}

void Personnage::RetirerArme()
{
    ArmeEquipe = NULL;
    cout <<"arme retirer" <<endl;
}




void Personnage::ChangerCasque(Casque *newCasque)
{
    CasqueEquipe = newCasque;
}
void Personnage::ChangerTorse(Torse *newTorse)
{
    TorseEquipe = newTorse;
}
void Personnage::ChangerGant(Gant *newGant)
{
    GantEquipe = newGant;
}
void Personnage::ChangerJambiere(Jambiere *newJambiere)
{
    JambiereEquipe = newJambiere;
}
void Personnage::ChangerChaussure(Chaussure *newChaussure)
{
    ChaussureEquipe = newChaussure;
}

void Personnage::RetirerCasque()
{
    cout<< CasqueEquipe->getProtection() <<endl;
    this->reduireEndurance(CasqueEquipe->getProtection());

    CasqueEquipe = NULL;
}
void Personnage::RetirerTorse()
{
    this->reduireEndurance(TorseEquipe->getProtection());
    TorseEquipe = NULL;
}
void Personnage::RetirerGant()
{
    this->reduireEndurance(GantEquipe->getProtection());
    GantEquipe = NULL;
}
void Personnage::RetirerJambiere()
{
    this->reduireEndurance(JambiereEquipe->getProtection());
    JambiereEquipe = NULL;
}
void Personnage::RetirerChaussure()
{
    if(ChaussureEquipe)
    {

    }
    this->reduireEndurance(ChaussureEquipe->getProtection());
    ChaussureEquipe = NULL;

}





Arme* Personnage::getArme()
{
    return ArmeEquipe;

}

Casque* Personnage::getCasque()
{
    return CasqueEquipe;
}

Torse* Personnage::getTorse()
{
    return TorseEquipe;
}

Gant* Personnage::getGant()
{
    return GantEquipe;
}

Jambiere* Personnage::getJambiere()
{
    return JambiereEquipe;
}

Chaussure* Personnage::getChaussure()
{
    return ChaussureEquipe;
}

void Personnage::setPositionInv(GameData &g)
{
    m_Inventaire.setPosition(Vector2f(g.Camera.getCenter().x - LFENETRE / 2,g.Camera.getCenter().y - HFENETRE /2));
}


void Personnage::OuvrirInv(gameWindow &fenetre,GameData &g,Carte &Monde)
{
    m_Inventaire.ouvrirInventaire(fenetre,g,Monde);

}


void Personnage::OuvrirSphr(gameWindow &fenetre, sf::Music &musique)
{
    //m_spherier.Menu(fenetre,musique);

}

bool Personnage::getEtatInv()
{
    return m_Inventaire.getEtat();

}

bool Personnage::getEtatSphr()
{
// return m_spherier.getEtat();

}


void Personnage::chargementInv(GameData &g)
{
    m_Inventaire.chargementInv(g);
}

void Personnage::AffichageCombat(gameWindow &fenetre)
{
    fenetre.draw(m_skin);
}

void Personnage::Affichage(gameWindow &fenetre)
{
    fenetre.draw(m_apparence);
}


void Personnage::AfficherHaut(gameWindow &fenetre)
{
    fenetre.draw(m_apparenceHaut);
}

void Personnage::AfficherBas(gameWindow &fenetre)
{
    fenetre.draw(m_apparenceBas);
}

std::string Personnage::getNom() const
{
    return m_nom;
}

void Personnage::gagnerExperience(int Don)
{}

void Personnage::PerdreVie(int qtt)
{
    m_vie -= qtt;
    if ( m_vie < 0)
        m_vie = 0;
}
void Personnage::Soigner(int soin)
{
    if(soin >0)
    {
        if(m_vie < m_MAXvie)
        {
            if((m_MAXvie - soin )< m_vie)
            {
                m_vie = m_MAXvie;
            }
            else   m_vie += soin;
        }
        else
        {
            m_vie = m_MAXvie;
        }
    }


}


void Personnage::Energie(int energie)
{
    if(energie > 0 )
    {
        if(m_energie < m_MAXenergie)
        {
            if((m_MAXenergie - energie )< m_energie)
            {
                m_energie = m_MAXenergie;
            }
            else   m_energie += energie;
        }
        else
        {
            m_energie = m_MAXenergie;
        }

    }
}

/*void Personnage::Attaquer(Ennemi &Cible)
{
    Cible.PerdreVie(15);
}*/


void Personnage::augmenterMaxvie()
{}

void Personnage::changerNom(std::string nom)
{
    m_nom  = nom;
}

int Personnage::getX()
{
    return m_X;
}

int Personnage::getY()
{
    return m_Y;
}

int Personnage::getSens()
{
    return m_sens;

}

Vector2f Personnage::getPosImg()
{
    return m_apparence.getPosition();
}




int Personnage::getFrame()
{
    return m_frame;
}

int Personnage::getVie()
{
    return m_vie;
}

int Personnage::getMaxVie()
{
    return m_MAXvie;
}

int Personnage::getEnergie()
{
    return m_energie;
}
int Personnage::getMaxEnergie()
{
    return m_MAXenergie;
}
int Personnage::getForce()
{
    return m_force;
}
int Personnage::getEndurance()
{
    return (m_endurance + m_enduranceSup ) ;
}

const Texture*  Personnage::getSprite()
{
    return  m_skin.getTexture();
}

void Personnage::Teleport(int X,int Y)
{
    m_X = X;
    m_Y = Y;
    int h = m_Texture.getSize().y;
    int l = m_Texture.getSize().x;
    m_apparence.setPosition(m_X*LTILE - (l/3 - LTILE),m_Y*HTILE - ((h/4) - HTILE));
    m_apparenceHaut.setPosition(m_X*LTILE - (l/3 - LTILE),m_Y*HTILE - ((h/4) - HTILE));
    m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h /8 );

}







void Personnage::ResetTempsDep()
{
    m_tempsDepart= 0.0;


}

bool Personnage::getMouvement()
{
    return m_mouvementEnCour;
}




void Personnage::deplacer(int direction,bool grille[],int X,int Y,Element Elm[],int n,Timer &temps)
{



    if(!m_mouvementEnCour)

    {

        m_sens = direction;

        if (direction == 4)   //gauche
        {
            sf::Rect<int> gauche0(0,h/4,l/NBFRAMEANIM,h/4);//On initialise le sprite
            sf::Rect<int> gaucheHaut0(0,h/4,l/NBFRAMEANIM,h/8);
            sf::Rect<int> gaucheBas0(0,3*h/8,l/NBFRAMEANIM,h/8);

            m_apparence.setTextureRect(gauche0);
            m_apparenceHaut.setTextureRect(gaucheHaut0);
            m_apparenceBas.setTextureRect(gaucheBas0);
            if (m_X)
            {
                if (grille[m_Y*X + m_X - 1] == 0)//Si pas de collision presente sur la carte
                {
                    int verificateur = 1;//On dit que l'on peut passer
                    for (int i = 0; i < n ; i++)//Si  element a collision present
                    {
                        if(Elm[i].getX() == m_X - 1 && m_Y == Elm[i].getY() && Elm[i].getcollision() == 1)
                            verificateur = 0;//On annule l'autorisation de passer
                    }
                    if(verificateur)//si on peut passer
                    {
                        m_X--;//On change la position
                        m_tempsDebut=temps.getElapsedTime();//on reinitialise le temps (pour les animations)
                        m_mouvementEnCour= true;//On dit que l'on est en mouvement.


                    }
                }
            }
        }


        else if (direction ==2) //Pour explication voir cas m_direction== 4
        {
            sf::Rect<int> Bas0(0,0,l/NBFRAMEANIM,h/4);
            sf::Rect<int> BasHaut0(0,0,l/NBFRAMEANIM,h/8);
            sf::Rect<int> BasBas0(0,h/8,l/NBFRAMEANIM,h/8);
            m_apparence.setTextureRect(Bas0);
            m_apparenceHaut.setTextureRect(BasHaut0);
            m_apparenceBas.setTextureRect(BasBas0);
            if (m_Y != Y - 1)
            {
                if (grille[(m_Y+1)*X + m_X] == 0)
                {
                    int verificateur = 1;
                    for (int i = 0; i < n ; i++)
                    {
                        if(Elm[i].getX() == m_X && m_Y + 1 == Elm[i].getY() && Elm[i].getcollision() == 1)
                            verificateur = 0;
                    }
                    if(verificateur)
                    {
                        m_Y++;
                        m_tempsDebut=temps.getElapsedTime();
                        m_mouvementEnCour= true;


                    }
                }
            }
        }


        else if (direction == 6) //Pour explication voir cas m_direction== 4
        {

            sf::Rect<int> Droite0(0,h/2,l/NBFRAMEANIM,h/4);
            sf::Rect<int> DroiteHaut0(0,h/2,l/NBFRAMEANIM,h/8);
            sf::Rect<int> DroiteBas0(0,5*h/8,l/NBFRAMEANIM,h/8);
            m_apparence.setTextureRect(Droite0);
            m_apparenceHaut.setTextureRect(DroiteHaut0);
            m_apparenceBas.setTextureRect(DroiteBas0);
            if (m_X != X - 1)
            {
                if (grille[m_Y*X + m_X + 1] == 0)
                {
                    int verificateur = 1;
                    for (int i = 0; i < n ; i++)
                    {
                        if(Elm[i].getX() == m_X + 1 && m_Y == Elm[i].getY() && Elm[i].getcollision() == 1)
                            verificateur = 0;
                    }
                    if(verificateur)
                    {
                        m_X++;
                        m_tempsDebut=temps.getElapsedTime();
                        m_mouvementEnCour= true;

                    }
                }
            }

        }


        else if (direction == 8) //Pour explication voir cas m_direction== 4
        {
            sf::Rect<int> Haut0(0,3*h/4,l/NBFRAMEANIM,h/4);
            sf::Rect<int> HautHaut0(0,3*h/4,l/NBFRAMEANIM,h/8);
            sf::Rect<int> HautBas0(0,7*h/8,l/NBFRAMEANIM,h/8);
            m_apparence.setTextureRect(Haut0);
            m_apparenceHaut.setTextureRect(HautHaut0);
            m_apparenceBas.setTextureRect(HautBas0);
            if(m_Y)
            {
                if (grille[(m_Y-1)*X + m_X] == 0)
                {
                    int verificateur = 1;
                    for (int i = 0; i < n ; i++)
                    {
                        if(Elm[i].getX() == m_X && m_Y - 1 == Elm[i].getY() && Elm[i].getcollision() == 1)
                            verificateur = 0;
                    }
                    if(verificateur)
                    {
                        m_Y--;
                        m_tempsDebut=temps.getElapsedTime();
                        m_mouvementEnCour= true;

                    }
                }
            }
        }
    }

}


void Personnage::ajouterForce(int force)
{
    m_force += force;
}
void Personnage::reduireForce(int force)
{
    m_force -= force;
}

void Personnage::ajouterEndurance(int endurance)
{
    m_enduranceSup += endurance;

}
void Personnage::reduireEndurance(int endurance)
{
    m_enduranceSup -= endurance;

}




void Personnage::Animer(Timer &temps)
{


    if(m_mouvementEnCour) //Si le personnage se deplace
    {


        if(!m_tempsDepInitialise)
        {
            m_tempsDebut = temps.getElapsedTime();
            m_tempsDepInitialise = true;

        }
        // cout<< m_X   <<"    " << m_Y<< endl;

        Vector2f pos = getPosImg();

        int h = m_Texture.getSize().y;
        int l = m_Texture.getSize().x;

        // cout << temps.getElapsedTime() - m_tempsDebut <<endl;

        if (m_sens == 4) //et si il regarde à gauche
        {
            m_distanceParcourue = (m_vitesseDep * LTILE) * (temps.getElapsedTime() - m_tempsDebut);//On calcule la distance parcourue totale depuis le debut du mouvment
            m_position.x = ((m_X + 1) * LTILE) - m_distanceParcourue; //m_x+1 pour compenser et ne pas avoir de décalage du sprite par rapport a la position réel
            m_apparence.setPosition(m_position.x- (l/NBFRAMEANIM - LTILE),pos.y); //On positionne l'apparence.
            m_apparenceHaut.setPosition(m_apparence.getPosition());
            m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h / 8 );

            if(m_distanceParcourue>=0 && m_distanceParcourue < LTILE / NBFRAMEANIM) // Si la distanceParcourue totale depuis le debut du mouvement est comprise entre 0 et 1/3 de la largeur d'une tile
            {

                sf::Rect<int> gauche0(0,h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> gaucheHaut0(0,h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> gaucheBas0(0,3*h/8,l/NBFRAMEANIM,h/8);

                m_apparence.setTextureRect(gauche0);       //On affiche le premier sprite du joueur
                m_apparenceHaut.setTextureRect(gaucheHaut0);
                m_apparenceBas.setTextureRect(gaucheBas0);
            }
            else if(m_distanceParcourue>=LTILE / NBFRAMEANIM && m_distanceParcourue < 2*LTILE / NBFRAMEANIM ) //Sinon si elle est comprise entre 1/3 et 2/3
            {
                sf::Rect<int> gauche1( l/NBFRAMEANIM ,h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> gaucheHaut1(l/NBFRAMEANIM , h/4 , l/NBFRAMEANIM , h/8);
                sf::Rect<int> gaucheBas1(l/NBFRAMEANIM , 3*h/8 , l/NBFRAMEANIM , h/8);
                m_apparence.setTextureRect(gauche1); // On donne le sprite numero 2
                m_apparenceHaut.setTextureRect(gaucheHaut1);
                m_apparenceBas.setTextureRect(gaucheBas1);

            }
            else if(m_distanceParcourue>= 2 * LTILE / NBFRAMEANIM && m_distanceParcourue < 3* LTILE / NBFRAMEANIM ) //Sinon si elle est comprise entre 2/3 et la largeur totale
            {
                sf::Rect<int> gauche2(2*l/NBFRAMEANIM,h/4, l / NBFRAMEANIM,h/4);
                sf::Rect<int> gaucheHaut2(2*l/NBFRAMEANIM , h/4 , l /NBFRAMEANIM , h/8);
                sf::Rect<int> gaucheBas2(2*l/NBFRAMEANIM , 3*h/8 , l / NBFRAMEANIM , h/8);
                m_apparence.setTextureRect(gauche2);//On change un derniere fois la tile pour celle de fin danimation
                m_apparenceHaut.setTextureRect(gaucheHaut2);
                m_apparenceBas.setTextureRect(gaucheBas2);

            }
            /*else if(m_distanceParcourue>= 3 * LTILE / NBFRAMEANIM && m_distanceParcourue < LTILE ) //Sinon si elle est comprise entre 2/3 et la largeur totale
            {
                if(NBFRAMEANIM>3)
                {
                    sf::Rect<int> gauche3(3*l/NBFRAMEANIM,h/4,4*l/NBFRAMEANIM,h/2);
                    sf::Rect<int> gaucheHaut3(3*l/NBFRAMEANIM , h/4 , 4*l/NBFRAMEANIM , 3*h/8);
                    sf::Rect<int> gaucheBas3(3*l/NBFRAMEANIM , 3*h/8 , 4*l/NBFRAMEANIM , h/2);
                    m_apparence.setTextureRect(gauche3);//On change un derniere fois la tile pour celle de fin danimation
                    m_apparenceHaut.setTextureRect(gaucheHaut3);
                    m_apparenceBas.setTextureRect(gaucheBas3);
                }

            }*/
            else//enfin si on depasse la longueur du tile ou que l'on ai une distance incohérente
            {
                m_mouvementEnCour = false;//on stoppe le mouvement
                m_tempsDepInitialise= false;
                m_distanceParcourue = 0;//on réinitialise la distance à 0

                sf::Rect<int> gauche0(0,h/4,l/NBFRAMEANIM,h/2);
                sf::Rect<int> gaucheHaut0(0,h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> gaucheBas0(0,3*h/8,l/NBFRAMEANIM,h/8);

                m_apparence.setTextureRect(gauche0);       //On affiche le premier sprite du joueur
                m_apparenceHaut.setTextureRect(gaucheHaut0);
                m_apparenceBas.setTextureRect(gaucheBas0); // et on remet le sprite de base en fonction du sens a l'apparence du personnage.

            }

        }

        else if (m_sens == 2)   //Pour explication voir cas m_sens== 4
        {


            m_distanceParcourue = (m_vitesseDep * LTILE) * (temps.getElapsedTime() - m_tempsDebut);

            m_position.y = ((m_Y -1) * LTILE)- ((h/4) - HTILE) + m_distanceParcourue;
            m_apparence.setPosition(pos.x,m_position.y);
            m_apparenceHaut.setPosition(m_apparence.getPosition());
            m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h / 8 );

            if(m_distanceParcourue>=0 && m_distanceParcourue < LTILE / NBFRAMEANIM)
            {


                sf::Rect<int> Bas0(0,0,l/NBFRAMEANIM,h/4);
                sf::Rect<int> BasHaut0(0,0,l/NBFRAMEANIM,h/8);
                sf::Rect<int> BasBas0(0,h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Bas0);
                m_apparenceHaut.setTextureRect(BasHaut0);
                m_apparenceBas.setTextureRect(BasBas0);


            }
            else if(m_distanceParcourue>=LTILE / NBFRAMEANIM && m_distanceParcourue < 2*LTILE / NBFRAMEANIM )
            {
                sf::Rect<int> Bas1(l/NBFRAMEANIM,0,l/NBFRAMEANIM,h/4);
                sf::Rect<int> BasHaut1(l/NBFRAMEANIM , 0 ,l /NBFRAMEANIM ,h/8);
                sf::Rect<int> BasBas1 (l/NBFRAMEANIM , h/8 ,l /NBFRAMEANIM ,h/8);
                m_apparence.setTextureRect(Bas1);
                m_apparenceHaut.setTextureRect(BasHaut1);
                m_apparenceBas.setTextureRect(BasBas1);

            }
            else if(m_distanceParcourue>=2 * LTILE / NBFRAMEANIM && m_distanceParcourue < 3*LTILE/NBFRAMEANIM )
            {
                sf::Rect<int> Bas2(2*l/NBFRAMEANIM,0,l/NBFRAMEANIM,h/4);
                sf::Rect<int> BasHaut2(2*l/NBFRAMEANIM,0,l/NBFRAMEANIM,h/8);
                sf::Rect<int> BasBas2(2*l/NBFRAMEANIM,h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Bas2);
                m_apparenceHaut.setTextureRect(BasHaut2);
                m_apparenceBas.setTextureRect(BasBas2);

            }
            /*else if(m_distanceParcourue>=3 * LTILE / NBFRAMEANIM && m_distanceParcourue < LTILE )
            {
                sf::Rect<int> Bas3(3*l/NBFRAMEANIM,0,l,h/4);
                sf::Rect<int> BasHaut3(3*l/NBFRAMEANIM,0,l,h/8);
                sf::Rect<int> BasBas3(3*l/NBFRAMEANIM,h/8,l,h/8);
                m_apparence.setTextureRect(Bas3);
                m_apparenceHaut.setTextureRect(BasHaut3);
                m_apparenceBas.setTextureRect(BasBas3);

            }*/
            else
            {
                m_mouvementEnCour = false;
                m_tempsDepInitialise= false;
                m_distanceParcourue = 0;

                sf::Rect<int> Bas0(0,0,l/NBFRAMEANIM,h/4);
                sf::Rect<int> BasHaut0(0,0,l/NBFRAMEANIM,h/8);
                sf::Rect<int> BasBas0(0,h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Bas0);
                m_apparenceHaut.setTextureRect(BasHaut0);
                m_apparenceBas.setTextureRect(BasBas0);


            }
        }

        else if (m_sens == 6)  //Pour explication voir cas m_sens== 4
        {


            m_distanceParcourue = (m_vitesseDep * LTILE) * (temps.getElapsedTime() - m_tempsDebut);

            m_position.x = ((m_X -1) * LTILE)-(l/3 - LTILE) + m_distanceParcourue;
            m_apparence.setPosition(m_position.x,pos.y);
            m_apparenceHaut.setPosition(m_apparence.getPosition());
            m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h / 8 );

            if(m_distanceParcourue>=0 && m_distanceParcourue < LTILE / NBFRAMEANIM)
            {
                sf::Rect<int> Droite0(0,h/2,l/NBFRAMEANIM,h/4);

                sf::Rect<int> DroiteHaut0(0,h/2,l/NBFRAMEANIM,h/8);
                sf::Rect<int> DroiteBas0(0,5*h/8,l/NBFRAMEANIM,h/8);

                m_apparence.setTextureRect(Droite0);

                m_apparenceHaut.setTextureRect(DroiteHaut0);
                m_apparenceBas.setTextureRect(DroiteBas0);
            }
            else if(m_distanceParcourue>=LTILE / NBFRAMEANIM && m_distanceParcourue < 2*LTILE / NBFRAMEANIM )
            {
                sf::Rect<int> Droite1(l/NBFRAMEANIM,h/2,l/NBFRAMEANIM,h/4);
                sf::Rect<int> DroiteHaut1(l/NBFRAMEANIM , h/2 ,  l/NBFRAMEANIM , h/8);
                sf::Rect<int> DroiteBas1 (l/NBFRAMEANIM , 5*h/8 ,l/NBFRAMEANIM,  h/8);
                m_apparence.setTextureRect(Droite1);
                m_apparenceHaut.setTextureRect(DroiteHaut1);
                m_apparenceBas.setTextureRect(DroiteBas1);
            }
            else if(m_distanceParcourue>=  2*LTILE / NBFRAMEANIM && m_distanceParcourue < 3*LTILE / NBFRAMEANIM )
            {
                sf::Rect<int> Droite2(2*l/NBFRAMEANIM,h/2,l/NBFRAMEANIM,h/4);
                sf::Rect<int> DroiteHaut2(2*l/NBFRAMEANIM , h/2 , l/NBFRAMEANIM, h/8 );
                sf::Rect<int> DroiteBas2 (2*l/NBFRAMEANIM , 5*h/8 , l/NBFRAMEANIM , h/8);
                m_apparence.setTextureRect(Droite2);
                m_apparenceHaut.setTextureRect(DroiteHaut2);
                m_apparenceBas.setTextureRect(DroiteBas2);

            }
            /*else if(m_distanceParcourue>=  3*LTILE / NBFRAMEANIM && m_distanceParcourue < LTILE )
            {
                sf::Rect<int> Droite3(3*l/NBFRAMEANIM,h/2,l,3*h/4);

                sf::Rect<int> DroiteHaut3(3*l/NBFRAMEANIM , h/2 , l, 5*h/8 );
                sf::Rect<int> DroiteBas3 (3*l/NBFRAMEANIM , 5*h/8 , l , 3*h/4);

                m_apparence.setTextureRect(Droite3);

                m_apparenceHaut.setTextureRect(DroiteHaut3);
                m_apparenceBas.setTextureRect(DroiteBas3);

            }*/
            else
            {
                m_mouvementEnCour = false;
                m_tempsDepInitialise= false;
                m_distanceParcourue = 0;

                sf::Rect<int> Droite0(0,h/2,l/NBFRAMEANIM,h/4);
                sf::Rect<int> DroiteHaut0(0,h/2,l/NBFRAMEANIM,h/8);
                sf::Rect<int> DroiteBas0(0,5*h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Droite0);
                m_apparenceHaut.setTextureRect(DroiteHaut0);
                m_apparenceBas.setTextureRect(DroiteBas0);
            }

        }

        else if (m_sens == 8)  //Pour explication voir cas m_sens== 4
        {

            m_distanceParcourue = (m_vitesseDep * LTILE) * (temps.getElapsedTime() - m_tempsDebut);


            m_position.y = ((m_Y +1) * LTILE) - ((h/4) - HTILE)- m_distanceParcourue;
            m_apparence.setPosition(pos.x,m_position.y);
            m_apparenceHaut.setPosition(m_apparence.getPosition());
            m_apparenceBas.setPosition(m_apparenceHaut.getPosition().x,m_apparenceHaut.getPosition().y + h / 8 );


            if(m_distanceParcourue>=0 && m_distanceParcourue < LTILE / NBFRAMEANIM)
            {

                sf::Rect<int> Haut0(0,3*h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> HautHaut0(0,3*h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> HautBas0(0,7*h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Haut0);
                m_apparenceHaut.setTextureRect(HautHaut0);
                m_apparenceBas.setTextureRect(HautBas0);
            }
            else if(m_distanceParcourue>=LTILE / NBFRAMEANIM && m_distanceParcourue < 2*LTILE / NBFRAMEANIM )
            {
                sf::Rect<int> Haut1(l/NBFRAMEANIM,3*h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> HautHaut1(l/NBFRAMEANIM,3*h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> HautBas1(l/NBFRAMEANIM,7*h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Haut1);
                m_apparenceHaut.setTextureRect(HautHaut1);
                m_apparenceBas.setTextureRect(HautBas1);

            }
            else if(m_distanceParcourue>= 2* LTILE / NBFRAMEANIM && m_distanceParcourue < 3*LTILE /NBFRAMEANIM )
            {
                sf::Rect<int> Haut2(2*l/NBFRAMEANIM,3*h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> HautHaut2(2*l/NBFRAMEANIM,3*h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> HautBas2(2*l/NBFRAMEANIM,7*h/8,l/NBFRAMEANIM,h/8);
                m_apparence.setTextureRect(Haut2);
                m_apparenceHaut.setTextureRect(HautHaut2);
                m_apparenceBas.setTextureRect(HautBas2);

            }/*
            else if(m_distanceParcourue>= 3* LTILE / NBFRAMEANIM && m_distanceParcourue < LTILE )
            {
                sf::Rect<int> Haut3(3*l/NBFRAMEANIM ,3*h/4,l,h);
                sf::Rect<int> HautHaut3(3*l/NBFRAMEANIM ,3*h/4,l,7*h/8);
                sf::Rect<int> HautBas3(3*l/NBFRAMEANIM ,7*h/8,l,h);
                m_apparence.setTextureRect(Haut3);
                m_apparenceHaut.setTextureRect(HautHaut3);
                m_apparenceBas.setTextureRect(HautBas3);

            }*/
            else
            {
                m_mouvementEnCour = false;
                m_tempsDepInitialise= false;
                m_distanceParcourue = 0;

                sf::Rect<int> Haut0(0,3*h/4,l/NBFRAMEANIM,h/4);
                sf::Rect<int> HautHaut0(0,3*h/4,l/NBFRAMEANIM,h/8);
                sf::Rect<int> HautBas0(0,7*h/8,l/NBFRAMEANIM,h/4);
                m_apparence.setTextureRect(Haut0);
                m_apparenceHaut.setTextureRect(HautHaut0);
                m_apparenceBas.setTextureRect(HautBas0);

            }
        }


    }
}


void Personnage::resetTempsDeb()
{
    m_tempsDebut=0;

}

