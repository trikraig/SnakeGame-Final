#include "circle.h"

#include <SFML/Graphics.hpp>



Circle::Circle(const sf::Vector2f & new_position, const sf::Color & new_color, const float & new_radius) : Shape(new_position, new_color), radius(new_radius)
{
}

void Circle::Render(sf::RenderWindow & window)
{
	// Create an instance of the SFML CircleShape and initialise it so radius is 100
	sf::CircleShape *shape = new sf::CircleShape(radius);

	// Set the shape's fill colour attribute to Green
	shape->setFillColor(color);

	shape->setPosition(position);

	window.draw(*shape);

	delete shape;

	

}
