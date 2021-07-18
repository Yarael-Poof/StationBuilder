#pragma once
#include <SFML/Graphics.hpp>
#include "textureManager.h"
#include "tile.h"
#include "engineMacros.h"
#include <stdlib.h> 
#include <string>

//direction chars: 0 = UL, 1 = UR, 2 = LL, 3 = LR
class isometricLevel
{	

public:
	isometricLevel();
	isometricLevel(textureManager* _textureMaster,float _levelSizeW = 1.f, float _levelSizeH = 1.f, float _tileSize = 10.f);
	~isometricLevel();
	void addFloor(sf::Vector2f _atWorldPosition);
	void addFloor(float _worldX, float _worldY);
	void addWall(sf::Vector2f _atWorldPosition, char _direction);
	void addWall(float _worldX, float _worldY, char _direction);
	void fillFloors();//fill entire level with floors
	void addObjectToTile(sf::Vector2f _tileCoords, std::string _textureKey);
	void clearAll();
	bool addEdgeWall(char _direction);//only for square levels return 0 if called on nonsquare level
	void draw(sf::RenderWindow&  _window);//add all the level's tiles to the window.
	void printTileInfos();//print dump all the objects on every tile of the level (verbose)
	void printTileInfo(sf::Vector2f _tileCoords);//show the objets present on the specific tile
	void drawTilePositionDebug(tgui::Gui& _gui);
	void setTextureManager(textureManager* _textureMaster);
	float getSizeW();
	float getSizeH();
	float getTileSize();
	void setSizeW(float _sizeW);
	void setSizeH(float _sizeH);
	void setTileSize(float _tileSize);

	sf::Vector2f isoToCart(sf::Vector2f _cart);
	sf::Vector2f cartToIso(sf::Vector2f _iso);
	std::vector<tile> levelTiles;//where our tiles are
	void setLevelOpacity(int _alphaAmount);
	void setTileColour(sf::Vector2f _tileCoords, sf::Color _colour);
	void clearTileColour();
	void setZOffset(float _zOffset);
	int	 coords2TileIndex(sf::Vector2f _tileCoords);
	int	 coords2TileIndex(int _tileX, int _tileY);

protected:
	
	float levelSizeW;
	float levelSizeH;
	float tileSize;
	textureManager* textureMaster;
};

