/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/
#define GLOBAL

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <ios>
#include "constantes.h"
#include <memory>





#include "outils.hpp"
#include "carte.hpp"


#include "gestionSouris.hpp"
#include "element.hpp"
#include "joueur.hpp"
#include "jeu.hpp"



using namespace sf;
using namespace std;


int main()
{
    debug = true;

    HFENETRE = 768;
    LFENETRE = 1024;


    Jeu jeu;
    jeu.intro();
    jeu.menuPrincipal();

    return EXIT_SUCCESS;
}

