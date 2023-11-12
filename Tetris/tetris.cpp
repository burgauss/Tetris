#include "tetris.hpp"

Tetris::Tetris()
{											  
	window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(360,720),
		"Tetris (remix)",
		sf::Style::Titlebar | sf::Style::Close
	);

	window->setPosition(sf::Vector2i(100, 100));

	title.loadFromFile(
}