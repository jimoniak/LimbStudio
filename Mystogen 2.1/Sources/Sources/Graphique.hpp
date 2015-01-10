#ifndef GRAPHIQUE
#define GRAPHIQUE



//#include "Prototypes.hpp"
//#include "Classes.h"



struct particule
{
    bool active; //active ou non


    int vie; //elle a une durée de vie
    int perteVie;//elle perd de la vie a chaque deplacement (sa vie est sa transparence)
    sf::RectangleShape m_apparence;//elle a une apparence
    sf::Vector2f position;//elle a une position
    sf::Vector2f direction;//elle suit un vecteur de deplacement
    sf::Color couleur;

    int typeParticule;


};


typedef particule particule;







class Barregraphique
{
private:


    sf::Sprite      m_BarreFond,m_BarreDessus;
    sf::Text                    m_parametre;
    std::string                     m_prefixe;
    sf::Font                         m_Police;
    sf::Vector2f                   m_Position;
    sf::Vector2f                  m_Dimension;
    sf::Texture                  m_TextureDessous, m_TextureDessus; //On peux créer des barres directement à partir d'Texture.
    sf::RectangleShape                m_dessous,m_dessus;



    bool                  m_centrage;
    int                m_ValeurParam;
    int             m_ValeurMaxParam;
    sf::Vector2f          m_decalage;

public:

    //Constructeur:
    Barregraphique();

    //Barregraphique(std::string ImgUn,std::string ImgDeux,std::string param,int valeur,int valMax,std::string font,int alpha1,int alpha2); //Constructeur permettant de construire une barre à partir d'Texture
    Barregraphique(std::string param,int valeur,int valMax,sf::Vector2f dimension,sf::Vector2f position,sf::Color c1,sf::Color c2);//Constructeur permettant de dessiner une barre

    //getters

    //setters
    void        ChargementPolice(sf::Font *font,int taille);
    void        setDecalage();
    void        setParamText(int taille,sf::Color couleur);
    void        setImgUn(std::string ressource);
    void        setImgDeux(std::string ressource);
    void        setPolice(sf::Font NewValue);
    void        setPosition(sf::Vector2f NewValue);
    void        setPosition(float X,float Y);
    void        setSize(sf::Vector2f NewValue);
    void        setSize(float X,float Y);
    void        setColor(sf::Color Color1,sf::Color Color2);
    void        setValeurMax(int newValueMax);

    //methodes

    void MajParametre(int newValuePar);
    void AfficherBarre(gameWindow &fenetre);

};


class Particule//particule
{
private:
    bool m_active; //active ou non


    int m_vie; //elle a une durée de vie
    int m_perteVie;//elle perd de la vie a chaque deplacement (sa vie est sa transparence)

    sf::RectangleShape m_apparence;//elle a une apparence
    sf::Color m_couleur;//une couleur

    sf::Vector2f m_position;//elle a une position
    sf::Vector2f m_posDep;//elle a une position d'origine
    sf::Vector2f m_direction;//elle suit un vecteur de deplacement
    sf::Vector2f m_encadrDirX;
    sf::Vector2f m_encadrDirY;

    int typeParticule;

public:
//Constructeur
    Particule();
    Particule(int vieDep,sf::Color couleur,sf::Vector2f position,int perteVie,sf::Vector2f EndrDirX,sf::Vector2f EndrDirY,sf::Vector2f dim);
    ~Particule();



//methode

    void setDir(sf::Vector2f DirX,sf::Vector2f DirY);//fonction pour forcé une mise a jour du vecteur de mouvement de la particule
    void setPosDep(sf::Vector2f newValues);

    void deplacerParticule();//fonction permettant de faire evoluer la particule , de sa naissance à sa mort/


    void afficher(gameWindow &fenetre); //pour afficher la particule sur la fenetre approprié.

};



class generateur
{
private:

    std::vector<Particule> m_particule;//vector de particule dimensionné a l'appel du constructeur
    std::vector<particule> m_particle;
    int                    m_nombreParticule;//nombre de particule (taille du vector)
    sf::Vector2f           m_position;
    sf::Vector2f           m_direction;
    sf::Vector2f           m_encadrementPerteVie;// vector permettant de choisir aleatoirement la perte d'opacité d'une particule par boucle entre en minima (.x) et un maxima (.y)
    sf::Vector2f           m_encadreVie;//même chose mais pour la vie de depart de la particule
    sf::Vector2f           m_endrDirX;//vector d'encadrement de choix aléatoire de la direction suivant x de la particule
    sf::Vector2f           m_endrDirY;//même chose mais suivant Y.


    float m_tempsDisp;

    int                    m_vie;//vie de la particule (determine son opacité , 255= 100% opaque et 0=0% )
    int                    m_perteVie;

    bool                   m_actif;

public:
    generateur();
    generateur(int nombrePart,sf::Vector2f pos,sf::Vector2f encadrDirX,sf::Vector2f encadrDirY, sf::Vector2f encadrPerte, sf::Vector2f encadreVie,sf::Color couleur,sf::Vector2f dim);
    ~generateur();
    void deplacergenerateur(sf::Vector2f newValue);
    void deplacerParticule(Timer &temps);
    void afficherParticule(gameWindow &fenetre);

    void reset();





};


#endif
