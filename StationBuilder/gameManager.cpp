#include "gameManager.h"

void gameManager::saveStationToDisc(station* _stationToSave, std::string _stationName)
{
	std::cout << "\n[INFO] Saving " << _stationName << " please wait...\n";
	boost::filesystem::path dir(_stationName);
	if (!(boost::filesystem::exists(dir))) {
		std::cout << "Doesn't Exists" << std::endl;

		if (boost::filesystem::create_directory(dir))
			std::cout << "....Successfully Created !" << std::endl;
	}
	for (int currentLevel = 0; currentLevel < _stationToSave->getLayerListSize(); currentLevel++)
	{
		saveLevelToDisc(_stationToSave->getIsoLevel(currentLevel), _stationName + "/" + std::to_string(currentLevel));
	}
}

void loadLevelFromDisc(station& _stationToRestoreInto, std::string _stationName, textureManager* _textureManager)
{
	std::cout << "\n[INFO] Loading " << _stationName << "please wait...\n";

}


void gameManager::saveLevelToDisc(isometricLevel* _levelToSave, std::string _levelName)
{	
	
	std::cout << "\n[INFO] Saving " << _levelName << ".level please wait...\n";
	levelDiscStructure toSave;
	toSave.sizeW = _levelToSave->getSizeW();
	toSave.sizeH = _levelToSave->getSizeH();
	toSave.tileSize = _levelToSave->getTileSize();
	for (int i = 0; i < _levelToSave->levelTiles.size(); i++)
	{

		std::string textureKeys = "";
		for (std::list<tileObject*>::iterator iter = _levelToSave->levelTiles[i].tileObjectsList.begin(); iter != _levelToSave->levelTiles[i].tileObjectsList.end(); ++iter)

		{
			textureKeys += (*iter)->tileTextureKey;
			
			if (iter != _levelToSave->levelTiles[i].tileObjectsList.begin())
			{
				textureKeys += ",";
			}
			

		}
		toSave.tileTypes.emplace(i, textureKeys);
		//std::cout <<toSave.tileTypes[i]<<"\n";
		
	}
	std::ofstream saveFile(_levelName + ".level");
	boost::archive::text_oarchive saveArchive(saveFile);
	saveArchive << toSave.sizeW;
	saveArchive << toSave.sizeH;
	saveArchive << toSave.tileSize;
	saveArchive << toSave.tileTypes;
	std::cout << "[INFO] " << _levelName << ".level saved successfully\n";
}

void gameManager::loadLevelFromDisc(isometricLevel& _levelToRestoreInto, std::string _levelName, textureManager* _textureManager)
{
	std::cout << "\n[INFO] Loading " << _levelName << ".level please wait...\n";
	levelDiscStructure toLoad;
	std::ifstream loadFile(_levelName + ".level");
	try {
		boost::archive::text_iarchive loadArchive(loadFile);
		try {
			loadArchive >> toLoad.sizeW;
			loadArchive >> toLoad.sizeH;
			loadArchive >> toLoad.tileSize;
			loadArchive >> toLoad.tileTypes;
		}
		catch (...)
		{
			std::cout << "[ERROR] failed to read .level file\n";
			
			exit(EXIT_FAILURE);
		}
	}
		catch (...)
		{
			std::cout << "[ERROR] failed to find the level file\n";
			exit(EXIT_FAILURE);
		}
	
	std::cout << "[INFO] Parsing level please wait...\n";
	_levelToRestoreInto.setSizeW(toLoad.sizeW);
	_levelToRestoreInto.setSizeH(toLoad.sizeH);
	_levelToRestoreInto.setTileSize(toLoad.tileSize);
	_levelToRestoreInto.setTextureManager(_textureManager);

	for (int y = 0; y < toLoad.sizeH; y++)
	{
		
		for (int x = 0; x < toLoad.sizeW; x++)
		{
			

			//std::cout << toLoad.tileTypes[x * y] << std::endl; this is not good, need to rework
			_levelToRestoreInto.levelTiles.push_back(tile(cartToIso(sf::Vector2f(toLoad.tileSize/ 2 * x, toLoad.tileSize/ 2 * y)), _textureManager, toLoad.tileTypes[x + y* toLoad.sizeW]));
		}

	}
	std::cout << "[INFO] "<<_levelName<<"load successful\n";
}

sf::Vector2f gameManager::isoToCart(sf::Vector2f _cart)
{
	sf::Vector2f iso(0.f, 0.f);
	iso.x = (2 * _cart.y + _cart.x) / 2;
	iso.y = (2 * _cart.y - _cart.x) / 2;
	return iso;
}

sf::Vector2f gameManager::cartToIso(sf::Vector2f _iso)
{
	sf::Vector2f cart(0.f, 0.f);
	cart.x = _iso.x - _iso.y;
	cart.y = (_iso.x + _iso.y) / 2;
	return cart;
}
