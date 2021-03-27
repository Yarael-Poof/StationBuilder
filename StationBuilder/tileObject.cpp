#include "tileObject.h"
tileObject::tileObject()
{

}
tileObject::tileObject(textureManager* _textureMaster, std::string _key, const sf::Vector2f& _screenPosition,
	 sf::Vector2f& _scale, float _rotation, const sf::Color& _colour)
{
	worldPosition = _screenPosition;
	setPosition(_screenPosition);//this will needed to be converted to screen coords
	setTexture(*(_textureMaster->getTexture(_key)));
	setColor(_colour);
	setRotation(_rotation);
	setScale(_scale);
	tileTextureKey = _key;
}


void tileObject::SetWorldPosition(float _x, float _y){}
void tileObject::SetWorldPosition(const sf::Vector2f& _position){}
sf::Vector2f tileObject::GetWorldPosition() { return worldPosition; }

void tileObject::SetWorldZ(float _z)
{
	sf::Vector2f currentPosition = getPosition();
	setPosition(currentPosition.x, currentPosition.y + _z);
	worldZ = _z;
}

void tileObject::resetWorldZ()
{
	sf::Vector2f currentPosition = getPosition();
	setPosition(currentPosition.x, currentPosition.y - worldZ);
	worldZ = 0;
}
float tileObject::GetWorldZ() { return worldZ; }