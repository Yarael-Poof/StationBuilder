#pragma once
#include <SFML/Graphics.hpp>
//this is a Sprite that is an objet within/ontop of a worldtile
#include <boost/serialization/base_object.hpp>
class tileObject : public sf::Sprite
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& worldPosition;
		ar& worldZ;
		ar& boost::serialization::base_object<sf::Sprite>(*this);
	}
public:
	
	tileObject(const sf::Texture* _texture, const sf::Vector2f& _screenPosition =sf::Vector2f(0,0),
    sf::Vector2f& _scale=sf::Vector2f(1,1), float _rotation=0.f, const sf::Color& _colour=sf::Color::White);
	void SetWorldPosition(float x, float y);
	void SetWorldPosition(const sf::Vector2f& position);
	sf::Vector2f GetWorldPosition();

	void SetWorldZ(float z);
	float GetWorldZ();
protected:
	sf::Vector2f worldPosition;//where in the world is the object, when we create the SFML sprite we must convert this to screen domain
	float worldZ = 0;//how high of the floor is it
	
};

