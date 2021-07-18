#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//class to hold sprite textures so that they are all kept in scope
class textureManager
{
public:
	void addTexture(std::string _key, std::string _pathToTexture)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(_pathToTexture))
		{
			std::cout << debugErrorString + __func__ << " Cannot load texture " << _pathToTexture << std::endl;
		}
		texture.setSmooth(false);
		textureMap[_key] = texture;
		keyMap[textureMap.size()] = _key;
	}
	sf::Texture* getTexture(std::string _key)
	{
		if (textureMap.count(_key) != 1)
		{
			std::cout << debugErrorString + __func__ << " fatal! the requested texture key does not exist in map" << std::endl;
			exit(EXIT_FAILURE);//replace this with a better recovery at some point
		}
		return &textureMap[_key];
	}
	std::string getTextureKey(int _index)
	{
		if (_index == -1)
		{
			return "empty";
		}
		return keyMap[_index];
	}

	void setTextureSmooth(std::string _key, bool _toggle)
	{
		textureMap[_key].setSmooth(_toggle);
	}

	int getTextureMapSize()
	{
		return textureMap.size();
	}
private:
	std::map<std::string, sf::Texture> textureMap;
	std::string debugErrorString = "[ERROR] from [Texture Manager].";
	std::string debuginfoString = "[Texture Manager] ";
	std::map<int, std::string> keyMap;
};

