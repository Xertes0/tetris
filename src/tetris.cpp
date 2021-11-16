#include "tetris.hpp"

#include <fmt/printf.h>

Tetris::Tetris() :
	m_block{},
	m_field{},
	m_block_gen{},
	m_timer{0},
	m_timer_end{16},
	m_is_falling(false) {}

void Tetris::update()
{
	if(m_timer++ >= m_timer_end) {
		if(!m_is_falling) {
			m_block = std::move(m_block_gen());
			m_is_falling = true;
		} else {
			m_block.value()->update(m_field, true);
		}

		m_timer = 0;
	} else {
		if(m_block.has_value())
			m_block.value()->update(m_field, false);
	}

	if(m_block.has_value()) {
		if(m_block.value()->has_fallen) {
			for(auto const [x,y] : m_block.value()->get_block_array()) {
				m_field.static_blocks[x][y] = StaticBlock{.color{sf::Color::Blue}};
				fmt::print("sblock x: {}, y: {}\n", x,y);
			}
			m_is_falling = false;
			m_block.reset();

			m_field.check_score();
		}
	}
}

void Tetris::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(m_block.has_value())
		target.draw(**m_block);

	target.draw(m_field);
}
