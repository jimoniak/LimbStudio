


#include <SFML/Graphics.hpp>

#include <GUI.hpp>
#include <iostream>

#include <stdlib.h>
#include <math.h>
#include <vector>

#include "constantes.hpp"
#include "outils.hpp"

#include "ressourceholder.hpp"
#include "element.hpp"
#include "carte.hpp"
#include "gestionSouris.hpp"
#include "editeur.hpp"


using namespace sf;
using namespace std;

Editeur::Editeur() :fenetrePrincipale(sf::VideoMode(LFENETRE, HFENETRE), "LimbEditor"),
    view1(Vector2f(0,350),Vector2f(1536,1156)),
    m_interfaceEdition(5)
{

    if (!font.loadFromFile("Data/Fonts/Timeless.ttf"))
    {

        std::cout<<"erreur avec Timeless.ttf"<<std::endl;
    }

    m_editeurOuvert = false;

    m_pageMenu = 0;
    m_carte = nullptr;
    m_ressourceHolder = nullptr;
    m_interfaceUtilise= false;
    m_elementSelectionner=RIEN;
    fenetrePrincipale.setVerticalSyncEnabled(true);
    m_horlogeInterne.restart();

     version.setFont(font);
     version.setCharacterSize(20);
     version.setColor(sf::Color::White);
     version.setPosition(10,HFENETRE-25);
     version.setString("test");


    if (!m_clickbuffer.loadFromFile("Data/Sounds/Clicks/click.wav")) cerr<<"Impossible de charger click.wav"<<endl;

    m_click.setBuffer(m_clickbuffer);


}



Editeur::~Editeur()
{
    if(m_carte!=nullptr)
        delete m_carte;
    if(m_ressourceHolder!=nullptr)
    delete m_ressourceHolder;

}



