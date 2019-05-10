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

	shape->setRotation(rotation);

	//xInc = rand() % 3 - 1;	//Movement direction -1, 0 , 1
	//yInc = rand() % 3 - 1;

	//position.x += xInc * speed;
	//position.y += yInc * speed;

	//// Check if off edges, if so - bounce and change speed
	//if (position.x < 0 || position.x >= window.getSize().x)
	//{
	//	xInc = -xInc;
	//	speed = rand() % 5 + 2;
	//}

	//if (position.y < 0 || position.y >= window.getSize().y)
	//{
	//	yInc = -yInc;
	//	speed = rand() % 5 + 2;
	//}

	window.draw(*shape);

	delete shape;

	

}

//void Circle::Grow(float multiplier)
//{
//	radius = radius * multiplier;
//}
//
//void Circle::Shrink(float multiplier)
//{
//	radius = radius / multiplier;
//}


