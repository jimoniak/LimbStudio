
#define NSTATS 6

//Lié au centre du trou noir du fond d'écran
#define CENTREIMGX 795
#define CENTREIMGY 570



#ifndef SPHERIER
#define SPHERIER


#include <SFML/Audio.hpp>
#include "Prototypes.hpp"
#include "Bouton.hpp"
/*
class GameWindow;

class Sphere
{
	private :
	int id;
	bool stat;
	int num;
	int qtt;
	bool active;


	public :
	Bouton bt;

	Sphere();
	void Load(int id,sf::Font &police,float x ,float y , sf::Image& img, bool isStat , int numero , int qtit , bool isActive );
	void Activate();
	bool IsActivated();
	bool IsStat();
	int GetNum();
	int GetQtt();
	void UpQtt();
	void UpNum();
	void Move(int x,int y);
	sf::Vector2f GetPos();
	void Info();
	sf::Color ResetColor();

};







class Spherier
{
	private:
	bool m_actif;

	bool loaded;
	bool edit;
	bool magnet;
	int Idmagnet;
	int stats[NSTATS];
	char sorts[256];
	std::vector <Sphere> t;
	int point;
	sf::Vector2f centre;
    float xsouris;
    float xvirtuel;
    float ysouris;
    float yvirtuel;
	float zoom;
	std::string NomJoueur;
	sf::Image BarrePixel;
	sf::Image sphere;
	sf::Image fond;
	sf::Sprite background;
	sf::Sprite SBarre;
	sf::String St[NSTATS+2];
	sf::Music musique;
	sf::SoundBuffer Switch;
    sf::Sound Sound;
	sf::Clock& Temps;
	sf::Font& police;

	public :

	Spherier(std::string File , sf::Font& polic , sf::Clock& Tp);
	void Save(std::string NomSauvegarde);
	void Load(std::string File);
	void EditMode();
	void ChangerEtat();
	bool GetEtat();

	void Menu(gameWindow &fen,sf::Music& Mus);
	bool Control(gameWindow &fen);
	void Affiche(gameWindow &fen ,unsigned char dark = 0);
	int ClosestSphere(unsigned int id);
	bool Activate(int id);
	int Cost(int id , int id2);
	int SphereUnder(float x , float y);
	void GivePoint(int amount);
	int GetStat(int num);
	int GetForce();
	int GetPrecision();
	int GetReflexe();
	int GetPerception();
	int GetMental();
	int GetCharisme();
	bool GetSort(int num);

};

*/
#endif

