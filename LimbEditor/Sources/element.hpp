
class ElementHolder
{

private:

    // std::vector<Element*> tableauElement;

    // std::vector<Element*> tableauElement;



public:




};





class Element
{

//Element present sur la carte (objectif,caisse...)


protected:

    bool m_poussable;// true = poussable, false= statique
    bool m_franchissable;




    enum Type_element m_element;
    static bool departPose ;


    sf::Sprite m_sprite;
    sf::Texture m_apparence;
    sf::Vector2f m_position;

public:

    static std::vector<Element*> tableauElement;
    Element();
    virtual ~Element();


    bool  estPoussable();
    bool  estFranchissable();

    virtual void actualiserPosition(sf::Vector2f position) = 0;


    //getter
    sf::Sprite getApparence();
    sf::Vector2f  getPosition();
    Type_element   getType();

};

class Caisse : public Element
{

public:
    Caisse();
    Caisse(sf::Vector2f position,RessourceHolder *rholder);
    ~Caisse();

    virtual void actualiserPosition(sf::Vector2f position);


};





class Objectif : public Element
{

private:
    bool m_resolu;

public:
    Objectif();

    Objectif(sf::Vector2f position,RessourceHolder *rholder);

    Objectif(sf::Vector2f position,RessourceHolder &rholder);


    void testEtat();
    void changerEtat(bool resolu);


    bool estResolu();




    void actualiserPosition(sf::Vector2f position);

};


class Depart: public Element
{
public:
    Depart();
    Depart(sf::Vector2f position,RessourceHolder *rholder);


    void actualiserPosition(sf::Vector2f position);

};


class Mur: public Element
{
private:
public:
    Mur();
    Mur(sf::Vector2f position,RessourceHolder *rholder);

    void actualiserPosition(sf::Vector2f position);


};


