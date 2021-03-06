
#ifndef JOUEUR
#define JOUEUR



class Jeu;


class Joueur {
private:

    //attribut d'apparence.
    sf::Sprite m_sprite;
    sf::Texture m_apparence;
    sf::Vector2u m_tailleTexture;
    int frame;
    int m_coteCarte;
    bool verouillageClavier;

    Carte *m_carte;
    sf::RenderWindow *m_fenetre;

    //Attributs liés aux deplacements et à l'animation du personnage.
    sf::Vector2f m_position;
    sf::Vector2f m_positionDepartAnimation;
    sf::Vector2f m_deplacement;
    int m_direction;
    sf::Clock m_horlogeAnimation;
    sf::Time  m_tempsAnimation;
    bool m_enDeplacement;


public:

    //constructeur:
    Joueur(sf::RenderWindow &fenetre,Carte *carte);
    Joueur(const Joueur&);
    ~Joueur();

    sf::Vector2f getPosition();
    //methodes utiles

    bool chargementTexture();
    void gererClavier(Jeu &jeu);

    void pousserElement(Element &element,Jeu &jeu);


    //methodes de deplacement:
    bool  enDeplacement();
    void deplacer(int direction,Jeu &jeu); // en case
    void animer();


    //actualisation
    void setPositionspr();

    //affichage
    void afficher(sf::RenderWindow &fenetre);

    sf::Sprite const getSprite();

};

#endif // JOUEUR
