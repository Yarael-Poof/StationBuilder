#pragma once
#include <SFML/Graphics.hpp>
#include "textureManager.h"
#include "tile.h"
#include "engineMacros.h"
#include <stdlib.h> 
#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/vector.hpp>
//direction chars: 0 = UL, 1 = UR, 2 = LL, 3 = LR
class isometricLevel
{	//let boost know what we want to serialise for saving to file
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& levelTiles;
		ar& levelSizeW;
		ar& levelSizeH;
		ar& tileSize;
		ar& stackLayer;
	}

public:
	isometricLevel();
	isometricLevel(textureManager* _textureMaster,float _levelSizeW = 1.f, float _levelSizeH = 1.f, float _tileSize = 10.f);
	~isometricLevel();
	void addFloor(sf::Vector2f _atWorldPosition);
	void addFloor(float _worldX, float _worldY);
	void addWall(sf::Vector2f _atWorldPosition, char _direction);
	void addWall(float _worldX, float _worldY, char _direction);
	void fillFloors();//fill entire level with floors
	void clearAll();
	bool addEdgeWall(char _direction);//only for square levels return 0 if called on nonsquare level
	void draw(sf::RenderWindow&  _window);//add all the level's tiles to the window.
	void printTileInfos();
	void drawTilePositionDebug(tgui::Gui& _gui);
	void setTextureManager(textureManager* _textureMaster);
	sf::Vector2f isoToCart(sf::Vector2f _cart);
	sf::Vector2f cartToIso(sf::Vector2f _iso);
	//where our tiles are

protected:
	std::vector<tile> levelTiles;
	float levelSizeW;
	float levelSizeH;
	float tileSize;
	float	stackLayer = 0; //which level is this at within each floor of the station
	textureManager* textureMaster;
};

