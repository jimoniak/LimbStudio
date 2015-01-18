
/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "constantes.h"
#include "carte.hpp"
#include "element.hpp"

#include "jeu.hpp"
#include "joueur.hpp"





Joueur::Joueur(sf::RenderWindow &fenetre,Carte* carte)
{

    m_fenetre = &fenetre;
    m_carte = carte;
    m_coteCarte = m_carte->getTaille();
    m_position = sf::Vector2f(0,0);

    m_direction = 0;
    m_enDeplacement = false;

    chargementTexture();
    // std::cout<<m_tailleTexture.x<<std::endl;

    bool departcharge =false;
    for(unsigned int i =0; i<m_carte->getElementHolder().size(); i++)
    {
        if(m_carte->getElementHolder()[i]->getType() == DEPART)
        {
            m_position = m_carte->getElementHolder()[i]->getPosition();
            departcharge=true;
        }

    }
    if(!departcharge)
    {
        std::cerr<<"erreur,chargement du joueur"<<std::endl;
        return;

    }

    setPositionspr();


}

Joueur::~Joueur()
{


}

bool Joueur::chargementTexture()
{
    if(!m_apparence.loadFromFile("Data/Player/GabaritPersonnage.png"))
    {
        std::cout<<"erreur lors de l'ouverture de la texture pour personnage"<<std::endl;
    }
    m_tailleTexture = m_apparence.getSize();
    m_sprite.setTexture(m_apparence);
    m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
    m_enDeplacement=false;

    return true;

}

void Joueur::gererClavier(Jeu &jeu)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) deplacer(1,jeu); //HAUT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) deplacer(2,jeu);//DROITE
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) deplacer(3,jeu);//BAS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) deplacer(4,jeu);//GAUCHE

}


void Joueur::pousserElement(Element &element,Jeu &jeu)
{
    sf::Vector2f deplacement;
    if(m_direction==1)  deplacement = sf::Vector2f(0,-1);
    if(m_direction==2)  deplacement = sf::Vector2f(1,0);
    if(m_direction==3)  deplacement = sf::Vector2f(0,1);
    if(m_direction==4)  deplacement = sf::Vector2f(-1,0);

    jeu.deplacerElement(element.getPosition(),element.getPosition()+deplacement);
    element.Deplacer(deplacement);

    // std::cout<< element.getPosition().x <<std::endl;

}

bool  Joueur::enDeplacement()
{
    if(m_enDeplacement) return true;
    else                          return false;
}



