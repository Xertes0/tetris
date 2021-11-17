#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <array>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

enum class KeyState : size_t
{
	Up,
	PressedOnce,
	Pressed,
};

constexpr size_t KEY_COUNT{4};

enum class Action
{
	Rotate,
	Left,
	Right,
	Down,
};

template<Action action>
struct KeyCode;

#define ADD_KEY(NAME, KEY_CODE) \
	template<> \
	struct KeyCode<NAME>\
	{ static constexpr auto value {KEY_CODE}; };

#define ACTIONS \
	Action::Rotate, \
	Action::Left, \
	Action::Right, \
	Action::Down

ADD_KEY(Action::Rotate, sf::Keyboard::Key::Up);
ADD_KEY(Action::Left,   sf::Keyboard::Key::Left);
ADD_KEY(Action::Right,  sf::Keyboard::Key::Right);
ADD_KEY(Action::Down,   sf::Keyboard::Key::Down);

class InputHandler
{
public:
	InputHandler();

	//void
	//process_event(sf::Event const & event);

	template<Action action>
	void
	process_key(auto & state)
	{
		if(sf::Keyboard::isKeyPressed(KeyCode<action>::value)) {
			if(state == KeyState::Up) {
				state = KeyState::PressedOnce;
			} else if(state == KeyState::PressedOnce) {
				state = KeyState::Pressed;
			}
		} else {
			state = KeyState::Up;
		};
	}
	
	template<Action... action>
	void
	process_key()
	{
		((process_key<action>(m_key_states[static_cast<size_t>(action)])), ...);
	};
	
	void
	process_keyboard();

	template<Action action>
	auto
	pressed_once() const -> bool
	{
		return m_key_states[static_cast<size_t>(action)] == KeyState::PressedOnce;
	}

	template<Action action>
	auto
	pressed() const -> bool
	{
		return m_key_states[static_cast<size_t>(action)] != KeyState::Up;
	}

private:
	std::array<KeyState, KEY_COUNT> m_key_states;
};

#endif // INPUT_HANDLER_HPP
