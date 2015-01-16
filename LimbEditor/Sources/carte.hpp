
#ifndef CARTE
#define CARTE



#include <SFML/Audio.hpp>

class Carte
{

private:
    unsigned int m_tailleCote;
    std::string m_nom;
    std::string m_packRessource;


    sf::Texture *m_textureBase;

    sf::Sprite  *m_base;

    std::vector<Type_element> m_tabElement;
    std::vector<Element*> m_ElementHolder;


    RessourceHolder *rholder;

     sf::SoundBuffer m_popbuffer;
     sf::Sound m_pop;



public:

    void creationBase();
    void creerElement(RessourceHolder &rholder);


    Carte();

    Carte(std::string nom,int taille);
    ~Carte();

    bool sauvegarder();
    bool charger(std::string const &nom);




    void ajouterElement(sf::Vector2f position,Type_element element,RessourceHolder &rholder);
    void supprimerElement(sf::Vector2f position);


    Element* getElement(int numero);


    std::string getNom();
    int getTaille();
    std::string getPackRessource();
    sf::Sprite getSprCarte();
    sf::Sprite getSprElem(int element);

    std::vector<Element*> getElementHolder();




};
#endif // CARTE




