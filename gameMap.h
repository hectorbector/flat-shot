#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>

using namespace std;

class GameMap
{
public:
    vector< vector<bool> > block;
    vector< vector<short> > density;
    int xdim, ydim;
    sf::Sprite mapSprite;

   GameMap();

private:
    sf::Texture mapTex;
    sf::Image blockImage;
    sf::Image densityImage;
};

#endif // MAP_H_INCLUDED
