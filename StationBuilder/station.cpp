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
int station::appendNewIsoLevel(float _levelSizeW, float _levelSizeH, float _tileSize, std::string _tileBaseTextureKey)
{	
	isoLayerList.push_back(isometricLevel(textureMaster, _levelSizeW, _levelSizeH, _tileSize));
	currentLevel = (isoLayerList.size() - 1);
	//fill the newly made level with empty tile textures
	for (int y = 0; y < isoLayerList[currentLevel].getSizeH(); y++)
	{
		
		for (int x = 0; x < isoLayerList[currentLevel].getSizeW(); x++)
		{
			
			isoLayerList[currentLevel].levelTiles.push_back(tile(cartToIso(sf::Vector2f(isoLayerList[currentLevel].getTileSize() / 2 * x, isoLayerList[currentLevel].getTileSize() / 2 * y)), textureMaster, _tileBaseTextureKey));
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
		//add checks here to see if we are adding sequentially. i.e do not allow a level to be added to layer 2 if we dont have 0 and 1 already.
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

	std::cout << this->debuginfoString + std::string(__func__) << " resize succesful, level added" << std::endl;
	currentLevel = _atWhichStackLayer;
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
	std::cout << this->debuginfoString << "cleared all levels" << std::endl;
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

int station::getLayerListSize()
{
	return int(isoLayerList.size());
}

int station::getCurrentLevel()
{
	return currentLevel;
}

void station::setCurrentLevel(int _levelNumber)
{
	currentLevel = _levelNumber;
}
void station::incCurrentLevel()
{
	if ((currentLevel + 1) >= int(isoLayerList.size()))
	{
		std::cout << this->debuginfoString + __func__ << " No higher levels to select" << std::endl;
		return;
	}
	else
	{
		
		currentLevel++;
		return;
	}
	
}

void station::decCurrentLevel()
{
	if (currentLevel - 1 < 0)
	{
		std::cout << this->debuginfoString + __func__<< " No lower levels to select" << std::endl;
		return;
	}
	else
	{
		currentLevel--;
		return;
	}
}
void station::setBuildMode(bool _toggle)
{
	buildMode = _toggle;
	

}
bool station::getBuildMode() { return buildMode; }
void station::fadeAndSlideAwayDown()
{	//animations for switching levls, not finished, needs hooking in somehow to the main render loop.
	sf::Clock timer;
	sf::Time startTime = timer.getElapsedTime();
	int alpha = 255;
	float zOffsetInc = 0.1;
	while((timer.getElapsedTime().asMilliseconds() - startTime.asMilliseconds()) < animationDurationms)
	{
		isoLayerList[currentLevel].setZOffset(zOffsetInc);
		isoLayerList[currentLevel].setLevelOpacity(alpha);
		alpha--;
		zOffsetInc + 0.1;
	}
	return;
}
void station::fadeAndSlideAwayUp()
{

}

void station::toggleBuildMode()
{
	buildMode = !buildMode;
	if (buildMode == false)//if we exit build mode, clear all highlighting on all levels.
	{	for(int i = 0;i < isoLayerList.size(); i ++)

		isoLayerList[i].clearTileColour();
	}
}

isometricLevel* station::getCurrentIsoLevel()
{
	return &isoLayerList[currentLevel];
}

void station::highlightTile(sf::Vector2f _tileCoords, sf::Color _colour)
{	
	
		isoLayerList[currentLevel].setTileColour(_tileCoords, _colour);
}

void station::highlightAllTiles(sf::Color _colour)
{
	for (int y = 1; y < isoLayerList[currentLevel].getSizeH() + 1; y++)
	{
		for (int x = 1; x < isoLayerList[currentLevel].getSizeW() + 1; x++)
		{ 
			isoLayerList[currentLevel].setTileColour(sf::Vector2f(x, y), _colour);
		}
	}
}