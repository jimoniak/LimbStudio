
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
#include "joueur.hpp"





Joueur::Joueur(sf::RenderWindow &fenetre,Carte* carte)
{


    m_fenetre = &fenetre;
    m_carte = carte;
    m_coteCarte = m_carte->getTaille();

    m_direction = 0;
    m_enDeplacement = false;




    chargementTexture();
    // std::cout<<m_tailleTexture.x<<std::endl;

    bool departcharge =false;
    for(unsigned int i =0;i<m_carte->getElementHolder().size();i++)
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

bool Joueur::chargementTexture()
{
    if(!m_apparence.loadFromFile("Data/Player/GabaritPersonnage.png")) {
        std::cout<<"erreur lors de l'ouverture de la texture pour personnage"<<std::endl;
    }
    m_tailleTexture = m_apparence.getSize();
    m_sprite.setTexture(m_apparence);
    m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
    m_enDeplacement=false;

    return true;

}

void Joueur::gererClavier()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) deplacer(1); //HAUT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) deplacer(2);//DROITE
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) deplacer(3);//BAS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) deplacer(4);//GAUCHE

}


void Joueur::pousserElement(Element &element)
{
    if(m_direction==1)  element.Deplacer(sf::Vector2f(0,-1));
    if(m_direction==2)  element.Deplacer(sf::Vector2f(1,0));
    if(m_direction==3)  element.Deplacer(sf::Vector2f(0,1));
    if(m_direction==4)  element.Deplacer(sf::Vector2f(-1,0));

    // std::cout<< element.getPosition().x <<std::endl;

}

bool  Joueur::enDeplacement()
{
    if(m_enDeplacement) return true;
    else                          return false;
}



