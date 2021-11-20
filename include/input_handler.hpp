#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <array>

#include <SFML/Window/Keyboard.hpp>

enum class KeyState : std::size_t
{
	Up,
	PressedOnce,
	Pressed,
};

template<typename action>
struct KeyCode;

template<int n>
struct ProcessKey
{
	static void exec(auto & state);
};

#define KEY_NAMESPACE Action

#define PROCESS_KEY(N, NAME) \
	template<> \
	struct ProcessKey<N> \
	{ \
		static void exec(auto & states) \
		{ \
			auto & state = states[NAME::index]; \
			if(sf::Keyboard::isKeyPressed(KeyCode<NAME>::value)) { \
				if(state == KeyState::Up) { \
					state = KeyState::PressedOnce; \
				} else if(state == KeyState::PressedOnce) { \
					state = KeyState::Pressed; \
				} \
			} else { \
				state = KeyState::Up; \
			}; \
			if constexpr(N != 0) { ProcessKey<N-1>::exec(states); } \
		} \
	}

#define ADD_KEY(N, NAME, KEY_CODE) \
	namespace KEY_NAMESPACE { struct NAME { static constexpr std::size_t index{N};}; }; \
	template<> \
	struct KeyCode<KEY_NAMESPACE::NAME> \
	{ static constexpr auto value {KEY_CODE}; }; \
	PROCESS_KEY(N, KEY_NAMESPACE::NAME)

constexpr std::size_t KEY_COUNT{5};

ADD_KEY(0, Rotate, sf::Keyboard::Key::Up);
ADD_KEY(1, Left,   sf::Keyboard::Key::Left);
ADD_KEY(2, Right,  sf::Keyboard::Key::Right);
ADD_KEY(3, Down,   sf::Keyboard::Key::Down);
ADD_KEY(4, Swap,   sf::Keyboard::Key::C);

class InputHandler
{
public:
	InputHandler();
	
	void
	process_keyboard();

	template<typename action>
	auto
	pressed_once() const -> bool
	{
		return m_key_states[action::index] == KeyState::PressedOnce;
	}

	template<typename action>
	auto
	pressed() const -> bool
	{
		return m_key_states[action::index] != KeyState::Up;
	}

private:
	std::array<KeyState, KEY_COUNT> m_key_states;
};

#endif // INPUT_HANDLER_HPP
