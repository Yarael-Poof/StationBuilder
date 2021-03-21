#pragma once
#include <SFML/Graphics.hpp>

	sf::Vector2f isoToCart(sf::Vector2f _cart)
	{
		sf::Vector2f iso(0.f, 0.f);
		iso.x = (2 * _cart.y + _cart.x) / 2;
		iso.y = (2 * _cart.y - _cart.x) / 2;
		return iso;
	}

	sf::Vector2f cartToIso(sf::Vector2f _iso)
	{
		sf::Vector2f cart(0.f, 0.f);
		cart.x = _iso.x - _iso.y;
		cart.y = (_iso.x + _iso.y) / 2;
		return cart;
	}


