//--------Jimoniak---------


#ifndef gESTIONAUDIO
#define gESTIONAUDIO

#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <string>

class MusiqueAmbiance
{
private:
    sf::Music m_musique;
    std::string m_cheminAcces;

    std::string m_nomMusique;
    std::string m_musiqueACharger;

public:
    void lancerMusique();
    void chargerMusique(std::string nom = "NotPrecised");
    void changerMusique(std::string const *nomCarte);

    void pause();
    void arreterMusique();

    sf::Music& getMusique();
    void setVolume(int v);
    int getVolume();
    float getDuree();



};

#endif
