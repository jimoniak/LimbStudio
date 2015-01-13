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
#include <math.h>
#include <vector>
#include "constantes.h"
#include <iostream>
#include <string>
#include <ios>


#include "outils.hpp"


#include "element.hpp"
#include "carte.hpp"
#include "gestionSouris.hpp"
#include "joueur.hpp"
#include "jeu.hpp"


using namespace sf;
using namespace std;

Jeu::Jeu() :fenetrePrincipale(sf::VideoMode(LFENETRE, HFENETRE), "LimbEscape"),
    view1(Vector2f(0,350),Vector2f(1536,1156)),
    gestionSouris(&fenetrePrincipale)
{
    if (!font.loadFromFile("Data/Fonts/Timeless.ttf")) {
        std::cout<<"erreur avec Timeless.ttf"<<std::endl;
    }

     infoSouris.setFont(font);
     infoSouris.setString("Souris en position : X:  , Y:  "); //text info coordonnées souris
     infoSouris.setColor(sf::Color::Blue);
     infoSouris.setCharacterSize(24);

      infoVersion.setFont(font);
      infoVersion.setString("Souris en position : X:  , Y:  "); //text info coordonnées souris
      infoVersion.setColor(sf::Color::Blue);
      infoVersion.setCharacterSize(18);
      infoVersion.setPosition(0,30);
      infoVersion.setString(VERSION);

      m_pageMenu=0;
      m_ressourceHolder = nullptr;
      m_carte = nullptr;

}

Jeu::~Jeu()
{
    if(m_carte!=nullptr) delete m_carte;
    if(m_ressourceHolder!=nullptr) delete m_ressourceHolder;
    if(m_joueur) delete m_joueur;

}


bool Jeu::objectifRempli()
{

    m_objectifRestant = m_repereObjectif.size();
    Objectif * cast;
    for(unsigned i=0; i< m_repereObjectif.size(); i++) {
        cast = dynamic_cast<Objectif*>(Element::tableauElement[m_repereObjectif[i]]);
        cast->testEtat();


        if(cast->estResolu()) {
            m_objectifRestant --;
        }

    }
    if(m_objectifRestant == 0) {
        return true;
    } else    return false;

}

int Jeu::gagner()
{
    fenetrePrincipale.clear();

    if(debug)cout<<"Gagné!"<<endl;

    if(debug)std::cout<<"fin!"<< endl;
    fenetrePrincipale.close();

    return EXIT_SUCCESS;

}

void Jeu::menuPrincipal()
{
    fenetrePrincipale.setKeyRepeatEnabled(false);

    sf::Texture textBoutonV;
    sf::Texture textBoutonR;
    if(!textBoutonR.loadFromFile("Data/GUI/boutonf.png")) std::cout<<"Erreur avec texture boutonf.png"<<std::endl;
    if(!textBoutonV.loadFromFile("Data/GUI/boutond.png")) std::cout<<"Erreur avec texture boutond.png"<<std::endl;

    lgui::Bouton jouer(font,&textBoutonR,&textBoutonV);  lgui::Bouton quitter(font,&textBoutonR,&textBoutonV);
    jouer.setTitre("Jouer");                                               quitter.setTitre("Quitter");
    jouer.setTailleTexte(15);                                             quitter.setTailleTexte(15);

     lgui::Bouton charger(font,&textBoutonR,&textBoutonV);
     charger.setTitre("Charger");
     charger.setTailleTexte(15);

    lgui::ZoneSaisie saisieNom( font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 - 50), sf::Color::Green ,sf::Color::Blue);

    jouer.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x ,HFENETRE /2 - 100));
    quitter.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x ,HFENETRE /2+100));
    charger.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x /2  ,HFENETRE /2+100));

    jouer.setFenetrelie(fenetrePrincipale);
    charger.setFenetrelie(fenetrePrincipale);
    quitter.setFenetrelie(fenetrePrincipale);
    saisieNom.setFenetrelie(fenetrePrincipale);
    sf::Event event;


    while (fenetrePrincipale.isOpen()) {

        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();

                 if(m_pageMenu==1)
            {
                saisieNom.actif(event);
            }

        }

        switch(m_pageMenu)
        {
            case 0:
        if(jouer.actionner()) {
            m_pageMenu++;

        }
        if(quitter.actionner()) {

        }
        break;
            case 1:
            if(charger.actionner()) {
            std::string nom;
            nom =  saisieNom.getTexte() ;
            chargerCarte(nom);
            Jeu::jouer();
            }

            break;
        }

        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        fenetrePrincipale.clear();

        if(m_pageMenu==0)
        {
        jouer.afficher();//
        quitter.afficher();//
        }
        else if(m_pageMenu == 1)
        {
            charger.afficher();
            saisieNom.afficher();

        }
        fenetrePrincipale.display();
        }
    }




