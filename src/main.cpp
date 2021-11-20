#include <fmt/format.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "input_handler.hpp"
#include "tetris.hpp"

void
center_window(sf::Window & window)
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
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);

	InputHandler input_handler{};
	Tetris tetris{};
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			//input_handler.process_event(event);
			if(event.type == sf::Event::Closed)
				window.close();
		}
		input_handler.process_keyboard();

		tetris.update(input_handler);

		window.clear(sf::Color::Black);

		window.draw(tetris);

		window.display();
	}

	return 0;
}
