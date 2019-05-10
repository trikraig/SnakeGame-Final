#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"

class Rectangle : public Shape
{
private:

	
	int width;
	int height;


public:

	Rectangle(const sf::Vector2f &new_position, const sf::Color &new_color, const int &new_width, const int &new_height);
	void Render(sf::RenderWindow& window) override;
};