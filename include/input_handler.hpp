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

template<typename action>
struct KeyCode;

template<int n>
struct ProcessKey
{
	static void exec(auto & state);
};

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
	namespace Action { struct NAME { static constexpr size_t index{N};}; }; \
	template<> \
	struct KeyCode<Action::NAME> \
	{ static constexpr auto value {KEY_CODE}; }; \
	PROCESS_KEY(N, Action::NAME)

constexpr size_t KEY_COUNT{4};

ADD_KEY(0, Rotate, sf::Keyboard::Key::Up);
ADD_KEY(1, Left,   sf::Keyboard::Key::Left);
ADD_KEY(2, Right,  sf::Keyboard::Key::Right);
ADD_KEY(3, Down,   sf::Keyboard::Key::Down);

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
