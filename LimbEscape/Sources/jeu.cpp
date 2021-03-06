/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbStudio

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

#include "vignette.hpp"


using namespace sf;
using namespace std;

Jeu::Jeu() :fenetrePrincipale(sf::VideoMode(LFENETRE, HFENETRE), "LimbEscape"),
    view1(Vector2f(0,HFENETRE / 2),Vector2f(LFENETRE,HFENETRE)),
    gestionSouris(&fenetrePrincipale)
{
    view1.zoom(1.2);
    if (!font.loadFromFile("Data/Fonts/upheavtt.ttf")) {
        std::cout<<"erreur avec la police upheavtt.ttf"<<std::endl;
    }

    if(!m_icone.loadFromFile("Data/icone.png")) std::cerr<<"impossible de charger icone.png"<<std::endl;

    fenetrePrincipale.setIcon(16,16,m_icone.getPixelsPtr());

     fond.setSize(sf::Vector2f(LFENETRE,HFENETRE));
     fond.setFillColor(sf::Color(125,125,200));


     m_texlimbEscape.loadFromFile("Data/LimbEscape.png");
     m_limbEscape.setTexture(m_texlimbEscape);


    m_limbEscape.setScale(0.8,0.8);
    m_limbEscape.setPosition(LFENETRE / 2  - (m_texlimbEscape.getSize().x/2   * 0.8)  , 0);

    if(!textBoutonR.loadFromFile("Data/GUI/boutonf.png")) std::cout<<"Erreur avec texture boutonf.png"<<std::endl;
    if(!textBoutonV.loadFromFile("Data/GUI/boutond.png")) std::cout<<"Erreur avec texture boutond.png"<<std::endl;

     infoSouris.setFont(font);
     infoSouris.setString("Souris en position : X:  , Y:  "); //text info coordonnées souris
     infoSouris.setColor(sf::Color::Blue);
     infoSouris.setCharacterSize(24);

      infoVersion.setFont(font);
      infoVersion.setString("Souris en position : X:  , Y:  "); //text info coordonnées souris
      infoVersion.setColor(sf::Color::Blue);
      infoVersion.setCharacterSize(20);
      infoVersion.setStyle(sf::Text::Bold);
      infoVersion.setPosition(0,10);
      infoVersion.setString(VERSION);

      m_pageMenu=0;
      m_ressourceHolder = nullptr;
      m_carte = nullptr;
      m_joueur = nullptr;

       fenetrePrincipale.setVerticalSyncEnabled(true);
       m_tabCartes = rechercheFichier("Cartes\\",".map");
       m_tabSuites = rechercheFichier("Cartes\\Suites\\",".ste");

       m_ptrthis = this;
       m_jouerSuite= false;
       m_comptSuite = 0;

         if (!m_clickbuffer.loadFromFile("Data/Sounds/Clicks/click.wav")) cerr<<"Impossible de charger click.wav"<<endl;
         m_click.setBuffer(m_clickbuffer);

          if(!m_theme.openFromFile("Data/Sounds/Musics/Main.ogg"))
            std::cerr<< "erreur musique!"<<std::endl;

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

        //std::cout<<m_objectifRestant <<"\b" ;

    }
    if(m_objectifRestant == 0) {
        return true;
    } else    return false;

}

