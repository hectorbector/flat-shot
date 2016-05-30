#ifndef PLAYERCHAR_H_INCLUDED
#define PLAYERCHAR_H_INCLUDED

using namespace std;

class PlayerChar
{
public:
    sf::Sprite charSprite;
    sf::Vector2f playerPos;
    sf::Vector2f velocity;
    sf::Vector2f gunPos;

    PlayerChar();
    PlayerChar(int x, int y);   //positions
    void update(sf::RenderWindow&, sf::Clock);

private:
    sf::Texture charTex;
    double speedMax;
    sf::Vector2f accel;
    float accelRun;

};

#endif // PLAYERCHAR_H_INCLUDED
