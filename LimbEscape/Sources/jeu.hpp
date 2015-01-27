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

    sf::Texture m_texlimbEscape;
    sf::Sprite m_limbEscape;
    sf::Image  m_icone;

    std::vector<unsigned int> m_repereObjectif;
    std::vector<std::string> m_tabCartes;
    std::vector<std::string> m_tabSuites;

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

   //Son
    sf::SoundBuffer m_clickbuffer;
    sf::Sound m_click;

    sf::Music m_theme;

public:

    Jeu* m_ptrthis;
    Jeu();
    ~Jeu();
    bool objectifRempli();
    int gagner();
    void intro();
    bool demarrer();
    void menuPrincipal();
    std::string menuVignette(std::vector<std::string> const  &liste);

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
    std::vector<std::string> rechercheFichier(std:: string chemin, std::string extension);
};
#endif // JEU