int Jeu::gagner()
{
    float tempsEcoule = m_chronometre.getElapsedTime().asSeconds();
    std::string s = utils::ConvertionFltString(tempsEcoule);

    if(s.size() >5) s.resize(5);
    sf::Text temps;
    temps.setFont(font);
    temps.setCharacterSize(18);
    temps.setColor(sf::Color::Blue);
    if(tempsEcoule < 60)
    {
    std::string s = utils::ConvertionFltString(tempsEcoule);
    if(s.size() >5) s.resize(5);
    temps.setString(L"Terminé en : " + s + " secondes ! ");
    }
    else
    {
        int minute = tempsEcoule / 60 ;
        float seconde = tempsEcoule - minute* 60 ;
        std:: string m;
        m = utils::ConvertionFltString(minute);
        s=utils::ConvertionFltString(seconde);
        if(s.size() >5) s.resize(5);

         temps.setString(L"Terminé en : " + m + " minute(s)  et  " + s + "secondes ! ");

    }
    temps.setPosition(LFENETRE/2 - temps.getLocalBounds().width / 2 , HFENETRE / 2 - 150);


    fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());
     lgui::Bouton suite(font,&textBoutonR,&textBoutonV);
     suite.setTitre("Suivant");
     suite.setTailleTexte(15);
     suite.setFenetrelie(fenetrePrincipale);
     suite.setPosition(sf::Vector2f(LFENETRE / 2  - ( textBoutonV.getSize().x /2),HFENETRE /2 - textBoutonR.getSize().y / 2 -15));





      sf::Event event;

    while (fenetrePrincipale.isOpen()) {

        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();


        }

        if(m_horlogeEvent.getElapsedTime().asSeconds() > 0.1)
        {

            if(suite.actionner())
            {
                m_click.play();
                 if(m_jouerSuite) {
                        m_comptSuite++;
                        if(m_comptSuite<m_suiteCarte.size()){
                                desallouer();
                                chargerCarte(m_suiteCarte[m_comptSuite]);
                                m_chronometre.restart();
                                return 0;
                        }
                        else
                        {
                                m_comptSuite =0;
                                m_jouerSuite = false;
                                return 1;
                        }

                }
                else return 1;

            }

        }


        fenetrePrincipale.clear();
        fenetrePrincipale.draw(fond);
        fenetrePrincipale.draw(temps);
        fenetrePrincipale.draw(m_limbEscape);
        suite.afficher();
        fenetrePrincipale.display();

    }
    return 0;

}