void Editeur::intro()
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

    while(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5 && fenetrePrincipale.isOpen())   //Boucle pour la SFML
    {
        if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()< 1)
        {
            sfmlSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()) * 255)));//On fait apparaitre le Logo
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 1  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 3)
        {
            sfmlSp.setColor(sf::Color(255,255,255,255)); //on garde le logo afficher un certain temps
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 3  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 4)
        {
            sfmlSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep.asSeconds() + 3)) * 255)))); //on fait disparaitre le logo
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds())))); //on change la transparence du texte de commande selon un sinus


        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01)
        {

            fenetrePrincipale.clear();
            fenetrePrincipale.draw(sfmlSp);
            fenetrePrincipale.draw(TextPasse);   //affichage...
            fenetrePrincipale.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }

        while (fenetrePrincipale.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))    return;

            switch(event.type )
            {

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



    while(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5 && fenetrePrincipale.isOpen())   //Même procéder pour le Logo de Jinn Studio
    {
        if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 1)
        {
            LimbSp.setColor(sf::Color(255,255,255, ((temps.getElapsedTime().asSeconds() - tempsDep.asSeconds()) * 255)));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 1  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 4)
        {
            LimbSp.setColor(sf::Color(255,255,255,255));
        }
        else if(temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() > 4  && temps.getElapsedTime().asSeconds() - tempsDep.asSeconds() < 5)
        {
            LimbSp.setColor(sf::Color(255,255,255,  255 - (((temps.getElapsedTime().asSeconds() - (tempsDep.asSeconds() + 4)) * 255))));
        }

        TextPasse.setColor(Color(255,255,255, 128*(1+sin(4 * temps.getElapsedTime().asSeconds()))));

        if(temps.getElapsedTime().asSeconds() - tempsatt > 0.01)
        {

            fenetrePrincipale.clear();
            fenetrePrincipale.draw(LimbSp);
            fenetrePrincipale.draw(TextPasse);   //affichage...
            fenetrePrincipale.display();
            tempsatt = temps.getElapsedTime().asSeconds();
        }



        while (fenetrePrincipale.pollEvent(event))
        {
            switch(event.type )
            {

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

void Editeur::menuPrincipal()
{

    sf::Texture texsplash;
    if(!texsplash.loadFromFile("Data/LimbEditor.png")) cerr<<"Impossible de charge LimbEditor.png"<<endl;

    sf::Sprite splash;
    splash.setTexture(texsplash);
    splash.setPosition(LFENETRE - texsplash.getSize().x ,0);

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(LFENETRE,HFENETRE));
    background.setFillColor(sf::Color(125,125,200));

    sf::Text creerNom;
    sf::Text textTaille;


    std::string charset = "0123456789";



    creerNom.setFont(font);
    creerNom.setCharacterSize(18);                      //texte qui indique la commande à utiliser pour passer
    creerNom.setColor(Color::Blue);

    creerNom.setString("Entrer un nom de carte:");


    textTaille.setFont(font);
    textTaille.setCharacterSize(18);                      //texte qui indique la commande à utiliser pour passer
    textTaille.setColor(Color::Blue);

    textTaille.setString("Entrer la taille de la carte: (entre 5 et 15)");

    fenetrePrincipale.setKeyRepeatEnabled(false);



    sf::Texture textBoutonV;
    sf::Texture textBoutonR;
    if(!textBoutonR.loadFromFile("Data/GUI/boutonf.png")) std::cout<<"Erreur avec texture boutonf.png"<<std::endl;
    if(!textBoutonV.loadFromFile("Data/GUI/boutond.png")) std::cout<<"Erreur avec texture boutond.png"<<std::endl;

    lgui::Bouton editer (font,&textBoutonR,&textBoutonV);
    lgui::Bouton quitter(font,&textBoutonR,&textBoutonV);
    lgui::Bouton retour (font,&textBoutonR,&textBoutonV);

    creerNom.setPosition(sf::Vector2f(LFENETRE/2-125  ,HFENETRE /2 - 100));
    textTaille.setPosition(sf::Vector2f(LFENETRE/2-125  ,HFENETRE /2 ));
    lgui::ZoneSaisie saisieNom( font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 - 50), sf::Color::Green ,sf::Color::Blue);
    lgui::ZoneSaisie saisieTaille( font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 +50), sf::Color::Green ,sf::Color::Blue);
    saisieTaille.setCharset(charset);
    lgui::Bouton creer(font,&textBoutonR,&textBoutonV);
    lgui::Bouton charger(font,&textBoutonR,&textBoutonV);

    editer.setFenetrelie(fenetrePrincipale);
    quitter.setFenetrelie(fenetrePrincipale);
    retour.setFenetrelie(fenetrePrincipale);
    creer.setFenetrelie(fenetrePrincipale);
    charger.setFenetrelie(fenetrePrincipale);
    saisieNom.setFenetrelie(fenetrePrincipale);
    saisieTaille.setFenetrelie(fenetrePrincipale);

    editer.setTitre ("Editer");
    quitter.setTitre("quitter");
    retour.setTitre("<--");
    creer.setTitre("Creer");
    charger.setTitre("Charger");

    editer.setTailleTexte(15);
    quitter.setTailleTexte(15);
    retour.setTailleTexte(15);
    creer.setTailleTexte(15);
    charger.setTailleTexte(15);


    editer.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2 -  50));
    quitter.setPosition(sf::Vector2f(LFENETRE / 2 - textBoutonV.getSize().x / 2 ,HFENETRE /2+ 50));
    retour.setPosition(sf::Vector2f(LFENETRE -200 - textBoutonV.getSize().x ,HFENETRE /2 - 50));
    creer.setPosition(sf::Vector2f(LFENETRE /2 - 125  ,  HFENETRE /2 + 200));
    charger.setPosition(sf::Vector2f(LFENETRE /2 + 30 ,HFENETRE /2 + 200));

    creerNom.setPosition(LFENETRE/2-125,HFENETRE/2 - 105);

    sf::Event event;

    while (fenetrePrincipale.isOpen())
    {
        while (fenetrePrincipale.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();
            if(m_pageMenu==1)
            {
                saisieNom.actif(event);
                saisieTaille.actif(event);
            }

        }

        switch(m_pageMenu)
        {
        case 0:

            if(editer.actionner())
            {
                m_click.play();
                m_pageMenu = 1;
            }
            if(quitter.actionner())
            {
                m_click.play();
                fenetrePrincipale.close();
            }

            break;
        case 1:

            if(retour.actionner())
            {
                m_click.play();
                m_pageMenu -- ;
            }
            if(creer.actionner())
            {
                m_click.play();
                std::string nom;
                std::string taille;
                nom =  saisieNom.getTexte() ;
                taille =  saisieTaille.getTexte();

                creerCarte(nom,taille);

                if(sauvergarderCarte())
                {
                    m_pageMenu++;
                    Editeur::editer();
                }
                else
                {
                    delete m_carte;
                    m_carte = nullptr;
                }

            }

            if(charger.actionner())
            {
                m_click.play();
                std::string test;
                test =  saisieNom.getTexte() ;
                if(chargerCarte(test))
                {
                    m_pageMenu++;
                    Editeur::editer();
                }
                else
                {

                    delete m_carte;
                    m_carte = nullptr;
                }

            }

            break;

        case 2:
            if(quitter.actionner())
            {
                m_click.play();
                fenetrePrincipale.close();
            }

            break;
        default:

            break;
        }


        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.
        fenetrePrincipale.clear();

        fenetrePrincipale.draw(background);


        switch(m_pageMenu)
        {
        case 0:
            editer.afficher();
            quitter.afficher();


            break;
        case 1:
            fenetrePrincipale.draw(creerNom);
            fenetrePrincipale.draw(textTaille);

            retour.afficher();
            creer.afficher();
            charger.afficher();
            saisieNom.afficher();
            saisieTaille.afficher();
            break;
        case 2:
            quitter.afficher();

            break;
        default:
            quitter.afficher();
            break;
        }

        fenetrePrincipale.draw(splash);


        fenetrePrincipale.draw(version);
        fenetrePrincipale.display();



    }





}
void Editeur::editer()
{

    sf::Texture tex[5];
    sf::Texture textBoutonV;
    sf::Texture textBoutonR;
    if(!textBoutonR.loadFromFile("Data/GUI/boutonf.png")) std::cout<<"Erreur avec texture boutonf.png"<<std::endl;
    if(!textBoutonV.loadFromFile("Data/GUI/boutond.png")) std::cout<<"Erreur avec texture boutond.png"<<std::endl;

    lgui::Bouton sauvegarder(font,&textBoutonR,&textBoutonV);
    sauvegarder.setFenetrelie(fenetrePrincipale);
    sauvegarder.setTitre("Sauver");
    sauvegarder.setTailleTexte(15);
    sauvegarder.setPosition(sf::Vector2f(LFENETRE - (150 + textBoutonV.getSize().x)  ,HFENETRE  - 100));

     lgui::Bouton retour(font,&textBoutonR,&textBoutonV);
     retour.setFenetrelie(fenetrePrincipale);
     retour.setTitre("<--");
     retour.setTailleTexte(15);
     retour.setPosition(sf::Vector2f(LFENETRE - (50 + textBoutonV.getSize().x)  ,HFENETRE  - 100));


    for(unsigned int i=0; i<m_interfaceEdition.size(); i++)
    {
        cout<<i<<endl;
        tex[i] = m_ressourceHolder->getTextureElem(i);
        m_interfaceEdition[i].setTextures(tex[i],tex[i]);
        m_interfaceEdition[i].setScale(0.5);
        sf::Vector2f position(LFENETRE - (tex[i].getSize().x * 0.5),i * (tex[0].getSize().y * 0.5));
        m_interfaceEdition[i].setPosition(position);
        m_interfaceEdition[i].setFenetrelie(fenetrePrincipale);
    }

    GestionSouris gestionSouris(&fenetrePrincipale);
    Selecteur selecteur;
    //sauvergarderCarte();


    sf::Text infoSouris;
    infoSouris.setFont(font);
    infoSouris.setString("Souris en position : X:  , Y:  "); //text info coordonnées souris
    infoSouris.setColor(sf::Color::Blue);
    infoSouris.setCharacterSize(24);
    std::string infSouris;


    sf::Event event;
    bool sourisCliq = false;

    while (fenetrePrincipale.isOpen())
    {

        while (fenetrePrincipale.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                fenetrePrincipale.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sourisCliq=true;
                }
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) view1.move(-100 * m_horlogeInterne.getElapsedTime().asSeconds(),0); // deplacement de la camera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) view1.move(100 * m_horlogeInterne.getElapsedTime().asSeconds(),0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view1.move(0,-100 * m_horlogeInterne.getElapsedTime().asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view1.move(0,100 * m_horlogeInterne.getElapsedTime().asSeconds());
         m_horlogeInterne.restart();




        if(m_interfaceEdition[0].actionner())
        {
            m_click.play();
            m_interfaceUtilise=true;
            m_elementSelectionner=CAISSE;
        }
        if(m_interfaceEdition[1].actionner())
        {
            m_click.play();
            m_interfaceUtilise=true;
            m_elementSelectionner=MUR;
        }
        if(m_interfaceEdition[2].actionner())
        {
            m_click.play();
            m_interfaceUtilise=true;
            m_elementSelectionner=OBJECTIF;
        }
        if(m_interfaceEdition[3].actionner())
        {
            m_click.play();
            m_interfaceUtilise=true;
            m_elementSelectionner=DEPART;
        }
        if(m_interfaceEdition[4].actionner())
        {
            m_click.play();
            m_interfaceUtilise=true;
            m_elementSelectionner=RIEN;
        }
        if(sauvegarder.actionner())
        {
            m_click.play();
            sauvergarderCarte();
            m_interfaceUtilise=true;
        }

          if(retour.actionner())
        {
            m_click.play();
            m_pageMenu--;
             delete m_carte;
             m_carte=nullptr;
            return ;
        }

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            if(sourisCliq==true)
            {


                if(gestionSouris.getCoordSouris().x < m_carte->getTaille() && gestionSouris.getCoordSouris().x>= 0
                        &&  gestionSouris.getCoordSouris().y < m_carte->getTaille() && gestionSouris.getCoordSouris().y>= 0 )

                    m_carte->ajouterElement(gestionSouris.getCoordSouris(),m_elementSelectionner,*m_ressourceHolder);
                sourisCliq = false;

            }

        }

        fenetrePrincipale.setView(view1);

        gestionSouris.CalcCoordCarte();
        infSouris = "Souris en position : X:" + utils::ConvertionFltString(gestionSouris.getCoordSouris().x )+  "Y:" +utils::ConvertionFltString(gestionSouris.getCoordSouris().y);
        infoSouris.setString(infSouris);
        selecteur.positionnerSelecteur(gestionSouris);


        fenetrePrincipale.clear();
        fenetrePrincipale.draw(m_carte->getSprCarte());


        for(unsigned int i= 0 ; i< m_carte->getElementHolder().size(); i++)
        {
            fenetrePrincipale.draw(m_carte->getSprElem(i));
        }


        if(gestionSouris.getCoordSouris().x<m_carte->getTaille() && gestionSouris.getCoordSouris().x>=0 && gestionSouris.getCoordSouris().y>=0 && gestionSouris.getCoordSouris().y< m_carte->getTaille())
        {

            fenetrePrincipale.draw(selecteur.getSprite());
        }

        fenetrePrincipale.setView(fenetrePrincipale.getDefaultView());//Changement de vue pour dessiner l'interface.



        for(unsigned int i = 0 ; i< m_interfaceEdition.size(); i++)
        {
            m_interfaceEdition[i].afficher();

        }
        sauvegarder.afficher();
        retour.afficher();
        fenetrePrincipale.draw(infoSouris);
        fenetrePrincipale.display();
        m_interfaceUtilise=false;
    }

    for( int i = 4 ; i>=0; i--)
    {
        m_interfaceEdition.pop_back();

        fenetrePrincipale.draw(infoSouris);
        fenetrePrincipale.display();

    }


}



bool Editeur::creerCarte(std::string nom,std::string taille)
{

    unsigned  int taillecote;
    if(taille != "_" && taille != "")
    {
        cout<<"test"<<endl;
         if(taille.size()>0) taillecote=utils::ConvStringInt(taille);
         cout<<taillecote<<endl;

    }

    if(taillecote<5 || taillecote>15)   taillecote = 10;
    m_carte = new Carte(nom,taillecote);

    if(m_ressourceHolder!= nullptr) delete m_ressourceHolder;
    m_ressourceHolder= new RessourceHolder();



}
bool Editeur::sauvergarderCarte()
{



    return  m_carte->sauvegarder();

}
bool Editeur::chargerCarte(std::string const &nom)
{


    m_carte = new Carte();
   if( !m_carte->charger(nom))
        {
             return false;
        }
   else
   {

    if(m_ressourceHolder!= nullptr) delete m_ressourceHolder;
    m_ressourceHolder= new RessourceHolder(m_carte->getPackRessource());

    m_carte->creerElement(*m_ressourceHolder);



   }


    // cout<< m_carte->getPackRessource()<<endl;


    return true;




}

RessourceHolder* Editeur::getRessourceHolder()
{
    return m_ressourceHolder;
}
