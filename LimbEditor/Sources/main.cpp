
#define GLOBAL

#include <SFML/Graphics.hpp>

#include <GUI.hpp>


#include <iostream>

#include "constantes.hpp"
#include "ressourceholder.hpp"
#include "element.hpp"
#include "carte.hpp"
#include "editeur.hpp"

int main()
{


    HFENETRE = sf::VideoMode::getDesktopMode ().height - 30;
    LFENETRE = 1024;
    Editeur editeur;

    editeur.intro();
    editeur.menuPrincipal();

    return EXIT_SUCCESS;

}
