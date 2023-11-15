#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Tetris
{
	static const std::uint32_t lines{ 20 };
	static const std::uint32_t cols{ 10 };
	static const std::uint32_t squares{ 4 };
	static const std::uint32_t shapes{ 7 };

	std::vector<std::vector<std::uint32_t>> area;
	std::vector<std::vector<std::uint32_t>> forms;

	struct Coords
	{
		std::uint32_t x, y;
	}z[squares]{}, k[squares]{};

	std::shared_ptr<sf::RenderWindow> window;
	sf::Texture tiles, bg;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Sprite> background;
	sf::Clock clock;
	sf::Font font;
	sf::Text txtScore, txtGameOver;
	float timercount, delay;

	int dirx, color, score, initPosition;
	bool rotate, gameover;

protected:
	void events();
	void draw();
	void moveToDown();
	void setRotate();
	void resetValues();
	void changePosition();
	bool maxLimit();
	void setScore();


public:
	Tetris();
	void run();

};

