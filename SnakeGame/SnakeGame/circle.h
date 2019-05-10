#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"

class Circle : public Shape
{
private:

float radius;
	

public:

	Circle(const sf::Vector2f &new_position, const sf::Color &new_color, const float &new_radius);
	void Render(sf::RenderWindow& window) override;
};