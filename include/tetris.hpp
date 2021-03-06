#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "input_handler.hpp"

#include "field.hpp"
#include "block.hpp"
#include "block_generator.hpp"

#include "level.hpp"

constexpr unsigned int const WIDTH  = 600; 
constexpr unsigned int const HEIGHT = 800;

class Tetris : public sf::Drawable
{
private:
	TexturePtrArray const m_stextures;
	TexturePtrArray const m_textures;

	Field          m_field;
	BlockGenerator m_block_gen;
	Level          m_level;

	unsigned int m_timer;

	bool m_is_falling;
	bool m_swaped;
	std::unique_ptr<Block> m_block;
	std::unique_ptr<Block> m_block_sbuf;

	virtual void
	draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Tetris();

	void
	update(InputHandler const & input_handler);
};

#endif // TETRIS_HPP