void Jeu::menuPrincipal()
{

    fenetrePrincipale.setKeyRepeatEnabled(false);

    sf::RectangleShape fondCredit;
    fondCredit.setFillColor(sf::Color(30,56,65,125));
    fondCredit.setSize(sf::Vector2f(LFENETRE / 2,HFENETRE/2));
    fondCredit.setPosition(LFENETRE/2 - fondCredit.getSize().x/2,HFENETRE/2 - fondCredit.getSize().y/2);

    sf::Text apropos;
    std::string version = VERSION;

    apropos.setFont(font);
    apropos.setCharacterSize(16);
    apropos.setColor(sf::Color::White);

    apropos.setString(L"Crédit : \n \n \n Limbescape réalisé par Jimmy PEAULT pour LimbStudio \n Limbescape est un projet OpenSource sous Licence:  \n CeCILL 2.1 \n\n\n\n" + version);
    apropos.setPosition(fondCredit.getPosition().x + fondCredit.getSize().x / 2 - apropos.getGlobalBounds().width / 2 , fondCredit.getPosition().y + fondCredit.getSize().y / 2 - apropos.getGlobalBounds().height / 2);

    lgui::Bouton jouer(font,&textBoutonR,&textBoutonV);  lgui::Bouton quitter(font,&textBoutonR,&textBoutonV);
    jouer.setTitre("Jouer");                                               quitter.setTitre("Quitter");
    jouer.setTailleTexte(15);                                             quitter.setTailleTexte(15);


     lgui::Bouton retour(font,&textBoutonR,&textBoutonV);
     retour.setTitre("Retour");
     retour.setTailleTexte(15);

      lgui::Bouton credit(font,&textBoutonR,&textBoutonV);
     credit.setTitre("Credit");
     credit.setTailleTexte(15);

    lgui::Bouton esbrouffe(font,&textBoutonR,&textBoutonV);
     esbrouffe.setTitre("Esbrouffe");
     esbrouffe.setTailleTexte(15);

      lgui::Bouton suite(font,&textBoutonR,&textBoutonV);
      suite.setTitre("Suites");
      suite.setTailleTexte(15);

      lgui::Bouton choisirSuite(font,&textBoutonR,&textBoutonV);
      choisirSuite.setTitre("Choisir");
      choisirSuite.setTailleTexte(15);

       lgui::Bouton classique(font,&textBoutonR,&textBoutonV);
      classique.setTitre("Classique");
      classique.setTailleTexte(15);


     lgui::Bouton charger(font,&textBoutonR,&textBoutonV);
     charger.setTitre("Choisir");
     charger.setTailleTexte(15);

      lgui::Bouton aleatoire(font,&textBoutonR,&textBoutonV);
     aleatoire.setTitre("Aleatoire");
     aleatoire.setTailleTexte(15);




    jouer.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2 - 50));
    esbrouffe.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2 + 150 ));
    suite.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2  ,HFENETRE /2 - 50 ));
    choisirSuite.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2 + 150 ));
    classique.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2  ,HFENETRE /2 - 50 ));
    quitter.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x /2,HFENETRE /2+150));
    charger.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2 + 150 ));
    aleatoire.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x /2  ,HFENETRE /2-50));
    retour.setPosition(sf::Vector2f(LFENETRE  - textBoutonV.getSize().x  - 30  ,HFENETRE -100));
    credit.setPosition(sf::Vector2f(LFENETRE  - textBoutonV.getSize().x  - 30  ,HFENETRE -100));

    jouer.setFenetrelie(fenetrePrincipale);
    esbrouffe.setFenetrelie(fenetrePrincipale);
    suite.setFenetrelie(fenetrePrincipale);
    choisirSuite.setFenetrelie(fenetrePrincipale);
    classique.setFenetrelie(fenetrePrincipale);
    charger.setFenetrelie(fenetrePrincipale);
    aleatoire.setFenetrelie(fenetrePrincipale);
    quitter.setFenetrelie(fenetrePrincipale);

    retour.setFenetrelie(fenetrePrincipale);
    credit.setFenetrelie(fenetrePrincipale);

    sf::Event event;

    while (fenetrePrincipale.isOpen()) {

        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();

        }


        if(m_horlogeEvent.getElapsedTime().asSeconds() > 0.1) // protection  afin d'eviter d'appuyer sur  deux boutons qui se superpose sur deux page connexes.
        {
        switch(m_pageMenu)
        {
            case 0:
        if(jouer.actionner()) {
            m_click.play();
            m_pageMenu++;
            m_horlogeEvent.restart();

        }

        if(credit.actionner())
        {
            m_click.play();
            m_pageMenu = 4;
            m_horlogeEvent.restart();


        }
        if(quitter.actionner()) {
                m_click.play();
                return;

        }
        break;
        case 1:
        if(esbrouffe.actionner()) {
            m_click.play();
            m_pageMenu++;
            m_horlogeEvent.restart();

        }
         if(suite.actionner()) {
            m_click.play();
            m_pageMenu=3;
            m_horlogeEvent.restart();

        }
        if(retour.actionner()) {
        m_click.play();
        m_pageMenu--;
        m_horlogeEvent.restart();
        }
        break;
            case 2:
            if(aleatoire.actionner())
            {
                m_click.play();
                int randnb;
                string carte;
                randnb= Randomizer::Random( 0, m_tabCartes.size()-1); //-1 est une sécurité pour pas sortir du tableau
                carte=  m_tabCartes[randnb];
                carte.resize(carte.size() - 4);// -4 pour retirer le ".map"
                chargerCarte(carte);

                Jeu::jouer();
                m_horlogeEvent.restart();


            }
            if(charger.actionner())
            {
            m_click.play();
            std::string nom;
            //nom =  saisieNom.getTexte() ;
            nom = menuVignette(m_tabCartes);
            if(nom != "errStr" && chargerCarte(nom))
            Jeu::jouer();
            m_horlogeEvent.restart();

            }
             if(retour.actionner())
            {
            m_click.play();
            m_pageMenu--;
            m_horlogeEvent.restart();
            }

            break;

            case 3:
                        if(retour.actionner()) {
                        m_click.play();
                        m_pageMenu =1;
                        m_horlogeEvent.restart();
                        }

                         if(classique.actionner()) {
                         m_click.play();
                         chargerSuite("Default");
                         Jeu::jouer();
                         m_horlogeEvent.restart();
                        }

                         if(choisirSuite.actionner()) {
                         m_click.play();
                         std::string nomSuite;
                         nomSuite= menuVignette(m_tabSuites);
                         if(nomSuite != "errStr" && chargerSuite(nomSuite) ) Jeu::jouer();
                         else std::cout<<"La fonction chargerSuite à retournee errStr"<<std::endl;
                         m_horlogeEvent.restart();


                        }
                break;
            case 4:
                if(retour.actionner()) {
                        m_click.play();
                        m_pageMenu =0;
                        m_horlogeEvent.restart();
                        }
                    break;

        }



        }

        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        fenetrePrincipale.clear();

        fenetrePrincipale.draw(fond);
        fenetrePrincipale.draw(m_limbEscape);

        if(m_pageMenu==0)
        {
        jouer.afficher();//
        quitter.afficher();//
        credit.afficher();
        }
        if(m_pageMenu==1)
        {
        esbrouffe.afficher();//
        suite.afficher();
        retour.afficher();
        }
        else if(m_pageMenu == 2)
        {
            aleatoire.afficher();
            charger.afficher();
            retour.afficher();

        }
        else if(m_pageMenu == 3)
        {

             classique.afficher();
             choisirSuite.afficher();
             retour.afficher();
        }
        else if(m_pageMenu == 4)
        {

            fenetrePrincipale.draw(fondCredit);
            fenetrePrincipale.draw(apropos);
            retour.afficher();
        }
        fenetrePrincipale.display();
        }
    }


