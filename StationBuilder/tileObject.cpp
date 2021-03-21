#include "tileObject.h"
tileObject::tileObject(const sf::Texture* _texture, const sf::Vector2f& _screenPosition,
	 sf::Vector2f& _scale, float _rotation, const sf::Color& _colour)
{
	worldPosition = _screenPosition;
	setPosition(_screenPosition);//this will needed to be converted to screen coords
	setTexture(*_texture);
	setColor(_colour);
	setRotation(_rotation);
	setScale(_scale);
}


void tileObject::SetWorldPosition(float x, float y){}
void tileObject::SetWorldPosition(const sf::Vector2f& position){}
sf::Vector2f tileObject::GetWorldPosition() { return worldPosition; }

void tileObject::SetWorldZ(float z){}
float tileObject::GetWorldZ() { return worldZ; }