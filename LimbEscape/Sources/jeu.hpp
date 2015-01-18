#ifndef JEU
#define JEU


#include <GUI.hpp>

#include "gestionSouris.hpp"
class Joueur;

class Jeu {
private:


    sf::RenderWindow fenetrePrincipale;
    sf::View view1;

    sf::RectangleShape fond;


    std::vector<unsigned int> m_repereObjectif;
    std::vector<std::string> m_tabCartes;
    int m_objectifRestant;
    std::vector<std::vector<Element*>> m_tabElement;

    std::vector<std::string> m_suiteCarte;
    bool m_jouerSuite;
    unsigned int m_comptSuite;

    RessourceHolder* m_ressourceHolder;
    Carte *m_carte;

    sf::Font font;

    sf::Text infoSouris;
    sf::Text infoVersion;
    sf::Texture textBoutonV;//texture bouton.
    sf::Texture textBoutonR;
    GestionSouris gestionSouris;
    Selecteur selecteur;
    int m_pageMenu;

    Joueur* m_joueur;

   sf::Clock m_horlogeInterne;
   sf::Clock m_horlogeEvent;
   sf::Clock m_chronometre;

public:

    Jeu* m_ptrthis;
    Jeu();
    ~Jeu();
    bool objectifRempli();
    int gagner();
    void intro();
    bool demarrer();
    void menuPrincipal();
    void jouer();

    bool desallouer();
    bool chargerSuite(std::string const &nom);
    bool chargerCarte(std::string const &nom);
    void trierElement();
    void deplacerElement(sf::Vector2f positionActuelle,sf::Vector2f positionNouvelle);
    std::vector<std::vector<Element*>> getTabElement();

    void reglerVue();

    //Affichage

    void AfficherScene();
    void AfficherHud();

    void InitNombreObjectif();
    void rechercheFichier(std:: string chemin, std::string extension);
};
#endif // JEU