std::string Jeu::menuVignette(std::vector<std::string> const &liste)
{


    sf::RectangleShape fondVignette;


     lgui::Bouton pageSuivante(font,&textBoutonR,&textBoutonV);
       pageSuivante.setTitre("->");
       pageSuivante.setTailleTexte(15);
       pageSuivante.setFenetrelie(fenetrePrincipale);
       pageSuivante.setPosition(sf::Vector2f(LFENETRE  -  (textBoutonR.getSize().x + 20),HFENETRE - 0.12 * HFENETRE));

       lgui::Bouton pagePrecedente(font,&textBoutonR,&textBoutonV);
       pagePrecedente.setTitre("<-");
       pagePrecedente.setTailleTexte(15);
       pagePrecedente.setFenetrelie(fenetrePrincipale);
       pagePrecedente.setPosition(sf::Vector2f( 20,HFENETRE - 0.12 * HFENETRE));

       lgui::Bouton retour(font,&textBoutonR,&textBoutonV);
       retour.setTitre("Retour");
       retour.setTailleTexte(15);
       retour.setFenetrelie(fenetrePrincipale);
       retour.setPosition(sf::Vector2f( LFENETRE / 2 -  textBoutonR.getSize().x /2 , HFENETRE - 0.12 * HFENETRE));

       sf::Texture vignette;
       vignette.loadFromFile("Data/GUI/vignette.png");
       sf::Texture vignetteS;
       vignetteS.loadFromFile("Data/GUI/vignetteS.png");

    std::vector<Vignette> tabptrVignette;

    sf::Vector2f positionVignette;
    unsigned int nombreRange = 3;
    unsigned int nombreElementRange = 4;
    unsigned int nombreElementPage = nombreRange * nombreElementRange ;

    unsigned int nbPage = liste.size() / nombreElementPage;
    unsigned int pageActuelle = 0;
    int offset =( LFENETRE - ((nombreElementRange - 1 )  * (0.2 * LFENETRE) + 50)) / 2 ;
    int tailleFondX = (((nombreElementRange - 1 )  * (0.2 * LFENETRE) )) + 90;
    int tailleFondY = (((nombreRange - 1)* (0.2*HFENETRE) + 120))  ;

    fondVignette.setSize(sf::Vector2f(tailleFondX,tailleFondY));
    fondVignette.setFillColor(sf::Color(30,56,65));
    fondVignette.setPosition(offset - 20 ,(m_texlimbEscape.getSize().y * 0.8 + 0.05 * HFENETRE) - 20);


    for(unsigned int i = 0 ; i< liste.size();i++)
    {
        tabptrVignette.push_back(Vignette(font));
         std::string s = liste[i];

        s.resize(liste[i].size() - 4);
        tabptrVignette[i].setTitre(s);
        tabptrVignette[i].setFenetrelie(fenetrePrincipale);

        tabptrVignette[i].setTextures(&vignette,&vignetteS);
        tabptrVignette[i].setScale(1);
    }

    for(unsigned int i = 0 ; i < (nbPage + 1) &&  i * nombreElementPage < liste.size() ; i++) // 12 elements par page
    {
           for(unsigned int j = 0 ; j < nombreRange && i * nombreElementPage + j * nombreElementRange < liste.size() ; j ++) // 3 rangés par page
           {
               positionVignette.y = m_texlimbEscape.getSize().y * 0.8 + 0.05 * HFENETRE + j* HFENETRE * 0.20;
               for(unsigned int k = 0 ; k< nombreElementRange &&i * nombreElementPage + j * nombreElementRange + k < liste.size();k++) // 4 elements par rangé
               {
                   positionVignette.x = offset + k * LFENETRE * 0.20;

                   tabptrVignette[i*nombreElementPage + j*nombreElementRange + k].setPosition(positionVignette);

               }

           }

    }

    sf::Event event;

    while (fenetrePrincipale.isOpen()) {

        while (fenetrePrincipale.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();

                if(m_horlogeEvent.getElapsedTime().asSeconds() > 0.1) // protection  afin d'eviter d'appuyer sur  deux bouton qui se superpose sur deux page connexes.
                {
                        if(pageSuivante.actionner())
                        {
                            m_click.play();
                            if(pageActuelle<nbPage)
                            pageActuelle++;
                            m_horlogeEvent.restart();
                        }

                        if(pagePrecedente.actionner())
                        {
                            m_click.play();
                            if(pageActuelle>0)
                            pageActuelle--;
                            m_horlogeEvent.restart();

                        }

                        if(retour.actionner())
                        {
                            m_click.play();
                            return "errStr" ;
                            m_horlogeEvent.restart();

                        }

                        for(unsigned int  i = 0 ; i<nombreElementPage  && nombreElementPage * pageActuelle +  i < tabptrVignette.size() ; i++)
                        {
                                if(tabptrVignette[nombreElementPage * pageActuelle + i ].actionner())
                                {
                                    return tabptrVignette[nombreElementPage * pageActuelle + i].getString();



                                }
                        }



                }

                fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());
                fenetrePrincipale.clear();
                fenetrePrincipale.draw(fond);
                fenetrePrincipale.draw(m_limbEscape);
                fenetrePrincipale.draw(fondVignette);

                for(unsigned i = 0 ; i<nombreElementPage  && nombreElementPage * pageActuelle +  i < tabptrVignette.size(); i++ )
                {
                    tabptrVignette[nombreElementPage * pageActuelle + i ].afficher();
                }

                pageSuivante.afficher();
                pagePrecedente.afficher();
                retour.afficher();
                fenetrePrincipale.display();

        }


    }

    return "errStr";

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
    m_chronometre.restart();
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

        if( objectifRempli() && !m_joueur->enDeplacement()){  if(gagner()) {desallouer();return;}}

       // if(horlogeEvent.getElapsedTime().asMilliseconds() - tempsBoucleEvent.asMilliseconds()>10) {

           m_joueur->gererClavier(*m_ptrthis);
            tempsBoucleEvent = horlogeEvent.getElapsedTime();
      //  }

        if(recharger.actionner())
        {
            m_click.play();
            std::string nomcarte;
            nomcarte = m_carte->getNom();
                desallouer();
                chargerCarte(nomcarte);
        }
        if(retour.actionner())
        {
            m_click.play();
             desallouer();
             m_jouerSuite = false;
            return;
        }

        //Actualise l'animation du personnage
       m_joueur->animer();

        fenetrePrincipale.clear(); //nettoyage de la fenetre


        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//placement dans la vue de l'interface afin de dessiner le fond.
         fenetrePrincipale.draw(fond);

        fenetrePrincipale.setView(view1); //Placement dans la vue prevue pour le jeu

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
                else
                {
                    if(m_joueur->getPosition().x == x  && m_joueur->getPosition().y == y)  m_joueur->afficher(fenetrePrincipale);
                }
            }

        }




        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        recharger.afficher();
        retour.afficher();
       // fenetrePrincipale.draw(infoSouris);
        fenetrePrincipale.draw(infoVersion);
        fenetrePrincipale.display();


    }


}

 bool Jeu::desallouer()
 {
      if(m_carte != nullptr) {delete m_carte;m_carte = nullptr;} //Si une carte existe dejà , on la supprime
      if(m_ressourceHolder != nullptr) {delete m_ressourceHolder;m_ressourceHolder=nullptr;} // On supprime le ressourceholder si il existe deja

      for(unsigned int i = 0 ; i<Element::tableauElement.size() ; i++) // On reset tout les elements deja existant .
    {   if(Element::tableauElement[i] != nullptr)
        delete Element::tableauElement[i];
    }
    Element::tableauElement.clear(); // on désalloue tout le vector

      if(m_joueur != nullptr ) {delete m_joueur;m_joueur=nullptr;} //joueur...
      return true;
 }


