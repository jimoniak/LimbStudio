#ifndef JEU
#define JEU


#include <GUI.hpp>

#include "gestionSouris.hpp"
class Joueur;

class Jeu {
private:
    sf::RenderWindow fenetrePrincipale;
    sf::View view1;
    std::vector<unsigned int> m_repereObjectif;
    std::vector<std::string> m_tabCartes;
    //Element * m_tabElement[][TAILLE_MAX];
    int m_objectifRestant;
    std::vector<std::vector<Element*>> m_tabElement;
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

    bool chargerCarte(std::string const &nom);
    void trierElement();
    void deplacerElement(sf::Vector2f positionActuelle,sf::Vector2f positionNouvelle);
    std::vector<std::vector<Element*>> getTabElement();

    void reglerVue();

    //Affichage

    void AfficherScene();
    void AfficherHud();

    void InitNombreObjectif();
    void rechercheFichier();
};
#endif // JEU
