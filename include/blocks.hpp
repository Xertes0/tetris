#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <array>

#include "field.hpp"

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
	virtual std::array<std::tuple<size_t,size_t>, 4>
	get_block_array() const = 0;
	
	template<typename CheckFallen, typename CheckMovement>
	void base_update(
		TetrisField const &field,
		bool tick,
		CheckFallen &check_fallen,
		CheckMovement &can_move
	);

protected:
	int m_rotation;
	sf::Vector2f m_position;
 	//std::array<sf::RectangleShape, 4> m_blocks; // TODO - optimalize

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif // BLOCKS_HPP
