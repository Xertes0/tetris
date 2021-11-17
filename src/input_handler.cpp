#include "input_handler.hpp"

#include <fmt/printf.h>

//void
//InputHandler::process_event(sf::Event const & event)
//{
//	switch(event.type) {
//		case sf::Event::KeyPressed:
//			fmt::print("Pressed: {}\n", event.key.code);
//			if(m_key_states[event.key.code] == KeyState::Up) {
//				m_key_states[event.key.code] = KeyState::PressedOnce;
//			} else if(m_key_states[event.key.code] == KeyState::PressedOnce){
//				m_key_states[event.key.code] = KeyState::Pressed;
//			}
//			break;
//		case sf::Event::KeyReleased:
//			m_key_states[event.key.code] = KeyState::Up;
//			break;
//		default: break;
//	}
//}

InputHandler::InputHandler() :
	m_key_states{}
{
	for(auto const & key : KEYS) {
		m_key_states[key] = KeyState::Up;
	}
}

void
InputHandler::process_keyboard()
{
	for(auto const & key : KEYS) {
		if(sf::Keyboard::isKeyPressed(key)) {
			if(m_key_states[key] == KeyState::Up) {
				m_key_states[key] = KeyState::PressedOnce;
			} else if(m_key_states[key] == KeyState::PressedOnce) {
				m_key_states[key] = KeyState::Pressed;
			}
		} else {
			m_key_states[key] = KeyState::Up;
		}
	}
}

auto
InputHandler::pressed_once(sf::Keyboard::Key const key) const -> bool
{
	auto const found = m_key_states.find(key);
	if(found != m_key_states.end()) {
		if(found->second == KeyState::PressedOnce) {
			return true;
		}
	}

	return false;
}

auto
InputHandler::pressed(sf::Keyboard::Key const key) const -> bool
{
	auto const found = m_key_states.find(key);
	if(found != m_key_states.end()) {
		if(found->second != KeyState::Up) {
			return true;
		}
	}

	return false;
}
