
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

#include "playerChar.h"
#include "ingameScreen.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shooter",sf::Style::Close);

    //create IngameScreen
    IngameScreen mainScreen(1000, 800);

    sf::View mainView(mainScreen.players.front().playerPos, sf::Vector2f(1000, 800));

    sf::Clock fullRunTime;

    //set up font and text for fps counter
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"));
    sf::Text fpsDisplay;
    fpsDisplay.setFont(font);
    fpsDisplay.setCharacterSize(12);
    fpsDisplay.setColor(sf::Color::Black);
    fpsDisplay.setStyle(sf::Text::Bold);
    fpsDisplay.setPosition(3,1);

    //set up fps clock and counter
    sf::Clock fpsClock;
    int frameCount = 0;

    //event loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mainScreen.fire();
                }
            }
        }

        //fps check and display
        frameCount += 1;
        if (fpsClock.getElapsedTime().asSeconds() > 1)
        {
            fpsClock.restart();
            int ticksLastSecond = mainScreen.tickCount - (fullRunTime.getElapsedTime().asSeconds()-1) * 1/mainScreen.tickrate.asSeconds();
            fpsDisplay.setString("fps "+to_string(frameCount)+"\ntps "+to_string(ticksLastSecond)+"\ntc "+to_string(mainScreen.tickCount));
            frameCount = 0;
            //mainScreen.tickCount = 0;
            //mainScreen.tickClock.restart();
        }

        //logic update
        window.setView(mainView);
        mainScreen.update(window);
        mainView.setCenter(mainScreen.players.front().playerPos);

        //draw
        window.clear(sf::Color::Red);
        mainScreen.draw(window);
        window.setView(window.getDefaultView());
        window.draw(fpsDisplay);
        window.display();
    }

    return 0;
}
