#pragma once
#include "isometricLevel.h"
#include "textureManager.h"
#include <SFML/graphics.hpp>
#include <iostream>
#include <string>
class station
{
public:
	station();//we should really just use the constructor with the texturemanager in it
	station(textureManager* _textureManager);
	~station();
	void setTextureManager(textureManager* _textureManager);//better to use the constructor instead of this, guess is useful if we want to change to a different set of textures easily
	int appendNewIsoLevel(float _levelSizeW = 1.f, float _levelSizeH = 1.f, float _tileSize = 64.f, std::string _tileBaseTextureKey = "empty");//adds and creates an empty level in the level list, returns index of where it just created it. Also sets currentLevel to the same.
	bool deleteIsoLevel(float _atWhichStackLayer);
	void deleteAllLevels();
	void addIsoLevel(isometricLevel _LevelToAdd, float _atWhichStackLayer);
	void drawLayer(sf::RenderWindow& _win, float _whichStackLayer);
	isometricLevel* getIsoLevel(float _atWhichStackLayer);
	sf::Vector2f isoToCart(sf::Vector2f _cart);
	sf::Vector2f cartToIso(sf::Vector2f _iso);
	int getLayerListSize();
	int getCurrentLevel();
	void setCurrentLevel(int _levelNumber);
	void incCurrentLevel();
	void decCurrentLevel();
	void fadeAndSlideAwayUp();
	void fadeAndSlideAwayDown();

private:
	int animationDurationms = 255;
	int currentLevel = 0;
	textureManager* textureMaster;
	std::vector<isometricLevel> isoLayerList;
	std::string debugErrorString = "[ERROR] from [Station].";
	std::string debuginfoString = "[Station] ";
};

