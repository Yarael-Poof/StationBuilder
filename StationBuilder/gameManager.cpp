#include "gameManager.h"

//need to add strem buffers here, writing is already really slow for just 25KB


void gameManager::saveLevelToDisc(isometricLevel& _levelToSave, std::string _levelName)
{	
	//this quite a c-style approach, not that great maybe rewrite later
	std::cout << "\n[INFO] Saving " << _levelName << ".level please wait...\n";
	levelDiscStructure toSave;
	toSave.sizeH = _levelToSave.getSizeH();
	toSave.sizeW = _levelToSave.getSizeW();
	toSave.tileSize = _levelToSave.getTileSize();
	for (int i = 0; i < _levelToSave.levelTiles.size(); i++)
	{

		std::string textureKeys = "";
		for (std::list<tileObject*>::iterator iter = _levelToSave.levelTiles[i].tileObjectsList.begin(); iter != _levelToSave.levelTiles[i].tileObjectsList.end(); ++iter)

		{
			textureKeys += (*iter)->tileTextureKey;
			
			if (iter != _levelToSave.levelTiles[i].tileObjectsList.end())
			{
				textureKeys += ",";
			}
			

		}
		toSave.tileTypes.emplace(i, textureKeys);
		//std::cout <<toSave.tileTypes[i]<<"\n";
		std::ofstream saveFile(_levelName + ".level");
		boost::archive::text_oarchive saveArchive(saveFile);
		saveArchive << toSave.sizeH;
		saveArchive << toSave.sizeW;
		saveArchive << toSave.tileSize;
		saveArchive << toSave.tileTypes;   
	}
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

			loadArchive >> toLoad.sizeH;
			loadArchive >> toLoad.sizeW;
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
	_levelToRestoreInto.setSizeH(toLoad.sizeH);
	_levelToRestoreInto.setSizeW(toLoad.tileSize);
	_levelToRestoreInto.setTileSize(toLoad.sizeH);
	_levelToRestoreInto.setTextureManager(_textureManager);

	for (int y = 0; y < toLoad.sizeH; y++)
	{
		
		for (int x = 0; x < toLoad.sizeW; x++)
		{
			

			
			_levelToRestoreInto.levelTiles.push_back(tile(cartToIso(sf::Vector2f(toLoad.tileSize/ 2 * x, toLoad.tileSize/ 2 * y)), _textureManager, "empty"));
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
