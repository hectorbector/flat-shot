#ifndef INGAMESCREEN_H_INCLUDED
#define INGAMESCREEN_H_INCLUDED

#include <list>

#include "gameMap.h"
#include "bullet.h"

using namespace std;

class IngameScreen
{
public:
    sf::Time tickrate;      //time between ticks
    list<PlayerChar> players;
    list<Bullet> bullets;
    int tickCount;          //number of ticks past
    sf::Clock mainClock;
    sf::Clock tickClock;
    GameMap currentMap;

    IngameScreen(int, int); //x, y, size of map
    void update(sf::RenderWindow&);
    void draw(sf::RenderWindow&);
    void fire();

private:
    sf::Texture bulletTex;
    void playerCollide(PlayerChar&);
};

#endif // INGAMESCREEN_H_INCLUDED
