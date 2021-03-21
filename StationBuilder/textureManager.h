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
			std::cout << "[ERROR] Cannot load texture " << _pathToTexture << std::endl;
		}
		texture.setSmooth(false);
		textureMap[_key] = texture;
	}
	sf::Texture* getTexture(std::string _key)
	{
		return &textureMap[_key];
	}

	void setTextureSmooth(std::string _key, bool _toggle)
	{
		textureMap[_key].setSmooth(_toggle);
	}
private:
	std::map<std::string, sf::Texture> textureMap;
};