bool Jeu::chargerSuite(std::string const &nom)
{
    m_suiteCarte.clear();
    std::string s;
     if(nom =="")
    {
        cerr<<"Erreur, Nom de suite inexistant";
        return false;
    }
    else if(nom.size() >300)
    {
        cerr<<"erreur, nom de suite trop long!";
        return false;
    }
    else
    {
        std::string chemin = "Cartes/Suites/" + nom  + ".ste";
        ifstream chargement(chemin.c_str(), ios ::binary);

        if(!chargement)
        {
            cerr<<"Erreur, Impossible de charger "<<nom<<"!"<<endl;
            return false;
        }
        else
        {

            while(getline(chargement,s))
            {
                m_suiteCarte.push_back(s);
            }

            chargement.close();

            chargerCarte(m_suiteCarte[0]);
        }
    m_jouerSuite= true;
    return true;
    }
}

bool Jeu::chargerCarte(std::string const &nom)
{


    m_carte = new Carte(); //On en crée une vierge
   if( !m_carte->charger(nom)) //On charge la carte à partir du fichier
        {
             return false; // si on echoue
        }
   else // Si la carte à correctement chargé
   {

    m_ressourceHolder= new RessourceHolder(m_carte->getPackRessource()); // On en crée un nouveau avec le pack de ressource de la carte.
    m_carte->assembler(m_ressourceHolder); // et on le refait pour la carte actuelle.
    trierElement(); // Enfin on tri les elements  dans un vector de jeu:: en enlevant le Depart et les objectif (pour l'affichage)
    m_joueur = new Joueur(fenetrePrincipale,m_carte);

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

    m_theme.play();//musique
    m_theme.setLoop(true);//en boucle
    sf::Text TextPasse;

    TextPasse.setFont(font);
    TextPasse.setCharacterSize(15);                      //texte qui indique la commande à utiliser pour passer
    TextPasse.setColor(sf:: Color::Green);
    TextPasse.setPosition(20,HFENETRE -50);
    TextPasse.setString("Appuyer sur E pour passer...");
    sf::Event event;

    sf::Texture textureLimb;               //Logo Limb'Studio
    sf::Texture textureSfml;
    if(!textureLimb.loadFromFile("Data/LimbStudio.png")) cout<< "Logo setLoopnon chargé!" <<endl;
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

       // TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds())))); //on change la transparence du texte de commande selon un sinus
        TextPasse.setColor(utils::changerTransparence(TextPasse.getColor(),128*(1+sin(4 * temps.getElapsedTime().asSeconds())))); //on change la transparence du texte de commande selon un sinus
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

       // TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));
         TextPasse.setColor(utils::changerTransparence(TextPasse.getColor(),128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));
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


std::vector<std::string> Jeu::rechercheFichier(std:: string chemin, std::string extension)
{
    string  commandeSysteme;
    std::vector<std::string> stringVector;
    if(chemin == "" || chemin.size() > 300  )
    {
        std::cerr<<"Chemin d'acces incorrecte!"<<std::endl;
        return stringVector;
    }
    else
    {
        if(!(extension == "" || extension.size() > 4))
        {
            #ifdef WINDOW
             commandeSysteme = "dir " + chemin + "*" + extension+"* /b > "+ chemin + "liste.txt" ;
            #endif // WINDOW
           #ifdef LINUX
           commandeSysteme = "ls " + chemin + "*" + extension + "/b > "+ chemin + "liste.txt" ;
           #endif // LINUX

        }

    }
    system(commandeSysteme.c_str());

     std::ifstream fichier((chemin + "liste.txt"));
     std::string s;
     unsigned int i = 0;

    if(fichier){
        while(std::getline(fichier,s))
            {

                stringVector.push_back(s);
               //std::cout<<m_tabCartes[i]<<std::endl;
               i++;
            }
    }
    else
    {
        std::cerr << "Impossible d'ouvrir liste.txt " << std::endl;
    }
    fichier.close();

    #ifdef WINDOW

    commandeSysteme = "del " + chemin + "liste.txt";
    #endif // WINDOW

    #ifdef  LINUX
    commandeSysteme = "rm " + chemin + "liste.txt";
    #endif // LINUX



    system(commandeSysteme.c_str());
    return stringVector;
}
