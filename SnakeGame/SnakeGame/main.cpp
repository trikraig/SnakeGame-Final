#include <iostream>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

#include "circle.h"
#include "rectangle.h"

#include <vector>
#include <time.h>
#include "main.h"

int main()
{
    // All SFML types and functions are contained in the sf namespace
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : V8009358");


	std::vector <Shape*> shapes;
	

	srand(time(NULL));

	for (int i = 0; i < 10; i++) // CIRCLE TEST.
	{
		sf::Vector2f *vector = new sf::Vector2f ((rand() % 800), (rand() % 600));
		sf::Color *color = new sf::Color((rand() % 250), (rand() % 250), (rand() % 250), (rand() % 250));
		int *radius = new int { rand() % 100 };
		
		shapes.push_back(new Circle (*vector,*color,*radius));

		delete vector;
		delete color;
		delete radius;
	}

	for (int i = 0; i < 10; i++) // RECTANGLE TEST.
	{
		sf::Vector2f *vector = new sf::Vector2f((rand() % 800), (rand() % 600));
		sf::Color *color = new sf::Color((rand() % 250), (rand() % 250), (rand() % 250), (rand() % 250));
		int *width = new int{ rand() % 200 };
		int *height = new int{ rand() % 100 };
		
		
		shapes.push_back(new Rectangle (*vector, *color, *width, *height));

		delete vector;
		delete color;
		delete width;
		delete height;
	}
	

    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
              window.close();
            break;
            default:
              break;
          }
        }

        // We must clear the window each time around the loop
        window.clear();

		
		for (Shape *shape : shapes)
		{
			shape->Render(window);
		}

		

	
        window.display();
    }

    std::cout << "SnakeGame: Finished" << std::endl;

	for (Shape *shape : shapes)
	{
		delete shape;
	}
	

    return 0;
}