void Joueur::deplacer(int direction,Jeu &jeu)
{

    bool sortieCarte = true;
    if(!m_enDeplacement)
    {

        m_direction = direction; // direction dans laquel on veut se deplacer
        m_positionDepartAnimation= m_sprite.getPosition(); // Offset pour le deplacement du sprite personnage
        sf::Vector2f  vecteurDep,deplacement; // vecteur servant a valider le deplacement
        bool obstacle = false; // pour verifier si oui ou non il y a un obstacle
        int x,y=0;

        if(direction==1) vecteurDep= sf::Vector2f(0,-1);
        if(direction==2) vecteurDep= sf::Vector2f(1,0);
        if(direction==3) vecteurDep= sf::Vector2f(0,1);
        if(direction==4) vecteurDep= sf::Vector2f(-1,0);

        deplacement= vecteurDep;

         if(direction==1 ) { m_deplacement.x = VECTEUR_DEPLACEMENT_X;m_deplacement.y = VECTEUR_DEPLACEMENT_Y * vecteurDep.y;}
         if(direction == 3) { m_deplacement.x = VECTEUR_DEPLACEMENT_X*(-1);m_deplacement.y = VECTEUR_DEPLACEMENT_Y ;}
        if(direction==2 ) { m_deplacement.x = VECTEUR_DEPLACEMENT_X * vecteurDep.x;m_deplacement.y = VECTEUR_DEPLACEMENT_Y;}
        if(direction == 4) { m_deplacement.x = VECTEUR_DEPLACEMENT_X * (-1);m_deplacement.y = VECTEUR_DEPLACEMENT_Y *(-1);}


        if((m_position.x + vecteurDep.x >=0 && m_position.x + vecteurDep.x < m_carte->getTaille() )&&  (m_position.y + vecteurDep.y >=0 && m_position.y + vecteurDep.y < m_carte->getTaille() ))
        { //si le deplacement nous fait rester sur la carte.
                      y=m_position.y + vecteurDep.y;
                      x=m_position.x + vecteurDep.x;

                      if(jeu.getTabElement()[y][x] != nullptr)//Si il y a un element
                      {
                          obstacle = true;

                      }



              if(!obstacle)  {m_position += deplacement; sortieCarte=false;}// Si pas d'element , on se deplace.

              else if (! jeu.getTabElement()[y][x]->estFranchissable()) //Si l'element present n'est pas franchissable
              {
                 if( jeu.getTabElement()[y][x]->estPoussable()) //mais que c'est un element poussable
                 {
                     if(jeu.getTabElement()[y + vecteurDep.y][x + vecteurDep.x] == nullptr &&
                        (x + vecteurDep.x >=0 && x + vecteurDep.x <= m_carte->getTaille() )  &&
                        (y + vecteurDep.y >=0 && y + vecteurDep.y <= m_carte->getTaille() )) // et qu'il n'y a rien devant celui-ci  et que l'on sera pas hors de la carte après le deplacement
                     {
                         m_position += deplacement;
                          pousserElement(* jeu.getTabElement()[y][x], jeu); // On pousse la caisse
                           sortieCarte=false;
                     }
                     else{} // sinon on ne fait rien
                 }
              }
        }
    }
        if(!sortieCarte) //Petite condition permettant d'initialiser l'animation du personnage.
    {
        m_enDeplacement =true;
        m_tempsAnimation=sf::seconds(0);
        m_horlogeAnimation.restart();
    }

    if(direction <1 || direction >4)
    {
        m_enDeplacement = false;

    }

}


void Joueur::animer()
{
    if(m_enDeplacement)
    {


        if(m_horlogeAnimation.getElapsedTime().asMilliseconds() -m_tempsAnimation.asMilliseconds()> 30)
        {

            m_sprite.setPosition( m_positionDepartAnimation.x +  (m_deplacement.x * ( m_tempsAnimation.asMilliseconds() / (float)TEMPSANIMATION) )   , m_positionDepartAnimation.y+ (m_deplacement.y * ( m_tempsAnimation.asMilliseconds() / (float)TEMPSANIMATION)) );
            m_tempsAnimation +=  m_horlogeAnimation.getElapsedTime() - m_tempsAnimation;

            if(m_direction ==1)
            {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 )
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 2)
                    {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 3)
                    {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) )
                {
                    if(frame != 4)
                    {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }

            if(m_direction ==2)
            {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 )
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,     m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 2)
                    {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 3)
                    {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) )
                {
                    if(frame != 4)
                    {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }


            if(m_direction ==3)
            {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 )
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,     2*m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 2)
                    {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 3)
                    {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) )
                {
                    if(frame != 4)
                    {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, 2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0, 2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }

            if(m_direction ==4)
            {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 )
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0,     3*m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 2)
                    {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 )
                {
                    if(frame != 3)
                    {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) )
                {
                    if(frame != 4)
                    {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, 3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else
                {
                    if(frame != 1)
                    {
                        m_sprite.setTextureRect(sf::IntRect(0, 3*m_tailleTexture.y /4,m_tailleTexture.x/4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }

            }

        }

    }
}

void Joueur::setPositionspr()
{
    m_sprite.setPosition(-int(m_coteCarte*LARGEUR_TILE)/2 + (DEMI_LTILE * m_position.x - DEMI_LTILE* m_position.y) + ((LARGEUR_TILE * m_coteCarte ) / 2)  - m_tailleTexture.x / 8, DEMI_HTILE * m_position.x + DEMI_HTILE * m_position.y - m_tailleTexture.y / 8);
    // std::cout<<m_sprite.getPosition().x<<"   "<<m_sprite.getPosition().y<<std::endl;
    //m_sprite.setPosition(0,0);
}


void Joueur::afficher(sf::RenderWindow &fenetre)
{
    fenetre.draw(m_sprite);
}

sf::Sprite const Joueur::getSprite()
{
    return m_sprite;

}
