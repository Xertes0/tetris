#ifndef BLOCK_SHAPES_HPP
#define BLOCK_SHAPES_HPP

#include "block.hpp"

#include <array>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "input_handler.hpp"

#include "block_types.hpp"
#include "block_textures.hpp"
#include "block_data.hpp"

#include <fmt/printf.h>

using TexturePtrArray = std::array<std::shared_ptr<sf::Texture>, BLOCK_TYPE_COUNT>;

template<BlockType block_type>
class BlockShape : public Block
{
public:
	BlockShape(TexturePtrArray const & textures)
	{
		type = block_type;
		texture_index = BlockShapeIndex<block_type>::value;
		m_rotation = 0;

		//m_texture.loadFromFile(BlockTexture<block_type>::path);
		//m_sprite.setTexture(m_texture);
		m_sprite.setTexture(*textures[BlockShapeIndex<block_type>::value]);
		m_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
		
		reset();
	};

	virtual void
	reset() override
	{
		m_position = sf::Vector2f{START_POSITION_X, START_POSITION_Y};
		if constexpr(block_type == BlockType::I) {
			m_sprite.setOrigin(sf::Vector2f{
				m_sprite.getLocalBounds().width/2,
				0
			});
		} else if(block_type == BlockType::O) {
			m_sprite.setOrigin(sf::Vector2f{
				m_sprite.getLocalBounds().width/2,
				m_sprite.getLocalBounds().height/2
			});
			m_position += sf::Vector2f{FIELD_SIZE, 0.f};
		} else if(
			block_type == BlockType::T ||
			block_type == BlockType::S ||
			block_type == BlockType::Z ||
			block_type == BlockType::J ||
			block_type == BlockType::L
		)
		{
			m_sprite.setOrigin(sf::Vector2f{
				m_sprite.getLocalBounds().width/2,
				m_sprite.getLocalBounds().height/2 +
					m_sprite.getLocalBounds().height/4
			});
			m_position += sf::Vector2f{FIELD_SIZE+FIELD_SIZE/2, FIELD_SIZE/2};
		}

		m_sprite.setPosition(m_position);
	}

private:
	virtual void
	draw(sf::RenderTarget & target, [[maybe_unused]] sf::RenderStates states) const override
	{
		target.draw(m_sprite);
	};

	virtual void
	update(InputHandler const & input_handler, Field const & field, bool tick) override
	{
		auto const check_fallen = [&]() -> bool {
			// Block check
			auto const block_array = get_block_array();
			for(auto const &[x,y] : block_array) {
				if(y == FIELD_Y_COUNT-1)
					continue;
				
				if(field.static_blocks[x][y+1].has_value()) {
					return true;
				}
			}

			// Ground check
			auto const gc_offset = BlockGrundCheckOffset<block_type>::value[m_rotation];
			if(m_position.y >= (FIELD_SIZE*(FIELD_Y_COUNT+gc_offset))+FIELD_OFFSET_Y) {
				return true;
			}

			return false;
		};

		auto const can_move = [&](Move const move_type) -> bool {
			switch(move_type) {
				case Move::Left:
					for(auto const &[x,y] : get_block_array()) {
						if(x == 0) {
							return false;
						}
						if(field.static_blocks[x-1][y].has_value()) {
							return false;
						}
					}
					return true;
				case Move::Right:
					for(auto const &[x,y] : get_block_array()) {
						if(x == FIELD_X_COUNT-1) {
							return false;
						}
						if(field.static_blocks[x+1][y].has_value()) {
							return false;
						}
					}
					return true;
				case Move::Rotate:
					rotate();
					if(is_illegal(field)) {
						c_rotate();
						return false;
					}
					c_rotate();
					return true;
			};
			throw std::runtime_error{"can_move wtf"};
		};

		base_update(input_handler, tick, check_fallen, can_move);
		if constexpr(
				block_type == BlockType::I ||
				block_type == BlockType::S ||
				block_type == BlockType::Z) {
			if(m_rotation > 1) {
				m_rotation -= 2;
			}
		} else if(block_type == BlockType::O) {
			if(m_rotation != 0) {
				m_rotation = 0;
			}
		}
		m_sprite.setRotation(90.f * m_rotation);
		m_sprite.setPosition(m_position);
	};

	virtual auto
	get_block_array() const -> std::array<std::tuple<int,int>, 4> override
	{
		std::array to_return = BlockArrays<block_type>::value[m_rotation];
		sf::Vector2f const root{
			(m_position.x-FIELD_OFFSET_X)/FIELD_SIZE + BlockArrayRootOffsets<block_type>::x,
			(m_position.y-FIELD_OFFSET_Y)/FIELD_SIZE + BlockArrayRootOffsets<block_type>::y
		};

		//fmt::print("root x: {}\n", root.x);
		//fmt::print("root y: {}\n", root.y);

		for(auto &[x,y] : to_return) {
			x += root.x;
			y += root.y;

			if(x>=FIELD_X_COUNT)
				x = 0;
			if(y>=FIELD_Y_COUNT)
				y = 0;
		}

		return to_return;
	};
};

#endif // BLOCK_SHAPES_HPP
