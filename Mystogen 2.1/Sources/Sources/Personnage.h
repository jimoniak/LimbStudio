#ifndef DEFPERS
#define DEFPERS




class Personnage
{

private:
    sf::Clock                   m_horlogeInterne;
    float                       m_tempsDepart;

    std::string                 m_nom;
    int                         m_X;
    int                         m_Y;
    int                         m_sens;
    int                         m_move;
    float                         m_frame;
    float                       m_vitesseDep;
    float                       m_tempsDebut;
    sf::Sprite                  m_apparence;

    sf::Sprite                  m_apparenceHaut;
    sf::Sprite                  m_apparenceBas;
    sf::Sprite                  m_skin;
    sf::Image                  m_image;
    sf::Texture                m_Texture;

    int h,l;

    sf::Texture                   m_battler;
    sf::Image                     m_imageBattler;

    bool m_mouvementEnCour;
    bool m_tempsDepInitialise;
    int m_distanceParcourue;
    sf::Vector2f m_position;

    // Stats
    int                         m_vie;
    int                         m_MAXvie;

    int                         m_energie;
    int                         m_MAXenergie;


    int                         m_vitalite; //ajout de vie supplementaire suivant la fonction m_vitalite * 10 = m_MAXvie;
    int                         m_ressource;//ajout d'energie supplementaire suivant la fonction m-ressource * 5 = m_MAXenergie


    int                         m_force;
    int                         m_forceSup;//force lié à l'équipement

    int                         m_endurance;
    int                         m_enduranceSup;//endurance lié à l'équipement


    int                         m_reflexe;
    int                         m_precision;
    int                         m_vitesse;
    int                         m_chance;



    //Equipement

    Arme *ArmeEquipe;
    Casque *CasqueEquipe;
    Torse *TorseEquipe;
    Gant  *GantEquipe;
    Jambiere *JambiereEquipe;
    Chaussure *ChaussureEquipe;


    Inventaire m_Inventaire;
//    Spherier m_spherier;


public:


//fonction concernant le moteur du jeu
    void ChangerEtatInv();
    void ChangerEtatSphr();
    void setPositionInv(GameData &g);
    void OuvrirInv(gameWindow &fenetre,GameData &g,Carte &Monde);
    bool getEtatInv();
    bool getEtatSphr();
    void OuvrirSphr(gameWindow &fenetre, sf::Music &musique);
    void chargementInv(GameData &g);

    void ChangerArme(Arme *newArme);
    void RetirerArme();
//fonction utilisé par l'inventaire:
    void ChangerCasque(Casque *newCasque);
    void ChangerTorse(Torse *newTorse);
    void ChangerGant(Gant *newGant);
    void ChangerJambiere(Jambiere *newJambiere);
    void ChangerChaussure(Chaussure *newChaussure);

    void RetireVetement(int valeur[]);
    void RetirerCasque();
    void RetirerTorse();
    void RetirerGant();
    void RetirerJambiere();
    void RetirerChaussure();

    Arme* getArme();
    Casque* getCasque();
    Torse*  getTorse();
    Gant* getGant();
    Jambiere* getJambiere();
    Chaussure* getChaussure();
//------------------------------------------------

    //Constructeur-Destructeur

    Personnage(gameWindow *fen,sf::Font& polic , sf::Clock &Tp);

    ~Personnage();

    //getter
    std::string getNom() const;
    int getX();
    int getY();
    int getSens();
    int getMove();
    int getFrame();
    int getVie();
    int getMaxVie();
    int getEnergie();
    int getMaxEnergie();
    int getForce();
    int getEndurance();


    const sf::Texture* getSprite();
    sf::Vector2f getPosImg();
    bool getMouvement();

    void Chargement(std::string &nomCarteACharger,GameData &g);
    void ChargementInventaire();

    //methode standard
    void ResetTempsDep();

    void upFrame(Timer temps);
    void Teleport(int X,int Y);
    void Attaquer(Ennemi &Cible);
    void Soigner(int soin);
    void Energie(int energie);
    void gagnerExperience(int Don);
    void PerdreVie(int qtt);
    void augmenterMaxvie();
    void changerNom(std::string nom);
    void ajouterForce(int force);
    void reduireForce(int force);
    void ajouterEndurance(int endurance);
    void reduireEndurance(int endurance);
    void deplacer(int direction,bool grille[],int X,int Y,Element Elm[],int n,Timer &temps);

    //Methode concernant affichage et animation

    void Animer(Timer &temps);
    void resetTempsDeb();
    void Affichage(gameWindow &fenetre);//methode qui affiche le sprite en entier .
    void AfficherHaut(gameWindow &fenetre);//methode qui permet dafficher que la partie haute du sprite
    void AfficherBas(gameWindow &fenetre);//et ici la partie basse   (utile pour la gestion des couches est autre bug daffichage sur les item)
    void AffichageCombat(gameWindow &fenetre);

};
#endif
