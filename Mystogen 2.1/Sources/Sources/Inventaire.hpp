/*---------------------------------------Inventaire.hpp--------------------------------------------------

Creation Jimoniak---------------------------------------------------------------------------------------

*/

#ifndef DEFINV
#define DEFINV

#include "constantes.hpp"

enum {CHOIXZONE,PERSONAEQUIP , SACADOS, OBJETCHOISI};


class EmplacementInv : public Bouton
{
protected:

    int m_quantite;  //quantité de l'objet possédé
    Item* m_objetLie;  //pointeur sur objet de class item ou heritiere de celle-ci
    sf::Texture m_IconeEmplacement;
    sf::Sprite m_fond;

    sf::Vector2f m_position; //position graphique (pour l'affichage de l'icone) .
    sf::Text m_Quantite;

public:

    void afficherIcone(gameWindow &fenetre);
    void PositionnerIconeObjet(Inventaire &inventaire,int numeroEmplacement);
    void setQuantite();
    void setFont(sf::Font &font);

    sf::Texture getIcone();
    std::string getDescription();
    std::string getNom();
    std::string getQuanti();
    friend class Inventaire;
    friend class Personnage;

    EmplacementInv();
    ~EmplacementInv();


};

class EmplacerEquip : public EmplacementInv
{
public:
    EmplacerEquip();
    ~EmplacerEquip();

    void setPosition(sf::Vector2f newValues);
    void setPosIcone();
    virtual void afficherIcone(gameWindow &fenetre);


    sf::Texture getIcone();
    std::string getDescription();
    std::string getNom();



    friend class Personnage;
    friend class Inventaire;

};



class Inventaire
{
private:
    bool m_setfont;                       // Bool qui permet de savoir si on a deja initialiser la police d'écriture
    int m_emplacementCible;               // variable qui permet de cibler un element dans le sac a dos
    int m_emplacementEquipCible;          //variable qui permet de cible un objet dans la zone d'équipement
    bool m_actif;                         //bool qui permet de savoir si l'inventaire est actid
    int m_zoneActif;                      //bool permettant de savoir si on évolue dans le sac a dos ou dans la zone d'équipement
    int m_choixZone;                      //bool qui permet de choisir une des zone
    int m_zoneMenu;                       //Bool qui indique au menu de choix (Utiliser, jeter...) où qu'il dois se situer
    int m_choixMenu;                      //Choix réaliser par le personnage dans le menu

    sf::Clock m_clock; //horloge pour transparence

    //graphique:

    sf::Texture m_FondIM; //Texture du fond de l'inventaire
    sf::Sprite m_FondSP;//sprite de l'Texture

    sf::Texture m_menuUtileIM;//fond pour le menu utiliser jeter etc...
    sf::Sprite m_menuUtileSP;

    Bouton m_Utiliser;  //different bouton lié à la navigation dans l'inventaire
    Bouton m_Jeter;
    Bouton m_Sortir;
    //sf::Text m_Utiliser;
    //sf::Text m_Jeter;

    sf::Text    m_forcePers;   //text qui montre les stats du personnage
    sf::Text     m_endurPers;

    Barregraphique m_BarreVie; //barre de vie et d'energie permettant d'Texturer la vie et l'energie restante du personage
    Barregraphique m_BarreEnergie;
    //------BarreVie-------

    sf::Vector2f m_DimBarreVie; //dimension des differentes barres et position
    sf::Vector2f m_PosBarreVie;
    //-----BarreEnergie

    sf::Vector2f m_DimBarreEnergie;
    sf::Vector2f m_PosBarreEnergie;





    sf::Texture m_Curseur1IM; //curseur de selection des objets.
    sf::Sprite m_Curseur1SP;

    sf::Texture  m_Curseur2IM;
    sf::Sprite m_Curseur2SP;

    //Texte de l'inventaire:

    sf::Text m_inventaireNom;
    sf::Text  m_SacADos;

    sf::Vector2f m_position;//position de l'inventaire centré sur la camera

    //-------------variable concernant l'objet selectionné.

    sf::Text m_nomObj; //le nom de l'objet sur lequel le curseur pointe
    sf::Text m_desObj; //la description
    sf::Text m_QuantiObj; //la quantité
    sf::Texture m_objSelIM; // l'Texture
    sf::Sprite m_objSelSP;//cadre de l'icone selectionne

    //emplacement de l'inventaire.
    EmplacementInv m_emplacement[NOMBRE_EMPLACEMENTEQUIP]; //emplacement du sacados
    EmplacerEquip EmplacementEquipement[6]; //emplacement de la zone équipement.



public:

    void chargementInv(GameData &GameData); // chargement de l'inventaire
    void ouvrirInventaire(gameWindow &fenetre,GameData &GameData ,Carte &Monde); //ouverture...
    void affichage(gameWindow &fenetre,GameData &g, Carte &Monde);
    void setPosition(sf::Vector2f newposition);
    void ChangerEtat(); // si 1 on ouvre l'inventaire
    sf::Vector2f getPosition(); //obtention de la position de l'inventaire (en coordonnée fenetre
    void PositionnerIcone();  //repositionnement des icones

    //lié au curseur:
    void DeplacerCurseur1();
    void DeplacerCurseur2();

    void setVie(Personnage &perso);    //actualisation des stats personnage
    void setEnergie(Personnage &perso);


    void setIconeObj();   //Actualisation des donnée de l'objet pointé
    void setDesobjtsel();
    void setnomObj();
    void setQuantObj();
    void PositionnerTextMenu();
    void setStringMenu();

    void UtiliserObjet(GameData &g,Inventaire &inv);
    void JeterObjet(GameData &g);
    void RetireQuantite(int quantite);

    void setForce(Personnage   &perso);
    void setEndurance(Personnage   &perso);


    void setInfo();// methode regroupant les autre methode concernant l'actualisation des donnée d'objet pointé
    void MiseEnPage(std::string messageAFormater); //formatage du texte pour la description


    bool getEtat(); //recuperation de l'état de l'inventaire
    int getEmplacementCible();




    //methode lié à la gestion des objet
    /*void changerPlaceObjet();
    void echangerObjet();

    void utiliserObjet();
    void ajouterObjet();*/

    Inventaire();
    ~Inventaire();


    friend class Personnage;






};





#endif
