

#ifndef CONSTANTE
#define CONSTANTE


#define LARGEUR_TILE    128
#define HAUTEUR_TILE      64
#define DEMI_LTILE               LARGEUR_TILE / 2
#define DEMI_HTILE               HAUTEUR_TILE / 2
#define COTECARTE          10
#define NOMBRECASE  COTECARTE * COTECARTE
#define TEMPSANIMATION 500
#define VECTEUR_DEPLACEMENT_X LARGEUR_TILE / 2
#define VECTEUR_DEPLACEMENT_Y HAUTEUR_TILE / 2
#define NOMBRE_FRAME 4

#define OFFSET_CARTE  0- (COTECARTE * LARGEUR_TILE) / 2

#define VERSION "Version alpha 0.5"



enum Type_element
{

    CAISSE,
    MUR,
    OBJECTIF,
    DEPART,
    RIEN
};
#endif // CONSTANTE

//creation d'un systeme permettant de declarer des varialbe global

#ifdef GLOBAL
#define Global
#else
#define Global extern
#endif

Global int HFENETRE;
Global int LFENETRE;
Global std::string nomOS;
Global bool debug;

#ifdef _WIN32
#define WINDOW
#endif

#ifdef  __linux__
#define LINUX
#endif
