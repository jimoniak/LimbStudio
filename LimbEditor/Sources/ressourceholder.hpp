#ifndef RESHOLDER
#define RESHOLDER



class RessourceHolder : public sf::NonCopyable
{


private:

private:


    std::vector<sf::Texture> m_tableTexture;
    std::string m_cheminTexture;


public:

public:

    RessourceHolder();
    RessourceHolder(std::string nomPack);
    ~RessourceHolder();
    bool charger();
    void nettoyer();

    sf::Texture getTextureElem(int element);



};


#endif // RESHOLDER
