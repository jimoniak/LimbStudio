#include <GUI.hpp>


class Jeu {
private:
    sf::RenderWindow fenetrePrincipale;
    sf::View view1;
    std::vector<unsigned int> m_repereObjectif;
    int m_objectifRestant;

    RessourceHolder* m_ressourceHolder;
    Carte *m_carte;

    sf::Font font;

    sf::Text infoSouris;
    sf::Text infoVersion;

    GestionSouris gestionSouris;
    Selecteur selecteur;
    int m_pageMenu;

    Joueur* m_joueur;

public:

    Jeu();
    ~Jeu();
    bool objectifRempli();
    int gagner();
    void intro();
    bool demarrer();
    void menuPrincipal();
    void jouer();

    bool chargerCarte(std::string const &nom);

    //Affichage

    void AfficherScene();
    void AfficherHud();

    void InitNombreObjectif();

};
