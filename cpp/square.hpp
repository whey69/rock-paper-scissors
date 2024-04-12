#pragma once

int clamp(int, int, int);

class square
{
public:
	sf::Vector2f position;
	int size;
	int type;
	void update();
	square();
private:
	sf::Vector2f vel;
};