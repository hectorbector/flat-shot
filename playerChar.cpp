#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define M_PI 3.1415926535897
#include <math.h>

#include "playerChar.h"

using namespace std;

PlayerChar::PlayerChar()
{
    if (!charTex.loadFromFile("sprites/manPlaceholder.png"));
    charTex.setSmooth(true);
    playerPos = sf::Vector2f(100,100);
    charSprite.setTexture(charTex);
    charSprite.setPosition(playerPos);
    charSprite.setOrigin(20,27);
    gunPos = sf::Vector2f(15.5, -27);
    velocity = sf::Vector2f(0,0);
    speedMax = 300;
    accel = sf::Vector2f(0,0);
    accelRun = 1600;
}

PlayerChar::PlayerChar(int x, int y)
{
    if (!charTex.loadFromFile("sprites/manPlaceholder.png"));
    charTex.setSmooth(true);
    playerPos = sf::Vector2f(x, y);
    charSprite.setTexture(charTex);
    charSprite.setPosition(playerPos);
    gunPos = sf::Vector2f(15.5, -27);
    charSprite.setOrigin(20,27);
    velocity = sf::Vector2f(0,0);
    speedMax = 300;
    accel = sf::Vector2f(0,0);
    accelRun = 1600;
}

void PlayerChar::update(sf::RenderWindow& window, sf::Clock clock)
{

        double timeStep = clock.getElapsedTime().asSeconds();                //set timestep
        sf::Vector2f accelTemp = sf::Vector2f(0,0);

        //if W key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            accelTemp.y = -accelRun;
            if (velocity.y > 0) accelTemp.y -= accelRun;
        }

        //if A key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            accelTemp.x = -accelRun;
            if (velocity.x > 0) accelTemp.x -= accelRun;
        }

        //if D key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            accelTemp.x = accelRun;
            if (velocity.x < 0) accelTemp.x += accelRun;
        }

        //if S key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            accelTemp.y = accelRun;
            if (velocity.y < 0) accelTemp.y += accelRun;
        }

        //if both W and S keys are pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            accelTemp.y = 0;
        }

        //if both A and D keys are pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            accelTemp.x = 0;
        }

        //accel angle calculator from running
        if (!((accelTemp.x == 0)||(accelTemp.y == 0)))
        {
            accel.x = accelTemp.x * sqrt(2);
            accel.y = accelTemp.y * sqrt(2);
        }
        else
        {
            accel.x = accelTemp.x;
            accel.y = accelTemp.y;
        }

        //velocity limiter
        double speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (speed > speedMax)
        {
            double reduce = (speed-speedMax)/speed;
            velocity.x -= velocity.x * reduce;
            velocity.y -= velocity.y * reduce;
        }


        //move sprite and calculate new velocity
        playerPos.x += timeStep * (velocity.x + timeStep * accel.x / 2);
        playerPos.y += timeStep * (velocity.y + timeStep * accel.y / 2);
        charSprite.setPosition(playerPos);
        velocity.x += timeStep * accel.x;
        velocity.y += timeStep * accel.y;


        //vertical decay
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        {
            double angle = 0;

            if (velocity.y != 0) angle = abs(atan(velocity.x/velocity.y));

            if (velocity.y > 0)
            {
                velocity.y -= timeStep*(accelRun)*cos(angle);
                if (velocity.y < 0) velocity.y = 0;
            }
            if (velocity.y < 0)
            {
                velocity.y += timeStep*(accelRun)*cos(angle);
                if (velocity.y > 0) velocity.y = 0;
            }
        }

        //horizontal decay
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {
            double angle = 0;

            if (velocity.x != 0) angle = abs(atan(velocity.y/velocity.x));

            if (velocity.x > 0)
            {
                velocity.x -= timeStep*(accelRun)*cos(angle);
                if (velocity.x < 0) velocity.x = 0;
            }
            if (velocity.x < 0)
            {
                velocity.x += timeStep*(accelRun)*cos(angle);
                if (velocity.x > 0) velocity.x = 0;
            }
        }


        //Point character at mouse
        sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2i relativePos;
        relativePos.x = mPos.x - playerPos.x;
        relativePos.y = mPos.y - playerPos.y;
        charSprite.setRotation(atan2(relativePos.y,relativePos.x)*180/M_PI+90);
}


