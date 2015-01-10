
class Carte;




class Editeur
{


private:


    sf::RenderWindow fenetrePrincipale;
    sf::View view1;
    sf::Font font;

    sf:: Text version;

    int m_pageMenu;
    bool m_editeurOuvert;

    sf::Clock m_horlogeInterne;

    bool m_interfaceUtilise;
    Type_element m_elementSelectionner;







    RessourceHolder* m_ressourceHolder;
    Carte* m_carte;

    std::vector<lgui::Bouton> m_interfaceEdition;

public:


public:

    Editeur();
    ~Editeur();

    void intro();
    void menuPrincipal();
    void editer();


    bool creerCarte(std::string nom,std::string taille);



    bool sauvergarderCarte();
    bool chargerCarte(std::string const &nom);
    RessourceHolder* getRessourceHolder();


};

