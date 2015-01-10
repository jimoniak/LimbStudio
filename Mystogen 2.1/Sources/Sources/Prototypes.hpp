//----------------------Prototypes.hpp----------------------------------------------

//jimoniak

//fichier contenant les prototypes des fonctions utilisé HORS class.
#ifndef PROTO
#define PROTO

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "gameWindow.hpp"

class Sphere;
class Spherier;
class Personnage;
class gameWindow;

class PanneauActif;
class MusiqueAmbiance;
class settingsMenu;
class Element;
class Timer;



struct Data
{
    std::string nom;
    float v;
};
typedef struct Data Data;





bool AddData(std::vector<Data> &D,std::string nom,float v);
float VData(std::vector<Data> &D,std::string nom);
bool DataExistante(std::vector<Data> &D,std::string nom);
sf::Rect<int> SubRectSelector(sf::Texture &texture,int Direction,float t);

void AnimationPersonnageThread(void* GameData);
void AffichageThread(void* GameData);

int Jeu(gameWindow  &FenetrePrincipale, GameData &g, settingsMenu &sMenu);
int Combat (gameWindow &fenetre,Personnage &Joueur,std::string infos[]);
void ChargeTexture(sf::Image Image[],sf::Texture texture[]);
void ChargeMonoTexture(sf::Image image[],sf::Texture texture[],std::string n);
void LireTailleCarte(std::string Nom,int *x,int *y);
void LireNombreElement(std::string nomCarte , int *n);
void LireInterrupteur(int tabInter[]);
int Cameraman (GameData &g);
void LoadElement(GameData &g);

int  ConvertionStringInt (std::string chaine);
std::string ConvertionIntString ( int nb );
std::string ConvertionFltString( float nombre);
std::string ConvIntString(int nombre);
int ConvStringInt(std::string chaine);
float ConvertionStringFlt(std::string m);
std::string StringNum(std::string s,unsigned int i=0, char separateur='|');

void Presentation(gameWindow &fenetre, GameData &g);

#endif
