#include "block.hpp"

#include <fmt/printf.h>

#include "block_textures.hpp"

Block::Block() :
	m_rotation{0},
	m_position{OFFSET_X, OFFSET_Y}
{
}

void Block::rotate()
{
	if(++m_rotation == 4)
		m_rotation = 0;
}
