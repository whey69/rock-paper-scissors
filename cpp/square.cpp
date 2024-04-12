#include <iostream>
#include <SFML\Graphics.hpp>
#include "square.hpp"

int clamp(int val, int min, int max)
{
	if (val > max)
	{
		return max;
	}
	if (val < min)
	{
		return min;
	}
	return val;
}

square::square()
{
	this->vel = sf::Vector2f((std::rand() % 4) - 2, (std::rand() % 4) - 2);
	if (this->vel.x == 0)
	{
		this->vel.x += 0.5f;
	}
	if (this->vel.y == 0)
	{
		this->vel.y += 0.5f;
	}
	this->size = 25;
	this->position = sf::Vector2f(clamp(std::rand() % 1280 - this->size, 0, 1280 - this->size), clamp(std::rand() % 620 - this->size, 0, 620 - this->size));
	this->type = std::rand() % 3;
}

void square::update()
{
	//std::cout << this->position.x << " " << this->position.y << "\n";
	this->position = sf::Vector2f(this->position.x + this->vel.x, this->position.y + this->vel.y);
	const sf::Vector2f pos = this->position;
	if (pos.x < 0 || pos.x > 1280 - this->size)
	{
		this->vel = sf::Vector2f(-this->vel.x, this->vel.y);
	}
	if (pos.y < 0 || pos.y > 620 - this->size)
	{
		this->vel = sf::Vector2f(this->vel.x, -this->vel.y);
	}
}