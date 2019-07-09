#include "game.h"
#include "food.h"
#include "water.h"
#include <vector>
#include <string>


//Test new branch - HELLO!

void Game::PlayGame(sf::RenderWindow & window, const int &numberOfPlayers, const int &numberOfcpuPlayers, const sf::Sprite &background)
{
	//Sets random positions and colour for all players. Sets the player number and added to the player array.
	for (int i = 0; i < numberOfPlayers; i++)
	{
		int newSnakeXpos;
		int newSnakeYPos;

		if (playerNumber == 1)
		{
			newSnakeXpos = static_cast <int> (screenWidth / 2);
			newSnakeYPos = static_cast <int> (screenHeight / 2);
		}
		else
		{
			newSnakeXpos = static_cast <int> (((rand() % screenWidth) / h) * h);
			newSnakeYPos = static_cast <int> (((rand() % screenHeight) / h) * h);
		}


		Snake *player = new Player(sf::Vector2f((float)newSnakeXpos, (float)newSnakeYPos), newSnakeColor, newSnakeHeadSize, playerNumber);
		allPlayers.push_back(player);
		playerNumber++;

	}

	//Sets random positions and colour for all cpu players. Sets the player number and adds to the player array. 
	for (int i = 0; i < numberOfcpuPlayers; i++)
	{
		int newSnakeXpos = static_cast <int> (((rand() % screenWidth) / h) * h);
		int newSnakeYPos = static_cast <int> (((rand() % screenHeight) / h) * h);



		Snake *player = new cpuSnake(sf::Vector2f((float)newSnakeXpos, (float)newSnakeYPos), newSnakeColor, newSnakeHeadSize, playerNumber);
		allPlayers.push_back(player);
		playerNumber++;

	}

	//Reference to what would be a player controlled Player 1. 
	Snake *&player = allPlayers[0];

	//Generate Random Food	 
	generateFood(screenWidth, screenHeight, newSnakeHeadSize);

	Water water(screenHeight, screenWidth);

	enum class EGameState
	{
		ePlay, eGameOver
	};

	//EDirection directionOne { EDirection::eEast }; //Default direction

	EGameState state{ EGameState::ePlay };


	std::cout << "SnakeGame: Starting" << std::endl;

	//State machine managing whether game is in play or game over.
	while (window.isOpen())
	{
		switch (state)
		{
		case EGameState::ePlay:

		{
			window.clear();

			window.draw(background);
			//Simulation

			//Clock to manage rate water descends.
			static sf::Clock waterClock;

			if (waterClock.getElapsedTime().asSeconds() > waterDropRate)
			{
				water.sink(newSnakeHeadSize);
				waterClock.restart();
			}

			//Clock to manage spawn rate of food.
			static sf::Clock foodClock;

			if (foodClock.getElapsedTime().asSeconds() > foodSpawnRate)
			{

				int it = 0;

				//Checks state of all food. If all exist in the game, marks allFoodPresent as true to prevent more food from spawning. 
				for (Food food : allFood)
				{
					if (food.getState() == false)
					{
						allFoodPresent = false;
						it++;
					}

					else if (it == allFood.size())
					{
						allFoodPresent = true;
					}
				}

				while (allFoodPresent == false)
				{
					int i = rand() % allFood.size();

					if (allFood[i].getState() == false)
					{
						allFood[i].toggleAlive();
						allFoodPresent = true;
					}
				}

				foodClock.restart();
			}


			//Loops and calls every function relevant to a snakes gameplay. 

			int currentDead{ 0 };

			for (Snake* player : allPlayers)
			{
				if (player->getIsDead() == false)
				{
					player->Update(allFood, allPlayers);
					player->Move(screenWidth, screenHeight);
					player->checkCollisions(screenWidth, screenHeight, water.getPosition(), allFood, allPlayers);
					player->Breath(water.getPosition());
				}
				else
					currentDead++;
			}

			//If all players are dead, Game Over.
			if (currentDead >= (int)allPlayers.size() || water.getPosition().y > water.getSize().y)
			{
				state = EGameState::eGameOver;
				break;
			}

			//Render all visual elements. Players, Water, Food, UI. 

			water.render(window);



			for (auto &food : allFood) //Draws food to window.
			{
				food.floatDown(water.getPosition());
				food.Render(window, newSnakeHeadSize);

			}

			for (Snake* snake : allPlayers)
			{
				if (snake->getIsDead() == false)
				{
					//Draws current snake to window.
					snake->Render(window);
				}
				//Draws text to window.
				DisplayUI(window, snake);
			}

			renderWalls(window); //Draws walls to window.

			//Game clock to add delay to refresh rate of window. 						
			static sf::Clock gameClock;

			while (gameClock.getElapsedTime().asMilliseconds() < gameDelay);
			gameClock.restart();


		}
		break;

		case EGameState::eGameOver:

			
			displayGameOver(window);
			return;

		default:
			break;
		}

		//Displays contents of window.	
		window.display();

	}	// Main loop that continues until we call window.close()


	std::cout << "SnakeGame: Finished" << std::endl;

	delete player;


}

