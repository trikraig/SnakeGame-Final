#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

//Created by Craig Palmer, V8009358.

//Background Artwork created by Luis Zuno(@ansimuz) CC - BY - 3.0 License
//Food Sprites created by benmhenry@gmail.com
//Font by https ://www.creativefabrica.com/designer/daymarius


int main()
{
	srand((int)time(0));

	const int screenWidth{ 800 };
	const int screenHeight{ 600 };

	sf::Font font;
	std::vector <sf::Text> mainMenu;
	sf::Texture texture;
	sf::Sprite background;

	//Check if texture file exists in directory
	if (!texture.loadFromFile("image.png"))
	{
		std::cout << "Error. Image not available" << std::endl;
	}


	//Check if font exists in directory.
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Error. Font not available" << std::endl;
	}

	//Background setup
	background.setTexture(texture);


	//Text for Main Menu
	sf::Text textTitle;
	textTitle.setString("UNDERWATER SNAKE");
	textTitle.setCharacterSize(60);
	textTitle.setPosition(100, 75);
	textTitle.setFont(font);
	textTitle.setFillColor(sf::Color(238, 5, 242));
	mainMenu.push_back(textTitle);

	sf::Text text1Player;
	text1Player.setString("1 Single Player");
	text1Player.setCharacterSize(35);
	text1Player.setPosition(150, 175);
	text1Player.setFont(font);
	text1Player.setFillColor(sf::Color(238, 5, 242));
	mainMenu.push_back(text1Player);

	sf::Text text2Player;
	text2Player.setString("2 Multiplayer");
	text2Player.setCharacterSize(35);
	text2Player.setPosition(150, 225);
	text2Player.setFont(font);
	text2Player.setFillColor(sf::Color(238, 5, 242));
	mainMenu.push_back(text2Player);

	sf::Text text3Player;
	text3Player.setString("3 Vs CPU");
	text3Player.setCharacterSize(35);
	text3Player.setPosition(150, 275);
	text3Player.setFont(font);
	text3Player.setFillColor(sf::Color(238, 5, 242));
	mainMenu.push_back(text3Player);

	sf::Text textQuit;
	textQuit.setString("Q Quit");
	textQuit.setCharacterSize(35);
	textQuit.setPosition(150, 325);
	textQuit.setFont(font);
	textQuit.setFillColor(sf::Color(238, 5, 242));
	mainMenu.push_back(textQuit);

	// Create an instance of the SFML RenderWindow type which represents the display
	// and initialise its size and title text
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "C++ Snake ICA : V8009358");

	// Main loop that continues until we call window.close()
	while (window.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Num1:
				{
					//Single Player, No Opponents.
					Game *game = new Game;
					game->PlayGame(window, 1, 0, background);
					delete game;
					break;
				}
				case sf::Keyboard::Num2:
				{
					//1P vs 2P
					Game *game = new Game;
					game->PlayGame(window, 2, 0, background);
					delete game;
					break;
				}
				case sf::Keyboard::Num3:
				{
					//1P vs 3 x CPUs
					Game *game = new Game;
					game->PlayGame(window, 1, 3, background);
					delete game;
					break;
				}
				case sf::Keyboard::Q:
				{
					window.close();
					break;
				}

				}

			case sf::Event::Closed:

				break;
			default:
				break;
			}
		}

		// We must clear the window each time around the loop
		window.clear();

		//draw background
		window.draw(background);

		// draw our circle shape to the window
		for (sf::Text text : mainMenu)
		{
			window.draw(text);
		}

		// Get the window to display its contents
		window.display();
	}

	std::cout << "SnakeGame: Finished" << std::endl;

	return 0;
}



