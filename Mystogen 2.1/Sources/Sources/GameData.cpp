
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "constantes.hpp"

#include "gameWindow.hpp"

#include "gestionAudio.h"
#include "Classes.h"


#include "Carte.hpp"

#include "Prototypes.hpp"
#include "Bouton.hpp"

#include "graphique.hpp"
#include "Inventaire.hpp"

#include "Spherier.hpp"
#include "Personnage.h"

#include "PanneauActif.h"
#include "Messagerie.hpp"

#include "GameData.hpp"






GameData::GameData():
Joueur(Fenetre,font,Temps)
{
}


GameData::~GameData()
{

}
