
#include "constantes.hpp"

#include <SFML/Graphics.hpp>

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
#include "Spherier.hpp"



std::string NomStat(int i)
{   switch (i)
    {   case 0 : return "Force : ";      break;
        case 1 : return "Precision : ";  break;
        case 2 : return "Reflexes : ";   break;
        case 3 : return "Perception : "; break;
        case 4 : return "Mental : ";     break;
        case 5 : return "Charisme : ";   break;
        case 6 : return "Xp : ";         break;
        default :return "Error";         break;
    }
}

sf::Color ColorNum(int i)
{   switch (i)
    {   case 0 : return sf::Color::Red;     break;
        case 1 : return sf::Color::Yellow;  break;
        case 2 : return sf::Color::green;   break;
        case 3 : return sf::Color::Cyan;    break;
        case 4 : return sf::Color::Blue;    break;
        case 5 : return sf::Color::Magenta; break;
        default :return sf::Color::White;   break;
    }
}



Sphere::Sphere() :
id(0),
stat(1),
num(0),
qtt(1),
active(0),
bt(0,0,32,32,1)
{

}

void Sphere::Load(int Id,sf::Font &police,float x ,float y , sf::Texture& img, bool isStat , int numero , int qtit , bool enable)
{
    id = Id;
    stat = isStat;
    num = numero;
    qtt = qtit;
    active = enable;
    bt.setPos(sf::Vector2f(x,y));
    bt.setSprite(img);
    bt.setTxt(ConvIntString(qtt),police,ResetColor(),20);
    bt.setStringPos(sf::Vector2f(x-8,y-10));
}

void Sphere::Activate()
{   active = !active;
    if(active)  bt.setMaskTransparence(255);
}

bool Sphere::IsActivated(){return active;}
bool Sphere::IsStat(){return stat;}
int Sphere::getNum(){return num;}
int Sphere::getQtt(){return qtt;}
void Sphere::UpQtt()
{   qtt++;
    if(qtt>9) qtt = 1;
    bt.setString(ConvIntString(qtt));
}

void Sphere::UpNum()
{   if(stat)
    {   num++;
        if(num>5) num = 0;
        ResetColor();
    }
}

void Sphere::Move(int x , int y) {bt.setPos(sf::Vector2f(x,y));}
sf::Vector2f Sphere::getPos(){return bt.getPos();}
void Sphere::Info()
{   std::cout << std::endl
              << " id : "  << id << std::endl
              << " stat: " << stat << std::endl
              << " num : " << num << std::endl
              << " qtt : " << qtt << std::endl
              << " x : "   << bt.getPos().x << std::endl
              << " y : "   << bt.getPos().y << std::endl;
}

sf::Color Sphere::ResetColor()
{   bt.setColorText(ColorNum(num));
    bt.setMask(ColorNum(num));
    return ColorNum(num);
}













Spherier::Spherier(std::string File , sf::Font& polic , sf::Clock &Tp) :
loaded(0),
edit(0),
magnet(0),
Idmagnet(-1),
BarrePixel(64,1,sf::Color::Black),
Temps(Tp),
police(polic)
{
    Load(File);}


void Spherier::Save(std::string NomSauvegarde)
{   std::string Full = ConvIntString(point);
    for (unsigned int i = 0 ; i < t.size() ; i++)
    {   Full += + "\n";
        Full += ConvIntString(t[i].IsStat()) +"|";
        Full += ConvIntString(t[i].getNum()) +"|";
        Full += ConvIntString(t[i].getQtt()) +"|";
        Full += ConvIntString(t[i].IsActivated()) +"|";
        Full += ConvIntString(t[i].bt.getPos().x/16) +"|";
        Full += ConvIntString(t[i].bt.getPos().y/16) +"|";
    }
    std::ofstream file( NomSauvegarde.c_str() , std::ios::out );
    if(file){file << Full;}
}



