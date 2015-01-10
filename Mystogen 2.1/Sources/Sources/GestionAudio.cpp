#include "gestionAudio.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
using namespace sf;

void MusiqueAmbiance::chargerMusique(std::string nom)
{
    if (nom != "NotPrecised") m_musiqueACharger = nom;
    if(m_nomMusique != m_musiqueACharger && m_musiqueACharger != "" )
    {
        m_nomMusique = m_musiqueACharger;
        if(m_musiqueACharger == "NoMusic")  this->arreterMusique();
        else
        {
            m_cheminAcces = "Ressources/Musics/" + m_musiqueACharger;
            if(!m_musique.openFromFile(m_cheminAcces.c_str()))  cout << "Impossible d'ouvrir: " << m_cheminAcces << endl;
            else    this->lancerMusique();
        }
    }
}

void MusiqueAmbiance::changerMusique(string const *NomCarte)
{
    string lignelue;
    m_cheminAcces= "Elements/"+*NomCarte+".elm";
    ifstream Musique(m_cheminAcces.c_str(),ios::in);
    if(!Musique)    cout << "impossible de charger: " << m_cheminAcces << endl;
    else
    {
        while(lignelue != "@")
        {
            getline(Musique,lignelue);
            if(lignelue == "EOF")
            {
                cout << "Pas d'@ trouv� !" << endl;
                return;
            }
        }
        getline(Musique,lignelue);
        m_musiqueACharger = lignelue;
    }
}

void MusiqueAmbiance::lancerMusique()
{
    m_musique.setLoop(true);
    m_musique.play();
}

void MusiqueAmbiance::pause() {}
void MusiqueAmbiance::arreterMusique()
{
    m_musique.setLoop(false);
    m_musique.stop();
}

void MusiqueAmbiance::setVolume(int v)
{
    m_musique.setVolume(v);
}

sf::Music& MusiqueAmbiance::getMusique()
{
    return m_musique;
}

int MusiqueAmbiance::getVolume()
{
    return m_musique.getVolume();
}

//float MusiqueAmbiance::getDuree(){}
