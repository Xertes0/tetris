#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <memory>
#include <optional>
#include <vector>

#include <SFML/Graphics.hpp>

#include "field.hpp"
#include "block.hpp"
#include "block_generator.hpp"

class Tetris : public sf::Drawable
{
private:
	TetrisField m_field;
	BlockGenerator m_block_gen;
	unsigned int m_timer;
	float m_timer_end;
	bool m_is_falling;
	std::optional<std::unique_ptr<Block>> m_block;
	std::vector<std::shared_ptr<sf::Texture>> m_stextures;

	void load_static_textures();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	Tetris();

	void update();
};

#endif // TETRIS_HPP
