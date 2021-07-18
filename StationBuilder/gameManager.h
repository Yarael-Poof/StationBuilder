#pragma once
#include "isometricLevel.h"
#include "textureManager.h"
#include "station.h"
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/filesystem.hpp>
class gameManager
{
public:
	struct levelDiscStructure {
		float sizeH;
		float sizeW;
		float tileSize;
		float stackLayer;
		std::map<int, std::string> tileTypes;
			
	};
	sf::Vector2f isoToCart(sf::Vector2f _cart);
	sf::Vector2f cartToIso(sf::Vector2f _iso);
	void saveStationToDisc(station* _stationToSave, std::string _stationName);
	void loadLevelFromDisc(station& _stationToRestoreInto, std::string _stationName, textureManager* _textureManager);
	void saveLevelToDisc(isometricLevel* _levelToSave, std::string _levelName);
	void loadLevelFromDisc(isometricLevel& _levelToRestoreInto,std::string _levelName, textureManager* _textureManager);
};

