#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>

constexpr float const FIELD_SIZE = 35.f;

constexpr unsigned int const FIELD_X_COUNT = 10;
constexpr unsigned int const FIELD_Y_COUNT = 20;

constexpr float const FIELD_WIDTH  = FIELD_SIZE * FIELD_X_COUNT;
constexpr float const FIELD_HEIGHT = FIELD_SIZE * FIELD_Y_COUNT;

class TetrisField : public sf::Drawable
{
	sf::VertexArray m_lines;

	public:
	TetrisField();
	
	private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // FIELD_HPP
