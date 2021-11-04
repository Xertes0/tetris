#include "tetris.hpp"

Tetris::Tetris() :
	m_blocks{},
	m_field{},
	m_block_gen{},
	m_timer{0},
	m_timer_end{120}
{}

void Tetris::main_loop()
{
	if(m_timer++ >= m_timer_end) {
		m_blocks.push_back(std::move(m_block_gen()));
		m_timer = 0;
	}
}

void Tetris::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for(auto const &block : m_blocks)
		target.draw(*block);

	target.draw(m_field);
}
