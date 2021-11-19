#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <array>
#include <memory>
#include <optional>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "input_handler.hpp"

#include "field.hpp"
#include "block.hpp"
#include "block_generator.hpp"

constexpr std::array<unsigned int, 30> LEVEL_TIMER {
	48,
	43,
	38,
	33,
	28,
	23,
	18,
	13,
	8,
	6,
	5,
	5,
	5,
	4,
	4,
	4,
	3,
	3,
	3,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	1,
};

constexpr unsigned int MAX_LEVEL {29};

class Tetris : public sf::Drawable
{
private:
	TexturePtrArray const m_stextures;
	TexturePtrArray const m_textures;

	Field          m_field;
	BlockGenerator m_block_gen;

	unsigned int m_timer;
	unsigned int m_level;
	unsigned int m_score;
	unsigned int m_lines_destroyed;

	bool m_is_falling;
	std::optional<std::unique_ptr<Block>> m_block;

	auto
	get_score(unsigned int destroyed) -> unsigned int;

	virtual void
	draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Tetris();

	void
	update(InputHandler const & input_handler);
};

#endif // TETRIS_HPP