void Spherier::Load(std::string File)
{
    m_actif=false;

    std::cout << "Chargement du Spherier !" << std::endl;
    File += ".sph";
    NomJoueur = File;
    sphere.loadFromFile("Ressources/Spherier/Sphere2.bmp");
    sphere.CreateMaskFromColor(sf::Color(255,255,255));
    fond.loadFromFile("Ressources/Spherier/SphereVortex.jpg");
    background.setTexture(fond);
    zoom = 2;
    centre.x = 0;
    centre.y = 0;
    background.setPosition(0,0);
    background.Scale(2,2);
    background.setCenter(CENTREIMgX,CENTREIMgY);

    for(int i = 0; i < 32 ; i++)    BarrePixel.setPixel(i,0,sf::Color(0,i,i,i*3));
    BarrePixel.CreateMaskFromColor(sf::Color::Black);
    SBarre.setTexture(BarrePixel);
    SBarre.setCenter(SBarre.getSize().x/2,SBarre.getSize().y/2);
    SBarre.setScaleX(90);
    SBarre.setScaleY(3);

    musique.OpenFromFile("Ressources/Spherier/Slow_eMotion.ogg");
    musique.setLoop(1);
    musique.setVolume(0);

    Switch.loadFromFile("Ressources/Spherier/SwitchOn.ogg");
    Sound.setBuffer(Switch);
    Sound.setVolume(20);

    std::string ligne;
    FILE* f = fopen(File.c_str(),"r");
    if(f) fclose(f);
    else File = "Ressources/Spherier/Spherier.sph";

    std::ifstream lecture(File.c_str(),std::ios::in);

    std::getline(lecture,ligne);
    point = ConvertionStringInt(ligne);
    std::getline(lecture,ligne);
    t.resize(0);
    while(lecture)
    {   t.resize(t.size()+1);
        int xs,ys;
        if(StringNum(ligne,4)[0] == '-')    xs = - ConvertionStringInt( StringNum(StringNum(ligne,4),1,'-'))*16;
        else xs = ConvertionStringInt(StringNum(ligne,4))*16;
        if(StringNum(ligne,5)[0] == '-')    ys = - ConvertionStringInt( StringNum(StringNum(ligne,5),1,'-'))*16;
        else ys = ConvertionStringInt(StringNum(ligne,5))*16;

       t[t.size()-1].Load(t.size()-1 , police , xs , ys , sphere ,
                           ConvertionStringInt(StringNum(ligne,0)) ,
                           ConvertionStringInt(StringNum(ligne,1)) ,
                           ConvertionStringInt(StringNum(ligne,2)) ,
                           ConvertionStringInt(StringNum(ligne,3))
                           );

        std::getline(lecture,ligne);
    }
    for ( int i = 0 ; i < NSTATS ; i++)
    {   stats[i] = 0;
        for (unsigned int j = 0 ; j < t.size() ; j++)
        {   if (t[j].getNum() == i && t[j].IsActivated())
            {   stats[i] += t[j].getQtt();
            }
        }
    }

    for ( int i = 0 ; i < NSTATS + 2 ; i++)
    {   if( i == NSTATS ) St[NSTATS].setString(NomStat(i)+ConvIntString(point));
        else if ( i == NSTATS + 1 ) St[NSTATS+1].setString("??");
        else St[i].setString(NomStat(i)+ConvIntString(stats[i]));

        St[i].setFont(police);
        St[i].setSize(10);
        St[i].setColor(ColorNum(i));
        St[i].setPosition(sf::Vector2f(LFENETRE/20 * ( 1 + i) , HFENETRE/2 - 30));
        St[i].setCenter(St[i].getRect().getWidth()/2.0-2,St[i].getRect().getHeight()/2.0+2);
    }
    loaded = 1;
}

void Spherier::EditMode()
{   edit = !edit;
    if(edit)
    {   for ( int i = 0 ; i < NSTATS + 1 ; i++)
        {   switch (i)
            {   case 0 : St[i].setString("F: UpQtt ");  break;
                case 1 : St[i].setString("C: UpNum ");  break;
                case 2 : St[i].setString("Espace: New");   break;
                case 3 : St[i].setString("T: Suppr"); break;
                case 4 : St[i].setString("E: Active");     break;
                case 5 : St[i].setString("R: Duplicate");   break;
                case 6 : St[i].setString("X: Info");         break;
                default : break;
            }
        }
    }
    else
    {   for ( int i = 0 ; i < NSTATS + 1 ; i++)
        {   if( i == NSTATS ) St[NSTATS].setString(NomStat(i)+ConvIntString(point));
            else if ( i == NSTATS + 1 ) St[NSTATS+1].setString("??");
            else St[i].setString(NomStat(i)+ConvIntString(stats[i]));
        }
    }
}