//Manages game UI.
void Game::DisplayUI(sf::RenderWindow & window, Snake* player)
{
	//Error if font could not be loaded/
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Error. Font not available" << std::endl;
	}

	int playerNumber = player->getPlayerNumber();

	sf::Text textBreath;
	sf::Text textScore;
	sf::Text textPlayer;

	textBreath.setString("Breath: ");
	textBreath.setFont(font);
	textBreath.setCharacterSize(30);
	textBreath.setFillColor(player->getColor());

	textPlayer.setString("Player " + std::to_string(player->getPlayerNumber()));
	textPlayer.setFont(font);
	textPlayer.setCharacterSize(30);
	textPlayer.setFillColor(player->getColor());

	textScore.setString("Score: " + std::to_string(player->getScore()));
	textScore.setFont(font);
	textScore.setCharacterSize(30);
	textScore.setFillColor(player->getColor());

	if (player->getIsDead())
	{
		textBreath.setString("DEAD. ");
	}

	//sf::RectangleShape breathBar(sf::Vector2f(player->getBreath()/2, 20));

	sf::RectangleShape breathBar(sf::Vector2f(20, player->getBreath() / 2));

	//Reuses the text properties and applies settings relevant to each player. 
	switch (playerNumber)
	{
	case 1:

		textPlayer.setPosition(10, 0);

		textBreath.setPosition(10, 30);

		breathBar.setPosition(sf::Vector2f(130, 10));

		textScore.setPosition(10, 60);



		break;

	case 2:

		textPlayer.setPosition(160, 0);

		textBreath.setPosition(160, 30);
		breathBar.setPosition(sf::Vector2f(280, 10));

		textScore.setPosition(160, 60);


		break;

	case 3:

		textPlayer.setPosition(310, 0);

		textBreath.setPosition(310, 30);
		breathBar.setPosition(sf::Vector2f(430, 10));

		textScore.setPosition(310, 60);

		break;

	case 4:

		textPlayer.setPosition(460, 0);

		textBreath.setPosition(460, 30);
		breathBar.setPosition(sf::Vector2f(580, 10));

		textScore.setPosition(460, 60);

		break;




	}

	//UI Elements 

	//Breath changes colour as the value associated to the player breath decreases.
	if (player->getBreath() > 80)
	{
		breathBar.setFillColor(sf::Color(0, 255, 0, 255));
	}

	else if (player->getBreath() < 80 && allPlayers[0]->getBreath() > 40)
	{
		breathBar.setFillColor(sf::Color(255, 255, 0, 255));
	}

	else if (player->getBreath() < 40)
	{
		breathBar.setFillColor(sf::Color(255, 0, 0, 255));
	}

	breathBar.setOutlineColor(sf::Color(0, 128, 128, 255));

	//Draws all UI elements to the window. 
	window.draw(breathBar);
	window.draw(textBreath);
	window.draw(textScore);
	window.draw(textPlayer);




}

