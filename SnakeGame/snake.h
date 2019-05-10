#pragma once

#include <list>
#include "food.h"
#include <vector>



class Snake
{
protected:

	int xInc{ 0 };
	int yInc{ 20 };
	int orientation{ 90 };
	int headSize;
	int playerNumber;
	int score{ 0 };
	int growAmount{ 0 };
	//For use with custom linked list instead of body.size().
	int currentSnakeSize;
	float breath{ 100 };
	float breathInc{ 1 };
	bool isDead{ false };
	bool isAboveWater{ false };
	bool isMoving{ false };
	bool countedDead{ false };
	bool isCPU;
	sf::Color color;

	enum class EDirection
	{
		eNorth, eEast, eSouth, eWest
	};

	//Default direction
	EDirection directionOne{ EDirection::eEast };
	//For prevention of snake going back on itself.
	EDirection previousDirection;
	//For AI to calculate next target.
	EDirection targetRelativeToPos;
	//Adjust range of movement
	const float& h = static_cast <float> (headSize * 2);
	//Stores position before added to std::list or the custom linked list.
	struct structSegment
	{
		sf::Vector2f position;
	};

	//Using the std::list, attmpted to create my own linked list, included the header and cpp file, named segment.h and segment.cpp.
	//Implemented in another file but was caught in an endless loop.
	std::list <structSegment> body;





public:

	Snake(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber);
	//Create deconstructor and run Clear function to delete custom linked list.
	~Snake();

	virtual void Update(std::vector<Food>& allFood, std::vector<Snake*> &allPlayers) = 0;
	virtual void clearTarget();
	void Render(sf::RenderWindow & window);
	void Move(const int &screenWidth, const int &screenHeight);
	void Shrink();
	void checkCollisions(const int &screenWidth, const int &screenHeight, const sf::Vector2f &waterPos, std::vector<Food>& allFood, std::vector <Snake*> &allPlayers);
	void changeDirection(const sf::Vector2f &new_position);
	void Breath(const sf::Vector2f &water);
	void setDead();

	//Related to custom linked list. Not used in game but for reference.
	void AddSegment(sf::Vector2f &new_position);
	void RemoveSegment();
	void Clear();

	//Get functions
	sf::Vector2f getPosition() const;
	int getHeadSize() const;
	int getScore();
	float getBreath();
	bool getIsDead();
	int getPlayerNumber();
	sf::Color getColor();

};
