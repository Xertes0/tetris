#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <array>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

enum class KeyState
{
	Up,
	PressedOnce,
	Pressed,
};

constexpr std::array<sf::Keyboard::Key, 4> KEYS {
	sf::Keyboard::Key::Up,
	sf::Keyboard::Key::Down,
	sf::Keyboard::Key::Left,
	sf::Keyboard::Key::Right
};

class InputHandler
{
public:
	InputHandler();

	//void
	//process_event(sf::Event const & event);
	
	void
	process_keyboard();

	auto
	pressed_once(sf::Keyboard::Key const key) const -> bool;

	auto
	pressed(sf::Keyboard::Key const key) const -> bool;

private:
	std::unordered_map<sf::Keyboard::Key, KeyState> m_key_states;
};

#endif // INPUT_HANDLER_HPP
