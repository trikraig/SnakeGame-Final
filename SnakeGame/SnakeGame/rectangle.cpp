#include <SFML/Graphics.hpp>
#include "rectangle.h"


Rectangle::Rectangle(const sf::Vector2f & new_position, const sf::Color & new_color, const int & new_width, const int & new_height) : Shape(new_position, new_color), width(new_width), height(new_height)
{
}

void Rectangle::Render(sf::RenderWindow & window)
{


	sf::RectangleShape *shape = new sf::RectangleShape();
	sf::Vector2f *size = new sf::Vector2f(width,height);

	shape->setSize(*size); 
	   
	
	shape->setFillColor(color);

	shape->setPosition(position);

	

	window.draw(*shape);

	delete size;
	delete shape;
}
