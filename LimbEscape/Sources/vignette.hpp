



class Vignette : public lgui::Bouton
{
    private:
    //sf::Text m_sousTitre;

    public:
        Vignette(sf::Font &font);
      ~Vignette();

    void setPosition(sf::Vector2f position);
    //void setTitre(std::string titre);
   // void  afficher();



};
