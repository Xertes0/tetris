#include "block_shapes.hpp"

template<BlockType block_type>
BlockShape<block_type>::BlockShape()
//	: m_rotation{0}
{
	m_rotation = 0;
}

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

BlockShape<BlockType::I>::BlockShape()
	: m_rectangle{sf::RectangleShape{}}
{
	m_rectangle.setSize(sf::Vector2f{FIELD_SIZE, FIELD_SIZE*4});
	m_rectangle.setPosition(m_position);
	m_rectangle.setFillColor(sf::Color::Blue);
	m_rectangle.setOrigin(sf::Vector2f{0, FIELD_SIZE*2});
}

void BlockShape<BlockType::I>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_rectangle);
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
		if(	m_rectangle.getRotation() == 90.f ||
			m_rectangle.getRotation() == 270.f)
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
	m_rectangle.setRotation(90.f * m_rotation);
	m_rectangle.setPosition(m_position);
}

std::array<std::tuple<size_t, size_t>, 4>
BlockShape<BlockType::I>::get_block_array() const
{
	std::array<std::tuple<size_t,size_t>, 4> to_return;
	if(	m_rectangle.getRotation() == 90.f ||
		m_rectangle.getRotation() == 270.f)
	{
		sf::Vector2f const root{
			(m_position.x-OFFSET_X)/FIELD_SIZE,
			(m_position.y-OFFSET_Y)/FIELD_SIZE
		};
		to_return = {
			std::make_tuple(root.x-2,root.y),
			std::make_tuple(root.x-1,root.y),
			std::make_tuple(root.x,root.y),
			std::make_tuple(root.x+1,root.y)
		};
	} else {
		sf::Vector2f const root{
			(m_position.x-OFFSET_X)/FIELD_SIZE,
			(m_position.y-OFFSET_Y)/FIELD_SIZE
		};
		to_return = {
			std::make_tuple(root.x,root.y-2),
			std::make_tuple(root.x,root.y-1),
			std::make_tuple(root.x,root.y),
			std::make_tuple(root.x,root.y+1)
		};
	}

	for(auto &[x,y] : to_return) {
		if(x>=FIELD_X_COUNT)
			x = 0;
		if(y>=FIELD_Y_COUNT)
			y = 0;
	}

	return to_return;
}

//void BlockShape<BlockType::O>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw O\n");
//}
//
//void BlockShape<BlockType::O>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
//
//void BlockShape<BlockType::T>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw T\n");
//}
//
//void BlockShape<BlockType::T>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
//
//void BlockShape<BlockType::S>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw S\n");
//}
//
//void BlockShape<BlockType::S>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
//
//void BlockShape<BlockType::Z>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw Z\n");
//}
//
//void BlockShape<BlockType::Z>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
//
//void BlockShape<BlockType::J>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw J\n");
//}
//
//void BlockShape<BlockType::J>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
//
//void BlockShape<BlockType::L>::draw(sf::RenderTarget &target, sf::RenderStates states) const
//{
//	fmt::print("Draw L\n");
//}
//
//void BlockShape<BlockType::L>::update()
//{
//	m_position += {0.f, FIELD_SIZE};
//}
