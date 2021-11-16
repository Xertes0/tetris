#include "block_shapes.hpp"

#include <filesystem>
#include <fmt/printf.h>

#include "block_textures.hpp"

template<typename CheckFallen, typename CheckMovement>
void Block::base_update(
	const TetrisField &field,
	bool tick,
	CheckFallen &check_fallen,
	CheckMovement &can_move
)
{
	bool down_pressed = false;
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		can_move(Move::Rotate))
	{
		rotate();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_position += {0.f, FIELD_SIZE};
		down_pressed = true;
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		can_move(Move::Right))
	{
		m_position += {FIELD_SIZE, 0.f};
	}
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
		can_move(Move::Left))
	{
		m_position += {-FIELD_SIZE, 0.f};
	}

	if(tick && !down_pressed)
		m_position += {0.f, FIELD_SIZE};

	has_fallen = check_fallen();
}

template<BlockType block_type>
BlockShape<block_type>::BlockShape() {}

BlockShape<BlockType::I>::BlockShape()
{
	texture_index = 0;
	m_rotation = 0;
	m_texture.loadFromFile(BlockTexture<BlockType::I>::path);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	m_sprite.setOrigin(sf::Vector2f{0, m_sprite.getLocalBounds().height/2});
}

void BlockShape<BlockType::I>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void BlockShape<BlockType::I>::update(TetrisField const & field, bool const tick)
{
	auto const check_fallen = [&]() -> bool {
		// Block check
		auto const block_array = get_block_array();
		for(auto const [x,y] : block_array) {
			if(y == FIELD_Y_COUNT-1)
				continue;
			
			if(field.static_blocks[x][y+1].has_value())
				return true;
		}

		// Ground check
		if(	m_sprite.getRotation() == 90.f ||
			m_sprite.getRotation() == 270.f)
		{
			if(m_position.y >= (FIELD_SIZE*(FIELD_Y_COUNT-1))+OFFSET_Y) {
				return true;
			}
		} else {
			if(m_position.y >= (FIELD_SIZE*(FIELD_Y_COUNT-2))+OFFSET_Y) {
				return true;
			}
		}

		return false;
	};

	auto const can_move = [&](Move const move_type) -> bool {
		switch(move_type) {
			case Move::Left:
				for(auto const [x,y] : get_block_array()) {
					if(x == 0)
						return false;
					if(field.static_blocks[x-1][y].has_value())
						return false;
				}
				return true;
			case Move::Right:
				for(auto const [x,y] : get_block_array()) {
					if(x == FIELD_X_COUNT-1)
						return false;
					if(field.static_blocks[x+1][y].has_value())
						return false;
				}
				return true;
			case Move::Rotate:
				return true;
		};
		throw std::runtime_error{"can_move wtf"};
	};

	base_update(field, tick, check_fallen, can_move);
	if(m_rotation > 1) {
		m_rotation -= 2;
	}
	m_sprite.setRotation(90.f * m_rotation);
	m_sprite.setPosition(m_position);
}

template<BlockType block_type>
std::array<std::tuple<int, int>, 4>
Block<block_type>::get_block_array() const
{
	std::array to_return = BlockArrays<BlockType::I>::value[0];
	sf::Vector2f const root{
		(m_position.x-OFFSET_X)/FIELD_SIZE,
		(m_position.y-OFFSET_Y)/FIELD_SIZE
	};

	for(auto &[x,y] : to_return) {
		x += root.x;
		y += root.y;

		if(x>=FIELD_X_COUNT)
			x = 0;
		if(y>=FIELD_Y_COUNT)
			y = 0;
	}

	return to_return;
}

BlockShape<BlockType::O>::BlockShape()
{
	texture_index = 1;
	m_rotation = 0;
	m_texture.loadFromFile(BlockTexture<BlockType::O>::path);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	m_sprite.setOrigin(sf::Vector2f{
		m_sprite.getLocalBounds().width/2,
		m_sprite.getLocalBounds().height/2
	});
	m_position += sf::Vector2f{FIELD_SIZE, 0.f};
	m_sprite.setPosition(m_position);
}

void BlockShape<BlockType::O>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void BlockShape<BlockType::O>::update(TetrisField const & field, bool const tick)
{
	auto const check_fallen = [&]() -> bool {
		// Block check
		auto const block_array = get_block_array();
		for(auto const [x,y] : block_array) {
			if(y == FIELD_Y_COUNT-1)
				continue;
			
			if(field.static_blocks[x][y+1].has_value())
				return true;
		}

		// Ground check
		if(m_position.y >= (FIELD_SIZE*(FIELD_Y_COUNT-1))+OFFSET_Y) {
			return true;
		}

		return false;
	};

	auto const can_move = [&](Move const move_type) -> bool {
		switch(move_type) {
			case Move::Left:
				for(auto const [x,y] : get_block_array()) {
					if(x == 0)
						return false;
					if(field.static_blocks[x-1][y].has_value())
						return false;
				}
				return true;
			case Move::Right:
				for(auto const [x,y] : get_block_array()) {
					if(x == FIELD_X_COUNT-1)
						return false;
					if(field.static_blocks[x+1][y].has_value())
						return false;
				}
				return true;
			case Move::Rotate:
				return true;
		};
		throw std::runtime_error{"can_move wtf"};
	};

	base_update(field, tick, check_fallen, can_move);
	if(m_rotation > 1) {
		m_rotation -= 2;
	}
	m_sprite.setRotation(90.f * m_rotation);
	m_sprite.setPosition(m_position);
}

