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
#include "Randomizer.hpp"



#include <math.h>
#include <vector>
#include "constantes.h"
#include <iostream>
#include <fstream>
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
    view1(Vector2f(0,HFENETRE / 2),Vector2f(LFENETRE,HFENETRE)),
    gestionSouris(&fenetrePrincipale)
{
    view1.zoom(1.2);
    if (!font.loadFromFile("Data/Fonts/Timeless.ttf")) {
        std::cout<<"erreur avec Timeless.ttf"<<std::endl;
    }

    if(!textBoutonR.loadFromFile("Data/GUI/boutonf.png")) std::cout<<"Erreur avec texture boutonf.png"<<std::endl;
    if(!textBoutonV.loadFromFile("Data/GUI/boutond.png")) std::cout<<"Erreur avec texture boutond.png"<<std::endl;

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
      m_joueur = nullptr;

       fenetrePrincipale.setVerticalSyncEnabled(true);
       rechercheFichier();

       m_ptrthis = this;

}

Jeu::~Jeu()
{
    if(m_carte!=nullptr) delete m_carte;
    if(m_ressourceHolder!=nullptr) delete m_ressourceHolder;
    if(m_joueur!= nullptr)  delete m_joueur;

}


bool Jeu::objectifRempli()
{

    m_objectifRestant = m_repereObjectif.size();
    Objectif * cast;
    for(unsigned i=0; i< m_repereObjectif.size(); i++) {
        cast = dynamic_cast<Objectif*>(m_carte->getElementHolder()[m_repereObjectif[i]]);
        cast->testEtat();


        if(cast->estResolu()) {
            m_objectifRestant --;
        }

        std::cout<<m_objectifRestant <<"\b" ;

    }
    if(m_objectifRestant == 0) {
        return true;
    } else    return false;

}

int Jeu::gagner()
{
    return EXIT_SUCCESS;

}

void Jeu::menuPrincipal()
{
    fenetrePrincipale.setKeyRepeatEnabled(false);

    lgui::Bouton jouer(font,&textBoutonR,&textBoutonV);  lgui::Bouton quitter(font,&textBoutonR,&textBoutonV);
    jouer.setTitre("Jouer");                                               quitter.setTitre("Quitter");
    jouer.setTailleTexte(15);                                             quitter.setTailleTexte(15);



     lgui::Bouton retour(font,&textBoutonR,&textBoutonV);
     retour.setTitre("Retour");
     retour.setTailleTexte(15);

    lgui::Bouton esbrouffe(font,&textBoutonR,&textBoutonV);
     esbrouffe.setTitre("Esbrouffe");
     esbrouffe.setTailleTexte(15);


     lgui::Bouton charger(font,&textBoutonR,&textBoutonV);
     charger.setTitre("Charger");
     charger.setTailleTexte(15);

      lgui::Bouton aleatoire(font,&textBoutonR,&textBoutonV);
     aleatoire.setTitre("Aleatoire");
     aleatoire.setTailleTexte(15);

    lgui::ZoneSaisie saisieNom( font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 ), sf::Color::Green ,sf::Color::Blue);

    jouer.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x ,HFENETRE /2 - 100));
    esbrouffe.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x ,HFENETRE /2 ));
    quitter.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x ,HFENETRE /2+100));
    charger.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x /2  ,HFENETRE /2+100));
    aleatoire.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x /2  ,HFENETRE /2-100));
    retour.setPosition(sf::Vector2f(LFENETRE  - textBoutonV.getSize().x  - 30  ,HFENETRE -100));

    jouer.setFenetrelie(fenetrePrincipale);
    esbrouffe.setFenetrelie(fenetrePrincipale);
    charger.setFenetrelie(fenetrePrincipale);
    aleatoire.setFenetrelie(fenetrePrincipale);
    quitter.setFenetrelie(fenetrePrincipale);
    saisieNom.setFenetrelie(fenetrePrincipale);
    retour.setFenetrelie(fenetrePrincipale);
    sf::Event event;


    while (fenetrePrincipale.isOpen()) {

        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();

                 if(m_pageMenu==2)
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
                return;

        }
        break;
        case 1:
        if(esbrouffe.actionner()) {
            m_pageMenu++;

        }
        if(retour.actionner()) {
        m_pageMenu--;
        }
        break;
            case 2:
            if(aleatoire.actionner())
            {

                int randnb;
                string carte;
                randnb= Randomizer::Random( 0, m_tabCartes.size()-1); //-1 est une sécurité pour pas sortir du tableau
                carte=  m_tabCartes[randnb];
                carte.resize(carte.size() - 4);// -4 pour retirer le ".map"
                chargerCarte(carte);

                Jeu::jouer();


            }
            if(charger.actionner())
            {

            std::string nom;
            nom =  saisieNom.getTexte() ;
            if(chargerCarte(nom))
            Jeu::jouer();

            }
             if(retour.actionner())
            {
            m_pageMenu--;
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
        if(m_pageMenu==1)
        {
        esbrouffe.afficher();//
        retour.afficher();
        }
        else if(m_pageMenu == 2)
        {
            aleatoire.afficher();
            charger.afficher();
            saisieNom.afficher();
            retour.afficher();

        }
        fenetrePrincipale.display();
        }
    }