void Spherier::ChangerEtat()
{
    m_actif = !m_actif;
}
bool Spherier::getEtat()
{
    return m_actif;
}


void Spherier::Menu(gameWindow &fen,sf::Music& Mus)
{   const sf::View* SaveV = &fen.getView();
    fen.setView(fen.getDefaultView());
    sf::Texture Prec(fen.Capture());
    sf::Sprite Sprec(Prec);

    float Volume = Mus.getVolume();
    float tecoule;
    float tini = Temps.getElapsedTime();

    do
    {   tecoule = 1000.0 * (Temps.getElapsedTime() - tini);
        if ( tecoule > 255.0) break;

        Mus.setVolume(Volume * (255.0 - tecoule)/255.0 );
        Sprec.setColor(sf::Color(255,255,255,255-tecoule));

        fen.Clear();
        fen.draw(Sprec);
        fen.setView(fen.getDefaultView()); // Ajout par Jimmy , permettant l'affichage de la souris personnalisé suivant le bon plan x,y  en non x,z.
        fen.Display();
    } while ( tecoule < 255.0);

    Mus.Pause();
    musique.play();

    centre.x = 0;
    centre.y = 0;
    zoom = 0.1;

    tini = Temps.getElapsedTime();
    tecoule = 0;
    do
    {   zoom = 0.1 + 2.0*sqrt(tecoule);
        musique.setVolume(Volume/2.0*zoom);
        fen.Clear();
        Affiche(fen,255.0-(tecoule)*282.5454);
        fen.setView(fen.getDefaultView()); // Ajout par Jimmy , permettant l'affichage de la souris personnalisé suivant le bon plan x,y  en non x,z.
        fen.Display();
        tecoule = Temps.getElapsedTime()-tini;
    }while(tecoule < 0.9025);
    zoom = 2;

    while(Control(fen))
    {   Affiche(fen);
        fen.setView(fen.getDefaultView()); // Ajout par Jimmy , permettant l'affichage de la souris personnalisé suivant le bon plan x,y  en non x,z.
        fen.Display();
    }

    float z = zoom;
    float d = z - 0.1 ;
    tini = Temps.getElapsedTime();
    tecoule = 0;
    do
    {   zoom = z - d * tecoule / 0.9025;
        musique.setVolume(Volume/z*zoom);
        fen.Clear();
        Affiche(fen,tecoule*282.5454);
        fen.setView(fen.getDefaultView()); // Ajout par Jimmy , permettant l'affichage de la souris personnalisé suivant le bon plan x,y  en non x,z.
        fen.Display();

        tecoule = Temps.getElapsedTime()-tini;
    }while(tecoule < 0.9025);


    musique.Stop();
    Mus.play();
    fen.setView(fen.getDefaultView());

    tini = Temps.getElapsedTime();
    do
    {   tecoule = 1000.0 * (Temps.getElapsedTime() - tini);
        if ( tecoule > 255.0) break;
        Mus.setVolume(Volume * (tecoule)/255.0    );
        Sprec.setColor(sf::Color(255,255,255,tecoule));
        fen.Clear();
        fen.draw(Sprec);
        fen.setView(fen.getDefaultView()); // Ajout par Jimmy , permettant l'affichage de la souris personnalisé suivant le bon plan x,y  en non x,z.
        fen.Display();
    } while ( tecoule < 255);
    Mus.setVolume(Volume);
    fen.setView(*SaveV);
}