void Joueur::deplacer(int direction)
{

    bool sortieCarte = true;
    if(!m_enDeplacement) {

        m_direction = direction;
        m_positionDepartAnimation= m_sprite.getPosition();
        unsigned int i;
        unsigned int j=0;
        bool obstacle = false;
        i=0;


        if(direction == 1 && m_position.y >0) { // si on va vers le haut, et que la case où l'on va n'est pas hors de la carte
            for(unsigned int cmpt=0; cmpt< Element::tableauElement.size(); cmpt++) { //on verifie la presence d'element sur la prochaine position du joueur
                if(Element::tableauElement[cmpt]->getPosition().y == (m_position.y -1) && m_position.x == Element::tableauElement[cmpt]->getPosition().x) { //si un element est present,
                    i=cmpt; //on enregistre sa position dans le tableau
                    break; //et on sort de la boucle
                }

            }
            if(!(Element::tableauElement[i]->getPosition().y == (m_position.y - 1)) || !(m_position.x == Element::tableauElement[i]->getPosition().x) ) { //si un element n'est pas present...
                m_position.y-=1;  //on deplace le joueur
                m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y= (-1) * VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;

            }

            else  if(Element::tableauElement[i]->estPoussable()) { //Si presence d'un element, est qu'il est poussable...
                if((m_position.y - 2) >= 0 ) { // si la position futur de l'element n'est pas hors de la carte...


                    for(j=0; j<Element::tableauElement.size(); j++) { // on verifie la presence d'un autre element sur le trajet de l'element poussé
                        if(j != i ) {
                            if(Element::tableauElement[i]->getPosition().x == Element::tableauElement[j]->getPosition().x  && ( Element::tableauElement[i]->getPosition().y - 1) == Element::tableauElement[j]->getPosition().y ) {
                                obstacle=true;
                                if(Element::tableauElement[j]->estFranchissable()) {
                                    if(Element::tableauElement[j]->getType() == OBJECTIF) {
                                        Objectif* cast;
                                        cast = dynamic_cast<Objectif*>(Element::tableauElement[j]);
                                        cast->testEtat();

                                        if(cast->estResolu()) {
                                            obstacle = true;
                                        } else obstacle = false;

                                    } else   obstacle = false;

                                }
                            }
                        }

                    }
                    if(!obstacle) {
                        m_position.y-=1;
                        m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                        m_deplacement.y= (-1) * VECTEUR_DEPLACEMENT_Y ;
                        sortieCarte=false;
                        pousserElement(*Element::tableauElement[i]);

                    }
                }
            } else  if(Element::tableauElement[i]->estFranchissable()) { // si un element est present et franchissable...

                bool presence = false;
                for(unsigned int j=0;j<Element::tableauElement.size();j++)
                {
                    if(j!= i )
                    {
                            if(Element::tableauElement[j]->getPosition() == Element::tableauElement[i]->getPosition())
                            {

                                    presence = true;

                            }
                    }



                }
                if(!presence){
                m_position.y-=1;  //on deplace le joueur
                m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y= (-1) * VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;
                }


            }
        } else if(direction ==2 && m_position.x<m_coteCarte-1) {

            for(unsigned int cmpt=0; cmpt< Element::tableauElement.size(); cmpt++) {

                if(Element::tableauElement[cmpt]->getPosition().x == (m_position.x +1) && m_position.y == Element::tableauElement[cmpt]->getPosition().y) {
                    i=cmpt;
                    break;
                }

            }

            //cout<< Element::tableauElement[i]->getPosition().x <<endl;

            if(!(Element::tableauElement[i]->getPosition().x == (m_position.x + 1)) || !(m_position.y == Element::tableauElement[i]->getPosition().y) ) {
                m_position.x+=1;
                m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y=  VECTEUR_DEPLACEMENT_Y;
                sortieCarte=false;
            }

            else  if(Element::tableauElement[i]->estPoussable()) {
                if((m_position.x + 2) < m_coteCarte ) {



                    for(j=0; j<Element::tableauElement.size(); j++) {
                        if(j != i ) {


                            if((Element::tableauElement[i]->getPosition().x + 1) == Element::tableauElement[j]->getPosition().x  &&  Element::tableauElement[i]->getPosition().y  == Element::tableauElement[j]->getPosition().y ) {
                                obstacle=true;
                                if(Element::tableauElement[j]->estFranchissable()) {
                                    if(Element::tableauElement[j]->getType() == OBJECTIF) {
                                        Objectif* cast;
                                        cast = dynamic_cast<Objectif*>(Element::tableauElement[j]);
                                        cast->testEtat();

                                        if(cast->estResolu()) {
                                            obstacle = true;
                                        } else obstacle = false;

                                    } else   obstacle = false;

                                }
                            }
                        }

                    }
                    if(!obstacle) {

                        m_position.x+=1;
                        m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                        m_deplacement.y=  VECTEUR_DEPLACEMENT_Y ;
                        sortieCarte=false;
                        pousserElement(*Element::tableauElement[i]);

                    }

                }
            } else  if(Element::tableauElement[i]->estFranchissable()) {

                  bool presence = false;
                for(unsigned int j=0;j<Element::tableauElement.size();j++)
                {
                    if(j!= i )
                    {
                            if(Element::tableauElement[j]->getPosition() == Element::tableauElement[i]->getPosition())
                            {

                                    presence = true;

                            }
                    }



                }
                if(!presence)
                {


                m_position.x+=1;
                m_deplacement.x = VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y=  VECTEUR_DEPLACEMENT_Y;
                sortieCarte=false;
                }
            }


        } else if(direction ==3 && m_position.y <m_coteCarte-1) {
            for(unsigned int cmpt=0; cmpt< Element::tableauElement.size(); cmpt++) {

                if(Element::tableauElement[cmpt]->getPosition().y == (m_position.y +1) && m_position.x == Element::tableauElement[cmpt]->getPosition().x) {
                    i=cmpt;
                    break;
                }

            }

            if(!(Element::tableauElement[i]->getPosition().y == (m_position.y + 1)) || !(m_position.x== Element::tableauElement[i]->getPosition().x) ) {
                m_position.y+=1;
                m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y=  VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;
                //  i=Element::tableauElement.size();

            }

            else  if(Element::tableauElement[i]->estPoussable()) {
                if((m_position.y + 2) < m_coteCarte ) {


                    for(j=0; j<Element::tableauElement.size(); j++) {
                        if(j != i ) {
                            if(Element::tableauElement[i]->getPosition().x  == Element::tableauElement[j]->getPosition().x  &&  (Element::tableauElement[i]->getPosition().y  + 1 )== Element::tableauElement[j] -> getPosition().y ) {
                                obstacle=true;
                                if(Element::tableauElement[j]->estFranchissable()) {
                                    if(Element::tableauElement[j]->getType() == OBJECTIF) {
                                        Objectif* cast;
                                        cast = dynamic_cast<Objectif*>(Element::tableauElement[j]);
                                        cast->testEtat();

                                        if(cast->estResolu()) {
                                            obstacle = true;
                                        } else obstacle = false;

                                    } else   obstacle = false;

                                }

                            }
                        }

                    }
                    if(!obstacle) {

                        m_position.y+=1;
                        m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                        m_deplacement.y=  VECTEUR_DEPLACEMENT_Y ;
                        sortieCarte=false;
                        pousserElement(*Element::tableauElement[i]);

                    }
                }
            } else  if(Element::tableauElement[i]->estFranchissable()) {

                 bool presence = false;
                for(unsigned int j=0;j<Element::tableauElement.size();j++)
                {
                    if(j!= i )
                    {
                            if(Element::tableauElement[j]->getPosition() == Element::tableauElement[i]->getPosition())
                            {

                                    presence = true;

                            }
                    }



                }
                if(!presence)
                {
                m_position.y+=1;
                m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y=  VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;
                }
            }
        } else if(direction ==4 && m_position.x>0) {
            for(unsigned int cmpt=0; cmpt< Element::tableauElement.size(); cmpt++) {

                if(Element::tableauElement[cmpt]->getPosition().x == (m_position.x -1) && m_position.y == Element::tableauElement[cmpt]->getPosition().y) {
                    i=cmpt;
                    break;
                }

            }

            if(!(Element::tableauElement[i]->getPosition().x == (m_position.x - 1)) || !(m_position.y == Element::tableauElement[i]->getPosition().y) ) {


                m_position.x-=1;
                m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y= (-1) *  VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;
                //  i=Element::tableauElement.size();

            }

            else  if(Element::tableauElement[i]->estPoussable()) {
                if((m_position.x - 2) >= 0 ) {

                    for(j=0; j<Element::tableauElement.size(); j++) {
                        if(j != i ) {
                            if((Element::tableauElement[i]->getPosition().x  - 1)== Element::tableauElement[j]->getPosition().x  && Element::tableauElement[i]->getPosition().y  == Element::tableauElement[j]->getPosition().y ) {
                                obstacle=true;
                                if(Element::tableauElement[j]->estFranchissable()) {
                                    if(Element::tableauElement[j]->getType() == OBJECTIF) {
                                        Objectif* cast;
                                        cast = dynamic_cast<Objectif*>(Element::tableauElement[j]);
                                        cast->testEtat();

                                        if(cast->estResolu()) {
                                            obstacle = true;
                                        } else obstacle = false;

                                    } else   obstacle = false;

                                }

                            }
                        }

                    }
                    if(!obstacle) {


                        m_position.x-=1;
                        m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                        m_deplacement.y= (-1) *  VECTEUR_DEPLACEMENT_Y ;
                        sortieCarte=false;
                        pousserElement(*Element::tableauElement[i]);
                    }

                }

            } else  if(Element::tableauElement[i]->estFranchissable()) {

                 bool presence = false;
                for(unsigned int j=0;j<Element::tableauElement.size();j++)
                {
                    if(j!= i )
                    {
                            if(Element::tableauElement[j]->getPosition() == Element::tableauElement[i]->getPosition())
                            {

                                 presence = true;

                            }
                    }



                }
                if(!presence)
                {
                m_position.x-=1;
                m_deplacement.x = (-1) * VECTEUR_DEPLACEMENT_X ;
                m_deplacement.y= (-1) *  VECTEUR_DEPLACEMENT_Y ;
                sortieCarte=false;
                }
            }
        }


    }

    if(!sortieCarte) {
        m_enDeplacement =true;
        m_tempsAnimation=sf::seconds(0);
        m_horlogeAnimation.restart();

    }

    if(direction <1 || direction >4) {
        m_enDeplacement = false;

    }






}


