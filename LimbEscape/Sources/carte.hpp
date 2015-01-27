
#ifndef CARTE
#define CARTE


#include <SFML/Audio.hpp>
#include "element.hpp"

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
    //RessourceHolder *m_rholder;

public:

    void creationBase(RessourceHolder *rholder);
    void assembler(RessourceHolder *rholder);

      Carte();
    ~Carte();

    bool charger(std::string const &nom);


    Element* getElement(int numero);
    std::string getNom();
    int getTaille();
    std::string getPackRessource();
    sf::Sprite getSprCarte();
    sf::Sprite getSprElem(int element);

    std::vector<Element*> getElementHolder();




};

#endif // CARTE