bool Spherier::Control(gameWindow &fen)
{   sf::Event ev;
    while(fen.getEvent(ev))
    {   if (ev.Type == sf::Event::Closed)
        {
            fen.Close();
            return 0;
        }else if (ev.Type == sf::Event::MouseWheelMoved)
        {   if      (ev.MouseWheel.Delta > 0 && zoom < 3)   zoom*=1.2;
            else if (ev.MouseWheel.Delta < 0 && zoom > 0.6) zoom/=1.2;
            ev.MouseWheel.Delta = 0;
        }else if (ev.Type == sf::Event::MouseMoved)
        {   xsouris = (2*ev.MouseMove.X - LFENETRE)/zoom;
            ysouris = (2*ev.MouseMove.Y - HFENETRE)/zoom;
            xvirtuel = xsouris + centre.x;
            yvirtuel = ysouris + centre.y;
            if(edit && magnet && Idmagnet != -1)    t[Idmagnet].Move(((int)xvirtuel/16)*16,((int)yvirtuel/16)*16);
        }else if (ev.Type == sf::Event::MouseButtonPressed)
        {   if(ev.MouseButton.Button == sf::Mouse::Left)
            {   if(!edit)
                {   for ( unsigned int i = 0 ; i < t.size() ; i++)
                    {   if ( t[i].bt.EstDessus(xvirtuel,yvirtuel) ) Activate(i);
                    }
                }
                else
                {   magnet = !magnet;
                    if(magnet)  Idmagnet = SphereUnder(xvirtuel,yvirtuel);
                }
                ev.Type = sf::Event::MouseButtonReleased;
            }
        }else if (ev.Type == sf::Event::KeyPressed)
        {   if(ev.Key.Code == 'a') { Save(NomJoueur); ChangerEtat(); return 0;}
            else if (ev.Key.Code == 'p') EditMode();
            if(edit)
            {   int Idsouris = SphereUnder(xvirtuel,yvirtuel);
                if (ev.Key.Code == sf::Key::Space)
                {   t.resize(t.size()+1);
                    t[t.size()-1].Load(t.size()-1 , police , ((int)xvirtuel/16)*16 , ((int)yvirtuel/16)*16 , sphere ,1 ,0 ,1 ,0);
                    t[t.size()-1].Move(((int)xvirtuel/16)*16,((int)yvirtuel/16)*16);
                }
                if(Idsouris > -1)
                {   if (ev.Key.Code == 'f')        t[Idsouris].UpQtt();
                    else if(ev.Key.Code == 'c')    t[Idsouris].UpNum();
                    else if(ev.Key.Code == 't')
                    {   t.erase(t.begin()+Idsouris);
                        for ( unsigned int i = Idsouris ; i < t.size() ; i++)
                            t[i].ResetColor();
                    }
                    else if(ev.Key.Code == 'e')
                    {   t[Idsouris].Activate();
                        if(t[Idsouris].IsActivated())
                        {   if(t[Idsouris].IsStat())  stats[t[Idsouris].getNum()] += t[Idsouris].getQtt();
                            else sorts[t[Idsouris].getNum()] = 1;
                        }
                        else
                        {   if(t[Idsouris].IsStat())  stats[t[Idsouris].getNum()] -= t[Idsouris].getQtt();
                            else sorts[t[Idsouris].getNum()] = 0;
                        }
                    }
                    else if(ev.Key.Code == 'x')    t[Idsouris].Info();
                    else if(ev.Key.Code == 'r')
                    {   t.resize(t.size()+1);
                        t[t.size()-1].Load(t.size()-1 , police , ((int)xvirtuel/16)*16 , ((int)yvirtuel/16)*16 , sphere ,
                                           t[Idsouris].IsStat() ,t[Idsouris].getNum() ,t[Idsouris].getQtt() ,t[Idsouris].IsActivated());
                        magnet = 1;
                        Idmagnet = t.size()-1;
                    }
                }
            }
        }
    }
    if      (fen.getInput().IsKeyDown(sf::Key::Z))    centre.y -= 25/zoom;
    else if (fen.getInput().IsKeyDown(sf::Key::S))    centre.y += 25/zoom;
    if      (fen.getInput().IsKeyDown(sf::Key::Q))    centre.x -= 25/zoom;
    else if (fen.getInput().IsKeyDown(sf::Key::D))    centre.x += 25/zoom;
    if      (fen.getInput().IsMouseButtonDown(sf::Mouse::Right))
    {   centre.x += xsouris/20;
        centre.y += ysouris/20;
    }
    return 1;
}


