#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define M_PI 3.1415926535897
#include <math.h>
#include <list>

#include "playerChar.h"
#include "ingameScreen.h"
#include "gameMap.h"
#include "bullet.h"

using namespace std;


IngameScreen::IngameScreen(int newId, int x, int y)
{
    if (!bulletTex.loadFromFile("sprites/bullet.png"));
    bulletTex.setSmooth(true);
    tickrate = sf::seconds(1.0/512.0);
    tickCount = 0;
    tickClock.restart();
    mainClock.restart();
    userId = newId;
    players.emplace_front(userId, 300, 300);
    userPlayer = &players.front();
}

void IngameScreen::update(sf::RenderWindow& window)
{
    //only update once per tick
    if (tickClock.getElapsedTime()-tickrate*float(tickCount)>tickrate)
    {
        for (list<PlayerChar>::iterator it = players.begin(); it != players.end(); ++it)
        {
            it->update(window, mainClock);
            playerCollide(*it);

        }
        for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
        {
            if (it->fly(currentMap, players, mainClock))
            {
               bullets.erase(it--);
            }
        }
        mainClock.restart();
        tickCount++;
    }
}

void IngameScreen::fire()
{
    bullets.emplace_front(*userPlayer, bulletTex);  //fires from player pointed to by userPlayer
}

void IngameScreen::draw(sf::RenderWindow& window)
{
    window.draw(currentMap.mapSprite);
    float timeStep = mainClock.getElapsedTime().asSeconds();
    for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
    {
        sf::Vector2f dir = it->direction;
        double spd = it->speed;
        sf::Vector2f newPos = it->bulletPos;
        newPos.x += dir.x * spd * timeStep;
        newPos.y += dir.y * spd * timeStep;
        it->bulletSprite.setPosition(newPos);
        window.draw(it->bulletSprite);
    }
    for (list<PlayerChar>::iterator it = players.begin(); it != players.end(); ++it)
    {
        sf::Vector2f vel = it->velocity;
        sf::Vector2f newPos = it->playerPos;
        newPos.x += vel.x * timeStep;
        newPos.y += vel.y * timeStep;
        it->charSprite.setPosition(newPos);
        window.draw(it->charSprite);
    }
}



void IngameScreen::playerCollide(PlayerChar& player)
{
    bool hit = true;

    const int precision = 100;
    const float dist = 15;
    const float pushAmount = .1;
    const float slip = 0.3 * tickrate.asSeconds();
    sf::Vector2f newVel = player.velocity;

    while (hit)
    {
        sf::Vector2f center = player.playerPos;
        int collisionNum = 0;
        float xPush = 0;
        float yPush = 0;

        for (int i = 0; i != precision; ++i)
        {
            float checkAngle = i * (2*M_PI/precision);
            float x = center.x + dist * sin(checkAngle);
            float y = center.y + dist * cos(checkAngle);
            bool hitDetected = false;
            if(x < 0 || x > currentMap.xdim || y < 0 || y > currentMap.ydim)
            {
                hitDetected = true;
            }
            else
            {
                hitDetected = currentMap.block[(int)x][(int)y];
            }

            if (hitDetected)
            {
                xPush += sin(checkAngle);
                yPush += cos(checkAngle);
                collisionNum++;
            }
        }

        if (collisionNum > 0)
        {
            //adjust position
            float xToPush = -xPush * pushAmount / collisionNum;
            float yToPush = -yPush * pushAmount / collisionNum;
            player.playerPos += sf::Vector2f(xToPush, yToPush);

            //adjust velocity
            float pushAngle = atan2(yPush, xPush);
            newVel.x -= newVel.x * abs(cos(pushAngle)) * slip;
            if (abs(player.velocity.x)-abs(newVel.x)<0) newVel.x = 0;
            newVel.y -= newVel.y * abs(sin(pushAngle)) * slip;
            if (abs(player.velocity.y)-abs(newVel.y)<0) newVel.y = 0;
        }
        else
        {
            hit = false;
        }
    }
    //apply adjusted velocity
    player.velocity = newVel;
}






