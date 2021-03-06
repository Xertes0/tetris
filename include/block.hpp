#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <array>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "input_handler.hpp"
#include "field.hpp"
#include "block_types.hpp"

constexpr float START_POSITION_X {FIELD_OFFSET_X + (FIELD_SIZE * 4)};
constexpr float START_POSITION_Y {FIELD_OFFSET_Y};

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
	BlockType type;

	bool   has_fallen {false};
	size_t texture_index;

	void
	rotate();

	void
	c_rotate();

	virtual void
	update(
		InputHandler const & input_handler,
		Field const &field,
		bool tick) = 0;

	virtual void
	reset() = 0;

	virtual auto
	get_block_array() const -> std::array<std::tuple<int,int>, 4> = 0;

	[[nodiscard]] auto
	is_illegal(Field const & field) -> bool;

protected:
	int m_rotation;

	sf::Vector2f m_position;
	sf::Texture  m_texture;
	sf::Sprite   m_sprite;
	
	template<typename CheckFallen, typename CheckMovement>
	void
	base_update(
		InputHandler const & input_handler,
		bool const tick,
		CheckFallen   const & check_fallen,
		CheckMovement const & can_move
	) {
		bool down_pressed = false;
		if( input_handler.pressed_once<Action::Rotate>() &&
			can_move(Move::Rotate))
		{
			rotate();
		}
		if(input_handler.pressed<Action::Down>()) {
			m_position += {0.f, FIELD_SIZE};
			down_pressed = true;
		}
		if( input_handler.pressed_once<Action::Right>() &&
			can_move(Move::Right))
		{
			m_position += {FIELD_SIZE, 0.f};
		}
		if( input_handler.pressed_once<Action::Left>() && 
			can_move(Move::Left))
		{
			m_position += {-FIELD_SIZE, 0.f};
		}

		if(tick && !down_pressed)
			m_position += {0.f, FIELD_SIZE};

		has_fallen = check_fallen();
	};

private:
	virtual void
	draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif // BLOCKS_HPP