void Spherier::Affiche(gameWindow &fen ,unsigned char dark)
{   if(centre.x > 1000 )        centre.x = 1000;
    else if (centre.x < -1000 ) centre.x = -1000;
    if(centre.y > 1000 )        centre.y = 1000;
    else if (centre.y < -1000 ) centre.y = -1000;

    background.setPosition(centre.x*0.9,centre.y*0.9);

    background.Rotate(-0.09);
    background.setScale(  sf::Vector2f(  4 /zoom + 0.05 * zoom, 4 /zoom + 0.05 * zoom  )   );

    for ( int i = 0 ; i < NSTATS + 1 ; i++)
    {   St[i].setScale(4/zoom,4/zoom);
        St[i].setPosition(centre.x + (LFENETRE/3.5 * (i+0.6) - LFENETRE - LFENETRE/8) / zoom , centre.y + (HFENETRE - 40)/zoom);
    }

    fen.setView(sf::View(centre , sf::Vector2f(LFENETRE/zoom,HFENETRE/zoom) ));
    fen.draw(background);

    for(int i =0 ; i < 360 ; i++)
    {   SBarre.Rotate(49.9998);
        SBarre.setPosition(800/2 * ( 0.5*sin(i+cos(10)/50)),800/2 * ( 0.5*cos(i+sin(10)/50)));
        fen.draw(SBarre);
    }

    for ( unsigned int i = 0 ; i < t.size() ; i++)
    {   if(t[i].IsActivated())  t[i].bt.Affichage(fen);
        else
        {   t[i].bt.setMaskTransparence(128*(1+sin(3 * Temps.getElapsedTime())));
            if(t[i].bt.Affichage2(fen,xvirtuel , yvirtuel))
            {   if( sf::Vector2f( xvirtuel , yvirtuel - 20) != St[NSTATS+1].getPosition() )
                {   St[NSTATS+1].setString(ConvIntString(Cost(i,ClosestSphere(i))));
                    St[NSTATS+1].setScale(4/zoom,4/zoom);
                    St[NSTATS+1].setPosition(  xvirtuel , yvirtuel - 20 );
                }
                fen.draw(St[NSTATS+1]);
            }
        }
    }

    for ( int i = 0 ; i < NSTATS + 1 ; i++) fen.draw(St[i]);

    if(dark != 0)
    {   sf::Texture a;
            a.Create(3,3,sf::Color(0,0,0,dark));
            a.setSmooth(0);
        sf::Sprite s;
            s.setTexture(a);
            s.setPosition(0,0);
            s.setCenter(2,2);
            s.setScale(3200/zoom,3200/zoom);
        fen.draw(s);
    }
}



int Spherier::ClosestSphere(unsigned int id)
{   int x = t[id].getPos().x;
	int y = t[id].getPos().y;
	int ir = 0;
	unsigned int d = 0xFFFFFFFF;
	for(unsigned int i=0 ; i < t.size() ; i++)
	{   if ( i != id && t[i].IsActivated())
		{   unsigned int a = (t[i].getPos().x - x) * (t[i].getPos().x - x) + (t[i].getPos().y - y) * (t[i].getPos().y - y);
			if ( a < d )
			{   ir = i;
				d = a;
			}
		}
	}
	return ir;
}



bool Spherier::Activate(int id)
{   if(t[id].IsActivated()) return 0;
	int a = Cost(id,ClosestSphere(id));
	if ( a > point ) return 0;
	point -= a;
	t[id].Activate();
	if(t[id].IsStat())  stats[t[id].getNum()] += t[id].getQtt();
	else sorts[t[id].getNum()] = 1;
	for ( int i = 0 ; i < NSTATS + 1 ; i++)
    {   if(i!= NSTATS) St[i].setString(NomStat(i)+ConvIntString(stats[i]));
        else St[i].setString(NomStat(i)+ConvIntString(point));
    }
    Sound.play();
	return 1;
}



int Spherier::Cost(int id , int id2)
{   int x1 = (t[id2].getPos().x - t[id].getPos().x)/16;
	int y1 = (t[id2].getPos().y - t[id].getPos().y)/16;
	return x1*x1 + y1*y1;
}


int Spherier::SphereUnder(float x , float y)
{   for ( unsigned int i = 0 ; i < t.size() ; i++)
    {   if(t[i].bt.EstDessus(x,y))  return i;
    }
    return -1;
}

void Spherier::givePoint(int amount){point += amount;}
int Spherier::getStat(int num){return stats[num];}
int Spherier::getForce(){return stats[0];}
int Spherier::getPrecision(){return stats[1];}
int Spherier::getReflexe(){return stats[2];}
int Spherier::getPerception(){return stats[3];}
int Spherier::getMental(){return stats[4];}
int Spherier::getCharisme(){return stats[5];}
bool Spherier::getSort(int num){return sorts[num];}
