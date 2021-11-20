#include "block.hpp"

#include <fmt/printf.h>

#include "block_textures.hpp"

Block::Block() :
	m_rotation{0},
	m_position{FIELD_OFFSET_X + (FIELD_SIZE * 4), FIELD_OFFSET_Y} {}

void
Block::rotate()
{
	if(++m_rotation == 4)
		m_rotation = 0;
}

void
Block::c_rotate()
{
	if(--m_rotation == -1)
		m_rotation = 3;
}

auto
Block::is_illegal(Field const & field) -> bool
{
	for(auto const &[x,y] : get_block_array()) {
		if( x > static_cast<int>(FIELD_X_COUNT)-1 ||
			y > static_cast<int>(FIELD_Y_COUNT)-1 ||
			x < 0 ||
			y < 0
		) {
			return true;
		}
		if(field.static_blocks[x][y].has_value()) {
			return true;
		}
	}

	return false;
}