void Game::displayGameOver(sf::RenderWindow & window)
{
	//Displays Game Over screen. As is called during state machine, overrides the game play window. 

	bool abort = false;

	sf::Text textScore;
	sf::Text textWinner;
	sf::Text textGameOver;
	sf::Text textReturn;
	sf::Text textCreditsA;
	sf::Text textCreditsB;
	sf::Text textCreditsC;

	Snake *winningSnake = allPlayers[0];

	for (Snake* snake : allPlayers)
	{
		if (snake->getScore() > winningSnake->getScore())
		{
			winningSnake = snake;
		}
	}

	textGameOver.setString("GAME OVER");
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(50);
	textGameOver.setFillColor(winningSnake->getColor());
	textGameOver.setPosition(300, 75);

	textWinner.setString("Player " + std::to_string(winningSnake->getPlayerNumber()) + " wins!");
	textWinner.setFont(font);
	textWinner.setCharacterSize(30);
	textWinner.setFillColor(winningSnake->getColor());
	textWinner.setPosition(150, 175);

	textScore.setString("Score: " + std::to_string(winningSnake->getScore()));
	textScore.setFont(font);
	textScore.setCharacterSize(30);
	textScore.setFillColor(winningSnake->getColor());
	textScore.setPosition(150, 225);

	textReturn.setString("Press SPACE to return to Main Menu ");
	textReturn.setFont(font);
	textReturn.setCharacterSize(30);
	textReturn.setFillColor(winningSnake->getColor());
	textReturn.setPosition(150, 275);

	textCreditsA.setString("Background Artwork created by Luis Zuno (@ansimuz)");
	textCreditsA.setFont(font);
	textCreditsA.setCharacterSize(15);
	textCreditsA.setFillColor(winningSnake->getColor());
	textCreditsA.setPosition(100, 500);

	textCreditsB.setString("Food Sprites created by benmhenry@gmail.com. ");
	textCreditsB.setFont(font);
	textCreditsB.setCharacterSize(15);
	textCreditsB.setFillColor(winningSnake->getColor());
	textCreditsB.setPosition(100, 525);

	textCreditsC.setString("Font created by https://www.creativefabrica.com/designer/daymarius ");
	textCreditsC.setFont(font);
	textCreditsC.setCharacterSize(15);
	textCreditsC.setFillColor(winningSnake->getColor());
	textCreditsC.setPosition(100, 550);




	//While maintains the game over screen until spacebar is pressed. 
	while (abort == false)
	{
		window.clear();
		window.draw(textGameOver);
		window.draw(textScore);
		window.draw(textWinner);
		window.draw(textReturn);
		window.draw(textCreditsA);
		window.draw(textCreditsB);
		window.draw(textCreditsC);

		window.display();
		//Can press spacebar to start a new game. 	   		      		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			abort = true;
		}

	}

	return;



}

void Game::generateFood(const int &screenWidth, const int &screenHeight, const int &snakeHeadSize)
{
	//Generates random food and adds to food array.

	for (int i = 0; i < 5; i++)
	{


		bool foodOK{ false };
		int xPos, yPos;


		xPos = static_cast <int> (((rand() % screenWidth) / h) * h);
		yPos = static_cast <int> (((rand() % screenHeight) / h) * h);



		/*yPos = rand() % screenHeight + 10;
		yPos = (yPos / h) * h;*/



		sf::Vector2f position{ (float)xPos , (float)yPos };
		sf::Color color;
		int score = (rand() % 4) + 1;

		switch (score)
		{
		case 1:
			color = sf::Color{ 128, 255 , 0, 255 };
			break;
		case 2:
			color = sf::Color{ 255, 255 , 0, 255 };
			break;
		case 3:
			color = sf::Color{ 255, 128 , 0, 255 };
			break;
		case 4:
			color = sf::Color{ 255, 0 , 0, 255 };
			break;
		case 5:
			color = sf::Color{ 255, 255 , 255, 255 };
			break;

		default:
			break;
		}



		Food food(position, color, score);

		allFood.push_back(food);
	}
}

void Game::renderWalls(sf::RenderWindow & window)
{
	//Renders the walls to the gameplay screen.
	sf::Vector2f position;

	float width = 0.01f;

	sf::Vector2f size((float)screenWidth * width, (float)screenHeight);

	sf::Color color{ 173,12,242,255 };

	sf::RectangleShape rectangle(sf::Vector2f(0, 0)); //Offset position from top of screen.

	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	rectangle.setSize(size);

	window.draw(rectangle); //Draws east wall.

	position.x = screenWidth - ((float)screenWidth * width);
	rectangle.setPosition(position);

	window.draw(rectangle); //Draws west wall.


	size.x = (float)screenWidth;
	size.y = (float)screenHeight * width;

	rectangle.setPosition(0, screenHeight - size.y);
	rectangle.setSize(size);


	window.draw(rectangle); //Draws south wall.

}