void Jeu::jouer()
{
    //Création de l'interface bouton
     reglerVue();
     lgui::Bouton recharger(font,&textBoutonR,&textBoutonV);
     recharger.setTitre("Recharger");
     recharger.setTailleTexte(15);
     recharger.setFenetrelie(fenetrePrincipale);
     recharger.setPosition(sf::Vector2f(LFENETRE - (textBoutonV.getSize().x + 15),HFENETRE - (textBoutonV.getSize().y + 30)));

      lgui::Bouton retour(font,&textBoutonR,&textBoutonV);
     retour.setTitre("Retour");
     retour.setTailleTexte(15);
     retour.setFenetrelie(fenetrePrincipale);
     retour.setPosition(sf::Vector2f(LFENETRE - (textBoutonV.getSize().x + 15),HFENETRE - (textBoutonV.getSize().y + 100)));


      std::string infSouris;

    //horloge pour limiter les evenements produit par seconde
    sf::Clock horlogeEvent;
    sf::Time tempsBoucleEvent;

    if(m_joueur != nullptr ) delete m_joueur; //joueur...
    m_joueur = new Joueur(fenetrePrincipale,m_carte);


    while (fenetrePrincipale.isOpen()) {
        sf::Event event;

        //Gestion des evenements et saisies utilisateur...
        while (fenetrePrincipale.pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();
            }

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) view1.move(-150 * m_horlogeInterne.getElapsedTime().asSeconds(),0); // deplacement de la camera
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) view1.move(150 * m_horlogeInterne.getElapsedTime().asSeconds(),0);
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view1.move(0,-150 * m_horlogeInterne.getElapsedTime().asSeconds());
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view1.move(0,150 * m_horlogeInterne.getElapsedTime().asSeconds());
         m_horlogeInterne.restart();

        if( objectifRempli() && !m_joueur->enDeplacement()){ return; /*gagner();*/}

        if(horlogeEvent.getElapsedTime().asMilliseconds() - tempsBoucleEvent.asMilliseconds()>10) {
           m_joueur->gererClavier(*m_ptrthis);
            tempsBoucleEvent = horlogeEvent.getElapsedTime();
        }

        if(recharger.actionner())
        {
                chargerCarte(m_carte->getNom());
                if(m_joueur != nullptr ) delete m_joueur; //joueur...
                m_joueur = new Joueur(fenetrePrincipale,m_carte);

        }
        if(retour.actionner())
        {
            return;
        }

        //Actualise l'animation du personnage
       m_joueur->animer();

        //Placement dans la vue prevue pour le jeu
        fenetrePrincipale.setView(view1);
        //Calcul des coordonées souris
        gestionSouris.CalcCoordCarte();
       /* infSouris = "Souris en position : X:" + utils::ConvertionFltString(gestionSouris.getCoordSouris().x )+  "Y:" +utils::ConvertionFltString(gestionSouris.getCoordSouris().y);
        infoSouris.setString(infSouris);
        selecteur.positionnerSelecteur(gestionSouris);*/


        fenetrePrincipale.clear(); //nettoyage de la fenetre


     //   if(gestionSouris.getCoordSouris().x<m_carte->getTaille() && gestionSouris.getCoordSouris().x>=0 && gestionSouris.getCoordSouris().y>=0 && gestionSouris.getCoordSouris().y< m_carte->getTaille()) {
     //     fenetrePrincipale.draw(selecteur.getSprite());
    //}

        fenetrePrincipale.draw(m_carte->getSprCarte());

        for(unsigned int i = 0 ; i< m_repereObjectif.size();i++) //Dessin des objectifs
        {
            fenetrePrincipale.draw(m_carte->getElementHolder()[m_repereObjectif[i]]->getApparence());
        }

        for(unsigned int y= 0 ; y<m_tabElement.size();y++) //dessin du reste.
        {

            for(unsigned int x =0 ; x< m_tabElement[y].size();x++ )
            {
                if(m_tabElement[y][x] !=nullptr)
                {
                    if(m_tabElement[y][x]->getType() != DEPART)
                    fenetrePrincipale.draw(m_tabElement[y][x]->getApparence());
                }
            }

        }

        m_joueur->afficher(fenetrePrincipale);


        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        recharger.afficher();
        retour.afficher();
       // fenetrePrincipale.draw(infoSouris);
        fenetrePrincipale.draw(infoVersion);
        fenetrePrincipale.display();


    }

}


