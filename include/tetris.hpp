#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "field.hpp"
#include "blocks.hpp"
#include "block_generator.hpp"

class Tetris : public sf::Drawable
{
	private:
	TetrisField m_field;
	BlockGenerator m_block_gen;
	unsigned int m_timer;
	unsigned int m_timer_end;
	std::vector<std::unique_ptr<Block>> m_blocks;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
	Tetris();

	void main_loop();
};

#endif // TETRIS_HPP
