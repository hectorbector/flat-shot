#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define M_PI 3.1415926535897
#include <math.h>

#include "bullet.h"
#include "playerChar.h"

using namespace std;



Bullet::Bullet(PlayerChar & shooter, sf::Texture & bulletTex)
{
    bulletSprite.setTexture(bulletTex);
    bulletSprite.setOrigin(1, 0);

    //find gun barrel
    sf::Vector2f absPos = shooter.charSprite.getPosition();
    double shooterRotation = shooter.charSprite.getRotation() * (M_PI/180);
    sf::Vector2f tempPos = sf::Vector2f(shooter.gunPos.x - absPos.x, shooter.gunPos.y - absPos.y);
    double s = sin(shooterRotation);
    double c = cos(shooterRotation);
    tempPos.x = shooter.gunPos.x * c - shooter.gunPos.y * s;
    tempPos.y = shooter.gunPos.x * s + shooter.gunPos.y * c;
    tempPos.x += absPos.x;
    tempPos.y += absPos.y;

    //set position, orientation, penetration, and speed
    bulletPos = tempPos;
    bulletSprite.setPosition(bulletPos);
    bulletSprite.setRotation(shooter.charSprite.getRotation());
    direction = sf::Vector2f(s, -c);
    startingSpeed = 1000;
    speed = startingSpeed;
    penetration = 200;
}

bool Bullet::fly(GameMap & currentMap, list<PlayerChar> & players, sf::Clock clock)
{
    float timeStep = clock.getElapsedTime().asSeconds();
    toMoveDist += speed * timeStep;
    while (toMoveDist > 1)
    {
        bulletPos += direction;
        if (collide(currentMap, players))
        {
            return true;
        }
        toMoveDist--;
    }
    return false;
}

bool Bullet::collide(GameMap & currentMap, list<PlayerChar> & players)
{
    sf::Vector2f c = bulletPos;

    if (bulletPos.x < 0 || bulletPos.x > currentMap.xdim ||
        bulletPos.y < 0 || bulletPos.y > currentMap.ydim)
    {
        return true;
    }
    else if (currentMap.density[c.x][c.y] == -1)
    {
        speed = 0;      //impenetrable
    }

    /*if (currentMap.density[c.x][c.y] == -2)
    {
        INSERT REFLECTION CODE HERE
    }*/

    if (penetration > 0) penetration -= currentMap.density[c.x][c.y];
    else speed -= currentMap.density[c.x][c.y];  //slows based on density

    if (speed < (startingSpeed/1.5))
    {
        return true;
    }

    return false;

}







