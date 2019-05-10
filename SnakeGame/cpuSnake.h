#pragma once
#include "snake.h"
#include <math.h>

class cpuSnake : public Snake
{

private:

	sf::Vector2f currentTarget;
	sf::Vector2f currentTargetSquared;
	sf::Vector2f currentPosSquared;
	int breathThreshold{ 25 };
	bool targetSet = false;
	bool needsAir;

public:

	cpuSnake(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber);
	void Update(std::vector<Food>& allFood, std::vector<Snake*> &allPlayers) override;
	void clearTarget() override;

};
