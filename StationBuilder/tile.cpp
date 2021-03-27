#include "tile.h"
tile::tile(sf::Vector2f _worldPosition, textureManager* _textureMaster, std::string _tileObjectCSVList)
{	//this will need to be rewritten to be able get each tileObject from _tileObjectCSVList. It is a string with 
	//the texture keys serpeated by commas.
	if (_tileObjectCSVList == "empty")
	{
		
		//change this to iterate through the _tileObjectCSVList to get texture keys.
		tileObjectsList.push_back(new tileObject(_textureMaster,"empty",_worldPosition));
	}
	else if (_tileObjectCSVList == "floor")
	{
		
		tileObjectsList.push_back(new tileObject(_textureMaster, "floor", _worldPosition));
		
	}
}	
tile::tile()
{

}
tile::~tile() {}
void tile::addTileObject(tileObject* _object)
{
	tileObjectsList.push_back(_object);
	tileObjectsList.unique();
}
void tile::removeTileObject(tileObject* _object)
{
	tileObjectsList.remove(_object);
}
void tile::clearTile()
{
	tileObjectsList.clear();
}

void tile::drawAllObjects(sf::RenderWindow& _window)
{	//iterate through the list of tile objects, select just the sfml sprite from within and draw to our window
	for (std::list<tileObject*>::iterator iter = tileObjectsList.begin(); iter != tileObjectsList.end();++iter)

	{
		//std::cout << (*iter)->getPosition().x;
		//std::cout << tileObjectsList.size();
		sf::Sprite* sprite = static_cast<sf::Sprite*>(*iter);
		//std::cout << sprite->getPosition().x << std::endl;
		_window.draw(*sprite);
	}
}
void tile::printAllObjectsInTile()
{
	for (std::list<tileObject*>::iterator iter = tileObjectsList.begin(); iter != tileObjectsList.end(); ++iter)
	{	
		std::cout << " has " << tileObjectsList.size() << " objects at: " << std::endl;
		
		std::cout << (*iter)->GetWorldPosition().x << "," << (*iter)->GetWorldPosition().y << std::endl;
	}

}

sf::Vector2f tile::getRootObjectCoords()
{
	std::list<tileObject*>::iterator root = tileObjectsList.begin();
	return (*root)->getPosition();
}