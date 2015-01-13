/*
    LimbEscape,
    Crée par Jimmy PEAULT sous le nom de LimbStudio

    Jeu sokoban en 2d isometrique

    utilisant la technologie de la SFML 2.1.


LimbEscape de Limb'Studio est mis à disposition selon les termes de la licence Creative Commons Attribution - Pas d’Utilisation Commerciale 4.0 International.
Les autorisations au-delà du champ de cette licence peuvent être obtenues à mail.limbStudio@gmail.com.

depot officiel : https://github.com/jimoniak/LimbEscape

*/
#include <string>
#include<SFML/Graphics.hpp>

#include "outils.hpp"

#include <ios>
#include <sstream>

namespace utils {

std::string  ConvertionFltString(float nombre )
{
    std::ostringstream os;
    os << nombre;
    return os.str();

}



}