void Joueur::animer()
{
    if(m_enDeplacement) {


        if(m_horlogeAnimation.getElapsedTime().asMilliseconds() -m_tempsAnimation.asMilliseconds()> 30) {

            m_sprite.setPosition( m_positionDepartAnimation.x +  (m_deplacement.x * ( m_tempsAnimation.asMilliseconds() / (float)TEMPSANIMATION) )   , m_positionDepartAnimation.y+ (m_deplacement.y * ( m_tempsAnimation.asMilliseconds() / (float)TEMPSANIMATION)) );
            m_tempsAnimation +=  m_horlogeAnimation.getElapsedTime() - m_tempsAnimation;

            if(m_direction ==1) {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 ) {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 2) {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 3) {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) ) {
                    if(frame != 4) {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,0,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }

            if(m_direction ==2) {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 ) {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,     m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 2) {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 3) {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) ) {
                    if(frame != 4) {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }


            if(m_direction ==3) {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 ) {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,     2*m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 2) {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 3) {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) ) {
                    if(frame != 4) {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, 2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0, 2*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                    setPositionspr();
                    m_enDeplacement=false;
                }


            }

            if(m_direction ==4) {


                if( m_tempsAnimation.asMilliseconds() >=0  && m_tempsAnimation.asMilliseconds()< TEMPSANIMATION / 4 ) {
                    if(frame != 1) {
                        m_sprite.setTextureRect(sf::IntRect(0,     3*m_tailleTexture.y/4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 1;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= TEMPSANIMATION / 4 && m_tempsAnimation.asMilliseconds()<  (2 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 2) {
                        m_sprite.setTextureRect(sf::IntRect(m_tailleTexture.x / 4,    3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 2;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>= (2 * TEMPSANIMATION ) / 4  && m_tempsAnimation.asMilliseconds()<  (3 * TEMPSANIMATION )/ 4 ) {
                    if(frame != 3) {
                        m_sprite.setTextureRect(sf::IntRect(2*m_tailleTexture.x/4,    3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 3;
                    }
                }

                else if(m_tempsAnimation.asMilliseconds()>=(3 * TEMPSANIMATION )/ 4 && m_tempsAnimation.asMilliseconds() <  (TEMPSANIMATION) ) {
                    if(frame != 4) {
                        m_sprite.setTextureRect(sf::IntRect(3*m_tailleTexture.x/4, 3*m_tailleTexture.y /4,m_tailleTexture.x /4 , m_tailleTexture.y /4));
                        frame = 4;
                    }
                }

                else {
                    if(frame != 1) {
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