void Jeu::jouer()
{

    sf::Clock horlogeEvent;
    sf::Time tempsBoucleEvent;
    m_joueur = new Joueur(fenetrePrincipale,m_carte);
    std::string infSouris;

    while (fenetrePrincipale.isOpen()) {
        sf::Event event;
        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();
        }

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) view1.move(-1,0); // deplacement de la camera
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) view1.move(1,0);
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view1.move(0,-1);
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view1.move(0,1);

        if(horlogeEvent.getElapsedTime().asMilliseconds() - tempsBoucleEvent.asMilliseconds()>30) {
           m_joueur->gererClavier();
            tempsBoucleEvent = horlogeEvent.getElapsedTime();
        }

       m_joueur->animer();

        fenetrePrincipale.setView(view1);
        gestionSouris.CalcCoordCarte();
        infSouris = "Souris en position : X:" + utils::ConvertionFltString(gestionSouris.getCoordSouris().x )+  "Y:" +utils::ConvertionFltString(gestionSouris.getCoordSouris().y);
        infoSouris.setString(infSouris);
        selecteur.positionnerSelecteur(gestionSouris);

        fenetrePrincipale.clear();

        if(gestionSouris.getCoordSouris().x<m_carte->getTaille() && gestionSouris.getCoordSouris().x>=0 && gestionSouris.getCoordSouris().y>=0 && gestionSouris.getCoordSouris().y< m_carte->getTaille()) {
            fenetrePrincipale.draw(selecteur.getSprite());
        }
        fenetrePrincipale.draw(m_carte->getSprCarte());

        for(unsigned int i= 0 ; i< m_carte->getElementHolder().size(); i++)
        {
            if(m_carte->getElementHolder()[i]->getType() != DEPART)
            {
            fenetrePrincipale.draw(m_carte->getSprElem(i));
            }
        }

        m_joueur->afficher(fenetrePrincipale);


        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        fenetrePrincipale.draw(infoSouris);
        fenetrePrincipale.draw(infoVersion);

        fenetrePrincipale.display();
    }

}


bool Jeu::chargerCarte(std::string const &nom)
{


    m_carte = new Carte();
   if( !m_carte->charger(nom))
        {
             return false;
        }
   else
   {

    if(m_ressourceHolder != nullptr) delete m_ressourceHolder;
    m_ressourceHolder= new RessourceHolder(m_carte->getPackRessource());

    m_carte->creerElement(*m_ressourceHolder);

    return true;



   }

}
void Jeu::intro()
{


    sf::Text TextPasse;

    TextPasse.setFont(font);
    TextPasse.setCharacterSize(15);                      //texte qui indique la commande à utiliser pour passer
    TextPasse.setColor(Color::White);
    TextPasse.setPosition(20,HFENETRE -50);
    TextPasse.setString("Appuyer sur E pour passer...");
    sf::Event event;


    sf::Texture textureLimb;               //Logo Limb'Studio
    sf::Texture textureSfml;
    if(!textureLimb.loadFromFile("Data/LimbStudio.png")) cout<< "Logo non chargé!" <<endl;
    if(!textureSfml.loadFromFile("Data/sfml.png")) cout<< "Logo non chargé!" <<endl;
    textureLimb.setSmooth(true);

    sf::Sprite LimbSp;
    sf::Sprite sfmlSp;      //Logo SFML

    LimbSp.setColor(sf::Color(255,255,255,0));
    LimbSp.setTexture(textureLimb);
    LimbSp.setPosition((LFENETRE - textureLimb.getSize().x) / 2 ,(HFENETRE - textureLimb.getSize().y) / 2 );

    sfmlSp.setColor(sf::Color(255,255,255,0));
    sfmlSp.setTexture(textureSfml);
    sfmlSp.setPosition((LFENETRE - textureSfml.getSize().x) / 2 ,(HFENETRE - textureSfml.getSize().y) / 2 );

    sf::Clock temps;
    sf::Time tempsDep = temps.getElapsedTime();
    float tempsatt= 0;

    while(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5 && fenetrePrincipale.isOpen()) { //Boucle pour la SFML
        if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()< 1) {
            sfmlSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()) * 255)));//On fait apparaitre le Logo
        } else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 1  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 3) {
            sfmlSp.setColor(sf::Color(255,255,255,255)); //on garde le logo afficher un certain temps
        } else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 3  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 4) {
            sfmlSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep.asSeconds() + 3)) * 255)))); //on fait disparaitre le logo
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds())))); //on change la transparence du texte de commande selon un sinus
        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01) {
            fenetrePrincipale.clear();
            fenetrePrincipale.draw(sfmlSp);
            fenetrePrincipale.draw(TextPasse);   //affichage...
            fenetrePrincipale.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }

        while (fenetrePrincipale.pollEvent(event)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))    return;

            switch(event.type ) {
            case  sf::Event::Closed :
                fenetrePrincipale.close();
                break;
            default :
                break;
            }


        }




    }

    temps.restart();  //on reset le temps
    tempsDep = temps.getElapsedTime();//on reactualise la pos de depart du temsp
    tempsatt= 0; //temps pour l'affichage.


    while(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5 && fenetrePrincipale.isOpen()) { //Même procéder pour le Logo de Jinn Studio
        if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 1) {
            LimbSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()) * 255)));
        } else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 1  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 4) {
            LimbSp.setColor(sf::Color(255,255,255,255));
        } else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 4  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5) {
            LimbSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep.asSeconds() + 4)) * 255))));
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));
        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01) {
            fenetrePrincipale.clear();
            fenetrePrincipale.draw(LimbSp);
            fenetrePrincipale.draw(TextPasse);   //affichage...
            fenetrePrincipale.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }

        while (fenetrePrincipale.pollEvent(event)) {
            switch(event.type ) {
            case  sf::Event::Closed :
                fenetrePrincipale.close();
                break;
            default :
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))    return;
        }


    }


}

bool Jeu::demarrer()
{

    return EXIT_SUCCESS;
}

void Jeu::AfficherScene()
{}
void  Jeu::AfficherHud()
{}

void Jeu::InitNombreObjectif()
{

    if(m_repereObjectif.size()==0) { // protection
        for(unsigned int i=0 ; i< m_carte->getElementHolder().size(); i++) { //on parcourt le tableau d'element
            if( m_carte->getElementHolder()[i]->getType() == OBJECTIF) { // Si on tombe sur un objectif
                m_repereObjectif.push_back(i); // On enregistre sa position dans le tableau d'element dans un autre tableau.

            }
        }
    }
}
