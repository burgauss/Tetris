#include "tetris.hpp"

Tetris::Tetris()
{	
	area.resize(lines);
	for (std::size_t i{}; i < area.size(); ++i)
	{
		area[i].resize(cols);
	}

	forms = {
		{1,3,5,7}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // S
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}, // O
	};



	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(360,720),
		"Tetris (remix)",
		sf::Style::Titlebar | sf::Style::Close
	);

	window->setPosition(sf::Vector2i(780, 200));

	tiles.loadFromFile("C:/Users/juanb/source/repos/Tetris/Resources/squares.png");
	sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(tiles);
	sprite->setTextureRect(sf::IntRect(0, 0, 36,36));

}

void Tetris::events()
{
	auto e = std::make_shared<sf::Event>();
	while (window->pollEvent(*e)) {
		if (e->type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

void Tetris::draw() {
	window->clear(sf::Color::Black);

	for (std::size_t i{}; i < squares; ++i)
	{
		sprite->setPosition(z[i].x * 36, z[i].y * 36);
		window->draw(*sprite);
	}

	window->display();
}

void Tetris::run()
{
	while (window->isOpen())
	{
		events();
		moveToDown();
		draw();
	}
}

void Tetris::moveToDown()
{
	std::uint32_t number = { 3 };
	//if (z[0].x == 0)
	//{
	for (std::size_t i{}; i < squares; ++i)
	{
		z[i].x = forms[number][i] % 2;
		z[i].y = forms[number][i] / 2;
	}
	//}

}