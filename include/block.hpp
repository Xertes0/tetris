#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <array>

#include "field.hpp"
#include "block_types.hpp"

constexpr size_t const BLOCK_COUNT = 7;

enum class Move
{
	Left,
	Right,
	Rotate,
};

class Block : public sf::Drawable
{
public:
	Block();

	bool has_fallen = false;

	void rotate();
	virtual void update(TetrisField const &field, bool tick) = 0;
	virtual std::array<std::tuple<int,int>, 4>
	get_block_array() const = 0;
	size_t texture_index;

protected:
	int m_rotation;
	sf::Vector2f m_position;

	sf::Texture m_texture;
	sf::Sprite  m_sprite;
	
	template<typename CheckFallen, typename CheckMovement>
	void base_update(
		bool tick,
		CheckFallen &check_fallen,
		CheckMovement &can_move
	) {
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
	};

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif // BLOCKS_HPP
