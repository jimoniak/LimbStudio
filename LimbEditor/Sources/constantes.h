/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/

#ifndef CONSTANTE
#define CONSTANTE


#define LARGEUR_TILE    128
#define HAUTEUR_TILE      64
#define DEMI_LTILE               LARGEUR_TILE / 2
#define DEMI_HTILE               HAUTEUR_TILE / 2
#define COTECARTE          10
#define NOMBRECASE  COTECARTE * COTECARTE
#define TEMPSANIMATION 400
#define VECTEUR_DEPLACEMENT_X LARGEUR_TILE / 2
#define VECTEUR_DEPLACEMENT_Y HAUTEUR_TILE / 2
#define NOMBRE_FRAME 4

#define OFFSET_CARTE  0- (COTECARTE * LARGEUR_TILE) / 2
#define VERSION "Version alpha 0.6"



enum Type_element {
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
