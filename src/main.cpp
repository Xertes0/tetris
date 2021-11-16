#include <fmt/format.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "tetris.hpp"
#include "game_state.hpp"

constexpr unsigned int const WIDTH  = 600; 
constexpr unsigned int const HEIGHT = 800;

void center_window(sf::Window &window)
{
	auto const desktop_mode = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktop_mode.width/2 - WIDTH/2, desktop_mode.height/2 - HEIGHT/2));
}

auto
main() -> int
{
	fmt::print("Hello tetris!\n");

	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Tetris");
	center_window(window);
	window.setFramerateLimit(16);

	Tetris tetris;
	GameState game_state{};
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		tetris.update();

		window.clear(sf::Color::Black);

		window.draw(tetris);

		window.display();
	}

	return 0;
}
