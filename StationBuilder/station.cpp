#include "station.h"

station::station()
{
	textureMaster = nullptr;
}
station::~station()
{

}
station::station(textureManager* _textureManager)
{
	textureMaster = _textureManager;
}
sf::Vector2f station::isoToCart(sf::Vector2f _cart)
{
	sf::Vector2f iso(0.f, 0.f);
	iso.x = (2 * _cart.y + _cart.x) / 2;
	iso.y = (2 * _cart.y - _cart.x) / 2;
	return iso;
}

sf::Vector2f station::cartToIso(sf::Vector2f _iso)
{
	sf::Vector2f cart(0.f, 0.f);
	cart.x = _iso.x - _iso.y;
	cart.y = (_iso.x + _iso.y) / 2;
	return cart;
}
int station::appendNewIsoLevel(float _levelSizeW, float _levelSizeH, float _tileSize)
{	
	isoLayerList.push_back(isometricLevel(textureMaster, _levelSizeW, _levelSizeH, _tileSize));
	currentLevel = (isoLayerList.size() - 1);
	//fill the newly made level with empty tile textures
	for (int y = 0; y < isoLayerList[currentLevel].getSizeH(); y++)
	{
		
		for (int x = 0; x < isoLayerList[currentLevel].getSizeW(); x++)
		{
			
			isoLayerList[currentLevel].levelTiles.push_back(tile(cartToIso(sf::Vector2f(isoLayerList[currentLevel].getTileSize() / 2 * x, isoLayerList[currentLevel].getTileSize() / 2 * y)), textureMaster, "empty"));
		}

	}
	return (isoLayerList.size() - 1);
}
void station::setTextureManager(textureManager* _textureManager)
{
	textureMaster = _textureManager;
}
void station::addIsoLevel(isometricLevel _LevelToAdd, float _atWhichStackLayer)
{	
	try {
		isoLayerList.at(int(_atWhichStackLayer));
		isoLayerList[int(_atWhichStackLayer)] = _LevelToAdd;
	}
	catch (...)
	{

		std::cout << this->debugErrorString + std::string(__func__) << " tried to add a level at a location that does not exist, attempting resize of isoLevelList"<<std::endl;
		isoLayerList.resize(int(_atWhichStackLayer) + 1);
		
		try {
			isoLayerList[int(_atWhichStackLayer)] = _LevelToAdd;
		}
		catch (...)
		{
			std::cout << this->debugErrorString + std::string(__func__) << "fatal! giving up, cannot add level" << std::endl;
		}
	}

	std::cout << this->debuginfoString << "level added" << std::endl;
}

bool station::deleteIsoLevel(float _atWhichStackLayer)
{
	try
	{
		isoLayerList.erase(isoLayerList.begin() + int(_atWhichStackLayer));
		return true;
	}
	catch (...)
	{
		std::cout << this->debugErrorString + std::string(__func__) << "attempted to delete a level from a location that does not exit" << std::endl;
		return false;
	}

}

void station::deleteAllLevels()
{
	isoLayerList.clear();
	std::cout << this->debuginfoString << "cleard all levels" << std::endl;
}

void station::drawLayer(sf::RenderWindow& _win, float _whichStackLayer)
{
	try {
		isoLayerList.at(int(_whichStackLayer));
	}
	catch(...){
		std::cout << this->debugErrorString + std::string(__func__) << " attempted to draw a level that does not exist" << std::endl;
		exit(EXIT_FAILURE);
	}
	isoLayerList[int(_whichStackLayer)].draw(_win);
}