bool Jeu::chargerCarte(std::string const &nom)
{

    if(m_carte != nullptr) delete m_carte; //Si une carte existe dejà , on la supprime
    m_carte = new Carte(); //On en crée une vierge
   if( !m_carte->charger(nom)) //On charge la carte à partir du fichier
        {
             return false; // si on echoue
        }
   else // Si la carte à correctement chargé
   {

    if(m_ressourceHolder != nullptr) delete m_ressourceHolder; // On supprime le ressourceholder si il existe deja
    m_ressourceHolder= new RessourceHolder(m_carte->getPackRessource()); // On en crée un nouveau avec le pack de ressource de la carte.

    for(unsigned int i = 0 ; i<Element::tableauElement.size() ; i++) // On reset tout les elements deja existant .
    {
        delete Element::tableauElement[i];

    }


    Element::tableauElement.clear(); // on désalloue tout le vector
    m_carte->creerElement(*m_ressourceHolder); // et on le refait pour la carte actuelle.
    trierElement(); // Enfin on tri les elements  dans un vector de jeu:: en enlevant le Depart et les objectif (pour l'affichage)

    return true;

   }

}

void Jeu::trierElement()
{

    if(m_tabElement.size()>0)
    {

        m_tabElement.clear();
    }

    for(unsigned int i = 0; i< TAILLE_MAX;i++)
    {
        m_tabElement.push_back(std::vector<Element*>(TAILLE_MAX));//Creation d'un vector double dimensionnel de taille TAILLE_MAX ( 15)

    }

    InitNombreObjectif();

    for(unsigned int i = 0 ; i< m_carte->getElementHolder().size();i++) //copie des pointeurs sur les element dans le tableau ,
    {
        if(m_carte->getElementHolder()[i]->getType() != OBJECTIF && m_carte->getElementHolder()[i]->getType() != DEPART) //a l'exception des OBJECTIF
        m_tabElement[m_carte->getElementHolder()[i]->getPosition().y][m_carte->getElementHolder()[i]->getPosition().x] = m_carte->getElementHolder()[i] ;

    }


}

void Jeu::deplacerElement(sf::Vector2f positionActuelle,sf::Vector2f positionNouvelle)
{
    Element* ptr;

    ptr= m_tabElement[positionActuelle.y][positionActuelle.x];
    m_tabElement[positionActuelle.y][positionActuelle.x] =nullptr;
    m_tabElement[positionNouvelle.y][positionNouvelle.x] = ptr;

}

std::vector<std::vector<Element*>> Jeu::getTabElement()
{
    return m_tabElement;

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

void Jeu::reglerVue()
{

    view1.setCenter(0, m_carte->getSprCarte().getTexture()->getSize().y / 2);
}

void Jeu::AfficherScene()
{}
void  Jeu::AfficherHud()
{}

void Jeu::InitNombreObjectif()
{
   m_repereObjectif.clear();

    if(m_repereObjectif.size()==0)
        { // protection
            for(unsigned int i=0 ; i< m_carte->getElementHolder().size(); i++) { //on parcourt le tableau d'element
            if( m_carte->getElementHolder()[i]->getType() == OBJECTIF) { // Si on tombe sur un objectif
                m_repereObjectif.push_back(i); // On enregistre sa position dans le tableau d'element dans un autre tableau.

            }
        }
    }
}


void Jeu::rechercheFichier()
{

    string cheminCarte = ".\\Cartes";

    system("dir Cartes\\*.map* /b > liste.txt");

     std::ifstream fichier("liste.txt");
     std::string s;
     unsigned int i = 0;

    if(fichier){
        while(std::getline(fichier,s))
            {

                m_tabCartes.push_back(s);
               //std::cout<<m_tabCartes[i]<<std::endl;
               i++;
            }
    }
    else
    {
        std::cout << "Ne peut ouvrir " << std::endl;
    }
    fichier.close();

}
