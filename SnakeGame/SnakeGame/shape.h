#pragma once
#include <SFML/Graphics.hpp>

class Shape
{
protected:

	

	sf::Vector2f position;
	sf::Color color;

public:

	Shape(sf::Vector2f new_position, sf::Color new_color);
	virtual void Render(sf::RenderWindow& window) = 0;

};
