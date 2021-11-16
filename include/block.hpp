#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <array>

#include "field.hpp"
#include "block_types.hpp"

constexpr size_t const BLOCK_COUNT = 2;

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
		TetrisField const &field,
		bool tick,
		CheckFallen &check_fallen,
		CheckMovement &can_move
	);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif // BLOCKS_HPP