//std::array<std::tuple<size_t, size_t>, 4>
//BlockShape<BlockType::O>::get_block_array() const
//{
//	std::array<std::tuple<size_t,size_t>, 4> to_return;
//	sf::Vector2f const root{
//		(m_position.x-OFFSET_X)/FIELD_SIZE,
//		(m_position.y-OFFSET_Y)/FIELD_SIZE
//	};
//
//	to_return = {
//		std::make_tuple(root.x-1, root.y-1),
//		std::make_tuple(root.x-1, root.y),
//		std::make_tuple(root.x,   root.y-1),
//		std::make_tuple(root.x,   root.y)
//	};
//
//	for(auto &[x,y] : to_return) {
//		if(x>=FIELD_X_COUNT)
//			x = 0;
//		if(y>=FIELD_Y_COUNT)
//			y = 0;
//	}
//
//	return to_return;
//}

BlockShape<BlockType::T>::BlockShape()
{
	texture_index = 2;
	m_rotation = 0;
	m_texture.loadFromFile(BlockTexture<BlockType::T>::path);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	m_sprite.setOrigin(sf::Vector2f{
		m_sprite.getLocalBounds().width/2,
		m_sprite.getLocalBounds().height/2 +
			m_sprite.getLocalBounds().height/4
	});
	m_position += sf::Vector2f{FIELD_SIZE+FIELD_SIZE/2, FIELD_SIZE/2};
	m_sprite.setPosition(m_position);
}

void BlockShape<BlockType::T>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void BlockShape<BlockType::T>::update(TetrisField const & field, bool const tick)
{
	auto const check_fallen = [&]() -> bool {
		// Block check
		auto const block_array = get_block_array();
		for(auto const [x,y] : block_array) {
			if(y == FIELD_Y_COUNT-1)
				continue;
			
			if(field.static_blocks[x][y+1].has_value())
				return true;
		}

		// Ground check
		if(m_position.y >= (FIELD_SIZE*(FIELD_Y_COUNT-1))+OFFSET_Y) {
			return true;
		}

		return false;
	};

	auto const can_move = [&](Move const move_type) -> bool {
		switch(move_type) {
			case Move::Left:
				for(auto const [x,y] : get_block_array()) {
					if(x == 0)
						return false;
					if(field.static_blocks[x-1][y].has_value())
						return false;
				}
				return true;
			case Move::Right:
				for(auto const [x,y] : get_block_array()) {
					if(x == FIELD_X_COUNT-1)
						return false;
					if(field.static_blocks[x+1][y].has_value())
						return false;
				}
				return true;
			case Move::Rotate:
				return true;
		};
		throw std::runtime_error{"can_move wtf"};
	};

	base_update(field, tick, check_fallen, can_move);
	m_sprite.setRotation(90.f * m_rotation);
	m_sprite.setPosition(m_position);
}

//std::array<std::tuple<size_t, size_t>, 4>
//BlockShape<BlockType::T>::get_block_array() const
//{
//	std::array<std::tuple<size_t,size_t>, 4> to_return;
//	sf::Vector2f const root{
//		(m_position.x-OFFSET_X)/FIELD_SIZE - 0.5f,
//		(m_position.y-OFFSET_Y)/FIELD_SIZE - 0.5f
//	};
//
//	switch(m_rotation) {
//		case 0:
//			to_return = {
//				std::make_tuple(root.x,   root.y-1),
//				std::make_tuple(root.x-1, root.y),
//				std::make_tuple(root.x,   root.y),
//				std::make_tuple(root.x+1, root.y)
//			};
//			break;
//		case 1:
//			to_return = {
//				std::make_tuple(root.x,   root.y-1),
//				std::make_tuple(root.x,   root.y+1),
//				std::make_tuple(root.x,   root.y),
//				std::make_tuple(root.x+1, root.y)
//			};
//			break;
//		case 2:
//			to_return = {
//				std::make_tuple(root.x,   root.y+1),
//				std::make_tuple(root.x-1, root.y),
//				std::make_tuple(root.x,   root.y),
//				std::make_tuple(root.x+1, root.y)
//			};
//			break;
//		case 3:
//			to_return = {
//				std::make_tuple(root.x,   root.y-1),
//				std::make_tuple(root.x,   root.y+1),
//				std::make_tuple(root.x,   root.y),
//				std::make_tuple(root.x-1, root.y)
//			};
//			break;
//	}
//
//	for(auto &[x,y] : to_return) {
//		if(x>=FIELD_X_COUNT)
//			x = 0;
//		if(y>=FIELD_Y_COUNT)
//			y = 0;
//	}
//
//	return to_return;
//}
