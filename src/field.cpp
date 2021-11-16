#include "field.hpp"

#include <fmt/printf.h>

#include "block_textures.hpp"

TetrisField::TetrisField() :
	static_blocks{}
{
	static sf::Vector2f const offset{OFFSET_X, OFFSET_Y};
	m_lines = sf::VertexArray(sf::Lines);
	for(auto x=0;x<FIELD_X_COUNT+1;x++)
	{
		m_lines.append(sf::Vertex(sf::Vector2f{FIELD_SIZE * x, 0.f} + offset));
		m_lines.append(sf::Vertex(sf::Vector2f{FIELD_SIZE * x, FIELD_HEIGHT} + offset));
	}
	for(auto y=0;y<FIELD_Y_COUNT+1;y++)
	{
		m_lines.append(sf::Vertex(sf::Vector2f{0.f,         FIELD_SIZE * y} + offset));
		m_lines.append(sf::Vertex(sf::Vector2f{FIELD_WIDTH, FIELD_SIZE * y} + offset));
	}
};

int TetrisField::check_score()
{
	auto const check_complete = [&]() -> std::optional<size_t> {
		for(size_t y=static_blocks[0].size()-1;y>0;y--) {
			bool complete = true;
			for(size_t x=0;x<static_blocks.size();x++) {
				if(!static_blocks[x][y].has_value()) {
					complete = false;
				}
			}

			if(complete) {
				return y;
			}
		}

		return {};
	};

	int score = 0;
	while(true) {
		if(auto const complete = check_complete(); complete.has_value()) {
			remove_row(*complete);
			score++;
		} else {
			return score;
		}
	}
	
}

void TetrisField::remove_row(size_t const row)
{
	for(size_t x=0;x<static_blocks.size();x++) {
		for(int y=row-1;y>=0;y--) {
			std::swap(static_blocks[x][y], static_blocks[x][y+1]);
		}
		static_blocks[x][0] = {};
	}
}

void TetrisField::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Sprite placehodler{};
	placehodler.setScale(SCALE_FACTOR, SCALE_FACTOR);

	for(size_t x=0; auto const &block_x : static_blocks) {
		for(size_t y=0; auto const &block : block_x) {
			if(block.has_value()) {
				placehodler.setPosition(sf::Vector2f{
					OFFSET_X+(FIELD_SIZE*x),
					OFFSET_Y+(FIELD_SIZE*y)
				});
				placehodler.setTexture(*block->texture);
				//fmt::print("Draw x: {}, y: {}\n", x, y);
				target.draw(placehodler);
			}

			y++;
		}

		x++;
	}

	target.draw(m_lines);
}
