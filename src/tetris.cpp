#include "tetris.hpp"

Tetris::Tetris() :
	m_block{{}},
	m_field{},
	m_block_gen{},
	m_timer{0},
	m_timer_end{120},
	m_is_falling(false)
{}

void Tetris::main_loop()
{
	if(m_timer++ >= m_timer_end) {
		if(!m_is_falling) {
			m_block = std::move(m_block_gen());
		}

		m_timer = 0;
	}
}

void Tetris::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(m_block.has_value())
		target.draw(**m_block);

	target.draw(m_field);
}
