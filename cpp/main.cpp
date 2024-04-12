#include <iostream>
#include <SFML/Graphics.hpp>
#include "square.hpp"

bool collides(const square& sq1, const square& sq2) {
	return sq1.position.x < sq2.position.x + sq2.size &&
		sq1.position.x + sq1.size > sq2.position.x &&
		sq1.position.y < sq2.position.y + sq2.size &&
		sq1.position.y + sq1.size > sq2.position.y;
}

int main()
{
	square sqrs[250];

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "font load fail alert alert";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(1280, 720), "rps");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					for (int i = 0; i < sizeof(sqrs) / sizeof(square); i++)
					{
						sqrs[i] = square();
					}
				}
			}
		}

		window.clear(sf::Color::Black);

		int left[3] = { 0, 0, 0 };
		if (sizeof(sqrs) / sizeof(square) == 0)
		{
			for (int i = 0; i < sizeof(sqrs) / sizeof(square); i++)
			{
				sqrs[i] = square();
			}
		}

		//std::cout << "sizeof sqrs / square" << sizeof(sqrs) / sizeof(square) << "\n";
		for (int i = 0; i < sizeof(sqrs)/sizeof(square); i++)
		{	
			//std::cout << "i=" << i << "\n";
			square &element = sqrs[i];
			element.update();
			for (int j = 0; j < sizeof(sqrs) / sizeof(square); j++)
			{
				int t = sqrs[j].type;
				if (i != j && element.type != t)
				{
					if (collides(element, sqrs[j]))
					{
						if (t == 0 && element.type == 2)
						{
							element.type = 0;
						}
						if (t == 1 && element.type == 0)
						{
							element.type = 1;
						}
						if (t == 2 && element.type == 1)
						{
							element.type = 2;
						}
					}
				}
			}

			left[element.type] += 1;

			sf::VertexArray triangle(sf::TrianglesStrip, 4); 
			triangle[0].position = sf::Vector2f(element.position.x, element.position.y);
			triangle[1].position = sf::Vector2f(element.position.x + element.size, element.position.y);
			triangle[2].position = sf::Vector2f(element.position.x, element.position.y + element.size); 
			triangle[3].position = sf::Vector2f(element.position.x + element.size, element.position.y + element.size);
			if(element.type == 0) {
				triangle[0].color = sf::Color(128, 128, 128);
				triangle[1].color = sf::Color(128, 128, 128);
				triangle[2].color = sf::Color(128, 128, 128);
				triangle[3].color = sf::Color(128, 128, 128);
			}
			if (element.type == 1)
			{
				triangle[0].color = sf::Color::White;
				triangle[1].color = sf::Color::White;
				triangle[2].color = sf::Color::White;
				triangle[3].color = sf::Color::White;
			}
			if (element.type == 2)
			{
				triangle[0].color = sf::Color::Red;
				triangle[1].color = sf::Color::Red;
				triangle[2].color = sf::Color::Red;
				triangle[3].color = sf::Color::Red;
			}
			window.draw(triangle); 
		}

		// this section is some of the worst one ive written yet
		sf::VertexArray infosqr(sf::TrianglesStrip, 4); 
		infosqr[0].position = sf::Vector2f(0, 620); 
		infosqr[1].position = sf::Vector2f(427, 620); 
		infosqr[2].position = sf::Vector2f(0, 720); 
		infosqr[3].position = sf::Vector2f(427, 720); 
		infosqr[0].color = sf::Color(128, 128, 128); 
		infosqr[1].color = sf::Color(128, 128, 128); 
		infosqr[2].color = sf::Color(128, 128, 128); 
		infosqr[3].color = sf::Color(128, 128, 128); 
		window.draw(infosqr); 
		infosqr[0].position = sf::Vector2f(427, 620); 
		infosqr[1].position = sf::Vector2f(853, 620); 
		infosqr[2].position = sf::Vector2f(427, 720); 
		infosqr[3].position = sf::Vector2f(853, 720); 
		infosqr[0].color = sf::Color::White; 
		infosqr[1].color = sf::Color::White; 
		infosqr[2].color = sf::Color::White; 
		infosqr[3].color = sf::Color::White; 
		window.draw(infosqr); 
		infosqr[0].position = sf::Vector2f(853, 620);
		infosqr[1].position = sf::Vector2f(1280, 620); 
		infosqr[2].position = sf::Vector2f(853, 720);
		infosqr[3].position = sf::Vector2f(1280, 720); 
		infosqr[0].color = sf::Color::Red; 
		infosqr[1].color = sf::Color::Red; 
		infosqr[2].color = sf::Color::Red; 
		infosqr[3].color = sf::Color::Red; 
		window.draw(infosqr); 

		sf::Text text;
		text.setFont(font);
		text.setString("rocks: " + std::to_string(left[0]));
		text.setCharacterSize(72);
		text.setFillColor(sf::Color::Black);
		text.setPosition(0, 620);
		window.draw(text);
		text.setString("papers: " + std::to_string(left[1]));
		text.setPosition(427, 620);
		window.draw(text);
		text.setString("scissors: " + std::to_string(left[2]));
		text.setPosition(853, 620);
		window.draw(text);
		window.display();
	}

	return 0;
}
