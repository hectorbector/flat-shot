#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>

#include "gameMap.h"


GameMap::GameMap()
{
    if (!mapTex.loadFromFile("sprites/testingMapDensity.png"));                                //MAKE CHOOSABLE IN FUTURE
    ifstream blockMap;
    blockMap.open("maps/testingBlockMap.mp", ios::binary);
    ifstream densityMap;
    densityMap.open("maps/testingDensityMap.mp", ios::binary);
    xdim = mapTex.getSize().x;
    ydim = mapTex.getSize().y;
    block = vector< vector<bool> >(xdim, vector<bool>(ydim, false));
    density = vector< vector<short> >(xdim, vector<short>(ydim, 0));
    mapSprite.setTexture(mapTex);
    mapSprite.setPosition(0,0);

    //build player collision map from blockImage
    int xi = 0;
    for (vector< vector<bool> >::iterator it = block.begin(); it != block.end(); ++it)
    {
        int yi = 0;
        for (vector<bool>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
        {
            bool temp = false;
            blockMap >> temp;
            *it2 = temp;
            yi++;
        }
        xi++;
    }
    blockMap.close();

    //build bullet collision map from densityImage
    int xi2 = 0;
    for (vector< vector<short> >::iterator it = density.begin(); it != density.end(); ++it)
    {
        int yi2 = 0;
        for (vector<short>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
        {
            int temp = 0;
            densityMap >> temp;
            *it2 = temp;
            yi2++;
        }
        xi2++;
    }
    densityMap.close();
}
