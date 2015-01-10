//-------------------Mystogen-----------------------------

//constante.h
#ifndef CONST
#define CONST

#include <string>

#define VERSION "alpha 0.6"
#define DEBUg 0
#define HTILE 32
#define LTILE 32 //constantes donnant la largeur et hauteur des tailles
//#define HFENETRE sf::VideoMode::getDesktopMode ().Height
//#define LFENETRE sf::VideoMode::getDesktopMode ().Width
#define TAILLETABID 6821 //constante donnant le nombre total de textures tiles à charger en memoire
#define NOMBRE_INTERRUPTEUR 100
#define NOMBRE_EMPLACEMENTEQUIP 25
#define CONSTANTE_EMPLACEMENT_POSITION 5 // 5 au carre 25 , sert pour "quadriller" l'inventaire
//#define NOMBRE_ATTRIBUT_VETEMENT
#define NBFRAMEANIM 3
#define FRAME 8.0


//#define HFENETRE 700
//#define LFENETRE 1024

enum {HAUT, BAS, gAUCHE, DROITE};
enum {FAIBLE, MOYEN , ELEVE};


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


#endif


//creation d'un systeme permettant de declarer des varialbe global





