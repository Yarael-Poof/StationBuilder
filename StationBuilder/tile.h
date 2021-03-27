#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "tileObject.h"
#include "engineMacros.h"
#include "textureManager.h"

//this a tile, one cell of the map. it has a position in the grid system of the map and can hold
//multiple tileObjects (sprites)
//tile types default 0, applies a blank sprite texture to the tyle
class tile
{	
public:
	tile();
	tile(sf::Vector2f _worldPosition, textureManager* _textureMaster,std::string _tileObjectCSVList = "empty");
	~tile();
	float tileSize = 64;
	
	void addTileObject(tileObject* _object);
	void removeTileObject(tileObject* _object);
	void clearTile();
	void drawAllObjects(sf::RenderWindow& _window);
	void printAllObjectsInTile();
	void setTileObjectColour(sf::Color _colour);
	sf::Vector2f getRootObjectCoords();//will look at tileObjecstList[0] and turn the objects world position.
	std::list<tileObject*> tileObjectsList;

protected:
	
	//list to hold pointers to objects on a tile, the actual objects are stored in our main level class
	//implement alpha blending between each tileObject at some point
};

