#include "field.hpp"

TetrisField::TetrisField()
{
	static sf::Vector2f const offset{50.f,50.f};
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

void TetrisField::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_lines);
}
