#pragma once
#include <SFML/Graphics.hpp>
//this is a Sprite that is an objet within/ontop of a worldtile
#include "textureManager.h"
class tileObject : public sf::Sprite
{
public:
	tileObject();
	tileObject(textureManager* _textureMaster,std::string _key, const sf::Vector2f& _screenPosition =sf::Vector2f(0,0),
    sf::Vector2f& _scale=sf::Vector2f(1,1), float _rotation=0.f, const sf::Color& _colour=sf::Color::White);
	void SetWorldPosition(float x, float y);
	void SetWorldPosition(const sf::Vector2f& position);
	sf::Vector2f GetWorldPosition();
	std::string tileTextureKey;
	void SetWorldZ(float z);
	float GetWorldZ();
protected:
	sf::Vector2f worldPosition;//where in the world is the object, when we create the SFML sprite we must convert this to screen domain
	float worldZ = 0;//how high of the floor is it
	
};

