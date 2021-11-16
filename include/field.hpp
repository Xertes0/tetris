#ifndef FIELD_HPP
#define FIELD_HPP

#include <array>
#include <optional>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

constexpr float FIELD_SIZE = 35.f;

constexpr unsigned int FIELD_X_COUNT = 10;
constexpr unsigned int FIELD_Y_COUNT = 20;

constexpr float FIELD_WIDTH  = FIELD_SIZE * FIELD_X_COUNT;
constexpr float FIELD_HEIGHT = FIELD_SIZE * FIELD_Y_COUNT;

constexpr float FIELD_OFFSET_X = 50.f;
constexpr float FIELD_OFFSET_Y = 50.f;

struct StaticBlock
{
	std::shared_ptr<sf::Texture> texture;
};

class Field : public sf::Drawable
{
	sf::VertexArray m_lines;

public:
	Field();
	std::array<std::array<std::optional<StaticBlock>, FIELD_Y_COUNT>, FIELD_X_COUNT> static_blocks;

	auto
	check_score() -> int;
	
private:
	void
	remove_row(size_t row);

	virtual void
	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // FIELD_HPP
