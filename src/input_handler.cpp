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
	for(auto & state : m_key_states) {
		state = KeyState::Up;
	}
}

void
InputHandler::process_keyboard()
{
	process_key<ACTIONS>();
}
