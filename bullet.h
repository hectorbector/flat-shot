#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <SFML/System.hpp>
#include <list>

#include "playerChar.h"
#include "gameMap.h"

class Bullet
{
public:
    sf::Vector2f bulletPos;
    sf::Vector2f direction;
    int startingSpeed;
    double speed;
    int penetration;
    sf::Sprite bulletSprite;

    Bullet(PlayerChar&, sf::Texture&);    //arg is shooter
    bool fly(GameMap&, list<PlayerChar>&, sf::Clock);
private:
    bool collide(GameMap&, list<PlayerChar>&);
    float toMoveDist = 0;

};

#endif // BULLET_H_INCLUDED
