
#ifndef MOUSE
#define MOUSE



class GestionSouris {
private:
    sf::RenderWindow *pfenetrePrincipale;
    Carte                    *pcarte;

    sf::Vector2f            PositionSourisFenetre;
    sf::Vector2f            Position2D;
    sf::Vector2f            PositionSourisGrille;
    sf::Vector2f            coorPointeurIso;

    sf::Image               m_overlaySouris;
    sf::Color                 couleurPixelOverlay;

public:
    GestionSouris(sf::RenderWindow *fenetre);
    sf::Vector2f CalcCoordCarte();
    sf::Vector2f getCoordSouris();

};


class Selecteur {
private:
    sf::Texture Selection;
    sf::Sprite spriteSelection;

public:
    Selecteur();
    void positionnerSelecteur(GestionSouris &souris);
    sf::Sprite getSprite();

};
#endif // MOUSE
