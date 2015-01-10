#include "Classes.h"
#include "constantes.hpp"

Timer::Timer()
{
    m_DifTot = 0.0;
    m_IsStop = 0;
}
void Timer::Stop()
{
    m_horlogeDeux.restart();
    m_IsStop = 1;
}
void Timer::ReStart()
{
    m_DifTot += m_horlogeDeux.getElapsedTime().asSeconds();
    m_IsStop = 0;
}
float Timer::getElapsedTime()
{
    return m_horlogeUn.getElapsedTime().asSeconds() - m_IsStop * m_horlogeDeux.getElapsedTime().asSeconds() - m_DifTot;
}

Timer::~Timer()
{

}

