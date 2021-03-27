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

	void setTextureSmooth(std::string _key, bool _toggle)
	{
		textureMap[_key].setSmooth(_toggle);
	}
private:
	std::map<std::string, sf::Texture> textureMap;
	std::string debugErrorString = "[ERROR] from [Texture Manager].";
	std::string debuginfoString = "[Texture Manager] ";
};

