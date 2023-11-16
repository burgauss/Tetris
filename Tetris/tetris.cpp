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

	bg.loadFromFile("C:/Users/juanb/source/repos/Tetris/Resources/background.png");
	background = std::make_shared<sf::Sprite>();
	background->setTexture(bg);
	dirx = score = initPosition = { 0 };
	rotate = gameover = { false };
	timercount = { 0.f };
	delay = { 0.3f };		  
	color = { 1 };

	std::uint32_t number = std::rand() % shapes;
	for (std::size_t i{}; i < squares; i++)
	{
		z[i].x = forms[number][i] % 2;
		z[i].y = forms[number][i] / 2;
	}

	initPosition = std::rand() % cols - 2;

	for (std::size_t i{}; i < squares; i++)
	{
		z[i].x += initPosition;
	}

	font.loadFromFile("C:/Users/juanb/source/repos/Tetris/Resources/font.ttf");
	txtScore.setFont(font);
	txtScore.setPosition(100.f, 10.f);
	txtScore.setString("SCORE: " + std::to_string(score));
	txtScore.setCharacterSize(30);
	txtScore.setOutlineThickness(3);   

	txtGameOver.setFont(font);
	txtGameOver.setPosition(100.f, 300.f);
	txtGameOver.setString("GAME OVER");
	txtGameOver.setCharacterSize(30);
	txtGameOver.setOutlineThickness(3);
	
}

/// <summary>
/// Handles events generated by keyboard commands.
/// Increments a counter with each call. See also: <see cref="Run"/>.
/// </summary>
void Tetris::events()
{
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timercount += time;



	auto e = std::make_shared<sf::Event>();
	while (window->pollEvent(*e)) {
		if (e->type == sf::Event::Closed)
		{
			window->close();
		}

		if (e->type == sf::Event::KeyPressed)
		{
			if (e->key.code == sf::Keyboard::Up)
			{
				rotate = true;
			}
			else if (e->key.code == sf::Keyboard::Right)
			{
				++dirx;
			}
			else if (e->key.code == sf::Keyboard::Left)
			{
				--dirx;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		delay = 0.05f;
	}
}

/// <summary>
/// Draw the sprites
/// call the method display from window <see cref="Tetris"/>. 
/// See also: <see cref="Run"/>.
/// </summary>
void Tetris::draw() {
	window->clear(sf::Color::Black);

	//draws the already stoped figures
	for (std::size_t i{}; i < lines; ++i)
	{
		for (std::size_t j{}; j < cols; ++j)
		{
			if (area[i][j] != 0)
			{
				sprite->setTextureRect(sf::IntRect(area[i][j] * 36, 0, 36, 36));
				sprite->setPosition(j * 36, i * 36);
				window->draw(*sprite);
			}
		}
	}

	for (std::size_t i{}; i < squares; ++i)
	{
		sprite->setTextureRect(sf::IntRect(color * 36, 0, 36, 36));
		sprite->setPosition(z[i].x * 36, z[i].y * 36);
		window->draw(*sprite);
	}

	window->draw(*background);
	window->draw(txtScore);
	if (gameover)
	{
		window->draw(txtGameOver);
	}
	window->display();
}

/// <summary>
/// Main event that calls other dependecies
/// </summary>
void Tetris::run()
{
	while (window->isOpen())
	{
		events();
		if (!gameover)
		{
			changePosition();
			setRotate();
			moveToDown();
			setScore();
			resetValues();
		}
		draw();
	}
}

/// <summary>
/// Handles the movement of the figures, the rotations and
/// evualates the limits in the grid
/// </summary>
void Tetris::moveToDown()
{
	if (timercount > delay)
	{

		for (std::size_t i{}; i < squares; ++i)
		{
			k[i] = z[i];
			++z[i].y;
		}

		if (maxLimit())
		{
			for (std::size_t i{}; i < squares; ++i)
			{
				area[k[i].y][k[i].x] = color;
			}

			std::uint32_t number = std::rand()%shapes;
			color = std::rand() % shapes + 1;
			initPosition = std::rand() % (cols - 2);


			for (std::size_t i{}; i < squares; ++i)
			{
				z[i].x = forms[number][i] % 2;
				z[i].y = forms[number][i] / 2;
			}

			for (std::size_t i{}; i < squares; i++)
			{
				z[i].x += initPosition;
			}
		}
		timercount = 0;
	}
}
/// <summary>
/// It has the mathematics for the rotation of figures
/// </summary>
void Tetris::setRotate()
{
	if (rotate)
	{
		Coords coords = z[1];
		for (std::size_t i{}; i < squares; ++i)
		{
			int x = z[i].y - coords.y;
			int y = z[i].x - coords.x;

			z[i].x = coords.x - x;
			z[i].y = coords.y + y;
		}

		if (maxLimit())
		{
			for (std::size_t i{}; i < squares; ++i)
			{
				z[i] = k[i];
			}
		}
	}


}

/// <summary>
/// Reset values
/// </summary>
void Tetris::resetValues()
{
	dirx = 0;
	rotate = false;
	delay = 0.3f;
}

/// <summary>
/// it moves the figures according to the information from 
/// <cref="events"/>
/// </summary>
void Tetris::changePosition()
{
	for (std::size_t i{}; i < squares; ++i)
	{
		k[i] = z[i];
		z[i].x += dirx;
	}
	if (maxLimit())
	{
		for (std::size_t i{}; i < squares; ++i)
		{
			z[i] = k[i];
		}
	}

}

/// <summary>
/// it evaluates the limits from side to side and the location under
/// </summary>
bool Tetris::maxLimit()
{
	for (std::size_t i{}; i < squares; ++i)
	{
		if (z[i].x < 0 ||
			z[i].x >= cols ||
			z[i].y >= lines	 ||
			area[ z[i].y ][ z[i].x ])
		{
			return true;
		}
	}
	return false;

}

/// <summary>
/// it contains the logic to calculate scores and stopping the game
/// </summary>
void Tetris::setScore()
{
	std::uint32_t match = lines - 1;
	for (std::size_t i = match; i >= 1; --i)
	{
		std::uint32_t sum{};
		for (std::size_t j{}; j < cols; ++j)
		{
			if (area[i][j])
			{
				if (i == 1)
				{
					gameover = true;
				}
				++sum;
			}
			area[match][j] = area[i][j];
		}
		if (sum < cols)
		{
			--match;
		}
		else
		{
			txtScore.setString("SCORE: " + std::to_string(++score));
		}
	}
}
